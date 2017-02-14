/*
 * six_lbcache.h
 *
 *  Created on: July 13, 2016
 *  Updated on: Jan 22, 2017; Feb 14, 2017
 *      Author: YY Wang, Qige
 *  Maintainer: Qige
 */

#ifndef SIX_LBCACHE_H_
#define SIX_LBCACHE_H_

// data types
typedef unsigned int			uint;
typedef unsigned char			uchar;
typedef char					byte;
typedef unsigned short 			ushort;

#define MIN(x, y)					(x < y ? x : y)

// empty debug print out
#ifdef _ENABLE_LBCACHE_DEBUG
#define LBC_DBG(format, ...)		{printf("lbcache > "format, ##__VA_ARGS__);}
#else
#define LBC_DBG(fmt, ...)			{}
#endif


// features
#define LBC_CLEAR_WHEN_MOVE
#define LBC_CLEAR_WHEN_READ

// @returns
enum LBC_ERR {
	LBC_OK = 0,
	LBC_ERR_CACHE_IS_FULL = 1,
	LBC_ERR_DATA_INVALID = 100,
	LBC_ERR_DATA_TOOLONG
};


#ifdef DEBUG_LBC
#define LBC_CONF_BF_LENGTH		16
#else
#define LBC_CONF_BF_LENGTH		1024
#endif

typedef struct {
	char *start;
	uint length;
	char *data_head;
	uint data_length;
	byte data[LBC_CONF_BF_LENGTH];
} LBCache;


/*
 * init loopback cache
 */
void lbc_init(LBCache *lbc);

/*
 * return bytes that saved
 * return value < 0, error number
 */
int lbc_save(LBCache *lbc, const byte *data, const uint data_length);

/*
 * return bytes that read from cache
 * return value < 0, error number
 */
int lbc_read(LBCache *lbc, byte *buff, uint *buff_length);

/*
 * return bytes that cache discarded
 * return value = 0, init loopback cache when "move" > "data_length"
 * return value < 0, error number
 */
int lbc_move(LBCache *lbc, uint move);


#endif /* SIX_LBCACHE_H_ */
