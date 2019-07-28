#ifndef _DVDCPXM_H
#define _DVDCPXM_H

#ifdef __cplusplus
extern "C" {
#endif

/* The block size of a DVD. */
#define DVDCPXM_BLOCK_SIZE     2048

/* The encrypted part of the block. */
#define DVDCPXM_ENCRYPTED_SIZE 1920

/* dvdcpxm_init() returns this value when unprotected media is loaded. */
#define DVDCPXM_MEDIA_UNPR     0

/* dvdcpxm_init() returns this value when CPPM protected media is loaded. */
#define DVDCPXM_MEDIA_CPPM     1

/* dvdcpxm_init() returns this value when CPRM protected media is loaded. */
#define DVDCPXM_MEDIA_CPRM     2

/* Flag to ask dvdcpxm_decrypt() to reset CCI byte of the data it processes. */
#define DVDCPXM_RESET_CCI      1

/* Flag to ask dvdcpxm_decrypt() to preserve CCI byte of the data it processes. */
#define DVDCPXM_PRESERVE_CCI   2


/*
 * Exported prototypes.
 */
extern int dvdcss_init   (char *psz_target);
extern int dvdcpxm_init   (char *psz_target);
extern int dvdcpxm_decrypt(void *p_buffer, int nr_blocks, int flags);

#ifdef __cplusplus
}
#endif

#endif /* <dvdcpxm.h> */

