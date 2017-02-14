/*
 * six_ipc_shm.h
 *
 *  Created on: July 13, 2016
 *  Updated on: Jan 22, 2017; Feb 14, 2017
 *      Author: Qige
 */

#ifndef SIX_IPC_SHM_H_
#define SIX_IPC_SHM_H_

// data types
typedef unsigned int			uint;
typedef unsigned char			uchar;
typedef char					byte;
typedef unsigned short 			ushort;


// pre defines
//#define IPC_SHM_USE_KEY_FILE


// empty debug print out
#ifdef _ENABLE_SHM_DEBUG
#define SHM_DBG(format, ...)		{printf("IPC shm > "format, ##__VA_ARGS__);}
#else
#define SHM_DBG(fmt, ...)			{}
#endif

enum IPC_SHM_ERR {
	SHM_OK = 0,
	SHM_ERR_GET = 1,
	SHM_ERR_AT,
};

int  shm_init(const void *key, int *sid, void **saddr, const uint ssize);
void shm_read(const void *src, void *dest, const uint length);
void shm_write(const void *src, void *dest, const uint length);
int  shm_free(int *sid, void **saddr);

#endif /* SIX_IPC_SHM_H_ */
