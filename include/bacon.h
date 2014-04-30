
/**
 * `bacon.h' - libbacon
 *
 * copyright (c) 2014 joseph werle <joseph.werle@gmail.com>
 */

#ifndef BACON_H

#if __GNUC__ >= 4
# define BACON_EXTERN __attribute__((visibility("default")))
#else
# define BACON_EXTERN
#endif

/**
 * Bacon version
 */

#ifndef BACON_VERSION
#define BACON_VERSION "0.0.1" // default
#endif

/**
 * Bacon alphabet
 */

#define BACON_ALPHA "ABCDEFGHIKLMNOPQRSTUWXYZ"

/**
 * Encodes a string with baconian cipher
 * using an alphabet
 */

BACON_EXTERN char *
bacon_encode (const char *, const char *);

/**
 * Decodes a string with baconian cipher
 * using an alphabet
 */

BACON_EXTERN char *
bacon_decode (const char *, const char *);

#endif

