/*
 * six_env.c
 *
 *  Created on: Jan 19, 2017
 *  Updated on: Feb 14, 2017
 *      Author: Qige
 */

#include "six_env.h"


// 0: Big-endian, 1: Little-endian
int os_env_little_endian(void)
{
	ushort x = 1;
	//uint y = (uint) x;
	return ((uint) x);
}
