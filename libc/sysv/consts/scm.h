#ifndef COSMOPOLITAN_LIBC_SYSV_CONSTS_SCM_H_
#define COSMOPOLITAN_LIBC_SYSV_CONSTS_SCM_H_
#if !(__ASSEMBLER__ + __LINKER__ + 0)
COSMOPOLITAN_C_START_

extern const int SCM_TIMESTAMP;
extern const int SCM_CREDENTIALS;
extern const int SCM_TIMESTAMPING;
extern const int SCM_TIMESTAMPNS;
extern const int SCM_WIFI_STATUS;

COSMOPOLITAN_C_END_
#endif /* !(__ASSEMBLER__ + __LINKER__ + 0) */

#define SCM_RIGHTS       1
#define SCM_TIMESTAMP    SCM_TIMESTAMP
#define SCM_CREDENTIALS  SCM_CREDENTIALS
#define SCM_TIMESTAMPING SCM_TIMESTAMPING
#define SCM_TIMESTAMPNS  SCM_TIMESTAMPNS
#define SCM_WIFI_STATUS  SCM_WIFI_STATUS


#endif /* COSMOPOLITAN_LIBC_SYSV_CONSTS_SCM_H_ */
