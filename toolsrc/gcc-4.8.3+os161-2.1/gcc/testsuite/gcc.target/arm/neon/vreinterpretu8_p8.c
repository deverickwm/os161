/* Test the `vreinterpretu8_p8' ARM Neon intrinsic.  */
/* This file was autogenerated by neon-testgen.  */

/* { dg-do assemble } */
/* { dg-require-effective-target arm_neon_ok } */
/* { dg-options "-save-temps -O0" } */
/* { dg-add-options arm_neon } */

#include "arm_neon.h"

void test_vreinterpretu8_p8 (void)
{
  uint8x8_t out_uint8x8_t;
  poly8x8_t arg0_poly8x8_t;

  out_uint8x8_t = vreinterpret_u8_p8 (arg0_poly8x8_t);
}

/* { dg-final { cleanup-saved-temps } } */
