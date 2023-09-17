/**
 *******************************************************************************
 * @version 0.0.2
 * @date 2021-08-22
 * @copyright Copyright © 2021 by University of Luxembourg.
 * @author Developed at SnT APSIA by: Hao Cheng.
 *******************************************************************************
 */

//Modified by PENGCHANG REN

#include "gfparith.h"
const uint64_t r_i_mont[LL_NWORDS-2][LL_NWORDS * 2] = {
{0x539bd275be,0x19305e79e7e,0x341c4de0891,0x6c26b614a93,0x539bd275be,0x19305e79e7e,0x341c4de0891,0x6c26b614a93,0x39211bc2877,0x6daacf50868,0x477b12e1e85,0x553d73305fc,0x39211bc2877,0x6daacf50868,0x477b12e1e85,0x553d73305fc,0x3ca42702733,0x25f3b10780a,0x759f7b05657,0xc78446d5,0x3ca42702733,0x25f3b10780a,0x759f7b05657,0xc78446d5},
{0x3b6087ae2cf,0x4314a59bdf5,0x2a81cb10c32,0x5d0e19c1d02,0x3b6087ae2cf,0x4314a59bdf5,0x2a81cb10c32,0x5d0e19c1d02,0x6f2b6943c78,0x7b9422c31b2,0x3e7dae99622,0x28b3ff32f91,0x6f2b6943c78,0x7b9422c31b2,0x3e7dae99622,0x28b3ff32f91,0xa783c67ed0,0x3717fc39fa,0x799ad9eb81a,0xfa5f83be0,0xa783c67ed0,0x3717fc39fa,0x799ad9eb81a,0xfa5f83be0},
{0x12f23349bf2,0x6624255d81b,0x1098ec38a91,0x4895cd2b49b,0x12f23349bf2,0x6624255d81b,0x1098ec38a91,0x4895cd2b49b,0x4dd620b668,0x4531eaf2492,0x5544ea17083,0x9223bea422,0x4dd620b668,0x4531eaf2492,0x5544ea17083,0x9223bea422,0x1385fa8b46f,0x33489d5b5fc,0x2669c924aa0,0x32a7a9463c,0x1385fa8b46f,0x33489d5b5fc,0x2669c924aa0,0x32a7a9463c},
{0x607b7a0ae6a,0x2bfac54f197,0xb1442dfc2a,0x626874d3770,0x607b7a0ae6a,0x2bfac54f197,0xb1442dfc2a,0x626874d3770,0x47730306916,0x89b4a50759,0x51ed6f96132,0xac55cffa7a,0x47730306916,0x89b4a50759,0x51ed6f96132,0xac55cffa7a,0x6532908fc25,0x3c79eebbc90,0x2d96f7865fe,0x25629c21c2,0x6532908fc25,0x3c79eebbc90,0x2d96f7865fe,0x25629c21c2},
{0x62d1ccf45ef,0x18dafb537f0,0x2f2d546dfa9,0x10face6542d,0x62d1ccf45ef,0x18dafb537f0,0x2f2d546dfa9,0x10face6542d,0x7fdd98b4397,0x7a7eec74055,0x23c1adeaa73,0x315164c8b6e,0x7fdd98b4397,0x7a7eec74055,0x23c1adeaa73,0x315164c8b6e,0x3367809495b,0x549985ef42c,0x3119c3fc9a,0x256d4345ff,0x3367809495b,0x549985ef42c,0x3119c3fc9a,0x256d4345ff},
{0x699a0abee5,0x15616ff2f12,0x4ccc95356d5,0x7cf2968c23,0x699a0abee5,0x15616ff2f12,0x4ccc95356d5,0x7cf2968c23,0x1de19c65410,0x56de484ea98,0x6262f2de89d,0x5d8238d960f,0x1de19c65410,0x56de484ea98,0x6262f2de89d,0x5d8238d960f,0xce6af46165,0x3f19381910b,0x3f50a0d8fc8,0xf576f9220,0xce6af46165,0x3f19381910b,0x3f50a0d8fc8,0xf576f9220},
{0x14131d165c1,0x7e8edbf81f8,0x7c1db88532a,0x778b924170d,0x14131d165c1,0x7e8edbf81f8,0x7c1db88532a,0x778b924170d,0x4e62a356efd,0x53e8325ccf0,0x25272fd98f8,0x2c0735da258,0x4e62a356efd,0x53e8325ccf0,0x25272fd98f8,0x2c0735da258,0x71de6dff0db,0x21842754db9,0x529a39969be,0x1f42636dc4,0x71de6dff0db,0x21842754db9,0x529a39969be,0x1f42636dc4},
{0x2fe6b4d4e85,0x2c6755bc027,0x2c5d2f4577c,0x79972eb2b74,0x2fe6b4d4e85,0x2c6755bc027,0x2c5d2f4577c,0x79972eb2b74,0x2aeef447860,0x26c66ed012c,0x3f75fe99c6a,0x18f271aac49,0x2aeef447860,0x26c66ed012c,0x3f75fe99c6a,0x18f271aac49,0x653c15d4902,0x58dc95586ea,0x44e38e0c538,0xc4d500300,0x653c15d4902,0x58dc95586ea,0x44e38e0c538,0xc4d500300},
{0x4e666325c08,0xd393f642f4,0x348009ad19f,0xaeb2b1ee05,0x4e666325c08,0xd393f642f4,0x348009ad19f,0xaeb2b1ee05,0x234aec69df0,0x6eb82d907b3,0x470d22b0ae2,0x55f259ad81d,0x234aec69df0,0x6eb82d907b3,0x470d22b0ae2,0x55f259ad81d,0x476f22001e2,0x14e3b9d52b3,0x6fa2d641ec8,0x203c1a1f40,0x476f22001e2,0x14e3b9d52b3,0x6fa2d641ec8,0x203c1a1f40},
{0x59728c167f7,0x6bd8c38d281,0x3058ff98f4c,0x104211fc8c,0x59728c167f7,0x6bd8c38d281,0x3058ff98f4c,0x104211fc8c,0x2a1acfe63cb,0xd2acc90691,0xd69cd1a0,0x6d79661ad1,0x2a1acfe63cb,0xd2acc90691,0xd69cd1a0,0x6d79661ad1,0x479eec11d4e,0x741b7c4930f,0x754cb748cb2,0x14d1944e92,0x479eec11d4e,0x741b7c4930f,0x754cb748cb2,0x14d1944e92}};

// (8x1)-way prime-field operations 

// field addition r = a + b mod 2p
// a, b in [0, 2p) -> r in [0, 2p)
void gfp_add_8x1w(htfe_t r, const htfe_t a, const htfe_t b)
{
  __m512i a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3], a4 = a[4];
  __m512i a5 = a[5], a6 = a[6], a7 = a[7], a8 = a[8], a9 = a[9]; 
  __m512i b0 = b[0], b1 = b[1], b2 = b[2], b3 = b[3], b4 = b[4];
  __m512i b5 = b[5], b6 = b[6], b7 = b[7], b8 = b[8], b9 = b[9];
  __m512i r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, smask;
  const __m512i vp0 = VSET1(ht_pmul2[0]), vp1 = VSET1(ht_pmul2[1]);
  const __m512i vp2 = VSET1(ht_pmul2[2]), vp3 = VSET1(ht_pmul2[3]);
  const __m512i vp4 = VSET1(ht_pmul2[4]), vp5 = VSET1(ht_pmul2[5]);
  const __m512i vp6 = VSET1(ht_pmul2[6]), vp7 = VSET1(ht_pmul2[7]);
  const __m512i vp8 = VSET1(ht_pmul2[8]), vp9 = VSET1(ht_pmul2[9]);
  const __m512i vbmask = VSET1(HT_BMASK);

  // r = a + b
  r0 = VADD(a0, b0); r1 = VADD(a1, b1); r2 = VADD(a2, b2); r3 = VADD(a3, b3); 
  r4 = VADD(a4, b4); r5 = VADD(a5, b5); r6 = VADD(a6, b6); r7 = VADD(a7, b7);
  r8 = VADD(a8, b8); r9 = VADD(a9, b9); 

  // r = a + b - 2p
  r0 = VSUB(r0, vp0); r1 = VSUB(r1, vp1); r2 = VSUB(r2, vp2); r3 = VSUB(r3, vp3);
  r4 = VSUB(r4, vp4); r5 = VSUB(r5, vp5); r6 = VSUB(r6, vp6); r7 = VSUB(r7, vp7);
  r8 = VSUB(r8, vp8); r9 = VSUB(r9, vp9); 

  // check the current r is positive or negative 
  // carry propagation
  r1  = VADD(r1, VSRA(r0, HT_BRADIX)); r0  = VAND(r0, vbmask);
  r2  = VADD(r2, VSRA(r1, HT_BRADIX)); r1  = VAND(r1, vbmask);
  r3  = VADD(r3, VSRA(r2, HT_BRADIX)); r2  = VAND(r2, vbmask);
  r4  = VADD(r4, VSRA(r3, HT_BRADIX)); r3  = VAND(r3, vbmask);
  r5  = VADD(r5, VSRA(r4, HT_BRADIX)); r4  = VAND(r4, vbmask);
  r6  = VADD(r6, VSRA(r5, HT_BRADIX)); r5  = VAND(r5, vbmask);
  r7  = VADD(r7, VSRA(r6, HT_BRADIX)); r6  = VAND(r6, vbmask);
  r8  = VADD(r8, VSRA(r7, HT_BRADIX)); r7  = VAND(r7, vbmask);
  r9  = VADD(r9, VSRA(r8, HT_BRADIX)); r8  = VAND(r8, vbmask);

  // if r is positive, then the corresponding element in smask = 0; 
  // if r is negative, then the corresponding element in smask = all-1.
  smask = VSRA(r9, 63);
  // r = r + (2p & smask), add either 2p or 0 to the current r
  r0 = VADD(r0, VAND(vp0, smask)); r1 = VADD(r1, VAND(vp1, smask));
  r2 = VADD(r2, VAND(vp2, smask)); r3 = VADD(r3, VAND(vp3, smask));
  r4 = VADD(r4, VAND(vp4, smask)); r5 = VADD(r5, VAND(vp5, smask));
  r6 = VADD(r6, VAND(vp6, smask)); r7 = VADD(r7, VAND(vp7, smask));
  r8 = VADD(r8, VAND(vp8, smask)); r9 = VADD(r9, VAND(vp9, smask));

  // carry propagation
  r1 = VADD(r1, VSHR(r0, HT_BRADIX)); r0 = VAND(r0, vbmask);
  r2 = VADD(r2, VSHR(r1, HT_BRADIX)); r1 = VAND(r1, vbmask);
  r3 = VADD(r3, VSHR(r2, HT_BRADIX)); r2 = VAND(r2, vbmask);
  r4 = VADD(r4, VSHR(r3, HT_BRADIX)); r3 = VAND(r3, vbmask);
  r5 = VADD(r5, VSHR(r4, HT_BRADIX)); r4 = VAND(r4, vbmask);
  r6 = VADD(r6, VSHR(r5, HT_BRADIX)); r5 = VAND(r5, vbmask);
  r7 = VADD(r7, VSHR(r6, HT_BRADIX)); r6 = VAND(r6, vbmask);
  r8 = VADD(r8, VSHR(r7, HT_BRADIX)); r7 = VAND(r7, vbmask);
  r9 = VADD(r9, VSHR(r8, HT_BRADIX)); r8 = VAND(r8, vbmask);
  r9 = VAND(r9, vbmask);

  r[0] = r0; r[1] = r1; r[2] = r2; r[3] = r3; r[4] = r4;  
  r[5] = r5; r[6] = r6; r[7] = r7; r[8] = r8; r[9] = r9;  
}

// field subtraction r = a - b mod 2p 
// a, b in [0, 2p) -> r in [0, 2p)
void gfp_sub_8x1w(htfe_t r, const htfe_t a, const htfe_t b)
{
  __m512i a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3], a4 = a[4];
  __m512i a5 = a[5], a6 = a[6], a7 = a[7], a8 = a[8], a9 = a[9]; 
  __m512i b0 = b[0], b1 = b[1], b2 = b[2], b3 = b[3], b4 = b[4];
  __m512i b5 = b[5], b6 = b[6], b7 = b[7], b8 = b[8], b9 = b[9];
  __m512i r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, smask;
  const __m512i vp0 = VSET1(ht_pmul2[0]), vp1 = VSET1(ht_pmul2[1]);
  const __m512i vp2 = VSET1(ht_pmul2[2]), vp3 = VSET1(ht_pmul2[3]);
  const __m512i vp4 = VSET1(ht_pmul2[4]), vp5 = VSET1(ht_pmul2[5]);
  const __m512i vp6 = VSET1(ht_pmul2[6]), vp7 = VSET1(ht_pmul2[7]);
  const __m512i vp8 = VSET1(ht_pmul2[8]), vp9 = VSET1(ht_pmul2[9]);
  const __m512i vbmask = VSET1(HT_BMASK);

  // r = a - b
  r0 = VSUB(a0, b0); r1 = VSUB(a1, b1); r2 = VSUB(a2, b2); r3 = VSUB(a3, b3);  
  r4 = VSUB(a4, b4); r5 = VSUB(a5, b5); r6 = VSUB(a6, b6); r7 = VSUB(a7, b7);  
  r8 = VSUB(a8, b8); r9 = VSUB(a9, b9);  

  // check the current r is positive or negative 
  // carry propagation
  r1  = VADD(r1, VSRA(r0, HT_BRADIX)); r0  = VAND(r0, vbmask);
  r2  = VADD(r2, VSRA(r1, HT_BRADIX)); r1  = VAND(r1, vbmask);
  r3  = VADD(r3, VSRA(r2, HT_BRADIX)); r2  = VAND(r2, vbmask);
  r4  = VADD(r4, VSRA(r3, HT_BRADIX)); r3  = VAND(r3, vbmask);
  r5  = VADD(r5, VSRA(r4, HT_BRADIX)); r4  = VAND(r4, vbmask);
  r6  = VADD(r6, VSRA(r5, HT_BRADIX)); r5  = VAND(r5, vbmask);
  r7  = VADD(r7, VSRA(r6, HT_BRADIX)); r6  = VAND(r6, vbmask);
  r8  = VADD(r8, VSRA(r7, HT_BRADIX)); r7  = VAND(r7, vbmask);
  r9  = VADD(r9, VSRA(r8, HT_BRADIX)); r8  = VAND(r8, vbmask);

  // if r is positive, then the corresponding element in smask = 0; 
  // if r is negative, then the corresponding element in smask = all-1.
  smask = VSRA(r9, 63);
  // r = r + (2p & smask), add either 2p or 0 to the current r
  r0 = VADD(r0, VAND(vp0, smask)); r1 = VADD(r1, VAND(vp1, smask));
  r2 = VADD(r2, VAND(vp2, smask)); r3 = VADD(r3, VAND(vp3, smask));
  r4 = VADD(r4, VAND(vp4, smask)); r5 = VADD(r5, VAND(vp5, smask));
  r6 = VADD(r6, VAND(vp6, smask)); r7 = VADD(r7, VAND(vp7, smask));
  r8 = VADD(r8, VAND(vp8, smask)); r9 = VADD(r9, VAND(vp9, smask));

  // carry propagation
  r1 = VADD(r1, VSHR(r0, HT_BRADIX)); r0 = VAND(r0, vbmask);
  r2 = VADD(r2, VSHR(r1, HT_BRADIX)); r1 = VAND(r1, vbmask);
  r3 = VADD(r3, VSHR(r2, HT_BRADIX)); r2 = VAND(r2, vbmask);
  r4 = VADD(r4, VSHR(r3, HT_BRADIX)); r3 = VAND(r3, vbmask);
  r5 = VADD(r5, VSHR(r4, HT_BRADIX)); r4 = VAND(r4, vbmask);
  r6 = VADD(r6, VSHR(r5, HT_BRADIX)); r5 = VAND(r5, vbmask);
  r7 = VADD(r7, VSHR(r6, HT_BRADIX)); r6 = VAND(r6, vbmask);
  r8 = VADD(r8, VSHR(r7, HT_BRADIX)); r7 = VAND(r7, vbmask);
  r9 = VADD(r9, VSHR(r8, HT_BRADIX)); r8 = VAND(r8, vbmask);
  r9 = VAND(r9, vbmask);

  r[0] = r0; r[1] = r1; r[2] = r2; r[3] = r3; r[4] = r4;  
  r[5] = r5; r[6] = r6; r[7] = r7; r[8] = r8; r[9] = r9;  
}

// Montgomery multiplication r = a * b mod 2p
// multiplication (product-scanning) interleaved with reduction (operand-scanning)
// -> r in [0, 2p)
void gfp_mul_8x1w(htfe_t r, const htfe_t a, const htfe_t b)
{
  __m512i a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3], a4 = a[4];
  __m512i a5 = a[5], a6 = a[6], a7 = a[7], a8 = a[8], a9 = a[9]; 
  __m512i b0 = b[0], b1 = b[1], b2 = b[2], b3 = b[3], b4 = b[4];
  __m512i b5 = b[5], b6 = b[6], b7 = b[7], b8 = b[8], b9 = b[9]; 
  __m512i  z0 = VZERO,  z1 = VZERO,  z2 = VZERO,  z3 = VZERO,  z4 = VZERO;
  __m512i  z5 = VZERO,  z6 = VZERO,  z7 = VZERO,  z8 = VZERO,  z9 = VZERO;
  __m512i z10 = VZERO, z11 = VZERO, z12 = VZERO, z13 = VZERO, z14 = VZERO;
  __m512i z15 = VZERO, z16 = VZERO, z17 = VZERO, z18 = VZERO, z19 = VZERO;
  __m512i r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, u;
  const __m512i vp0 = VSET1(ht_p[0]), vp1 = VSET1(ht_p[1]);
  const __m512i vp2 = VSET1(ht_p[2]), vp3 = VSET1(ht_p[3]);
  const __m512i vp4 = VSET1(ht_p[4]), vp5 = VSET1(ht_p[5]);
  const __m512i vp6 = VSET1(ht_p[6]), vp7 = VSET1(ht_p[7]);
  const __m512i vp8 = VSET1(ht_p[8]), vp9 = VSET1(ht_p[9]);
  const __m512i vbmask = VSET1(HT_BMASK), vw = VSET1(HT_MONTW), zero = VZERO;

  // ---------------------------------------------------------------------------
  // 1st loop of integer multiplication 

  z0 = VMACLO(z0, a0, b0);
  z1 = VMACHI(z1, a0, b0);

  z1 = VMACLO(z1, a0, b1); z1 = VMACLO(z1, a1, b0);
  z2 = VMACHI(z2, a0, b1); z2 = VMACHI(z2, a1, b0);

  z2 = VMACLO(z2, a0, b2); z2 = VMACLO(z2, a1, b1); z2 = VMACLO(z2, a2, b0);
  z3 = VMACHI(z3, a0, b2); z3 = VMACHI(z3, a1, b1); z3 = VMACHI(z3, a2, b0);

  z3 = VMACLO(z3, a0, b3); z3 = VMACLO(z3, a1, b2); z3 = VMACLO(z3, a2, b1); 
  z3 = VMACLO(z3, a3, b0);
  z4 = VMACHI(z4, a0, b3); z4 = VMACHI(z4, a1, b2); z4 = VMACHI(z4, a2, b1); 
  z4 = VMACHI(z4, a3, b0);

  z4 = VMACLO(z4, a0, b4); z4 = VMACLO(z4, a1, b3); z4 = VMACLO(z4, a2, b2); 
  z4 = VMACLO(z4, a3, b1); z4 = VMACLO(z4, a4, b0);
  z5 = VMACHI(z5, a0, b4); z5 = VMACHI(z5, a1, b3); z5 = VMACHI(z5, a2, b2); 
  z5 = VMACHI(z5, a3, b1); z5 = VMACHI(z5, a4, b0);

  z5 = VMACLO(z5, a0, b5); z5 = VMACLO(z5, a1, b4); z5 = VMACLO(z5, a2, b3); 
  z5 = VMACLO(z5, a3, b2); z5 = VMACLO(z5, a4, b1); z5 = VMACLO(z5, a5, b0);
  z6 = VMACHI(z6, a0, b5); z6 = VMACHI(z6, a1, b4); z6 = VMACHI(z6, a2, b3); 
  z6 = VMACHI(z6, a3, b2); z6 = VMACHI(z6, a4, b1); z6 = VMACHI(z6, a5, b0);

  z6 = VMACLO(z6, a0, b6); z6 = VMACLO(z6, a1, b5); z6 = VMACLO(z6, a2, b4); 
  z6 = VMACLO(z6, a3, b3); z6 = VMACLO(z6, a4, b2); z6 = VMACLO(z6, a5, b1); 
  z6 = VMACLO(z6, a6, b0);
  z7 = VMACHI(z7, a0, b6); z7 = VMACHI(z7, a1, b5); z7 = VMACHI(z7, a2, b4); 
  z7 = VMACHI(z7, a3, b3); z7 = VMACHI(z7, a4, b2); z7 = VMACHI(z7, a5, b1); 
  z7 = VMACHI(z7, a6, b0);

  z7 = VMACLO(z7, a0, b7); z7 = VMACLO(z7, a1, b6); z7 = VMACLO(z7, a2, b5); 
  z7 = VMACLO(z7, a3, b4); z7 = VMACLO(z7, a4, b3); z7 = VMACLO(z7, a5, b2); 
  z7 = VMACLO(z7, a6, b1); z7 = VMACLO(z7, a7, b0);
  z8 = VMACHI(z8, a0, b7); z8 = VMACHI(z8, a1, b6); z8 = VMACHI(z8, a2, b5); 
  z8 = VMACHI(z8, a3, b4); z8 = VMACHI(z8, a4, b3); z8 = VMACHI(z8, a5, b2); 
  z8 = VMACHI(z8, a6, b1); z8 = VMACHI(z8, a7, b0);

  z8 = VMACLO(z8, a0, b8); z8 = VMACLO(z8, a1, b7); z8 = VMACLO(z8, a2, b6); 
  z8 = VMACLO(z8, a3, b5); z8 = VMACLO(z8, a4, b4); z8 = VMACLO(z8, a5, b3); 
  z8 = VMACLO(z8, a6, b2); z8 = VMACLO(z8, a7, b1); z8 = VMACLO(z8, a8, b0);
  z9 = VMACHI(z9, a0, b8); z9 = VMACHI(z9, a1, b7); z9 = VMACHI(z9, a2, b6); 
  z9 = VMACHI(z9, a3, b5); z9 = VMACHI(z9, a4, b4); z9 = VMACHI(z9, a5, b3); 
  z9 = VMACHI(z9, a6, b2); z9 = VMACHI(z9, a7, b1); z9 = VMACHI(z9, a8, b0);

  z9 = VMACLO(z9, a0, b9); z9 = VMACLO(z9, a1, b8); z9 = VMACLO(z9, a2, b7); 
  z9 = VMACLO(z9, a3, b6); z9 = VMACLO(z9, a4, b5); z9 = VMACLO(z9, a5, b4); 
  z9 = VMACLO(z9, a6, b3); z9 = VMACLO(z9, a7, b2); z9 = VMACLO(z9, a8, b1); 
  z9 = VMACLO(z9, a9, b0);
  z10 = VMACHI(z10, a0, b9); z10 = VMACHI(z10, a1, b8); z10 = VMACHI(z10, a2, b7); 
  z10 = VMACHI(z10, a3, b6); z10 = VMACHI(z10, a4, b5); z10 = VMACHI(z10, a5, b4); 
  z10 = VMACHI(z10, a6, b3); z10 = VMACHI(z10, a7, b2); z10 = VMACHI(z10, a8, b1); 
  z10 = VMACHI(z10, a9, b0);

  // ---------------------------------------------------------------------------
  // 2nd loop of integer multiplication + Montgomery reduction  

  u = VMACLO(zero, z0, vw); 
  z0 = VMACLO(z0, u, vp0); z1  = VMACHI(z1,  u, vp0); 
  z1 = VMACLO(z1, u, vp1); z2  = VMACHI(z2,  u, vp1); 
  z2 = VMACLO(z2, u, vp2); z3  = VMACHI(z3,  u, vp2); 
  z3 = VMACLO(z3, u, vp3); z4  = VMACHI(z4,  u, vp3); 
  z4 = VMACLO(z4, u, vp4); z5  = VMACHI(z5,  u, vp4); 
  z5 = VMACLO(z5, u, vp5); z6  = VMACHI(z6,  u, vp5); 
  z6 = VMACLO(z6, u, vp6); z7  = VMACHI(z7,  u, vp6); 
  z7 = VMACLO(z7, u, vp7); z8  = VMACHI(z8,  u, vp7); 
  z8 = VMACLO(z8, u, vp8); z9  = VMACHI(z9,  u, vp8); 
  z9 = VMACLO(z9, u, vp9); z10 = VMACHI(z10, u, vp9); 
  z1 = VADD(z1, VSHR(z0, HT_BRADIX));

  z10 = VMACLO(z10, a1, b9); z10 = VMACLO(z10, a2, b8); z10 = VMACLO(z10, a3, b7); 
  z10 = VMACLO(z10, a4, b6); z10 = VMACLO(z10, a5, b5); z10 = VMACLO(z10, a6, b4); 
  z10 = VMACLO(z10, a7, b3); z10 = VMACLO(z10, a8, b2); z10 = VMACLO(z10, a9, b1);
  z11 = VMACHI(z11, a1, b9); z11 = VMACHI(z11, a2, b8); z11 = VMACHI(z11, a3, b7); 
  z11 = VMACHI(z11, a4, b6); z11 = VMACHI(z11, a5, b5); z11 = VMACHI(z11, a6, b4); 
  z11 = VMACHI(z11, a7, b3); z11 = VMACHI(z11, a8, b2); z11 = VMACHI(z11, a9, b1); 

  u = VMACLO(zero, z1, vw); 
  z1  = VMACLO(z1,  u, vp0); z2  = VMACHI(z2,  u, vp0); 
  z2  = VMACLO(z2,  u, vp1); z3  = VMACHI(z3,  u, vp1); 
  z3  = VMACLO(z3,  u, vp2); z4  = VMACHI(z4,  u, vp2); 
  z4  = VMACLO(z4,  u, vp3); z5  = VMACHI(z5,  u, vp3); 
  z5  = VMACLO(z5,  u, vp4); z6  = VMACHI(z6,  u, vp4); 
  z6  = VMACLO(z6,  u, vp5); z7  = VMACHI(z7,  u, vp5); 
  z7  = VMACLO(z7,  u, vp6); z8  = VMACHI(z8,  u, vp6); 
  z8  = VMACLO(z8,  u, vp7); z9  = VMACHI(z9,  u, vp7); 
  z9  = VMACLO(z9,  u, vp8); z10 = VMACHI(z10, u, vp8); 
  z10 = VMACLO(z10, u, vp9); z11 = VMACHI(z11, u, vp9); 
  z2 = VADD(z2, VSHR(z1, HT_BRADIX));

  z11 = VMACLO(z11, a2, b9); z11 = VMACLO(z11, a3, b8); z11 = VMACLO(z11, a4, b7); 
  z11 = VMACLO(z11, a5, b6); z11 = VMACLO(z11, a6, b5); z11 = VMACLO(z11, a7, b4); 
  z11 = VMACLO(z11, a8, b3); z11 = VMACLO(z11, a9, b2);
  z12 = VMACHI(z12, a2, b9); z12 = VMACHI(z12, a3, b8); z12 = VMACHI(z12, a4, b7); 
  z12 = VMACHI(z12, a5, b6); z12 = VMACHI(z12, a6, b5); z12 = VMACHI(z12, a7, b4); 
  z12 = VMACHI(z12, a8, b3); z12 = VMACHI(z12, a9, b2);

  u = VMACLO(zero, z2, vw); 
  z2  = VMACLO(z2,  u, vp0); z3  = VMACHI(z3,  u, vp0); 
  z3  = VMACLO(z3,  u, vp1); z4  = VMACHI(z4,  u, vp1); 
  z4  = VMACLO(z4,  u, vp2); z5  = VMACHI(z5,  u, vp2); 
  z5  = VMACLO(z5,  u, vp3); z6  = VMACHI(z6,  u, vp3); 
  z6  = VMACLO(z6,  u, vp4); z7  = VMACHI(z7,  u, vp4); 
  z7  = VMACLO(z7,  u, vp5); z8  = VMACHI(z8,  u, vp5); 
  z8  = VMACLO(z8,  u, vp6); z9  = VMACHI(z9,  u, vp6); 
  z9  = VMACLO(z9,  u, vp7); z10 = VMACHI(z10, u, vp7); 
  z10 = VMACLO(z10, u, vp8); z11 = VMACHI(z11, u, vp8); 
  z11 = VMACLO(z11, u, vp9); z12 = VMACHI(z12, u, vp9); 
  z3 = VADD(z3, VSHR(z2, HT_BRADIX));

  z12 = VMACLO(z12, a3, b9); z12 = VMACLO(z12, a4, b8); z12 = VMACLO(z12, a5, b7); 
  z12 = VMACLO(z12, a6, b6); z12 = VMACLO(z12, a7, b5); z12 = VMACLO(z12, a8, b4); 
  z12 = VMACLO(z12, a9, b3);
  z13 = VMACHI(z13, a3, b9); z13 = VMACHI(z13, a4, b8); z13 = VMACHI(z13, a5, b7); 
  z13 = VMACHI(z13, a6, b6); z13 = VMACHI(z13, a7, b5); z13 = VMACHI(z13, a8, b4); 
  z13 = VMACHI(z13, a9, b3);

  u = VMACLO(zero, z3, vw); 
  z3  = VMACLO(z3,  u, vp0); z4  = VMACHI(z4,  u, vp0); 
  z4  = VMACLO(z4,  u, vp1); z5  = VMACHI(z5,  u, vp1); 
  z5  = VMACLO(z5,  u, vp2); z6  = VMACHI(z6,  u, vp2); 
  z6  = VMACLO(z6,  u, vp3); z7  = VMACHI(z7,  u, vp3); 
  z7  = VMACLO(z7,  u, vp4); z8  = VMACHI(z8,  u, vp4); 
  z8  = VMACLO(z8,  u, vp5); z9  = VMACHI(z9,  u, vp5); 
  z9  = VMACLO(z9,  u, vp6); z10 = VMACHI(z10, u, vp6); 
  z10 = VMACLO(z10, u, vp7); z11 = VMACHI(z11, u, vp7); 
  z11 = VMACLO(z11, u, vp8); z12 = VMACHI(z12, u, vp8); 
  z12 = VMACLO(z12, u, vp9); z13 = VMACHI(z13, u, vp9); 
  z4 = VADD(z4, VSHR(z3, HT_BRADIX));

  z13 = VMACLO(z13, a4, b9); z13 = VMACLO(z13, a5, b8); z13 = VMACLO(z13, a6, b7); 
  z13 = VMACLO(z13, a7, b6); z13 = VMACLO(z13, a8, b5); z13 = VMACLO(z13, a9, b4);
  z14 = VMACHI(z14, a4, b9); z14 = VMACHI(z14, a5, b8); z14 = VMACHI(z14, a6, b7); 
  z14 = VMACHI(z14, a7, b6); z14 = VMACHI(z14, a8, b5); z14 = VMACHI(z14, a9, b4);

  u = VMACLO(zero, z4, vw); 
  z4  = VMACLO(z4,  u, vp0); z5  = VMACHI(z5,  u, vp0); 
  z5  = VMACLO(z5,  u, vp1); z6  = VMACHI(z6,  u, vp1); 
  z6  = VMACLO(z6,  u, vp2); z7  = VMACHI(z7,  u, vp2); 
  z7  = VMACLO(z7,  u, vp3); z8  = VMACHI(z8,  u, vp3); 
  z8  = VMACLO(z8,  u, vp4); z9  = VMACHI(z9,  u, vp4); 
  z9  = VMACLO(z9,  u, vp5); z10 = VMACHI(z10, u, vp5); 
  z10 = VMACLO(z10, u, vp6); z11 = VMACHI(z11, u, vp6); 
  z11 = VMACLO(z11, u, vp7); z12 = VMACHI(z12, u, vp7); 
  z12 = VMACLO(z12, u, vp8); z13 = VMACHI(z13, u, vp8); 
  z13 = VMACLO(z13, u, vp9); z14 = VMACHI(z14, u, vp9); 
  z5 = VADD(z5, VSHR(z4, HT_BRADIX)); 

  z14 = VMACLO(z14, a5, b9); z14 = VMACLO(z14, a6, b8); z14 = VMACLO(z14, a7, b7); 
  z14 = VMACLO(z14, a8, b6); z14 = VMACLO(z14, a9, b5);
  z15 = VMACHI(z15, a5, b9); z15 = VMACHI(z15, a6, b8); z15 = VMACHI(z15, a7, b7); 
  z15 = VMACHI(z15, a8, b6); z15 = VMACHI(z15, a9, b5);

  u = VMACLO(zero, z5, vw); 
  z5  = VMACLO(z5,  u, vp0); z6  = VMACHI(z6,  u, vp0); 
  z6  = VMACLO(z6,  u, vp1); z7  = VMACHI(z7,  u, vp1); 
  z7  = VMACLO(z7,  u, vp2); z8  = VMACHI(z8,  u, vp2); 
  z8  = VMACLO(z8,  u, vp3); z9  = VMACHI(z9,  u, vp3); 
  z9  = VMACLO(z9,  u, vp4); z10 = VMACHI(z10, u, vp4); 
  z10 = VMACLO(z10, u, vp5); z11 = VMACHI(z11, u, vp5); 
  z11 = VMACLO(z11, u, vp6); z12 = VMACHI(z12, u, vp6); 
  z12 = VMACLO(z12, u, vp7); z13 = VMACHI(z13, u, vp7); 
  z13 = VMACLO(z13, u, vp8); z14 = VMACHI(z14, u, vp8); 
  z14 = VMACLO(z14, u, vp9); z15 = VMACHI(z15, u, vp9); 
  z6 = VADD(z6, VSHR(z5, HT_BRADIX));

  z15 = VMACLO(z15, a6, b9); z15 = VMACLO(z15, a7, b8); z15 = VMACLO(z15, a8, b7); 
  z15 = VMACLO(z15, a9, b6);
  z16 = VMACHI(z16, a6, b9); z16 = VMACHI(z16, a7, b8); z16 = VMACHI(z16, a8, b7); 
  z16 = VMACHI(z16, a9, b6);

  u = VMACLO(zero, z6, vw); 
  z6  = VMACLO(z6,  u, vp0); z7  = VMACHI(z7,  u, vp0); 
  z7  = VMACLO(z7,  u, vp1); z8  = VMACHI(z8,  u, vp1); 
  z8  = VMACLO(z8,  u, vp2); z9  = VMACHI(z9,  u, vp2); 
  z9  = VMACLO(z9,  u, vp3); z10 = VMACHI(z10, u, vp3); 
  z10 = VMACLO(z10, u, vp4); z11 = VMACHI(z11, u, vp4); 
  z11 = VMACLO(z11, u, vp5); z12 = VMACHI(z12, u, vp5); 
  z12 = VMACLO(z12, u, vp6); z13 = VMACHI(z13, u, vp6); 
  z13 = VMACLO(z13, u, vp7); z14 = VMACHI(z14, u, vp7); 
  z14 = VMACLO(z14, u, vp8); z15 = VMACHI(z15, u, vp8); 
  z15 = VMACLO(z15, u, vp9); z16 = VMACHI(z16, u, vp9); 
  z7 = VADD(z7, VSHR(z6, HT_BRADIX));  

  z16 = VMACLO(z16, a7, b9); z16 = VMACLO(z16, a8, b8); z16 = VMACLO(z16, a9, b7);
  z17 = VMACHI(z17, a7, b9); z17 = VMACHI(z17, a8, b8); z17 = VMACHI(z17, a9, b7);

  u = VMACLO(zero, z7, vw); 
  z7  = VMACLO(z7,  u, vp0); z8  = VMACHI(z8,  u, vp0); 
  z8  = VMACLO(z8,  u, vp1); z9  = VMACHI(z9,  u, vp1); 
  z9  = VMACLO(z9,  u, vp2); z10 = VMACHI(z10, u, vp2); 
  z10 = VMACLO(z10, u, vp3); z11 = VMACHI(z11, u, vp3); 
  z11 = VMACLO(z11, u, vp4); z12 = VMACHI(z12, u, vp4); 
  z12 = VMACLO(z12, u, vp5); z13 = VMACHI(z13, u, vp5); 
  z13 = VMACLO(z13, u, vp6); z14 = VMACHI(z14, u, vp6); 
  z14 = VMACLO(z14, u, vp7); z15 = VMACHI(z15, u, vp7); 
  z15 = VMACLO(z15, u, vp8); z16 = VMACHI(z16, u, vp8); 
  z16 = VMACLO(z16, u, vp9); z17 = VMACHI(z17, u, vp9); 
  z8 = VADD(z8, VSHR(z7, HT_BRADIX)); 

  z17 = VMACLO(z17, a8, b9); z17 = VMACLO(z17, a9, b8);
  z18 = VMACHI(z18, a8, b9); z18 = VMACHI(z18, a9, b8);

  u = VMACLO(zero, z8, vw); 
  z8  = VMACLO(z8,  u, vp0); z9  = VMACHI(z9,  u, vp0); 
  z9  = VMACLO(z9,  u, vp1); z10 = VMACHI(z10, u, vp1); 
  z10 = VMACLO(z10, u, vp2); z11 = VMACHI(z11, u, vp2); 
  z11 = VMACLO(z11, u, vp3); z12 = VMACHI(z12, u, vp3); 
  z12 = VMACLO(z12, u, vp4); z13 = VMACHI(z13, u, vp4); 
  z13 = VMACLO(z13, u, vp5); z14 = VMACHI(z14, u, vp5); 
  z14 = VMACLO(z14, u, vp6); z15 = VMACHI(z15, u, vp6); 
  z15 = VMACLO(z15, u, vp7); z16 = VMACHI(z16, u, vp7); 
  z16 = VMACLO(z16, u, vp8); z17 = VMACHI(z17, u, vp8); 
  z17 = VMACLO(z17, u, vp9); z18 = VMACHI(z18, u, vp9); 
  z9 = VADD(z9, VSHR(z8, HT_BRADIX));  

  z18 = VMACLO(z18, a9, b9);
  z19 = VMACHI(z19, a9, b9);

  u = VMACLO(zero, z9, vw); 
  z9  = VMACLO(z9,  u, vp0); z10 = VMACHI(z10, u, vp0); 
  z10 = VMACLO(z10, u, vp1); z11 = VMACHI(z11, u, vp1); 
  z11 = VMACLO(z11, u, vp2); z12 = VMACHI(z12, u, vp2); 
  z12 = VMACLO(z12, u, vp3); z13 = VMACHI(z13, u, vp3); 
  z13 = VMACLO(z13, u, vp4); z14 = VMACHI(z14, u, vp4); 
  z14 = VMACLO(z14, u, vp5); z15 = VMACHI(z15, u, vp5); 
  z15 = VMACLO(z15, u, vp6); z16 = VMACHI(z16, u, vp6); 
  z16 = VMACLO(z16, u, vp7); z17 = VMACHI(z17, u, vp7); 
  z17 = VMACLO(z17, u, vp8); z18 = VMACHI(z18, u, vp8); 
  z18 = VMACLO(z18, u, vp9); z19 = VMACHI(z19, u, vp9);
  z10 = VADD(z10, VSHR(z9, HT_BRADIX));

  // carry propagation
  z11 = VADD(z11, VSHR(z10, HT_BRADIX)); z10 = VAND(z10, vbmask);
  z12 = VADD(z12, VSHR(z11, HT_BRADIX)); z11 = VAND(z11, vbmask);
  z13 = VADD(z13, VSHR(z12, HT_BRADIX)); z12 = VAND(z12, vbmask);
  z14 = VADD(z14, VSHR(z13, HT_BRADIX)); z13 = VAND(z13, vbmask);
  z15 = VADD(z15, VSHR(z14, HT_BRADIX)); z14 = VAND(z14, vbmask);
  z16 = VADD(z16, VSHR(z15, HT_BRADIX)); z15 = VAND(z15, vbmask);
  z17 = VADD(z17, VSHR(z16, HT_BRADIX)); z16 = VAND(z16, vbmask);
  z18 = VADD(z18, VSHR(z17, HT_BRADIX)); z17 = VAND(z17, vbmask);
  z19 = VADD(z19, VSHR(z18, HT_BRADIX)); z18 = VAND(z18, vbmask);

  // ---------------------------------------------------------------------------

  r[0] = z10; r[1] = z11; r[2] = z12; r[3] = z13; r[4] = z14; 
  r[5] = z15; r[6] = z16; r[7] = z17; r[8] = z18; r[9] = z19;  
}

// Montgomery squaring r = a^2 mod 2p
// squaring (product-scanning) interleaved with reduction (operand-scanning)
// -> r in [0, 2p)
void gfp_sqr_8x1w(htfe_t r, const htfe_t a)
{
  __m512i a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3], a4 = a[4];
  __m512i a5 = a[5], a6 = a[6], a7 = a[7], a8 = a[8], a9 = a[9]; 
  __m512i  z0 = VZERO,  z1 = VZERO,  z2 = VZERO,  z3 = VZERO,  z4 = VZERO;
  __m512i  z5 = VZERO,  z6 = VZERO,  z7 = VZERO,  z8 = VZERO,  z9 = VZERO;
  __m512i z10 = VZERO, z11 = VZERO, z12 = VZERO, z13 = VZERO, z14 = VZERO;
  __m512i z15 = VZERO, z16 = VZERO, z17 = VZERO, z18 = VZERO, z19 = VZERO;
  __m512i r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, u;
  const __m512i vp0 = VSET1(ht_p[0]), vp1 = VSET1(ht_p[1]);
  const __m512i vp2 = VSET1(ht_p[2]), vp3 = VSET1(ht_p[3]);
  const __m512i vp4 = VSET1(ht_p[4]), vp5 = VSET1(ht_p[5]);
  const __m512i vp6 = VSET1(ht_p[6]), vp7 = VSET1(ht_p[7]);
  const __m512i vp8 = VSET1(ht_p[8]), vp9 = VSET1(ht_p[9]);
  const __m512i vbmask = VSET1(HT_BMASK), vw = VSET1(HT_MONTW), zero = VZERO;

  // ---------------------------------------------------------------------------
  // 1st loop of integer squaring

  z1 = VMACLO(z1, a0, a1);
  z2 = VMACHI(z2, a0, a1);
  z1 = VADD(z1, z1);
  z0 = VMACLO(z0, a0, a0); z1 = VMACHI(z1, a0, a0);

  z2 = VMACLO(z2, a0, a2); 
  z3 = VMACHI(z3, a0, a2);
  z2 = VADD(z2, z2);

  z3 = VMACLO(z3, a0, a3); z3 = VMACLO(z3, a1, a2); 
  z4 = VMACHI(z4, a0, a3); z4 = VMACHI(z4, a1, a2); 
  z3 = VADD(z3, z3);
  z2 = VMACLO(z2, a1, a1); z3 = VMACHI(z3, a1, a1); 

  z4 = VMACLO(z4, a0, a4); z4 = VMACLO(z4, a1, a3); 
  z5 = VMACHI(z5, a0, a4); z5 = VMACHI(z5, a1, a3); 
  z4 = VADD(z4, z4);

  z5 = VMACLO(z5, a0, a5); z5 = VMACLO(z5, a1, a4); z5 = VMACLO(z5, a2, a3); 
  z6 = VMACHI(z6, a0, a5); z6 = VMACHI(z6, a1, a4); z6 = VMACHI(z6, a2, a3); 
  z5 = VADD(z5, z5);
  z4 = VMACLO(z4, a2, a2); z5 = VMACHI(z5, a2, a2); 

  z6 = VMACLO(z6, a0, a6); z6 = VMACLO(z6, a1, a5); z6 = VMACLO(z6, a2, a4); 
  z7 = VMACHI(z7, a0, a6); z7 = VMACHI(z7, a1, a5); z7 = VMACHI(z7, a2, a4); 
  z6 = VADD(z6, z6);

  z7 = VMACLO(z7, a0, a7); z7 = VMACLO(z7, a1, a6); z7 = VMACLO(z7, a2, a5); 
  z7 = VMACLO(z7, a3, a4); 
  z8 = VMACHI(z8, a0, a7); z8 = VMACHI(z8, a1, a6); z8 = VMACHI(z8, a2, a5); 
  z8 = VMACHI(z8, a3, a4); 
  z7 = VADD(z7, z7);
  z6 = VMACLO(z6, a3, a3); z7 = VMACHI(z7, a3, a3); 

  z8 = VMACLO(z8, a0, a8); z8 = VMACLO(z8, a1, a7); z8 = VMACLO(z8, a2, a6); 
  z8 = VMACLO(z8, a3, a5);  
  z9 = VMACHI(z9, a0, a8); z9 = VMACHI(z9, a1, a7); z9 = VMACHI(z9, a2, a6); 
  z9 = VMACHI(z9, a3, a5); 
  z8 = VADD(z8, z8);

  z9 = VMACLO(z9, a0, a9); z9 = VMACLO(z9, a1, a8); z9 = VMACLO(z9, a2, a7); 
  z9 = VMACLO(z9, a3, a6); z9 = VMACLO(z9, a4, a5); 
  z10 = VMACHI(z10, a0, a9); z10 = VMACHI(z10, a1, a8); z10 = VMACHI(z10, a2, a7); 
  z10 = VMACHI(z10, a3, a6); z10 = VMACHI(z10, a4, a5);
  z9 = VADD(z9, z9);
  z8 = VMACLO(z8, a4, a4); z9 = VMACHI(z9, a4, a4); 

  // ---------------------------------------------------------------------------
  // 2nd loop of integer squaring + Montgomery reduction

  z10 = VMACLO(z10, a1, a9); z10 = VMACLO(z10, a2, a8); z10 = VMACLO(z10, a3, a7); 
  z10 = VMACLO(z10, a4, a6); 
  z11 = VMACHI(z11, a1, a9); z11 = VMACHI(z11, a2, a8); z11 = VMACHI(z11, a3, a7); 
  z11 = VMACHI(z11, a4, a6);
  z10 = VADD(z10, z10);

  u = VMACLO(zero, z0, vw); 
  z0 = VMACLO(z0, u, vp0); z1  = VMACHI(z1,  u, vp0); 
  z1 = VMACLO(z1, u, vp1); z2  = VMACHI(z2,  u, vp1); 
  z2 = VMACLO(z2, u, vp2); z3  = VMACHI(z3,  u, vp2); 
  z3 = VMACLO(z3, u, vp3); z4  = VMACHI(z4,  u, vp3); 
  z4 = VMACLO(z4, u, vp4); z5  = VMACHI(z5,  u, vp4); 
  z5 = VMACLO(z5, u, vp5); z6  = VMACHI(z6,  u, vp5); 
  z6 = VMACLO(z6, u, vp6); z7  = VMACHI(z7,  u, vp6); 
  z7 = VMACLO(z7, u, vp7); z8  = VMACHI(z8,  u, vp7); 
  z8 = VMACLO(z8, u, vp8); z9  = VMACHI(z9,  u, vp8); 
  z9 = VMACLO(z9, u, vp9); z10 = VMACHI(z10, u, vp9); 
  z1 = VADD(z1, VSHR(z0, HT_BRADIX));

  z11 = VMACLO(z11, a2, a9); z11 = VMACLO(z11, a3, a8); z11 = VMACLO(z11, a4, a7); 
  z11 = VMACLO(z11, a5, a6); 
  z12 = VMACHI(z12, a2, a9); z12 = VMACHI(z12, a3, a8); z12 = VMACHI(z12, a4, a7); 
  z12 = VMACHI(z12, a5, a6);
  z11 = VADD(z11, z11);
  z10 = VMACLO(z10, a5, a5); z11 = VMACHI(z11, a5, a5); 

  u = VMACLO(zero, z1, vw); 
  z1  = VMACLO(z1,  u, vp0); z2  = VMACHI(z2,  u, vp0); 
  z2  = VMACLO(z2,  u, vp1); z3  = VMACHI(z3,  u, vp1); 
  z3  = VMACLO(z3,  u, vp2); z4  = VMACHI(z4,  u, vp2); 
  z4  = VMACLO(z4,  u, vp3); z5  = VMACHI(z5,  u, vp3); 
  z5  = VMACLO(z5,  u, vp4); z6  = VMACHI(z6,  u, vp4); 
  z6  = VMACLO(z6,  u, vp5); z7  = VMACHI(z7,  u, vp5); 
  z7  = VMACLO(z7,  u, vp6); z8  = VMACHI(z8,  u, vp6); 
  z8  = VMACLO(z8,  u, vp7); z9  = VMACHI(z9,  u, vp7); 
  z9  = VMACLO(z9,  u, vp8); z10 = VMACHI(z10, u, vp8); 
  z10 = VMACLO(z10, u, vp9); z11 = VMACHI(z11, u, vp9); 
  z2 = VADD(z2, VSHR(z1, HT_BRADIX));  

  z12 = VMACLO(z12, a3, a9); z12 = VMACLO(z12, a4, a8); z12 = VMACLO(z12, a5, a7); 
  z13 = VMACHI(z13, a3, a9); z13 = VMACHI(z13, a4, a8); z13 = VMACHI(z13, a5, a7); 
  z12 = VADD(z12, z12);

  u = VMACLO(zero, z2, vw); 
  z2  = VMACLO(z2,  u, vp0); z3  = VMACHI(z3,  u, vp0); 
  z3  = VMACLO(z3,  u, vp1); z4  = VMACHI(z4,  u, vp1); 
  z4  = VMACLO(z4,  u, vp2); z5  = VMACHI(z5,  u, vp2); 
  z5  = VMACLO(z5,  u, vp3); z6  = VMACHI(z6,  u, vp3); 
  z6  = VMACLO(z6,  u, vp4); z7  = VMACHI(z7,  u, vp4); 
  z7  = VMACLO(z7,  u, vp5); z8  = VMACHI(z8,  u, vp5); 
  z8  = VMACLO(z8,  u, vp6); z9  = VMACHI(z9,  u, vp6); 
  z9  = VMACLO(z9,  u, vp7); z10 = VMACHI(z10, u, vp7); 
  z10 = VMACLO(z10, u, vp8); z11 = VMACHI(z11, u, vp8); 
  z11 = VMACLO(z11, u, vp9); z12 = VMACHI(z12, u, vp9); 
  z3 = VADD(z3, VSHR(z2, HT_BRADIX));

  z13 = VMACLO(z13, a4, a9); z13 = VMACLO(z13, a5, a8); z13 = VMACLO(z13, a6, a7); 
  z14 = VMACHI(z14, a4, a9); z14 = VMACHI(z14, a5, a8); z14 = VMACHI(z14, a6, a7); 
  z13 = VADD(z13, z13);
  z12 = VMACLO(z12, a6, a6); z13 = VMACHI(z13, a6, a6); 

  u = VMACLO(zero, z3, vw); 
  z3  = VMACLO(z3,  u, vp0); z4  = VMACHI(z4,  u, vp0); 
  z4  = VMACLO(z4,  u, vp1); z5  = VMACHI(z5,  u, vp1); 
  z5  = VMACLO(z5,  u, vp2); z6  = VMACHI(z6,  u, vp2); 
  z6  = VMACLO(z6,  u, vp3); z7  = VMACHI(z7,  u, vp3); 
  z7  = VMACLO(z7,  u, vp4); z8  = VMACHI(z8,  u, vp4); 
  z8  = VMACLO(z8,  u, vp5); z9  = VMACHI(z9,  u, vp5); 
  z9  = VMACLO(z9,  u, vp6); z10 = VMACHI(z10, u, vp6); 
  z10 = VMACLO(z10, u, vp7); z11 = VMACHI(z11, u, vp7); 
  z11 = VMACLO(z11, u, vp8); z12 = VMACHI(z12, u, vp8); 
  z12 = VMACLO(z12, u, vp9); z13 = VMACHI(z13, u, vp9); 
  z4 = VADD(z4, VSHR(z3, HT_BRADIX));

  z14 = VMACLO(z14, a5, a9); z14 = VMACLO(z14, a6, a8); 
  z15 = VMACHI(z15, a5, a9); z15 = VMACHI(z15, a6, a8); 
  z14 = VADD(z14, z14);

  u = VMACLO(zero, z4, vw); 
  z4  = VMACLO(z4,  u, vp0); z5  = VMACHI(z5,  u, vp0); 
  z5  = VMACLO(z5,  u, vp1); z6  = VMACHI(z6,  u, vp1); 
  z6  = VMACLO(z6,  u, vp2); z7  = VMACHI(z7,  u, vp2); 
  z7  = VMACLO(z7,  u, vp3); z8  = VMACHI(z8,  u, vp3); 
  z8  = VMACLO(z8,  u, vp4); z9  = VMACHI(z9,  u, vp4); 
  z9  = VMACLO(z9,  u, vp5); z10 = VMACHI(z10, u, vp5); 
  z10 = VMACLO(z10, u, vp6); z11 = VMACHI(z11, u, vp6); 
  z11 = VMACLO(z11, u, vp7); z12 = VMACHI(z12, u, vp7); 
  z12 = VMACLO(z12, u, vp8); z13 = VMACHI(z13, u, vp8); 
  z13 = VMACLO(z13, u, vp9); z14 = VMACHI(z14, u, vp9); 
  z5 = VADD(z5, VSHR(z4, HT_BRADIX));

  z15 = VMACLO(z15, a6, a9); z15 = VMACLO(z15, a7, a8); 
  z16 = VMACHI(z16, a6, a9); z16 = VMACHI(z16, a7, a8);
  z15 = VADD(z15, z15);
  z14 = VMACLO(z14, a7, a7); z15 = VMACHI(z15, a7, a7);

  u = VMACLO(zero, z5, vw); 
  z5  = VMACLO(z5,  u, vp0); z6  = VMACHI(z6,  u, vp0); 
  z6  = VMACLO(z6,  u, vp1); z7  = VMACHI(z7,  u, vp1); 
  z7  = VMACLO(z7,  u, vp2); z8  = VMACHI(z8,  u, vp2); 
  z8  = VMACLO(z8,  u, vp3); z9  = VMACHI(z9,  u, vp3); 
  z9  = VMACLO(z9,  u, vp4); z10 = VMACHI(z10, u, vp4); 
  z10 = VMACLO(z10, u, vp5); z11 = VMACHI(z11, u, vp5); 
  z11 = VMACLO(z11, u, vp6); z12 = VMACHI(z12, u, vp6); 
  z12 = VMACLO(z12, u, vp7); z13 = VMACHI(z13, u, vp7); 
  z13 = VMACLO(z13, u, vp8); z14 = VMACHI(z14, u, vp8); 
  z14 = VMACLO(z14, u, vp9); z15 = VMACHI(z15, u, vp9); 
  z6 = VADD(z6, VSHR(z5, HT_BRADIX));

  z16 = VMACLO(z16, a7, a9);  
  z17 = VMACHI(z17, a7, a9); 
  z16 = VADD(z16, z16);

  u = VMACLO(zero, z6, vw); 
  z6  = VMACLO(z6,  u, vp0); z7  = VMACHI(z7,  u, vp0); 
  z7  = VMACLO(z7,  u, vp1); z8  = VMACHI(z8,  u, vp1); 
  z8  = VMACLO(z8,  u, vp2); z9  = VMACHI(z9,  u, vp2); 
  z9  = VMACLO(z9,  u, vp3); z10 = VMACHI(z10, u, vp3); 
  z10 = VMACLO(z10, u, vp4); z11 = VMACHI(z11, u, vp4); 
  z11 = VMACLO(z11, u, vp5); z12 = VMACHI(z12, u, vp5); 
  z12 = VMACLO(z12, u, vp6); z13 = VMACHI(z13, u, vp6); 
  z13 = VMACLO(z13, u, vp7); z14 = VMACHI(z14, u, vp7); 
  z14 = VMACLO(z14, u, vp8); z15 = VMACHI(z15, u, vp8); 
  z15 = VMACLO(z15, u, vp9); z16 = VMACHI(z16, u, vp9); 
  z7 = VADD(z7, VSHR(z6, HT_BRADIX)); 

  z17 = VMACLO(z17, a8, a9); 
  z18 = VMACHI(z18, a8, a9);
  z17 = VADD(z17, z17);
  z16 = VMACLO(z16, a8, a8); z17 = VMACHI(z17, a8, a8); 

  u = VMACLO(zero, z7, vw); 
  z7  = VMACLO(z7,  u, vp0); z8  = VMACHI(z8,  u, vp0); 
  z8  = VMACLO(z8,  u, vp1); z9  = VMACHI(z9,  u, vp1); 
  z9  = VMACLO(z9,  u, vp2); z10 = VMACHI(z10, u, vp2); 
  z10 = VMACLO(z10, u, vp3); z11 = VMACHI(z11, u, vp3); 
  z11 = VMACLO(z11, u, vp4); z12 = VMACHI(z12, u, vp4); 
  z12 = VMACLO(z12, u, vp5); z13 = VMACHI(z13, u, vp5); 
  z13 = VMACLO(z13, u, vp6); z14 = VMACHI(z14, u, vp6); 
  z14 = VMACLO(z14, u, vp7); z15 = VMACHI(z15, u, vp7); 
  z15 = VMACLO(z15, u, vp8); z16 = VMACHI(z16, u, vp8); 
  z16 = VMACLO(z16, u, vp9); z17 = VMACHI(z17, u, vp9); 
  z8 = VADD(z8, VSHR(z7, HT_BRADIX)); 

  z18 = VADD(z18, z18);

  u = VMACLO(zero, z8, vw); 
  z8  = VMACLO(z8,  u, vp0); z9  = VMACHI(z9,  u, vp0); 
  z9  = VMACLO(z9,  u, vp1); z10 = VMACHI(z10, u, vp1); 
  z10 = VMACLO(z10, u, vp2); z11 = VMACHI(z11, u, vp2); 
  z11 = VMACLO(z11, u, vp3); z12 = VMACHI(z12, u, vp3); 
  z12 = VMACLO(z12, u, vp4); z13 = VMACHI(z13, u, vp4); 
  z13 = VMACLO(z13, u, vp5); z14 = VMACHI(z14, u, vp5); 
  z14 = VMACLO(z14, u, vp6); z15 = VMACHI(z15, u, vp6); 
  z15 = VMACLO(z15, u, vp7); z16 = VMACHI(z16, u, vp7); 
  z16 = VMACLO(z16, u, vp8); z17 = VMACHI(z17, u, vp8); 
  z17 = VMACLO(z17, u, vp9); z18 = VMACHI(z18, u, vp9); 
  z9 = VADD(z9, VSHR(z8, HT_BRADIX)); 

  z18 = VMACLO(z18, a9, a9);
  z19 = VMACHI(z19, a9, a9);

  u = VMACLO(zero, z9, vw); 
  z9  = VMACLO(z9,  u, vp0); z10 = VMACHI(z10, u, vp0); 
  z10 = VMACLO(z10, u, vp1); z11 = VMACHI(z11, u, vp1); 
  z11 = VMACLO(z11, u, vp2); z12 = VMACHI(z12, u, vp2); 
  z12 = VMACLO(z12, u, vp3); z13 = VMACHI(z13, u, vp3); 
  z13 = VMACLO(z13, u, vp4); z14 = VMACHI(z14, u, vp4); 
  z14 = VMACLO(z14, u, vp5); z15 = VMACHI(z15, u, vp5); 
  z15 = VMACLO(z15, u, vp6); z16 = VMACHI(z16, u, vp6); 
  z16 = VMACLO(z16, u, vp7); z17 = VMACHI(z17, u, vp7); 
  z17 = VMACLO(z17, u, vp8); z18 = VMACHI(z18, u, vp8); 
  z18 = VMACLO(z18, u, vp9); z19 = VMACHI(z19, u, vp9);
  z10 = VADD(z10, VSHR(z9, HT_BRADIX));

  z11 = VADD(z11, VSHR(z10, HT_BRADIX)); z10 = VAND(z10, vbmask);
  z12 = VADD(z12, VSHR(z11, HT_BRADIX)); z11 = VAND(z11, vbmask);
  z13 = VADD(z13, VSHR(z12, HT_BRADIX)); z12 = VAND(z12, vbmask);
  z14 = VADD(z14, VSHR(z13, HT_BRADIX)); z13 = VAND(z13, vbmask);
  z15 = VADD(z15, VSHR(z14, HT_BRADIX)); z14 = VAND(z14, vbmask);
  z16 = VADD(z16, VSHR(z15, HT_BRADIX)); z15 = VAND(z15, vbmask);
  z17 = VADD(z17, VSHR(z16, HT_BRADIX)); z16 = VAND(z16, vbmask);
  z18 = VADD(z18, VSHR(z17, HT_BRADIX)); z17 = VAND(z17, vbmask);
  z19 = VADD(z19, VSHR(z18, HT_BRADIX)); z18 = VAND(z18, vbmask);

  // ---------------------------------------------------------------------------

  r[0] = z10; r[1] = z11; r[2] = z12; r[3] = z13; r[4] = z14; 
  r[5] = z15; r[6] = z16; r[7] = z17; r[8] = z18; r[9] = z19; 
}

// field exponentiation r = a^e mod 2p
// the exponent e is a *public* parameter and is the *same* for all 8 instances
// -> r in [0, 2p)
void gfp_pow_8x1w(htfe_t r, const htfe_t a, const uint64_t *e)
{
  htfe_t b;
  uint64_t t;
  int i, j;
  
  for (i = 0; i < HT_NWORDS; i++) {
    r[i] = VSET1(ht_montR[i]);
    b[i] = a[i];    
  }

  for (i = 0; i < 8; i++) {
    t = e[i];
    for (j = 0; j < 64; j++, t>>=1) {
      if (t&1) gfp_mul_8x1w(r, r, b);
      gfp_sqr_8x1w(b, b);
    }
  }
}

// field multiplicative inversion r = a^(-1) = a^(p-2) mod 2p
// -> r in [0, 2p)
void gfp_inv_8x1w(htfe_t r, const htfe_t a)
{
  gfp_pow_8x1w(r, a, u64_psub2);
}

// reduce the field element from [0, 2p) to [0, p)
// a in [0, 2p) -> r in [0, p)
void gfp_rdcp_8x1w(htfe_t r, const htfe_t a)
{
  __m512i a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3], a4 = a[4];
  __m512i a5 = a[5], a6 = a[6], a7 = a[7], a8 = a[8], a9 = a[9]; 
  __m512i r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, smask;
  const __m512i vp0 = VSET1(ht_p[0]), vp1 = VSET1(ht_p[1]);
  const __m512i vp2 = VSET1(ht_p[2]), vp3 = VSET1(ht_p[3]);
  const __m512i vp4 = VSET1(ht_p[4]), vp5 = VSET1(ht_p[5]);
  const __m512i vp6 = VSET1(ht_p[6]), vp7 = VSET1(ht_p[7]);
  const __m512i vp8 = VSET1(ht_p[8]), vp9 = VSET1(ht_p[9]);
  const __m512i vbmask = VSET1(HT_BMASK);

  // r = a - p
  r0 = VSUB(a0, vp0); r1 = VSUB(a1, vp1); r2 = VSUB(a2, vp2); r3 = VSUB(a3, vp3);  
  r4 = VSUB(a4, vp4); r5 = VSUB(a5, vp5); r6 = VSUB(a6, vp6); r7 = VSUB(a7, vp7);  
  r8 = VSUB(a8, vp8); r9 = VSUB(a9, vp9); 

  // check the current r is positive or negative 
  // carry propagation
  r1  = VADD(r1, VSRA(r0, HT_BRADIX)); r0  = VAND(r0, vbmask);
  r2  = VADD(r2, VSRA(r1, HT_BRADIX)); r1  = VAND(r1, vbmask);
  r3  = VADD(r3, VSRA(r2, HT_BRADIX)); r2  = VAND(r2, vbmask);
  r4  = VADD(r4, VSRA(r3, HT_BRADIX)); r3  = VAND(r3, vbmask);
  r5  = VADD(r5, VSRA(r4, HT_BRADIX)); r4  = VAND(r4, vbmask);
  r6  = VADD(r6, VSRA(r5, HT_BRADIX)); r5  = VAND(r5, vbmask);
  r7  = VADD(r7, VSRA(r6, HT_BRADIX)); r6  = VAND(r6, vbmask);
  r8  = VADD(r8, VSRA(r7, HT_BRADIX)); r7  = VAND(r7, vbmask);
  r9  = VADD(r9, VSRA(r8, HT_BRADIX)); r8  = VAND(r8, vbmask);

  // if r is positive, then the corresponding element in smask = 0; 
  // if r is negative, then the corresponding element in smask = all-1.
  smask = VSRA(r9, 63);
  // r = r + (p & smask), add either p or 0 to the current r
  r0 = VADD(r0, VAND(vp0, smask)); r1 = VADD(r1, VAND(vp1, smask));
  r2 = VADD(r2, VAND(vp2, smask)); r3 = VADD(r3, VAND(vp3, smask));
  r4 = VADD(r4, VAND(vp4, smask)); r5 = VADD(r5, VAND(vp5, smask));
  r6 = VADD(r6, VAND(vp6, smask)); r7 = VADD(r7, VAND(vp7, smask));
  r8 = VADD(r8, VAND(vp8, smask)); r9 = VADD(r9, VAND(vp9, smask));

  // carry propagation
  r1 = VADD(r1, VSHR(r0, HT_BRADIX)); r0 = VAND(r0, vbmask);
  r2 = VADD(r2, VSHR(r1, HT_BRADIX)); r1 = VAND(r1, vbmask);
  r3 = VADD(r3, VSHR(r2, HT_BRADIX)); r2 = VAND(r2, vbmask);
  r4 = VADD(r4, VSHR(r3, HT_BRADIX)); r3 = VAND(r3, vbmask);
  r5 = VADD(r5, VSHR(r4, HT_BRADIX)); r4 = VAND(r4, vbmask);
  r6 = VADD(r6, VSHR(r5, HT_BRADIX)); r5 = VAND(r5, vbmask);
  r7 = VADD(r7, VSHR(r6, HT_BRADIX)); r6 = VAND(r6, vbmask);
  r8 = VADD(r8, VSHR(r7, HT_BRADIX)); r7 = VAND(r7, vbmask);
  r9 = VADD(r9, VSHR(r8, HT_BRADIX)); r8 = VAND(r8, vbmask);
  r9 = VAND(r9, vbmask);

  r[0] = r0; r[1] = r1; r[2] = r2; r[3] = r3; r[4] = r4;  
  r[5] = r5; r[6] = r6; r[7] = r7; r[8] = r8; r[9] = r9; 
}

// set the field element r to be 0
// -> r = 0
void gfp_zero_8x1w(htfe_t r)
{
  r[0] = VZERO; r[1] = VZERO; r[2] = VZERO; r[3] = VZERO; r[4] = VZERO; 
  r[5] = VZERO; r[6] = VZERO; r[7] = VZERO; r[8] = VZERO; r[9] = VZERO; 
}

// convert an integer from number domain to Montgomery domain r = a * R^2 mod 2p
// -> r in [0, 2p)
void gfp_num2mont_8x1w(htfe_t r, const htfe_t a)
{
  int i;
  htfe_t vR2;

  for (i = 0; i < HT_NWORDS; i++) vR2[i] = VSET1(ht_montR2[i]);
  gfp_mul_8x1w(r, a, vR2);              // r = a * R^2 mod 2p
}

// convert an integer from Montgomery domain to number domain r = a * 1 mod 2p
// -> r in [0, p)
void gfp_mont2num_8x1w(htfe_t r, const htfe_t a)
{
  htfe_t vone;

  gfp_zero_8x1w(vone);                  // vone = 0
  vone[0] = VSET1(1);                   // vone = 1
  gfp_mul_8x1w(r, a, vone);             // r = a * 1 mod 2p
  gfp_rdcp_8x1w(r, r);                  // r = r mod p
}

// copy field element a to r
void gfp_copy_8x1w(htfe_t r, const htfe_t a)
{
  r[0] = a[0]; r[1] = a[1]; r[2] = a[2]; r[3] = a[3]; r[4] = a[4];  
  r[5] = a[5]; r[6] = a[6]; r[7] = a[7]; r[8] = a[8]; r[9] = a[9];  
}

// conditional move
// move field element a to r if b == 1; do not move if b == 0
void gfp_cmove_8x1w(htfe_t r, htfe_t a, const __m512i b)
{
  __m512i r0 = r[0], r1 = r[1], r2 = r[2], r3 = r[3], r4 = r[4];
  __m512i r5 = r[5], r6 = r[6], r7 = r[7], r8 = r[8], r9 = r[9];
  __m512i a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3], a4 = a[4];
  __m512i a5 = a[5], a6 = a[6], a7 = a[7], a8 = a[8], a9 = a[9]; 
  __m512i x0, x1, x2, x3, x4, x5, x6, x7, x8, x9;
  const __m512i xmask = VSUB(VZERO, VAND(b, VSET1(1)));

  // x = r ^ a
  x0 = VXOR(r0, a0); x1 = VXOR(r1, a1); x2 = VXOR(r2, a2); x3 = VXOR(r3, a3);
  x4 = VXOR(r4, a4); x5 = VXOR(r5, a5); x6 = VXOR(r6, a6); x7 = VXOR(r7, a7);
  x8 = VXOR(r8, a8); x9 = VXOR(r9, a9); 

  // x = (r ^ a) & xmask
  x0 = VAND(x0, xmask); x1 = VAND(x1, xmask); x2 = VAND(x2, xmask); x3 = VAND(x3, xmask); 
  x4 = VAND(x4, xmask); x5 = VAND(x5, xmask); x6 = VAND(x6, xmask); x7 = VAND(x7, xmask); 
  x8 = VAND(x8, xmask); x9 = VAND(x9, xmask); 

  // r = r ^ ((r ^ a) & xmask) = r ^ 0 or r ^ r ^ a = r or a
  r0 = VXOR(r0, x0); r1 = VXOR(r1, x1); r2 = VXOR(r2, x2); r3 = VXOR(r3, x3);
  r4 = VXOR(r4, x4); r5 = VXOR(r5, x5); r6 = VXOR(r6, x6); r7 = VXOR(r7, x7);
  r8 = VXOR(r8, x8); r9 = VXOR(r9, x9);   

  r[0] = r0; r[1] = r1; r[2] = r2; r[3] = r3; r[4] = r4;  
  r[5] = r5; r[6] = r6; r[7] = r7; r[8] = r8; r[9] = r9;
}

// conditional swap
// swap field elements a and r if b == 1; do not swap if b == 0
void gfp_cswap_8x1w(htfe_t r, htfe_t a, const __m512i b)
{
  __m512i r0 = r[0], r1 = r[1], r2 = r[2], r3 = r[3], r4 = r[4];
  __m512i r5 = r[5], r6 = r[6], r7 = r[7], r8 = r[8], r9 = r[9];
  __m512i a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3], a4 = a[4];
  __m512i a5 = a[5], a6 = a[6], a7 = a[7], a8 = a[8], a9 = a[9]; 
  __m512i x0, x1, x2, x3, x4, x5, x6, x7, x8, x9;
  const __m512i xmask = VSUB(VZERO, VAND(b, VSET1(1)));

  // x = r ^ a
  x0 = VXOR(r0, a0); x1 = VXOR(r1, a1); x2 = VXOR(r2, a2); x3 = VXOR(r3, a3);
  x4 = VXOR(r4, a4); x5 = VXOR(r5, a5); x6 = VXOR(r6, a6); x7 = VXOR(r7, a7);
  x8 = VXOR(r8, a8); x9 = VXOR(r9, a9); 

  // x = (r ^ a) & mask
  x0 = VAND(x0, xmask); x1 = VAND(x1, xmask); x2 = VAND(x2, xmask); x3 = VAND(x3, xmask); 
  x4 = VAND(x4, xmask); x5 = VAND(x5, xmask); x6 = VAND(x6, xmask); x7 = VAND(x7, xmask); 
  x8 = VAND(x8, xmask); x9 = VAND(x9, xmask); 

  // r = r ^ ((r ^ a) & mask) = r ^ 0 or r ^ r ^ a = r or a
  r0 = VXOR(r0, x0); r1 = VXOR(r1, x1); r2 = VXOR(r2, x2); r3 = VXOR(r3, x3);
  r4 = VXOR(r4, x4); r5 = VXOR(r5, x5); r6 = VXOR(r6, x6); r7 = VXOR(r7, x7);
  r8 = VXOR(r8, x8); r9 = VXOR(r9, x9);  

  // a = a ^ ((r ^ a) & mask) = a ^ 0 or a ^ r ^ a = a or r
  a0 = VXOR(a0, x0); a1 = VXOR(a1, x1); a2 = VXOR(a2, x2); a3 = VXOR(a3, x3);
  a4 = VXOR(a4, x4); a5 = VXOR(a5, x5); a6 = VXOR(a6, x6); a7 = VXOR(a7, x7);
  a8 = VXOR(a8, x8); a9 = VXOR(a9, x9);  


  r[0] = r0; r[1] = r1; r[2] = r2; r[3] = r3; r[4] = r4;  
  r[5] = r5; r[6] = r6; r[7] = r7; r[8] = r8; r[9] = r9;

  a[0] = a0; a[1] = a1; a[2] = a2; a[3] = a3; a[4] = a4;  
  a[5] = a5; a[6] = a6; a[7] = a7; a[8] = a8; a[9] = a9;
}

// check whether the field element is a square in the field  
// if a is     a square in the field, return 1; 
// if a is not a square in the field, return 0.
__m512i gfp_issqr_8x1w(const htfe_t a)
{  
  htfe_t t0, t1;
  __m512i r = VZERO;
  int i;

  // compute r = a^((p-1)/2) - 1 
  // r is 0 if a is a square; r is non-0 if a is not a square
  gfp_copy_8x1w(t0, a);                 // t0 = a
  gfp_pow_8x1w(t1, t0, u64_pdiv2);      // t1 = a^((p-1)/2)
  gfp_rdcp_8x1w(t1, t1);                // t1 in [0, p) and strictly radix-52 now 
  for (i = 0; i < HT_NWORDS; i++)       // r = t1 - 1
    r = VOR(r, VSUB(t1[i], VSET1(ht_montR[i])));
  
  r = VAND(r, VSET1(HT_BMASK));         // r is 52-bit now 
  r = VSUB(VZERO, r);                   // r = 0 - r
  r = VSHR(r, 63);                      // r = r >> 63

  // now r == 0 means "a" is a square; r == 1 means "a" is not a square 
  // so we need to XOR r
  r = VXOR(r, VSET1(1));                // r = r ^ 1

  return r;
}

// check whether the field element is zero 
// if a is     zero, return 1; 
// if a is not zero, return 0.
__m512i gfp_iszero_8x1w(const htfe_t a)
{
  __m512i a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3], a4 = a[4];
  __m512i a5 = a[5], a6 = a[6], a7 = a[7], a8 = a[8], a9 = a[9]; 
  __m512i t = VZERO;

  // t = OR all the limbs of a
  t = VOR(t, a0); t = VOR(t, a1); t = VOR(t, a2); t = VOR(t, a3);   
  t = VOR(t, a4); t = VOR(t, a5); t = VOR(t, a6); t = VOR(t, a7);  
  t = VOR(t, a8); t = VOR(t, a9);  

  // if a == 0 then t is all-0; otherwise t is non-0
  t = VAND(t, VSET1(HT_BMASK));         // t is 52-bit now 
  t = VSUB(VZERO, t);                   // t is all-0 (if a is zero) or negative (if a is non-zero)
  t = VSHR(t, 63);                      // t is 0 (zero) or 1 (not zero)
  t = VXOR(t, VSET1(1));                // t = t ^ 1

  return t;
}

// -----------------------------------------------------------------------------
// (2x4)-way prime-field operations 

// 2-way *integer* <add | sub> with *simple* carry propagation <r | s> = <a+b | c-d+2p> 
// a, b, c, d in [0, 2p) -> r, s in [0, 4p)
void gfp_addsubi_2x4w(llfe_t rs, const llfe_t ac, const llfe_t bd)
{
  const __m512i ac0 = ac[0], ac1 = ac[1], ac2 = ac[2];
  const __m512i bd0 = bd[0], bd1 = bd[1], bd2 = bd[2];
  __m512i pp0 = VSET(ll_pmul2[9] , ll_pmul2[6], ll_pmul2[3], ll_pmul2[0], ll_pmul2[9] , ll_pmul2[6], ll_pmul2[3], ll_pmul2[0]);
  __m512i pp1 = VSET(ll_pmul2[10], ll_pmul2[7], ll_pmul2[4], ll_pmul2[1], ll_pmul2[10], ll_pmul2[7], ll_pmul2[4], ll_pmul2[1]);
  __m512i pp2 = VSET(ll_pmul2[11], ll_pmul2[8], ll_pmul2[5], ll_pmul2[2], ll_pmul2[11], ll_pmul2[8], ll_pmul2[5], ll_pmul2[2]);
  const __m512i bp0 = VMBLEND(0x0F, bd[0], pp0);
  const __m512i bp1 = VMBLEND(0x0F, bd[1], pp1);
  const __m512i bp2 = VMBLEND(0x0F, bd[2], pp2);
  const __m512i vbmask = VSET1(LL_BMASK);
  __m512i rs0, rs1, rs2, carry;

  // r = a + b | s = c + 2p
  rs0 = VADD(ac0, bp0); rs1 = VADD(ac1, bp1); rs2 = VADD(ac2, bp2);

  // r = r - 0 | s = s - d
  // rs0 = VSUB(rs0, nd0);  rs1 = VSUB(rs1, nd1); rs2 = VSUB(rs2, nd2);
  rs0 = VMSUB(rs0, 0x0F, rs0, bd0);
  rs1 = VMSUB(rs1, 0x0F, rs1, bd1);
  rs2 = VMSUB(rs2, 0x0F, rs2, bd2);

  // *simple* carry propagation (some limbs are finally 44-bit not 43-bit)
  carry = VSRA(rs0, LL_BRADIX); rs0 = VAND(rs0, vbmask); rs1 = VADD(rs1, carry);
  carry = VSRA(rs1, LL_BRADIX); rs1 = VAND(rs1, vbmask); rs2 = VADD(rs2, carry);
  carry = VSRA(rs2, LL_BRADIX); rs2 = VAND(rs2, vbmask); 
  rs0 = VMADD(rs0, 0xEE, rs0, VPERM(carry, 0x93));

  rs[0] = rs0; rs[1] = rs1; rs[2] = rs2;
}

// 2-way *integer* <sub | add> with *simple* carry propagation <r | s> = <a-b+2p | c+d>
// a, b, c, d in [0, 2p) -> r, s in [0, 4p)
void gfp_subaddi_2x4w(llfe_t rs, const llfe_t ac, const llfe_t bd)
{
  const __m512i ac0 = ac[0], ac1 = ac[1], ac2 = ac[2];
  const __m512i bd0 = bd[0], bd1 = bd[1], bd2 = bd[2];
  __m512i pp0 = VSET(ll_pmul2[9] , ll_pmul2[6], ll_pmul2[3], ll_pmul2[0], ll_pmul2[9] , ll_pmul2[6], ll_pmul2[3], ll_pmul2[0]);
  __m512i pp1 = VSET(ll_pmul2[10], ll_pmul2[7], ll_pmul2[4], ll_pmul2[1], ll_pmul2[10], ll_pmul2[7], ll_pmul2[4], ll_pmul2[1]);
  __m512i pp2 = VSET(ll_pmul2[11], ll_pmul2[8], ll_pmul2[5], ll_pmul2[2], ll_pmul2[11], ll_pmul2[8], ll_pmul2[5], ll_pmul2[2]);
  const __m512i pd0 = VMBLEND(0x0F, pp0, bd[0]);
  const __m512i pd1 = VMBLEND(0x0F, pp1, bd[1]);
  const __m512i pd2 = VMBLEND(0x0F, pp2, bd[2]);
  const __m512i vbmask = VSET1(LL_BMASK);
  __m512i rs0, rs1, rs2, carry;

  // r = a + 2p | s = c + d
  rs0 = VADD(ac0, pd0); rs1 = VADD(ac1, pd1); rs2 = VADD(ac2, pd2);

  // r = r - b | s = s - 0
  // rs0 = VSUB(rs0, bn0);  rs1 = VSUB(rs1, bn1); rs2 = VSUB(rs2, bn2);
  rs0 = VMSUB(rs0, 0xF0, rs0, bd0);
  rs1 = VMSUB(rs1, 0xF0, rs1, bd1);
  rs2 = VMSUB(rs2, 0xF0, rs2, bd2);

  // *simple* carry propagation (some limbs are finally 44-bit not 43-bit)
  carry = VSRA(rs0, LL_BRADIX); rs0 = VAND(rs0, vbmask); rs1 = VADD(rs1, carry);
  carry = VSRA(rs1, LL_BRADIX); rs1 = VAND(rs1, vbmask); rs2 = VADD(rs2, carry);
  carry = VSRA(rs2, LL_BRADIX); rs2 = VAND(rs2, vbmask); 
  rs0 = VMADD(rs0, 0xEE, rs0, VPERM(carry, 0x93));

  rs[0] = rs0; rs[1] = rs1; rs[2] = rs2;
}

// 2-way *modular* <add | sub> with *complete* carry propagation <r | s> = <a+b | c-d> mod 2p
// a, b, c, d in [0, 2p) -> r, s in [0, 2p)
void gfp_addsubc_2x4w(llfe_t rs, const llfe_t ac, const llfe_t bd)
{
  const __m512i ac0 = ac[0], ac1 = ac[1], ac2 = ac[2];
  const __m512i bd0 = bd[0], bd1 = bd[1], bd2 = bd[2];
  const __m512i pp0 = VSET(ll_pmul2[9] , ll_pmul2[6], ll_pmul2[3], ll_pmul2[0], ll_pmul2[9] , ll_pmul2[6], ll_pmul2[3], ll_pmul2[0]);
  const __m512i pp1 = VSET(ll_pmul2[10], ll_pmul2[7], ll_pmul2[4], ll_pmul2[1], ll_pmul2[10], ll_pmul2[7], ll_pmul2[4], ll_pmul2[1]);
  const __m512i pp2 = VSET(ll_pmul2[11], ll_pmul2[8], ll_pmul2[5], ll_pmul2[2], ll_pmul2[11], ll_pmul2[8], ll_pmul2[5], ll_pmul2[2]);
  const __m512i pd0 = VMBLEND(0x0F, pp0, bd[0]);
  const __m512i pd1 = VMBLEND(0x0F, pp1, bd[1]);
  const __m512i pd2 = VMBLEND(0x0F, pp2, bd[2]);
  const __m512i vbmask = VSET1(LL_BMASK);
  __m512i rs0, rs1, rs2, carry, smask;

  // r = a + b | s = c + 0
  // rs0 = VADD(ac0, bn0); rs1 = VADD(ac1, bn1); rs2 = VADD(ac2, bn2);
  rs0 = VMADD(ac0, 0xF0, ac0, bd0);
  rs1 = VMADD(ac1, 0xF0, ac1, bd1);
  rs2 = VMADD(ac2, 0xF0, ac2, bd2);

  // r = r - 2p | s = s - d
  rs0 = VSUB(rs0, pd0);  rs1 = VSUB(rs1, pd1); rs2 = VSUB(rs2, pd2);

  // check r and s are respectively postive or negative 
  carry = VSRA(rs0, LL_BRADIX);
  rs0 = VMAND(rs0, 0x11, rs0, vbmask);
  rs1 = VMADD(rs1, 0x11, rs1, carry);
  carry = VSRA(rs1, LL_BRADIX);
  rs1 = VMAND(rs1, 0x11, rs1, vbmask);
  rs2 = VMADD(rs2, 0x11, rs2, carry);
  carry = VSRA(rs2, LL_BRADIX);
  rs2 = VMAND(rs2, 0x11, rs2, vbmask);
  rs0 = VMADD(rs0, 0x22, rs0, VSHUF(carry,0x4E));
  carry = VSRA(rs0, LL_BRADIX);
  rs0 = VMAND(rs0, 0x22, rs0, vbmask);
  rs1 = VMADD(rs1, 0x22, rs1, carry);
  carry = VSRA(rs1, LL_BRADIX);
  rs1 = VMAND(rs1, 0x22, rs1, vbmask);
  rs2 = VMADD(rs2, 0x22, rs2, carry);
  carry = VSRA(rs2, LL_BRADIX);
  rs2 = VMAND(rs2, 0x22, rs2, vbmask);
  rs0 = VMADD(rs0, 0x44, rs0, VPERM(carry, 0xD8));
  carry = VSRA(rs0, LL_BRADIX);
  rs0 = VMAND(rs0, 0x44, rs0, vbmask);
  rs1 = VMADD(rs1, 0x44, rs1, carry);
  carry = VSRA(rs1, LL_BRADIX);
  rs1 = VMAND(rs1, 0x44, rs1, vbmask);
  rs2 = VMADD(rs2, 0x44, rs2, carry);
  carry = VSRA(rs2, LL_BRADIX);
  rs2 = VMAND(rs2, 0x44, rs2, vbmask);
  rs0 = VMADD(rs0, 0x88, rs0, VSHUF(carry,0x4E));
  carry = VSRA(rs0, LL_BRADIX);
  rs0 = VMAND(rs0, 0x88, rs0, vbmask);
  rs1 = VMADD(rs1, 0x88, rs1, carry);
  carry = VSRA(rs1, LL_BRADIX);
  rs1 = VMAND(rs1, 0x88, rs1, vbmask);
  rs2 = VMADD(rs2, 0x88, rs2, carry);
  smask = VMOR(VZERO, 0x88, VZERO, rs2);
  smask = VSRA(smask, 63);            // smask = all-0/-1 0 0 0 | all-0/-1 0 0 0
  smask = VPERM(smask, 0xFF);         // smask = all-0/-1 | all-0/-1

  // add 2p to r/s or not 
  rs0 = VADD(rs0, VAND(pp0, smask));
  rs1 = VADD(rs1, VAND(pp1, smask));
  rs2 = VADD(rs2, VAND(pp2, smask));

  // carry propagation
  carry = VSRA(rs0, LL_BRADIX);
  rs0 = VMAND(rs0, 0x11, rs0, vbmask);
  rs1 = VMADD(rs1, 0x11, rs1, carry);
  carry = VSRA(rs1, LL_BRADIX);
  rs1 = VMAND(rs1, 0x11, rs1, vbmask);
  rs2 = VMADD(rs2, 0x11, rs2, carry);
  carry = VSRA(rs2, LL_BRADIX);
  rs2 = VMAND(rs2, 0x11, rs2, vbmask);
  rs0 = VMADD(rs0, 0x22, rs0, VSHUF(carry,0x4E));
  carry = VSRA(rs0, LL_BRADIX);
  rs0 = VMAND(rs0, 0x22, rs0, vbmask);
  rs1 = VMADD(rs1, 0x22, rs1, carry);
  carry = VSRA(rs1, LL_BRADIX);
  rs1 = VMAND(rs1, 0x22, rs1, vbmask);
  rs2 = VMADD(rs2, 0x22, rs2, carry);
  carry = VSRA(rs2, LL_BRADIX);
  rs2 = VMAND(rs2, 0x22, rs2, vbmask);
  rs0 = VMADD(rs0, 0x44, rs0, VPERM(carry, 0xD8));
  carry = VSRA(rs0, LL_BRADIX);
  rs0 = VMAND(rs0, 0x44, rs0, vbmask);
  rs1 = VMADD(rs1, 0x44, rs1, carry);
  carry = VSRA(rs1, LL_BRADIX);
  rs1 = VMAND(rs1, 0x44, rs1, vbmask);
  rs2 = VMADD(rs2, 0x44, rs2, carry);
  carry = VSRA(rs2, LL_BRADIX);
  rs2 = VMAND(rs2, 0x44, rs2, vbmask);
  rs0 = VMADD(rs0, 0x88, rs0, VSHUF(carry,0x4E));
  carry = VSRA(rs0, LL_BRADIX);
  rs0 = VMAND(rs0, 0x88, rs0, vbmask);
  rs1 = VMADD(rs1, 0x88, rs1, carry);
  carry = VSRA(rs1, LL_BRADIX);
  rs1 = VMAND(rs1, 0x88, rs1, vbmask);
  rs2 = VMADD(rs2, 0x88, rs2, carry);

  rs[0] = rs0; rs[1] = rs1; rs[2] = rs2;
}

// 2-way *modular* <sub | add> with *complete* carry propagation <r | s> = <a-b | c+d> mod 2p
// a, b, c, d in [0, 2p) -> r, s in [0, 2p)
void gfp_subaddc_2x4w(llfe_t rs, const llfe_t ac, const llfe_t bd)
{
  const __m512i ac0 = ac[0], ac1 = ac[1], ac2 = ac[2];
  const __m512i bd0 = bd[0], bd1 = bd[1], bd2 = bd[2];
  const __m512i pp0 = VSET(ll_pmul2[9] , ll_pmul2[6], ll_pmul2[3], ll_pmul2[0], ll_pmul2[9] , ll_pmul2[6], ll_pmul2[3], ll_pmul2[0]);
  const __m512i pp1 = VSET(ll_pmul2[10], ll_pmul2[7], ll_pmul2[4], ll_pmul2[1], ll_pmul2[10], ll_pmul2[7], ll_pmul2[4], ll_pmul2[1]);
  const __m512i pp2 = VSET(ll_pmul2[11], ll_pmul2[8], ll_pmul2[5], ll_pmul2[2], ll_pmul2[11], ll_pmul2[8], ll_pmul2[5], ll_pmul2[2]);
  const __m512i bp0 = VMBLEND(0x0F, bd[0], pp0);
  const __m512i bp1 = VMBLEND(0x0F, bd[1], pp1);
  const __m512i bp2 = VMBLEND(0x0F, bd[2], pp2);
  const __m512i vbmask = VSET1(LL_BMASK);
  __m512i rs0, rs1, rs2, carry, smask;

  // r = a + 0 | s = c + d
  // rs0 = VADD(ac0, nd0); rs1 = VADD(ac1, nd1); rs2 = VADD(ac2, nd2);
  rs0 = VMADD(ac0, 0x0F, ac0, bd0);
  rs1 = VMADD(ac1, 0x0F, ac1, bd1);
  rs2 = VMADD(ac2, 0x0F, ac2, bd2);

  // r = r - b | s = s - 2p
  rs0 = VSUB(rs0, bp0); rs1 = VSUB(rs1, bp1); rs2 = VSUB(rs2, bp2);

  // check r and s are respectively postive or negative 
  carry = VSRA(rs0, LL_BRADIX);
  rs0 = VMAND(rs0, 0x11, rs0, vbmask);
  rs1 = VMADD(rs1, 0x11, rs1, carry);
  carry = VSRA(rs1, LL_BRADIX);
  rs1 = VMAND(rs1, 0x11, rs1, vbmask);
  rs2 = VMADD(rs2, 0x11, rs2, carry);
  carry = VSRA(rs2, LL_BRADIX);
  rs2 = VMAND(rs2, 0x11, rs2, vbmask);
  rs0 = VMADD(rs0, 0x22, rs0, VSHUF(carry,0x4E));
  carry = VSRA(rs0, LL_BRADIX);
  rs0 = VMAND(rs0, 0x22, rs0, vbmask);
  rs1 = VMADD(rs1, 0x22, rs1, carry);
  carry = VSRA(rs1, LL_BRADIX);
  rs1 = VMAND(rs1, 0x22, rs1, vbmask);
  rs2 = VMADD(rs2, 0x22, rs2, carry);
  carry = VSRA(rs2, LL_BRADIX);
  rs2 = VMAND(rs2, 0x22, rs2, vbmask);
  rs0 = VMADD(rs0, 0x44, rs0, VPERM(carry, 0xD8));
  carry = VSRA(rs0, LL_BRADIX);
  rs0 = VMAND(rs0, 0x44, rs0, vbmask);
  rs1 = VMADD(rs1, 0x44, rs1, carry);
  carry = VSRA(rs1, LL_BRADIX);
  rs1 = VMAND(rs1, 0x44, rs1, vbmask);
  rs2 = VMADD(rs2, 0x44, rs2, carry);
  carry = VSRA(rs2, LL_BRADIX);
  rs2 = VMAND(rs2, 0x44, rs2, vbmask);
  rs0 = VMADD(rs0, 0x88, rs0, VSHUF(carry,0x4E));
  carry = VSRA(rs0, LL_BRADIX);
  rs0 = VMAND(rs0, 0x88, rs0, vbmask);
  rs1 = VMADD(rs1, 0x88, rs1, carry);
  carry = VSRA(rs1, LL_BRADIX);
  rs1 = VMAND(rs1, 0x88, rs1, vbmask);
  rs2 = VMADD(rs2, 0x88, rs2, carry);
  smask = VMOR(VZERO, 0x88, VZERO, rs2);
  smask = VSRA(smask, 63);            // smask = all-0/-1 0 0 0 | all-0/-1 0 0 0
  smask = VPERM(smask, 0xFF);         // smask = all-0/-1 | all-0/-1

  // add 2p to r/s or not 
  rs0 = VADD(rs0, VAND(pp0, smask));
  rs1 = VADD(rs1, VAND(pp1, smask));
  rs2 = VADD(rs2, VAND(pp2, smask));

  // carry propagation
  carry = VSRA(rs0, LL_BRADIX);
  rs0 = VMAND(rs0, 0x11, rs0, vbmask);
  rs1 = VMADD(rs1, 0x11, rs1, carry);
  carry = VSRA(rs1, LL_BRADIX);
  rs1 = VMAND(rs1, 0x11, rs1, vbmask);
  rs2 = VMADD(rs2, 0x11, rs2, carry);
  carry = VSRA(rs2, LL_BRADIX);
  rs2 = VMAND(rs2, 0x11, rs2, vbmask);
  rs0 = VMADD(rs0, 0x22, rs0, VSHUF(carry,0x4E));
  carry = VSRA(rs0, LL_BRADIX);
  rs0 = VMAND(rs0, 0x22, rs0, vbmask);
  rs1 = VMADD(rs1, 0x22, rs1, carry);
  carry = VSRA(rs1, LL_BRADIX);
  rs1 = VMAND(rs1, 0x22, rs1, vbmask);
  rs2 = VMADD(rs2, 0x22, rs2, carry);
  carry = VSRA(rs2, LL_BRADIX);
  rs2 = VMAND(rs2, 0x22, rs2, vbmask);
  rs0 = VMADD(rs0, 0x44, rs0, VPERM(carry, 0xD8));
  carry = VSRA(rs0, LL_BRADIX);
  rs0 = VMAND(rs0, 0x44, rs0, vbmask);
  rs1 = VMADD(rs1, 0x44, rs1, carry);
  carry = VSRA(rs1, LL_BRADIX);
  rs1 = VMAND(rs1, 0x44, rs1, vbmask);
  rs2 = VMADD(rs2, 0x44, rs2, carry);
  carry = VSRA(rs2, LL_BRADIX);
  rs2 = VMAND(rs2, 0x44, rs2, vbmask);
  rs0 = VMADD(rs0, 0x88, rs0, VSHUF(carry,0x4E));
  carry = VSRA(rs0, LL_BRADIX);
  rs0 = VMAND(rs0, 0x88, rs0, vbmask);
  rs1 = VMADD(rs1, 0x88, rs1, carry);
  carry = VSRA(rs1, LL_BRADIX);
  rs1 = VMAND(rs1, 0x88, rs1, vbmask);
  rs2 = VMADD(rs2, 0x88, rs2, carry);

  rs[0] = rs0; rs[1] = rs1; rs[2] = rs2;
}



#define RADIX LL_BRADIX
#define BROADCAST_LOWEST(A) _mm512_permutex_epi64(A, 0b00000000)
// H<-VZERO; L<- (H <<(52 - 43)) +(L >> 43)
#define NEXTLIMB(H, L) \
tmp = _mm512_maskz_permutex_epi64(0x77, L##0, 0x39);\
H##0 = _mm512_add_epi64(H##0, _mm512_srli_epi64(L##0, 52));\
H##0 = _mm512_slli_epi64(H##0, 52 - RADIX);\
L##0 = _mm512_add_epi64(H##0, L##1);\
H##1 = _mm512_slli_epi64(H##1, 52 - RADIX);\
L##1 = _mm512_add_epi64(H##1, L##2);\
H##2 = _mm512_slli_epi64(H##2, 52 - RADIX);\
L##2 = _mm512_add_epi64(H##2, _mm512_and_epi64(tmp, VSET1(((1LL<<52) - 1))));\
H##0 = VZERO; H##1 = VZERO; H##2 = VZERO;

#define CAT(A, B) A##B
#define MADLO(DST, ADDER, MUL1, MUL2)   DST##0 = _mm512_madd52lo_epu64(ADDER##0, MUL1##0, MUL2);\
                                        DST##1 = _mm512_madd52lo_epu64(ADDER##1, MUL1##1, MUL2);\
                                        DST##2 = _mm512_madd52lo_epu64(ADDER##2, MUL1##2, MUL2);
#define MADHI(DST, ADDER, MUL1, MUL2)   DST##0 = _mm512_madd52hi_epu64(ADDER##0, MUL1##0, MUL2);\
                                        DST##1 = _mm512_madd52hi_epu64(ADDER##1, MUL1##1, MUL2);\
                                        DST##2 = _mm512_madd52hi_epu64(ADDER##2, MUL1##2, MUL2);

#define MUL(I)\
MADLO(sl, sl, a, m##I); MADHI(sh, sh, a, m##I);\
q = BROADCAST_LOWEST(sl0);\
MADLO(msl, msl, r##I, q); MADHI(msh, msh, r##I, q);\
NEXTLIMB(sh, sl);

// Montgomery multiplication r = a * b mod 2p
// multiplication (operand-scanning) interleaved with reduction (operand-scanning)
// -> r in [0, 2p)

void gfp_mul_2x4w(llfe_t c, const llfe_t a, const llfe_t b) {
    __m512i a0=a[0], a1 = a[1], a2 = a[2];
    __m512i b0=b[0], b1 = b[1], b2 = b[2];
    //each limb of b
    __m512i m0 = _mm512_permutex_epi64(b0, 0x00), m3 = _mm512_permutex_epi64(b0, 0x55), m6 = _mm512_permutex_epi64(b0, 0xAA), m9 = _mm512_permutex_epi64(b0, 0xFF);
    __m512i m1 = _mm512_permutex_epi64(b1, 0x00), m4 = _mm512_permutex_epi64(b1, 0x55), m7 = _mm512_permutex_epi64(b1, 0xAA), m10= _mm512_permutex_epi64(b1, 0xFF);
    __m512i m2 = _mm512_permutex_epi64(b2, 0x00), m5 = _mm512_permutex_epi64(b2, 0x55), m8 = _mm512_permutex_epi64(b2, 0xAA), m11= _mm512_permutex_epi64(b2, 0xFF);
    //__m512i r%d0 = _mm512_load_epi64(r_i_mont[%d] + 0), r%d1 = _mm512_load_epi64(r_i_mont[%d] + 8),r%d2 = _mm512_load_epi64(r_i_mont[%d] + 16);
    //Load constants
    __m512i r00 = _mm512_load_epi64(r_i_mont[9] + 0), r01 = _mm512_load_epi64(r_i_mont[9] + 8),r02 = _mm512_load_epi64(r_i_mont[9] + 16);
    __m512i r10 = _mm512_load_epi64(r_i_mont[8] + 0), r11 = _mm512_load_epi64(r_i_mont[8] + 8),r12 = _mm512_load_epi64(r_i_mont[8] + 16);
    __m512i r20 = _mm512_load_epi64(r_i_mont[7] + 0), r21 = _mm512_load_epi64(r_i_mont[7] + 8),r22 = _mm512_load_epi64(r_i_mont[7] + 16);
    __m512i r30 = _mm512_load_epi64(r_i_mont[6] + 0), r31 = _mm512_load_epi64(r_i_mont[6] + 8),r32 = _mm512_load_epi64(r_i_mont[6] + 16);
    __m512i r40 = _mm512_load_epi64(r_i_mont[5] + 0), r41 = _mm512_load_epi64(r_i_mont[5] + 8),r42 = _mm512_load_epi64(r_i_mont[5] + 16);
    __m512i r50 = _mm512_load_epi64(r_i_mont[4] + 0), r51 = _mm512_load_epi64(r_i_mont[4] + 8),r52 = _mm512_load_epi64(r_i_mont[4] + 16);
    __m512i r60 = _mm512_load_epi64(r_i_mont[3] + 0), r61 = _mm512_load_epi64(r_i_mont[3] + 8),r62 = _mm512_load_epi64(r_i_mont[3] + 16);
    __m512i r70 = _mm512_load_epi64(r_i_mont[2] + 0), r71 = _mm512_load_epi64(r_i_mont[2] + 8),r72 = _mm512_load_epi64(r_i_mont[2] + 16);
    __m512i r80 = _mm512_load_epi64(r_i_mont[1] + 0), r81 = _mm512_load_epi64(r_i_mont[1] + 8),r82 = _mm512_load_epi64(r_i_mont[1] + 16);
    __m512i r90 = _mm512_load_epi64(r_i_mont[0] + 0), r91 = _mm512_load_epi64(r_i_mont[0] + 8),r92 = _mm512_load_epi64(r_i_mont[0] + 16);

    const __m512i p0 = VSET(ll_p[9],  ll_p[6], ll_p[3], ll_p[0], ll_p[9],  ll_p[6], ll_p[3], ll_p[0]);
    const __m512i p1 = VSET(ll_p[10], ll_p[7], ll_p[4], ll_p[1], ll_p[10], ll_p[7], ll_p[4], ll_p[1]);
    const __m512i p2 = VSET(ll_p[11], ll_p[8], ll_p[5], ll_p[2], ll_p[11], ll_p[8], ll_p[5], ll_p[2]);
    
    //sh: Sum, high half
    //sl: Sum, low half

    
    __m512i sh0 = VZERO, sl0 = VZERO, msh0 = VZERO, msl0 = VZERO;
    __m512i sh1 = VZERO, sl1 = VZERO, msh1 = VZERO, msl1 = VZERO;
    __m512i sh2 = VZERO, sl2 = VZERO, msh2 = VZERO, msl2 = VZERO;
    __m512i q, tmp, vw = VSET1(LL_MONTW), vbmask = VSET1(LL_BMASK);
    //0
    MUL(0); MUL(1); MUL(2); MUL(3); MUL(4); MUL(5); MUL(6); MUL(7); MUL(8); MUL(9);

    sl0 = _mm512_add_epi64(sl0, msl0); sl1 = _mm512_add_epi64(sl1, msl1); sl2 = _mm512_add_epi64(sl2, msl2);
    sh0 = msh0; sh1 = msh1; sh2 = msh2;
    msh0 = VZERO, msl0 = VZERO;
    msh1 = VZERO, msl1 = VZERO;
    msh2 = VZERO, msl2 = VZERO;
    MADLO(sl, sl, a, m10); MADHI(sh, sh, a, m10);
    q = BROADCAST_LOWEST(sl0);
    q = _mm512_madd52lo_epu64(VZERO, q, vw);
    q = _mm512_and_epi64(q, vbmask);
    MADLO(sl, sl, p, q); MADHI(sh, sh, p, q);
    //shift
    tmp = _mm512_maskz_permutex_epi64(0x77, sl0, 0x39);
    sh0 = _mm512_slli_epi64(sh0, 52 - RADIX);
    sh0 = _mm512_add_epi64(sh0, _mm512_srli_epi64(sl0, RADIX));
    sl0 = _mm512_add_epi64(sh0, sl1);
    sh1 = _mm512_slli_epi64(sh1, 52 - RADIX);
    sl1 = _mm512_add_epi64(sh1, sl2);
    sh2 = _mm512_slli_epi64(sh2, 52 - RADIX);
    sl2 = _mm512_add_epi64(sh2, _mm512_and_epi64(tmp, vbmask));
    sh0 = VZERO; sh1 = VZERO; sh2 = VZERO;  
    MADLO(sl, sl, a, m11); MADHI(sh, sh, a, m11);
    q = BROADCAST_LOWEST(sl0);
    q = _mm512_madd52lo_epu64(VZERO, q, vw);
    q = _mm512_and_epi64(q, vbmask);
    MADLO(sl, sl, p, q); MADHI(sh, sh, p, q);
    tmp = _mm512_maskz_permutex_epi64(0x77, sl0, 0x39);
    sh0 = _mm512_slli_epi64(sh0, 52 - RADIX);
    sh0 = _mm512_add_epi64(sh0, _mm512_srli_epi64(sl0, RADIX));
    sl0 = _mm512_add_epi64(sh0, sl1);
    sh1 = _mm512_slli_epi64(sh1, 52 - RADIX);
    sl1 = _mm512_add_epi64(sh1, sl2);
    sh2 = _mm512_slli_epi64(sh2, 52 - RADIX);
    sl2 = _mm512_add_epi64(sh2, _mm512_and_epi64(tmp, vbmask));

    sh2 = _mm512_srli_epi64(sl1, RADIX);
    sh1 = _mm512_srli_epi64(sl0, RADIX);
    sh0 = _mm512_maskz_permutex_epi64(0xEE, sl2, 0x93);
    sh0 = _mm512_srli_epi64(sh0, RADIX);
    sl2 = _mm512_and_epi64(sl2, vbmask);
    sl1 = _mm512_and_epi64(sl1, vbmask);
    sl0 = _mm512_and_epi64(sl0, vbmask);
    sl2 = _mm512_add_epi64(sl2, sh2);
    sl1 = _mm512_add_epi64(sl1, sh1);
    sl0 = _mm512_add_epi64(sl0, sh0);
    c[0] = sl0; c[1] = sl1; c[2] = sl2;
}
#define RED(I)\
q = BROADCAST_LOWEST(sl0);\
MADLO(msl, msl, r##I, q); MADHI(msh, msh, r##I, q);\
NEXTLIMB(sh, sl);
// Montgomery squaring r = a^2 mod 2p
// squaring (operand-scanning) interleaved with reduction (operand-scanning)
// -> r in [0, 2p)
void gfp_sqr_2x4w(llfe_t c, const llfe_t b) {
    __m512i b0=b[0], b1 = b[1], b2 = b[2];
    __m512i b1_2 = _mm512_add_epi64(b1, b1);
    __m512i b2_2 = _mm512_add_epi64(b2, b2);
    //each limb of b
    __m512i m0 = _mm512_permutex_epi64(b0, 0x00), m3 = _mm512_permutex_epi64(b0, 0x55), m6 = _mm512_permutex_epi64(b0, 0xAA), m9 = _mm512_permutex_epi64(b0, 0xFF);
    __m512i m1 = _mm512_permutex_epi64(b1, 0x00), m4 = _mm512_permutex_epi64(b1, 0x55), m7 = _mm512_permutex_epi64(b1, 0xAA), m10= _mm512_permutex_epi64(b1, 0xFF);
    __m512i m2 = _mm512_permutex_epi64(b2, 0x00), m5 = _mm512_permutex_epi64(b2, 0x55), m8 = _mm512_permutex_epi64(b2, 0xAA), m11= _mm512_permutex_epi64(b2, 0xFF);
    //__m512i r%d0 = _mm512_load_epi64(r_i_mont[%d] + 0), r%d1 = _mm512_load_epi64(r_i_mont[%d] + 8),r%d2 = _mm512_load_epi64(r_i_mont[%d] + 16);
    //Load constants
    __m512i r00 = _mm512_load_epi64(r_i_mont[9] + 0), r01 = _mm512_load_epi64(r_i_mont[9] + 8),r02 = _mm512_load_epi64(r_i_mont[9] + 16);
    __m512i r10 = _mm512_load_epi64(r_i_mont[8] + 0), r11 = _mm512_load_epi64(r_i_mont[8] + 8),r12 = _mm512_load_epi64(r_i_mont[8] + 16);
    __m512i r20 = _mm512_load_epi64(r_i_mont[7] + 0), r21 = _mm512_load_epi64(r_i_mont[7] + 8),r22 = _mm512_load_epi64(r_i_mont[7] + 16);
    __m512i r30 = _mm512_load_epi64(r_i_mont[6] + 0), r31 = _mm512_load_epi64(r_i_mont[6] + 8),r32 = _mm512_load_epi64(r_i_mont[6] + 16);
    __m512i r40 = _mm512_load_epi64(r_i_mont[5] + 0), r41 = _mm512_load_epi64(r_i_mont[5] + 8),r42 = _mm512_load_epi64(r_i_mont[5] + 16);
    __m512i r50 = _mm512_load_epi64(r_i_mont[4] + 0), r51 = _mm512_load_epi64(r_i_mont[4] + 8),r52 = _mm512_load_epi64(r_i_mont[4] + 16);
    __m512i r60 = _mm512_load_epi64(r_i_mont[3] + 0), r61 = _mm512_load_epi64(r_i_mont[3] + 8),r62 = _mm512_load_epi64(r_i_mont[3] + 16);
    __m512i r70 = _mm512_load_epi64(r_i_mont[2] + 0), r71 = _mm512_load_epi64(r_i_mont[2] + 8),r72 = _mm512_load_epi64(r_i_mont[2] + 16);
    __m512i r80 = _mm512_load_epi64(r_i_mont[1] + 0), r81 = _mm512_load_epi64(r_i_mont[1] + 8),r82 = _mm512_load_epi64(r_i_mont[1] + 16);
    __m512i r90 = _mm512_load_epi64(r_i_mont[0] + 0), r91 = _mm512_load_epi64(r_i_mont[0] + 8),r92 = _mm512_load_epi64(r_i_mont[0] + 16);

    const __m512i p0 = VSET(ll_p[9],  ll_p[6], ll_p[3], ll_p[0], ll_p[9],  ll_p[6], ll_p[3], ll_p[0]);
    const __m512i p1 = VSET(ll_p[10], ll_p[7], ll_p[4], ll_p[1], ll_p[10], ll_p[7], ll_p[4], ll_p[1]);
    const __m512i p2 = VSET(ll_p[11], ll_p[8], ll_p[5], ll_p[2], ll_p[11], ll_p[8], ll_p[5], ll_p[2]);
    
    //sh: Sum, high half
    //sl: Sum, low half

    __m512i sh0 = VZERO, sl0 = VZERO, msh0 = VZERO, msl0 = VZERO;
    __m512i sh1 = VZERO, sl1 = VZERO, msh1 = VZERO, msl1 = VZERO;
    __m512i sh2 = VZERO, sl2 = VZERO, msh2 = VZERO, msl2 = VZERO;
    __m512i q, tmp, vw = VSET1(LL_MONTW), vbmask = VSET1(LL_BMASK);
    //0
    
    //MUL(0);
    sl0 = _mm512_madd52lo_epu64(sl0, b0, m0);
    sl1 = _mm512_madd52lo_epu64(sl1, b1_2, m0);
    sl2 = _mm512_madd52lo_epu64(sl2, b2_2, m0);
    sh0 = _mm512_madd52hi_epu64(sh0, b0, m0);
    sh1 = _mm512_madd52hi_epu64(sh1, b1_2, m0);
    sh2 = _mm512_madd52hi_epu64(sh2, b2_2, m0);
    RED(0);
    
    // MUL(1); 
    sl1 = _mm512_madd52lo_epu64(sl1, b1, m1);
    sl2 = _mm512_madd52lo_epu64(sl2, b2_2, m1);
    sh1 = _mm512_madd52hi_epu64(sh1, b1, m1);
    sh2 = _mm512_madd52hi_epu64(sh2, b2_2, m1);
    RED(1);
    //MUL(2)
    sl2 = _mm512_madd52lo_epu64(sl2, b2, m2);
    sh2 = _mm512_madd52hi_epu64(sh2, b2, m2);
    RED(2);
    //MUL(3);
    sl0 = _mm512_madd52lo_epu64(sl0, b0, m3);
    sl1 = _mm512_madd52lo_epu64(sl1, b1_2, m3);
    sl2 = _mm512_madd52lo_epu64(sl2, b2_2, m3);
    sh0 = _mm512_madd52hi_epu64(sh0, b0, m3);
    sh1 = _mm512_madd52hi_epu64(sh1, b1_2, m3);
    sh2 = _mm512_madd52hi_epu64(sh2, b2_2, m3);
    RED(3);
    //MUL(4);
    sl1 = _mm512_madd52lo_epu64(sl1, b1, m4);
    sl2 = _mm512_madd52lo_epu64(sl2, b2_2, m4);
    sh1 = _mm512_madd52hi_epu64(sh1, b1, m4);
    sh2 = _mm512_madd52hi_epu64(sh2, b2_2, m4);
    RED(4);
    //MUL(5);
    sl2 = _mm512_madd52lo_epu64(sl2, b2, m5);
    sh2 = _mm512_madd52hi_epu64(sh2, b2, m5);
    RED(5);
    //MUL(6);
    sl0 = _mm512_madd52lo_epu64(sl0, b0, m6);
    sl1 = _mm512_madd52lo_epu64(sl1, b1_2, m6);
    sl2 = _mm512_madd52lo_epu64(sl2, b2_2, m6);
    sh0 = _mm512_madd52hi_epu64(sh0, b0, m6);
    sh1 = _mm512_madd52hi_epu64(sh1, b1_2, m6);
    sh2 = _mm512_madd52hi_epu64(sh2, b2_2, m6);
    RED(6);
    //MUL(7);
    sl1 = _mm512_madd52lo_epu64(sl1, b1, m7);
    sl2 = _mm512_madd52lo_epu64(sl2, b2_2, m7);
    sh1 = _mm512_madd52hi_epu64(sh1, b1, m7);
    sh2 = _mm512_madd52hi_epu64(sh2, b2_2, m7);
    RED(7);
    //MUL(8);
    sl2 = _mm512_madd52lo_epu64(sl2, b2, m8);
    sh2 = _mm512_madd52hi_epu64(sh2, b2, m8);
    RED(8);
    //MUL(9);
    sl0 = _mm512_madd52lo_epu64(sl0, b0, m9);
    sl1 = _mm512_madd52lo_epu64(sl1, b1_2, m9);
    sl2 = _mm512_madd52lo_epu64(sl2, b2_2, m9);
    sh0 = _mm512_madd52hi_epu64(sh0, b0, m9);
    sh1 = _mm512_madd52hi_epu64(sh1, b1_2, m9);
    sh2 = _mm512_madd52hi_epu64(sh2, b2_2, m9);
    RED(9);

    sl0 = _mm512_add_epi64(sl0, msl0); sl1 = _mm512_add_epi64(sl1, msl1); sl2 = _mm512_add_epi64(sl2, msl2);
    sh0 = msh0; sh1 = msh1; sh2 = msh2;
    msh0 = VZERO, msl0 = VZERO;
    msh1 = VZERO, msl1 = VZERO;
    msh2 = VZERO, msl2 = VZERO;
    //MADLO(sl, sl, a, m10); MADHI(sh, sh, a, m10);
    sl1 = _mm512_madd52lo_epu64(sl1, b1, m10);
    sl2 = _mm512_madd52lo_epu64(sl2, b2_2, m10);
    sh1 = _mm512_madd52hi_epu64(sh1, b1, m10);
    sh2 = _mm512_madd52hi_epu64(sh2, b2_2, m10);
    //RED(10)
    q = BROADCAST_LOWEST(sl0);
    q = _mm512_madd52lo_epu64(VZERO, q, vw);
    q = _mm512_and_epi64(q, vbmask);
    MADLO(sl, sl, p, q); MADHI(sh, sh, p, q);
    //shift
    tmp = _mm512_maskz_permutex_epi64(0x77, sl0, 0x39);
    sh0 = _mm512_slli_epi64(sh0, 52 - RADIX);
    sh0 = _mm512_add_epi64(sh0, _mm512_srli_epi64(sl0, RADIX));
    sl0 = _mm512_add_epi64(sh0, sl1);
    sh1 = _mm512_slli_epi64(sh1, 52 - RADIX);
    sl1 = _mm512_add_epi64(sh1, sl2);
    sh2 = _mm512_slli_epi64(sh2, 52 - RADIX);
    sl2 = _mm512_add_epi64(sh2, _mm512_and_epi64(tmp, vbmask));
    sh0 = VZERO; sh1 = VZERO; sh2 = VZERO;  
    //MADLO(sl, sl, a, m11); MADHI(sh, sh, a, m11);
    sl2 = _mm512_madd52lo_epu64(sl2, b2, m11);
    sh2 = _mm512_madd52hi_epu64(sh2, b2, m11);
    //RED(11);
    q = BROADCAST_LOWEST(sl0);
    q = _mm512_madd52lo_epu64(VZERO, q, vw);
    q = _mm512_and_epi64(q, vbmask);
    MADLO(sl, sl, p, q); MADHI(sh, sh, p, q);
    tmp = _mm512_maskz_permutex_epi64(0x77, sl0, 0x39);
    sh0 = _mm512_slli_epi64(sh0, 52 - RADIX);
    sh0 = _mm512_add_epi64(sh0, _mm512_srli_epi64(sl0, RADIX));
    sl0 = _mm512_add_epi64(sh0, sl1);
    sh1 = _mm512_slli_epi64(sh1, 52 - RADIX);
    sl1 = _mm512_add_epi64(sh1, sl2);
    sh2 = _mm512_slli_epi64(sh2, 52 - RADIX);
    sl2 = _mm512_add_epi64(sh2, _mm512_and_epi64(tmp, vbmask));

    sh2 = _mm512_srli_epi64(sl1, RADIX);
    sh1 = _mm512_srli_epi64(sl0, RADIX);
    sh0 = _mm512_maskz_permutex_epi64(0xEE, sl2, 0x93);
    sh0 = _mm512_srli_epi64(sh0, RADIX);
    sl2 = _mm512_and_epi64(sl2, vbmask);
    sl1 = _mm512_and_epi64(sl1, vbmask);
    sl0 = _mm512_and_epi64(sl0, vbmask);
    sl2 = _mm512_add_epi64(sl2, sh2);
    sl1 = _mm512_add_epi64(sl1, sh1);
    sl0 = _mm512_add_epi64(sl0, sh0);
    
    c[0] = sl0; c[1] = sl1; c[2] = sl2;

}
// field exponentiation r = a^e mod 2p
// the exponent e is a *public* parameter
// -> r in [0, 2p)
void gfp_pow_2x4w(llfe_t r, const llfe_t a, const uint64_t *e)
{
  llfe_t z0, z1, z2, one;
  uint64_t t;
  uint8_t m;
  int i, j;

  one[0] = VSET(ll_montR[9] , ll_montR[6], ll_montR[3], ll_montR[0], ll_montR[9] , ll_montR[6], ll_montR[3], ll_montR[0]);
  one[1] = VSET(ll_montR[10], ll_montR[7], ll_montR[4], ll_montR[1], ll_montR[10], ll_montR[7], ll_montR[4], ll_montR[1]);
  one[2] = VSET(ll_montR[11], ll_montR[8], ll_montR[5], ll_montR[2], ll_montR[11], ll_montR[8], ll_montR[5], ll_montR[2]);

  gfp_copy_2x4w(r, one);                // r  = 1   | 1
  vec_permzl_2x4w(z0, a);               // z0 = 0   | a
  gfp_sqr_2x4w(z1, z0);                 // z1 = 0   | a^2
  vec_permlh_2x4w(z1, z1);              // z1 = a^2 | 0
  vec_blend_2x4w(z0, z1, z0, 0x0F);     // z0 = a^2 | a

  for (i = 0; i < 8; i++) {
    t = e[i];

    // TODO: a fixed chain?
    for (j = 0; j < 64; j+=2, t>>=2) {
      // if-else statement is based on the public parameter
      if ((t&3) == 3) gfp_mul_2x4w(r, r, z0);
      else if ((t&3) == 1) {
        vec_blend_2x4w(z1, one, z0, 0x0F);  // z1 = 1  | z0
        gfp_mul_2x4w(r, r, z1);
      }
      else if ((t&3) == 2) {
        vec_blend_2x4w(z1, z0, one, 0x0F);  // z1 = z0 | 1
        gfp_mul_2x4w(r, r, z1);
      }
      gfp_sqr_2x4w(z0, z0);             // z0 = z0^4 | z0^2
      gfp_sqr_2x4w(z0, z0);             // z0 = z0^8 | z0^4
    }
  }

  vec_permzh_2x4w(z1, r);                     
  vec_permzl_2x4w(r, r);
  gfp_mul_2x4w(r, r, z1);
  gfp_carryp_2x4w(r);                   // make r strictly radix-43
}

// field multiplicative inversion r = a^(-1) = a^(p-2) mod 2p
// -> r in [0, 2p)
void gfp_inv_2x4w(llfe_t r, const llfe_t a)
{
  gfp_pow_2x4w(r, a, u64_psub2);
}

// reduce the field element from [0, 2p) to [0, p)
// a in [0, 2p) -> r in [0, p)
void gfp_rdcp_2x4w(llfe_t r, const llfe_t a)
{
  const __m512i a0 = a[0], a1 = a[1], a2 = a[2];
  __m512i pp0 = VSET(ll_p[9] , ll_p[6], ll_p[3], ll_p[0], ll_p[9] , ll_p[6], ll_p[3], ll_p[0]);
  __m512i pp1 = VSET(ll_p[10], ll_p[7], ll_p[4], ll_p[1], ll_p[10], ll_p[7], ll_p[4], ll_p[1]);
  __m512i pp2 = VSET(ll_p[11], ll_p[8], ll_p[5], ll_p[2], ll_p[11], ll_p[8], ll_p[5], ll_p[2]);
  const __m512i vbmask = VSET1(LL_BMASK);
  __m512i r0, r1, r2, carry, smask;

  // r = a - p
  r0 = VSUB(a0, pp0); r1 = VSUB(a1, pp1); r2 = VSUB(a2, pp2);

  // check r is postive or negative 
  carry = VSRA(r0, LL_BRADIX);
  r0 = VMAND(r0, 0x11, r0, vbmask);
  r1 = VMADD(r1, 0x11, r1, carry);
  carry = VSRA(r1, LL_BRADIX);
  r1 = VMAND(r1, 0x11, r1, vbmask);
  r2 = VMADD(r2, 0x11, r2, carry);
  carry = VSRA(r2, LL_BRADIX);
  r2 = VMAND(r2, 0x11, r2, vbmask);
  r0 = VMADD(r0, 0x22, r0, VSHUF(carry,0x4E));
  carry = VSRA(r0, LL_BRADIX);
  r0 = VMAND(r0, 0x22, r0, vbmask);
  r1 = VMADD(r1, 0x22, r1, carry);
  carry = VSRA(r1, LL_BRADIX);
  r1 = VMAND(r1, 0x22, r1, vbmask);
  r2 = VMADD(r2, 0x22, r2, carry);
  carry = VSRA(r2, LL_BRADIX);
  r2 = VMAND(r2, 0x22, r2, vbmask);
  r0 = VMADD(r0, 0x44, r0, VPERM(carry, 0xD8));
  carry = VSRA(r0, LL_BRADIX);
  r0 = VMAND(r0, 0x44, r0, vbmask);
  r1 = VMADD(r1, 0x44, r1, carry);
  carry = VSRA(r1, LL_BRADIX);
  r1 = VMAND(r1, 0x44, r1, vbmask);
  r2 = VMADD(r2, 0x44, r2, carry);
  carry = VSRA(r2, LL_BRADIX);
  r2 = VMAND(r2, 0x44, r2, vbmask);
  r0 = VMADD(r0, 0x88, r0, VSHUF(carry,0x4E));
  carry = VSRA(r0, LL_BRADIX);
  r0 = VMAND(r0, 0x88, r0, vbmask);
  r1 = VMADD(r1, 0x88, r1, carry);
  carry = VSRA(r1, LL_BRADIX);
  r1 = VMAND(r1, 0x88, r1, vbmask);
  r2 = VMADD(r2, 0x88, r2, carry);
  smask = VMOR(VZERO, 0x88, VZERO, r2);
  smask = VSRA(smask, 63);            // smask = all-0/-1 0 0 0 | all-0/-1 0 0 0
  smask = VPERM(smask, 0xFF);         // smask = all-0/-1 | all-0/-1

  // add p to r/s or not 
  r0 = VADD(r0, VAND(pp0, smask));
  r1 = VADD(r1, VAND(pp1, smask));
  r2 = VADD(r2, VAND(pp2, smask));

  // *complete* carry propagation
  carry = VSRA(r0, LL_BRADIX);
  r0 = VMAND(r0, 0x11, r0, vbmask);
  r1 = VMADD(r1, 0x11, r1, carry);
  carry = VSRA(r1, LL_BRADIX);
  r1 = VMAND(r1, 0x11, r1, vbmask);
  r2 = VMADD(r2, 0x11, r2, carry);
  carry = VSRA(r2, LL_BRADIX);
  r2 = VMAND(r2, 0x11, r2, vbmask);
  r0 = VMADD(r0, 0x22, r0, VSHUF(carry,0x4E));
  carry = VSRA(r0, LL_BRADIX);
  r0 = VMAND(r0, 0x22, r0, vbmask);
  r1 = VMADD(r1, 0x22, r1, carry);
  carry = VSRA(r1, LL_BRADIX);
  r1 = VMAND(r1, 0x22, r1, vbmask);
  r2 = VMADD(r2, 0x22, r2, carry);
  carry = VSRA(r2, LL_BRADIX);
  r2 = VMAND(r2, 0x22, r2, vbmask);
  r0 = VMADD(r0, 0x44, r0, VPERM(carry, 0xD8));
  carry = VSRA(r0, LL_BRADIX);
  r0 = VMAND(r0, 0x44, r0, vbmask);
  r1 = VMADD(r1, 0x44, r1, carry);
  carry = VSRA(r1, LL_BRADIX);
  r1 = VMAND(r1, 0x44, r1, vbmask);
  r2 = VMADD(r2, 0x44, r2, carry);
  carry = VSRA(r2, LL_BRADIX);
  r2 = VMAND(r2, 0x44, r2, vbmask);
  r0 = VMADD(r0, 0x88, r0, VSHUF(carry,0x4E));
  carry = VSRA(r0, LL_BRADIX);
  r0 = VMAND(r0, 0x88, r0, vbmask);
  r1 = VMADD(r1, 0x88, r1, carry);
  carry = VSRA(r1, LL_BRADIX);
  r1 = VMAND(r1, 0x88, r1, vbmask);
  r2 = VMADD(r2, 0x88, r2, carry);

  r[0] = r0; r[1] = r1; r[2] = r2;
}

// a complete carry propagation to make r strictly radix-43
void gfp_carryp_2x4w(llfe_t r)
{
  const __m512i vbmask = VSET1(LL_BMASK);
  __m512i r0 = r[0], r1 = r[1], r2 = r[2], carry;

  // carry propagation
  carry = VSRA(r0, LL_BRADIX);
  r0 = VMAND(r0, 0x11, r0, vbmask);
  r1 = VMADD(r1, 0x11, r1, carry);
  carry = VSRA(r1, LL_BRADIX);
  r1 = VMAND(r1, 0x11, r1, vbmask);
  r2 = VMADD(r2, 0x11, r2, carry);
  carry = VSRA(r2, LL_BRADIX);
  r2 = VMAND(r2, 0x11, r2, vbmask);
  r0 = VMADD(r0, 0x22, r0, VSHUF(carry,0x4E));
  carry = VSRA(r0, LL_BRADIX);
  r0 = VMAND(r0, 0x22, r0, vbmask);
  r1 = VMADD(r1, 0x22, r1, carry);
  carry = VSRA(r1, LL_BRADIX);
  r1 = VMAND(r1, 0x22, r1, vbmask);
  r2 = VMADD(r2, 0x22, r2, carry);
  carry = VSRA(r2, LL_BRADIX);
  r2 = VMAND(r2, 0x22, r2, vbmask);
  r0 = VMADD(r0, 0x44, r0, VPERM(carry, 0xD8));
  carry = VSRA(r0, LL_BRADIX);
  r0 = VMAND(r0, 0x44, r0, vbmask);
  r1 = VMADD(r1, 0x44, r1, carry);
  carry = VSRA(r1, LL_BRADIX);
  r1 = VMAND(r1, 0x44, r1, vbmask);
  r2 = VMADD(r2, 0x44, r2, carry);
  carry = VSRA(r2, LL_BRADIX);
  r2 = VMAND(r2, 0x44, r2, vbmask);
  r0 = VMADD(r0, 0x88, r0, VSHUF(carry,0x4E));
  carry = VSRA(r0, LL_BRADIX);
  r0 = VMAND(r0, 0x88, r0, vbmask);
  r1 = VMADD(r1, 0x88, r1, carry);
  carry = VSRA(r1, LL_BRADIX);
  r1 = VMAND(r1, 0x88, r1, vbmask);
  r2 = VMADD(r2, 0x88, r2, carry);

  r[0] = r0; r[1] = r1; r[2] = r2;
}

// set the field element r to be 0
// -> r = 0
void gfp_zero_2x4w(llfe_t r)
{
  r[0] = VZERO; 
  r[1] = VZERO; 
  r[2] = VZERO; 
}

// convert an integer from number domain to Montgomery domain r = a * R^2 mod 2p
// -> r in [0, 2p)
void gfp_num2mont_2x4w(llfe_t r, const llfe_t a)
{
  llfe_t vR2;
  int i;

  vR2[0] = VSET(ll_montR2[9],  ll_montR2[6], ll_montR2[3], ll_montR2[0], ll_montR2[9],  ll_montR2[6], ll_montR2[3], ll_montR2[0]);
  vR2[1] = VSET(ll_montR2[10], ll_montR2[7], ll_montR2[4], ll_montR2[1], ll_montR2[10], ll_montR2[7], ll_montR2[4], ll_montR2[1]);
  vR2[2] = VSET(ll_montR2[11], ll_montR2[8], ll_montR2[5], ll_montR2[2], ll_montR2[11], ll_montR2[8], ll_montR2[5], ll_montR2[2]);

  gfp_mul_2x4w(r, a, vR2);              // r = a * R^2 mod 2p
  gfp_carryp_2x4w(r);                   // make r strictly radix-43
}

// convert an integer from Montgomery domain to number domain r = a * 1 mod 2p
// -> r in [0, p)
void gfp_mont2num_2x4w(llfe_t r, const llfe_t a)
{
  llfe_t one;

  one[0] = VSET(0, 0, 0, 1, 0, 0, 0, 1);
  one[1] = VZERO;
  one[2] = VZERO;

  gfp_mul_2x4w(r, a, one);              // r = a * 1 mod 2p
  gfp_rdcp_2x4w(r, r);                  // make r in [0, p) and strictly radix-43
}

// copy field element a to r
void gfp_copy_2x4w(llfe_t r, const llfe_t a)
{
  r[0] = a[0]; r[1] = a[1]; r[2] = a[2];
}

// conditional move
// move field element a to r if b == 1; do not move if b == 0
void gfp_cmove_2x4w(llfe_t r, llfe_t a, const uint8_t b)
{
  __m512i r0 = r[0], r1 = r[1], r2 = r[2];
  __m512i a0 = a[0], a1 = a[1], a2 = a[2];  
  __m512i x0, x1, x2;
  const __m512i xmask = VSET1(0-(b&1));

  x0 = VXOR(r0, a0);    x1 = VXOR(r1, a1);    x2 = VXOR(r2, a2);
  x0 = VAND(x0, xmask); x1 = VAND(x1, xmask); x2 = VAND(x2, xmask);
  r0 = VXOR(r0, x0);    r1 = VXOR(r1, x1);    r2 = VXOR(r2, x2);

  r[0] = r0; r[1] = r1; r[2] = r2;
}

// conditional swap
// swap field elements a and r if b == 1; do not swap if b == 0
void gfp_cswap_2x4w(llfe_t r, llfe_t a, const uint8_t b)
{
  __m512i r0 = r[0], r1 = r[1], r2 = r[2];
  __m512i a0 = a[0], a1 = a[1], a2 = a[2];  
  __m512i x0, x1, x2;
  const __m512i xmask = VSET1(0-(b&1));

  x0 = VXOR(r0, a0); x1 = VXOR(r1, a1); x2 = VXOR(r2, a2);
  x0 = VAND(x0, xmask); x1 = VAND(x1, xmask); x2 = VAND(x2, xmask);
  r0 = VXOR(r0, x0); r1 = VXOR(r1, x1); r2 = VXOR(r2, x2);
  a0 = VXOR(a0, x0); a1 = VXOR(a1, x1); a2 = VXOR(a2, x2);

  r[0] = r0; r[1] = r1; r[2] = r2;
  a[0] = a0; a[1] = a1; a[2] = a2;
}

// check whether the field element is a square in the field  
// if a is     a square in the field, return 1; 
// if a is not a square in the field, return 0.
uint8_t gfp_issqr_2x4w(const llfe_t a)
{
  llfe_t t0, t1, vR;
  __m512i r = VZERO;
  uint64_t z;
  int i;

  // compute r = a^((p-1)/2) - 1 
  // r is 0 if a is a square; r is non-0 if a is not a square
  gfp_copy_2x4w(t0, a);                 // t0 = a 
  gfp_pow_2x4w(t1, t0, u64_pdiv2);      // t1 = a^((p-1)/2)
  gfp_rdcp_2x4w(t1, t1);                // make t1 in [0, p) and strictly radix-43

  // vR = 0 | R
  vR[0] = VSET(0, 0, 0, 0, ll_montR[9],  ll_montR[6], ll_montR[3], ll_montR[0]);
  vR[1] = VSET(0, 0, 0, 0, ll_montR[10], ll_montR[7], ll_montR[4], ll_montR[1]);
  vR[2] = VSET(0, 0, 0, 0, ll_montR[11], ll_montR[8], ll_montR[5], ll_montR[2]);

  // r = a^((p-1)/2) - 1
  r = VOR(r, VSUB(t1[0], vR[0]));
  r = VOR(r, VSUB(t1[1], vR[1]));
  r = VOR(r, VSUB(t1[2], vR[2]));

  z = VORRDC(r);
  z = z & LL_BMASK;                     
  z = 0 - z;                            
  z = z >> 63;

  // now z == 0 means "a" is a square; z == 1 means "a" is not a square 
  // so we need to XOR z
  z = z^1;

  return (uint8_t) (z&1);
}

// check whether the field element is zero 
// if a is     zero, return 1; 
// if a is not zero, return 0.
// a must in [0, p) and strictly radix-43 -> 
uint8_t gfp_iszero_2x4w(const llfe_t a)
{
  __m512i t;
  uint64_t r;

  t = VOR(a[0], a[1]);      // t = OR all the limbs of a
  t = VOR(t, a[2]);

  r = VORRDC(t);
  r = r & (LL_BMASK<<1);    // some limbs might be 44-bit
  r = 0 - r;                // r is all-0 (if a is zero) or negative (if a is non-zero)
  r = r >> 63;              // r is 0 (zero) or 1 (not zero)
  r = r ^ 1;                // r = r ^ 1

  return (uint8_t) (r&1);
}

// permute vectors from <h | l> to <l | h>
void vec_permlh_2x4w(llfe_t r, const llfe_t a)
{
  __m512i a0 = a[0], a1 = a[1], a2 = a[2];
  __m512i r0, r1, r2;

  // r = h|l|h|l >> 256 = l|h
  r0 = VALIGNR(a0, a0, 4);
  r1 = VALIGNR(a1, a1, 4);
  r2 = VALIGNR(a2, a2, 4);

  r[0] = r0; r[1] = r1; r[2] = r2;
}

// permute vectors from <h | l> to <0 | l>
void vec_permzl_2x4w(llfe_t r, const llfe_t a)
{
  __m512i a0 = a[0], a1 = a[1], a2 = a[2];
  __m512i r0, r1, r2;

  // r = h^h | l = 0 | l 
  r0 = VMXOR(a0, 0xF0, a0, a0);
  r1 = VMXOR(a1, 0xF0, a1, a1);
  r2 = VMXOR(a2, 0xF0, a2, a2);

  r[0] = r0; r[1] = r1; r[2] = r2;
}

// permute vectors from <h | l> to <0 | h>
void vec_permzh_2x4w(llfe_t r, const llfe_t a)
{
  __m512i a0 = a[0], a1 = a[1], a2 = a[2];
  __m512i r0, r1, r2;

  // r = h|l|h|l >> 256 = l|h -> 0|h
  r0 = VZALIGNR(0x0F, a0, a0, 4);
  r1 = VZALIGNR(0x0F, a1, a1, 4);
  r2 = VZALIGNR(0x0F, a2, a2, 4);

  r[0] = r0; r[1] = r1; r[2] = r2;
}

// permute vectors from <h | l> to <l | l>
void vec_permll_2x4w(llfe_t r, const llfe_t a)
{
  __m512i a0 = a[0], a1 = a[1], a2 = a[2];
  __m512i r0, r1, r2;
  __m512i mask = VSET(3, 2, 1, 0, 3, 2, 1, 0);

  r0 = VPERMV(mask, a0);
  r1 = VPERMV(mask, a1);
  r2 = VPERMV(mask, a2);

  r[0] = r0; r[1] = r1; r[2] = r2;
}

// permute vectors from <h | l> to <h | h>
void vec_permhh_2x4w(llfe_t r, const llfe_t a)
{
  __m512i a0 = a[0], a1 = a[1], a2 = a[2];
  __m512i r0, r1, r2;
  __m512i mask = VSET(7, 6, 5, 4, 7, 6, 5, 4);

  r0 = VPERMV(mask, a0);
  r1 = VPERMV(mask, a1);
  r2 = VPERMV(mask, a2);

  r[0] = r0; r[1] = r1; r[2] = r2;
}

// blend vectors a and b into r according to the mask 
void vec_blend_2x4w(llfe_t r, const llfe_t a, const llfe_t b, const uint8_t mask)
{
  __m512i a0 = a[0], a1 = a[1], a2 = a[2]; 
  __m512i b0 = b[0], b1 = b[1], b2 = b[2];
  __m512i r0, r1, r2;

  r0 = VMBLEND(mask, a0, b0);
  r1 = VMBLEND(mask, a1, b1);
  r2 = VMBLEND(mask, a2, b2);

  r[0] = r0; r[1] = r1; r[2] = r2;
}

// -----------------------------------------------------------------------------
// other prime-field operations 

// check whether two 32-bit unsinged integers are equal
// if two integers are     equal, return 1;
// if two integers are not equal, return 0.
uint8_t u32_iseql(const uint32_t a, const uint32_t b)
{
  uint32_t r = 0;
  unsigned char *ta = (unsigned char *)&a;
  unsigned char *tb = (unsigned char *)&b;
  r = (ta[0] ^ tb[0]) | (ta[1] ^ tb[1]) | (ta[2] ^ tb[2]) |  (ta[3] ^ tb[3]);
  r = (-r);
  r = r >> 31;
  return (uint8_t)(1-r);
}

// a complete carry propagation for mpi43
void mpi43_carryp(uint64_t *a)
{
  int i;

  for (i = 0; i < LL_NWORDS-1; i++) {
    a[i+1] += a[i]>>LL_BRADIX;
    a[i] &= LL_BMASK;
  }
}
