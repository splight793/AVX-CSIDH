/**
 *******************************************************************************
 * @version 0.0.1
 * @date 2021-07-01
 * @copyright Copyright © 2021 by University of Luxembourg.
 * @author Developed at SnT APSIA by: Hao Cheng.
 *******************************************************************************
 */

#ifndef _UTILS_H
#define _UTILS_H

#include <stdio.h>
#include <stdint.h>
#include "gfparith.h"

void mpi_print(const char *c, const uint64_t *a, int len);
void mpi_conv_64to52(uint64_t *r, const uint64_t *a, int rlen, int alen);
void mpi_conv_52to64(uint64_t *r, const uint64_t *a, int rlen, int alen);
void mpi_conv_52to43(uint64_t *r, const uint64_t *a, int rlen, int alen);
void mpi_conv_43to52(uint64_t *r, const uint64_t *a, int rlen, int alen);
void mpi_conv_43to64(uint64_t *r, const uint64_t *a, int rlen, int alen);
void mpi_conv_64to43(uint64_t *r, const uint64_t *a, int rlen, int alen);

#endif