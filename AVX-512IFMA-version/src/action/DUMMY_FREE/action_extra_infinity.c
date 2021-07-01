/**
 *******************************************************************************
 * @version 0.0.1
 * @date 2021-07-01
 * @copyright Copyright © 2021 by University of Luxembourg.
 * @author Developed at SnT APSIA by: Hao Cheng.
 *******************************************************************************
 */

#include "action.h"
#include <string.h>
#include <stdio.h>

// cmove for small 7-bit integer 
static void u8_cmove(uint8_t *r, const uint8_t a, const uint8_t b)
{
  uint8_t x;

  x = *r ^ a;
  x = x & (-b);
  *r = *r ^ x;
}

// look up the secret exponent in constant time 
static __m512i querye_8x1w(size_t pos, const __m512i e[])
{
  __m512i r = e[0], x;
  uint8_t b;
  size_t i;

  for (i = 0; i < N; i++) {
    b = u32_iseql(i, pos);
    x = VXOR(r, e[i]);
    x = VAND(x, VSET1(-b));
    r = VXOR(r, x);
  }
  return r;
}

// look up the secret exponent in constant time
static uint8_t querye_2x4w(size_t pos, uint8_t const e[])
{
  uint8_t r = e[0], b;
  size_t i;

  for(i = 1; i < N; i++)
  {
    b = u32_iseql(i, pos);
    u8_cmove(&r, e[i], b);
  }
  return r;
}

// check whether the small integer is zero
static __m512i u8_iszero_8x1w(const __m512i a)
{
  __m512i r;

  r = VSUB(VZERO, a);
  r = VSHR(r, 63);
  return VXOR(VAND(r, VSET1(1)), VSET1(1));
}

// check whether the small 7-bit integer is zero 
static uint8_t u8_iszero(const uint8_t a)
{
  uint8_t r;

  r = 0-a;
  r = r >> 7;
  return (r&1)^1;
}

// The unbatched component which is a low-latency CSIDH class group action 
// will be executed sequentially 8 times.
static void action_2x4w(llpoint_t C, const uint8_t *sk, const llpoint_t A)
{
  uint8_t ba[N], sizeba = 0, compba[N], sicoba = 0, lastiso;
  uint8_t e[N], bc, ec = 0, fnsh[N] = { 0 }, isocnt[N] = { 0 };
  llpoint_t A0, T0, T1, G0, G1, K[HLMAX];
  int total = 0, i, j;

  // extra-infinity
  for (i = 0; i < N; i++) fnsh[i] = 1;
  for (i = 0; i < LL_NUMIDX; i++) {
    isocnt[ll_idx[i]] = B[ll_idx[i]];
    fnsh[ll_idx[i]] = 0;
  }
  total = HT_NUMISO; // HT_NUMISO isogenies have been computed in the batched component

  // Initialize variables for computing CSIDH class group action.  
  point_copy_2x4w(A0, A);                     // initialize curve
  for (i = 0; i < N; i++) e[i] = sk[i];       // initialize the secret exponents
  
  // Since there are only few isogeny computations in the unbatched component, 
  // we will not use SIMBA here         
  // initialize BA and COMPBA                         
  for (i = 0; i < N; i++) {                   
    if (isocnt[i] == 0) {
      compba[sicoba] = i;
      sicoba += 1;
      fnsh[i] = 1;
    }
    else {
      lastiso = i;
      ba[sizeba] = i;
      sizeba += 1;
    }
  }

  // the main loop
  while (total < NUMISO) {
    elligator_2x4w(T1, T0, A0);              
    yDBL_2x4w(T0, T0, A0);
    yDBL_2x4w(T0, T0, A0);                    
    yDBL_2x4w(T1, T1, A0);
    yDBL_2x4w(T1, T1, A0);                    

    for (i = 0; i < sicoba; i++) {
      yMUL_2x4w(T0, T0, A0, compba[i]);    
      yMUL_2x4w(T1, T1, A0, compba[i]);
    }

    for (i = 0; i < sizeba; i++) {
      if (fnsh[ba[i]]) continue;
      else { 
        ec = querye_2x4w(ba[i], e);
        point_cswap_2x4w(T0, T1, ec&1);
        point_copy_2x4w(G0, T0);
        point_copy_2x4w(G1, T1);

        for (j = i+1; j < sizeba; j++)
          if (!fnsh[ba[j]]) yMUL_2x4w(G0, G0, A0, ba[j]);

        if ((!point_isinf_2x4w(G0)) && (!point_isinf_2x4w(G1))) {
          bc = u8_iszero(ec>>1);
          yISOG_2x4w(K, A0, G0, A0, ba[i]);

          if (ba[i] != lastiso) {
            yEVAL_2x4w(T0, T0, K, ba[i]);
            yEVAL_2x4w(T1, T1, K, ba[i]);

            yMUL_2x4w(T1, T1, A0, ba[i]);         
          }

          e[ba[i]] = ((((ec>>1) - (bc^1))^bc) << 1) ^ ((ec&1)^bc);
          isocnt[ba[i]] -= 1;
          total += 1;
        }
        else {
          yMUL_2x4w(T1, T1, A0, ba[i]);
        }

        point_cswap_2x4w(T0, T1, ec&1);

        if (isocnt[ba[i]] == 0) {
          fnsh[ba[i]] = 1;
          compba[sicoba] = ba[i];
          sicoba += 1;
        }
      } 
    }
  }
  point_copy_2x4w(C, A0);
}

// The batched component. 
static void action_8x1w(htpoint_t C, __m512i* e, const __m512i *sk, const htpoint_t A)
{
  uint8_t ba[NUMBA][MAXSIZEBA], sizeba[NUMBA], compba[NUMBA][N], sicoba[NUMBA], lastiso[NUMBA];
  uint8_t fnsh[N] = { 0 }, isocnt[N] = { 0 };
  __m512i ec = VZERO, inf, bc, vone = VSET1(1), t, x;  
  htpoint A0, T0, T1, G0, G1, K[HLMAX];
  int count = 0, total = 0, i, j, m = 0, numba = NUMBA;
  uint64_t f_inf;

  // Initialize SIMBA variables. 
  memcpy(ba, BATCHES, N);
  memcpy(sizeba, SIZEBA, NUMBA);
  memcpy(compba, COMPBA, NUMBA*N);
  memcpy(sicoba, SICOBA, NUMBA);
  memcpy(lastiso, LASTISO, NUMBA);

  // Initialize variables for computing CSIDH class group action.
  point_copy_8x1w(&A0, A);
  memcpy(isocnt, B, N);

  // extra-infinity 
  for (i = 0; i < LL_NUMIDX; i++) {
    isocnt[ll_idx[i]] = 0;
    fnsh[ll_idx[i]] = 1;                // these isogenies will be computed in the unbatched component 
  }
  // put these primes directly in the complement of the batch 
  compba[3][sicoba[3]] = ba[3][13];
  sicoba[3] += 1;
  compba[2][sicoba[2]] = ba[2][13];
  sicoba[2] += 1;
  compba[1][sicoba[1]] = ba[1][13];
  sicoba[1] += 1;
  compba[0][sicoba[0]] = ba[0][13];
  sicoba[0] += 1;
  compba[4][sicoba[4]] = ba[4][12];
  sicoba[4] += 1;
  compba[3][sicoba[3]] = ba[3][12];
  sicoba[3] += 1;
  compba[2][sicoba[2]] = ba[2][12];
  sicoba[2] += 1;
  compba[1][sicoba[1]] = ba[1][12];
  sicoba[1] += 1;
  compba[0][sicoba[0]] = ba[0][12];
  sicoba[0] += 1;

  while (total < HT_NUMISO) {
    m = (m+1) % numba;                  // public parameter SIMBA index

    if (count == ROUND*NUMBA) {         // merge the BAs when required rounds finished
      m = 0;                    
      sicoba[0] = 0;          
      sizeba[0] = 0;
      numba = 1;

      for (i = 0; i < N; i++) {
        if (!isocnt[i]) {
          compba[0][sicoba[0]] = i;
          sicoba[0] += 1;
        }
        else {
          lastiso[0] = i;
          ba[0][sizeba[0]] = i;
          sizeba[0] += 1;
        }
      }
    }

    elligator_8x1w(&T1, &T0, &A0);
    yDBL_8x1w(&T0, &T0, &A0); 
    yDBL_8x1w(&T0, &T0, &A0);
    yDBL_8x1w(&T1, &T1, &A0);
    yDBL_8x1w(&T1, &T1, &A0); 

    for (i = 0; i < sicoba[m]; i++) {
      yMUL_8x1w(&T0, &T0, &A0, compba[m][i]); 
      yMUL_8x1w(&T1, &T1, &A0, compba[m][i]);
    }

    for (i = 0; i < sizeba[m]; i++) {
      if (fnsh[ba[m][i]]) continue;
      else {
        ec = querye_8x1w(ba[m][i], e);
        point_cswap_8x1w(&T0, &T1, VAND(ec, VSET1(1)));
        point_copy_8x1w(&G0, &T0);
        point_copy_8x1w(&G1, &T1);

        for (j = i+1; j < sizeba[m]; j++) 
          if (!fnsh[ba[m][j]]) yMUL_8x1w(&G0, &G0, &A0, ba[m][j]);

        // extra-infinity
        inf = point_isinf_8x1w(&G0);
        inf = VOR(inf, point_isinf_8x1w(&G1));
        f_inf = VORRDC(inf);
      
        //////////////////////////////////////////////////////////
        // extra-infinity

        if (!f_inf) {

          bc = u8_iszero_8x1w(VSHR(ec, 1));

          yISOG_8x1w(K, &A0, &G0, &A0, ba[m][i]);

          if (ba[m][i] != lastiso[m]) {
            yEVAL_8x1w(&T0, &T0, K, ba[m][i]);
            yEVAL_8x1w(&T1, &T1, K, ba[m][i]);

            yMUL_8x1w(&T1, &T1, &A0, ba[m][i]);
          }
          t = VSHR(ec, 1);
          t = VSUB(t, VXOR(bc, vone));
          t = VXOR(t, bc);
          t = VSHL(t, 1);
          e[ba[m][i]] = VXOR(t, VXOR(VAND(ec, vone), bc));

          isocnt[ba[m][i]] -= 1;
          total += 1; 
        }
        else {
          yMUL_8x1w(&T0, &T0, &A0, ba[m][i]);
          yMUL_8x1w(&T1, &T1, &A0, ba[m][i]);
        }

        point_cswap_8x1w(&T0, &T1, VAND(ec, vone));
        
        if (!isocnt[ba[m][i]]) {
          fnsh[ba[m][i]] = 1;
          compba[m][sicoba[m]] = ba[m][i];
          sicoba[m] += 1;
        }
        /////////////////////////////////
      }
    }
    count += 1;
  }
  point_copy_8x1w(C, &A0);
}

// The complete CSIDH group action using extra-infinity method.  
void action(htpoint_t C, const __m512i *sk, const htpoint_t A)
{
  __m512i e[N];
  htpoint A0;
  int i;

  // Initialize the exponent vector.
  for (i = 0; i < N; i++) e[i] = sk[i];

  // Execute the batched component. 
  action_8x1w(&A0, e, sk, A);

  // ---------------------------------------------------------------------------
  // The batched component has completed at this moment.
  // We now extract the variables of each instance for the unbatched low-latency component.

  llpoint_t llC[8], llA[8];
  uint64_t a43[8][LL_NWORDS] = {0}, a52[8][HT_NWORDS] = {0};
  uint64_t ad43[8][LL_NWORDS] = {0}, ad52[8][HT_NWORDS] = {0};
  uint8_t lle[8][N];

  // Convert coefficients from Montgomery domain to number domain,
  // because the Montgomery domain (R = 2^516) of low-latency component is different 
  // from the Montgomery domain (R' = 2^520) of high-throughput component 
  gfp_mont2num_8x1w(A0.y, A0.y);
  gfp_mont2num_8x1w(A0.z, A0.z);

  // extract the curve coefficient for each instance
  for(i = 0; i < HT_NWORDS; i++) {
    a52[0][i] = VEXTR64(VEXTR256(A0.y[i], 0), 0);
    a52[1][i] = VEXTR64(VEXTR256(A0.y[i], 0), 1);
    a52[2][i] = VEXTR64(VEXTR256(A0.y[i], 0), 2);
    a52[3][i] = VEXTR64(VEXTR256(A0.y[i], 0), 3);
    a52[4][i] = VEXTR64(VEXTR256(A0.y[i], 1), 0);
    a52[5][i] = VEXTR64(VEXTR256(A0.y[i], 1), 1);
    a52[6][i] = VEXTR64(VEXTR256(A0.y[i], 1), 2);
    a52[7][i] = VEXTR64(VEXTR256(A0.y[i], 1), 3);

    ad52[0][i] = VEXTR64(VEXTR256(A0.z[i], 0), 0);
    ad52[1][i] = VEXTR64(VEXTR256(A0.z[i], 0), 1);
    ad52[2][i] = VEXTR64(VEXTR256(A0.z[i], 0), 2);
    ad52[3][i] = VEXTR64(VEXTR256(A0.z[i], 0), 3);
    ad52[4][i] = VEXTR64(VEXTR256(A0.z[i], 1), 0);
    ad52[5][i] = VEXTR64(VEXTR256(A0.z[i], 1), 1);
    ad52[6][i] = VEXTR64(VEXTR256(A0.z[i], 1), 2);
    ad52[7][i] = VEXTR64(VEXTR256(A0.z[i], 1), 3);
  }

  // convert from radix-52 to radix-43
  for (i = 0; i < 8; i++) {
    mpi_conv_52to43(a43[i], a52[i], LL_NWORDS, HT_NWORDS);
    mpi_conv_52to43(ad43[i], ad52[i], LL_NWORDS, HT_NWORDS);
  }

  // form the (2x4)-way limb vector set
  for (i = 0; i < 8; i++) {
    llA[i][0] = VSET(a43[i][9] , a43[i][6], a43[i][3], a43[i][0], ad43[i][9] , ad43[i][6], ad43[i][3], ad43[i][0]);
    llA[i][1] = VSET(a43[i][10], a43[i][7], a43[i][4], a43[i][1], ad43[i][10], ad43[i][7], ad43[i][4], ad43[i][1]);
    llA[i][2] = VSET(a43[i][11], a43[i][8], a43[i][5], a43[i][2], ad43[i][11], ad43[i][8], ad43[i][5], ad43[i][2]);
    gfp_num2mont_2x4w(llA[i], llA[i]);  // convert to Montgomery domain
  }

  // extract the secret exponent for each instance
  for (i = 0; i < N; i++) {
    lle[0][i] = VEXTR64(VEXTR256(e[i], 0), 0); 
    lle[1][i] = VEXTR64(VEXTR256(e[i], 0), 1); 
    lle[2][i] = VEXTR64(VEXTR256(e[i], 0), 2); 
    lle[3][i] = VEXTR64(VEXTR256(e[i], 0), 3); 
    lle[4][i] = VEXTR64(VEXTR256(e[i], 1), 0); 
    lle[5][i] = VEXTR64(VEXTR256(e[i], 1), 1); 
    lle[6][i] = VEXTR64(VEXTR256(e[i], 1), 2); 
    lle[7][i] = VEXTR64(VEXTR256(e[i], 1), 3); 
  }

  // ---------------------------------------------------------------------------
  // Perform sequentially the unbatched component for each instance.

  for (i = 0; i < 8; i++) action_2x4w(llC[i], lle[i], llA[i]);

  // ---------------------------------------------------------------------------
  // The entire CSIDH class group action has completed at this moment.

  for (i = 0; i < 8; i++) gfp_mont2num_2x4w(llC[i], llC[i]);

  for (i = 0; i < 8; i++) {
    a43[i][0]  = VEXTR64(VEXTR256(llC[i][0], 1), 0);
    a43[i][1]  = VEXTR64(VEXTR256(llC[i][1], 1), 0);
    a43[i][2]  = VEXTR64(VEXTR256(llC[i][2], 1), 0);
    a43[i][3]  = VEXTR64(VEXTR256(llC[i][0], 1), 1);
    a43[i][4]  = VEXTR64(VEXTR256(llC[i][1], 1), 1);
    a43[i][5]  = VEXTR64(VEXTR256(llC[i][2], 1), 1);
    a43[i][6]  = VEXTR64(VEXTR256(llC[i][0], 1), 2);
    a43[i][7]  = VEXTR64(VEXTR256(llC[i][1], 1), 2);
    a43[i][8]  = VEXTR64(VEXTR256(llC[i][2], 1), 2);
    a43[i][9]  = VEXTR64(VEXTR256(llC[i][0], 1), 3);
    a43[i][10] = VEXTR64(VEXTR256(llC[i][1], 1), 3);
    a43[i][11] = VEXTR64(VEXTR256(llC[i][2], 1), 3);

    ad43[i][0]  = VEXTR64(VEXTR256(llC[i][0], 0), 0);
    ad43[i][1]  = VEXTR64(VEXTR256(llC[i][1], 0), 0);
    ad43[i][2]  = VEXTR64(VEXTR256(llC[i][2], 0), 0);
    ad43[i][3]  = VEXTR64(VEXTR256(llC[i][0], 0), 1);
    ad43[i][4]  = VEXTR64(VEXTR256(llC[i][1], 0), 1);
    ad43[i][5]  = VEXTR64(VEXTR256(llC[i][2], 0), 1);
    ad43[i][6]  = VEXTR64(VEXTR256(llC[i][0], 0), 2);
    ad43[i][7]  = VEXTR64(VEXTR256(llC[i][1], 0), 2);
    ad43[i][8]  = VEXTR64(VEXTR256(llC[i][2], 0), 2);
    ad43[i][9]  = VEXTR64(VEXTR256(llC[i][0], 0), 3);
    ad43[i][10] = VEXTR64(VEXTR256(llC[i][1], 0), 3);
    ad43[i][11] = VEXTR64(VEXTR256(llC[i][2], 0), 3);

    mpi43_carryp(a43[i]);
    mpi43_carryp(ad43[i]);

    mpi_conv_43to52(a52[i], a43[i], HT_NWORDS, LL_NWORDS);
    mpi_conv_43to52(ad52[i], ad43[i], HT_NWORDS, LL_NWORDS);
  } 

  // form the final (8x1)-way result
  for (i = 0; i < HT_NWORDS; i++) {
    C->y[i] = VSET(a52[7][i],  a52[6][i],  a52[5][i],  a52[4][i],  a52[3][i],  a52[2][i],  a52[1][i],  a52[0][i]);
    C->z[i] = VSET(ad52[7][i], ad52[6][i], ad52[5][i], ad52[4][i], ad52[3][i], ad52[2][i], ad52[1][i], ad52[0][i]);
  }

  // convert from number domain to Montgomery domain 
  gfp_num2mont_8x1w(C->y, C->y);
  gfp_num2mont_8x1w(C->z, C->z);
} 

// The functions below are from [CVCCD+19] code for generating the secret key.

static void cmov(int8_t *r, const int8_t a, uint32_t b)
{
  uint32_t t;
  b = -b; /* Now b is either 0 or 0xffffffff */
  t = (*r ^ a) & b;
  *r ^= t;
}

// constant-time comparison: -1 if x < y, 0 otherwise.
static int32_t issmaller(int32_t x, int32_t y)
{
  int32_t xy = x ^ y;
  int32_t c = x - y;
  c ^= xy & (c ^ x);
  return (c >> 31);
}

void random_sk(uint8_t *sk)
{
  uint8_t i, tmp, r;
  int8_t exp, sgn;
  for(i = 0; i < N; i++)
  {

    r = B[i] & 0x1;						// B_i mod 2

    // exp is randomly selected from |[ 0, B ]|
    randombytes(&tmp, 1);
    while ( issmaller((int32_t)B[i], (int32_t)tmp) == -1 )	// constant-time comparison
      randombytes(&tmp, 1);

    exp = (int8_t)tmp;

    // Mapping integers from |[ 0, B |] into
    //                                      |[ -B/2, B/2]| if B is even, or
    //                                      |[ -(B+1)/2, (B-1)/2 ]| if B is odd.
    exp = ( (exp << 1) - (B[i] + r) ) >> 1;

    // Mapping into the set |[-B, B]|.
    exp = (exp << 1) + r;
    sgn = exp >> 7;	// sign of exp

    // Next, to write  key[i] = e || ((1 + sgn)/2)
    cmov(&exp, -exp, sgn == -1);
    sk[i] = (exp << 1) ^ (1 & (1 + sgn));
  }
}
