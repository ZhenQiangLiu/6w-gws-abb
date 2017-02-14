/*
 * six_env.h
 *
 *  Created on: Jan 19, 2017
 *  Updated on: Feb 14, 2017
 *      Author: Qige
 */

#ifndef SIX_ENV_H_
#define SIX_ENV_H_

// data types
typedef unsigned int			uint;
typedef unsigned char			uchar;
typedef char					byte;
typedef unsigned short 			ushort;

typedef union {
	ushort val;
	struct {
		byte low;
		byte high;
	} bytes;
} U_UInt2UShort;


// @return 0: Big-endian
// @return 1: Little-endian
int os_env_little_endian(void);

#endif /* SIX_ENV_H_ */
