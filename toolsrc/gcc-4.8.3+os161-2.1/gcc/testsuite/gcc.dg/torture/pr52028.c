/* { dg-do run } */
/* { dg-require-effective-target int32plus } */
/* { dg-options "-ftree-loop-distribution" } */

#define CAST_LONG unsigned int
typedef struct cast_key_st
{
  CAST_LONG data[32];
} CAST_KEY;
#define CAST_exp(l,A,a,n) \
	A[n/4]=l; \
	a[n+3]=(l    )&0xff; \
	a[n+2]=(l>> 8)&0xff; \
	a[n+1]=(l>>16)&0xff; \
	a[n+0]=(l>>24)&0xff;

CAST_LONG CAST_S_table[1024];

#define S4 (CAST_S_table + 000)
#define S5 (CAST_S_table + 256)
#define S6 (CAST_S_table + 512)
#define S7 (CAST_S_table + 768)

void
CAST_set_key (CAST_KEY * key)
{
  CAST_LONG x[16];
  CAST_LONG z[16];
  CAST_LONG k[32];
  CAST_LONG X[4] = {0,0,0,0}, Z[4];
  CAST_LONG l, *K = k;
  int i;
  for (i = 0; i < 16; i++)
    x[i] = 0;
  for (;;)
    {
      l = X[0] ^ S4[x[13]] ^ S5[x[15]] ^ S6[x[12]] ^ S7[x[14]] ^ S6[x[8]];
      CAST_exp (l, Z, z, 0);
      CAST_exp (l, Z, z, 4);
      CAST_exp (l, Z, z, 8);
      CAST_exp (l, Z, z, 12);
      K[0] = S4[z[8]] ^ S5[z[9]] ^ S6[z[7]] ^ S7[z[6]] ^ S4[z[2]];
      K[1] = S4[z[10]] ^ S5[z[11]] ^ S6[z[5]] ^ S7[z[4]] ^ S5[z[6]];
      K[2] = S4[z[12]] ^ S5[z[13]] ^ S6[z[3]] ^ S7[z[2]] ^ S6[z[9]];
      K[3] = S4[z[14]] ^ S5[z[15]] ^ S6[z[1]] ^ S7[z[0]] ^ S7[z[12]];
      K[4] = S4[x[3]] ^ S5[x[2]] ^ S6[x[12]] ^ S7[x[13]] ^ S4[x[8]];
      K[5] = S4[x[1]] ^ S5[x[0]] ^ S6[x[14]] ^ S7[x[15]] ^ S5[x[13]];
      K[6] = S4[x[7]] ^ S5[x[6]] ^ S6[x[8]] ^ S7[x[9]] ^ S6[x[3]];
      K[7] = S4[x[5]] ^ S5[x[4]] ^ S6[x[10]] ^ S7[x[11]] ^ S7[x[7]];
      K[8] = S4[z[3]] ^ S5[z[2]] ^ S6[z[12]] ^ S7[z[13]] ^ S4[z[9]];
      K[9] = S4[z[1]] ^ S5[z[0]] ^ S6[z[14]] ^ S7[z[15]] ^ S5[z[12]];
      K[10] = S4[z[7]] ^ S5[z[6]] ^ S6[z[8]] ^ S7[z[9]] ^ S6[z[2]];
      K[11] = S4[z[5]] ^ S5[z[4]] ^ S6[z[10]] ^ S7[z[11]] ^ S7[z[6]];
      l = Z[2] ^ S4[z[5]] ^ S5[z[7]] ^ S6[z[4]] ^ S7[z[6]] ^ S6[z[0]];
      CAST_exp (l, X, x, 0);
      K[12] = S4[x[8]] ^ S5[x[9]] ^ S6[x[7]] ^ S7[x[6]] ^ S4[x[3]];
      K[13] = S4[x[10]] ^ S5[x[11]] ^ S6[x[5]] ^ S7[x[4]] ^ S5[x[7]];
      K[14] = S4[x[12]] ^ S5[x[13]] ^ S6[x[3]] ^ S7[x[2]] ^ S6[x[8]];
      K[15] = S4[x[14]] ^ S5[x[15]] ^ S6[x[1]] ^ S7[x[0]] ^ S7[x[13]];
      if (K != k)
	break;
      K += 16;
    }
  for (i = 0; i < 16; i++)
    {
      key->data[i * 2] = k[i];
      key->data[i * 2 + 1] = ((k[i + 16]) + 16) & 0x1f;
    }
}

int
main ()
{
  CAST_KEY ref = { {0x0069B3F8, 0x00000013, 0x000AEFF8, 0x00000013, 0x004AD0E0, 0x0000001B, 0x00818F18, 0x00000018, 0x008FF000, 0x0000001B, 0x002D1C00, 0x0000001B, 0x00EA2800, 0x00000010, 0x00C73400, 0x00000010, 0x004BF8E0, 0x0000001B, 0x00B3D718, 0x00000018, 0x00B0EBF8, 0x00000013, 0x003247F8, 0x00000013, 0x00C5BA20, 0x00000010, 0x002D1C00, 0x00000010, 0x0060822B, 0x00000008, 0x0096236B, 0x0000001B} };
  CAST_KEY key;
  unsigned i;
  for (i = 1; i < 1024; i++)
    CAST_S_table[i] = (CAST_S_table[i-1] * 7 + 3) & 0xFFFFFF;
  CAST_set_key (&key);
  if (__builtin_memcmp(&ref, &key, sizeof(ref)))
    __builtin_abort();
  return 0;
}