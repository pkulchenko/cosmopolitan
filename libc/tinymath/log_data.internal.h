#ifndef COSMOPOLITAN_LIBC_TINYMATH_LOG_DATA_H_
#define COSMOPOLITAN_LIBC_TINYMATH_LOG_DATA_H_

#define LOG_TABLE_BITS  7
#define LOG_POLY_ORDER  6
#define LOG_POLY1_ORDER 12

#if !(__ASSEMBLER__ + __LINKER__ + 0)
COSMOPOLITAN_C_START_

extern hidden const struct log_data {
  double ln2hi;
  double ln2lo;
  double poly[LOG_POLY_ORDER - 1]; /* First coefficient is 1.  */
  double poly1[LOG_POLY1_ORDER - 1];
  struct {
    double invc, logc;
  } tab[1 << LOG_TABLE_BITS];
#if !__FP_FAST_FMA
  struct {
    double chi, clo;
  } tab2[1 << LOG_TABLE_BITS];
#endif
} __log_data;

COSMOPOLITAN_C_END_
#endif /* !(__ASSEMBLER__ + __LINKER__ + 0) */
#endif /* COSMOPOLITAN_LIBC_TINYMATH_LOG_DATA_H_ */
