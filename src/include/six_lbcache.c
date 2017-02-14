/*
 * six_lbcache.c
 *
 *  Created on: July 13, 2016
 *  Updated on: Jan 22, 2017; Feb 14, 2017
 *      Author: YY Wang, Qige
 *  Maintainer: Qige
 */
#include <stdio.h>
#include <string.h>
#include "six_lbcache.h"


void lbc_init(LBCache *lbc)
{
	memset(lbc, 0, sizeof(LBCache));

	lbc->start = lbc->data;
	lbc->length = sizeof(lbc->data) - 1;

	lbc->data_head = lbc->start;
	lbc->data_length = 0;


	LBC_DBG("empty all data, reset all\n");
}

/*
 * save data (str/hex) to lbc
 * - test data length;
 * - test bytes available;
 * - calc basic counters;
 * - copy;
 */
int lbc_save(LBCache *lbc, const byte *data, const uint data_length)
{
	//+ buffer length = data length + data available length
	uint lbc_length, lbc_data_length, lbc_da_length;
	lbc_length = lbc->length;
	lbc_data_length = lbc->data_length;
	lbc_da_length = lbc_length - lbc_data_length;

	if (lbc_da_length < 1)
		return LBC_ERR_CACHE_IS_FULL;
	if (data_length < 1)
		return LBC_ERR_DATA_INVALID;
	if (data_length > lbc_da_length)
		return LBC_ERR_DATA_TOOLONG;

	//+ buffer length = data head to start + data head to tail
	uint dh_to_start, dh_to_tail;
	dh_to_start = lbc->data_head - lbc->start;
	dh_to_tail = lbc_length - dh_to_start;

	//+ data available
	uint da_tail;
	if (dh_to_tail >= lbc_data_length) {
		da_tail = dh_to_tail - lbc_data_length;
	} else {
		da_tail = 0;
	}

	LBC_DBG("length/data length/bytes available = %d/%d/%d\n",
			lbc_length, lbc_data_length, lbc_da_length);
	LBC_DBG("data head/tail = %d/%d, bytes available in tail = %d\n",
			dh_to_start, dh_to_tail, da_tail);

	//+ save
	if (lbc_data_length > 0) {
		if (da_tail >= data_length) {
			memcpy(lbc->data_head + lbc_data_length, data, data_length);
		} else {

			/*memcpy(lbc->data_head + lbc_data_length, data, da_tail);
			if (lbc_data_length > dh_to_tail) {
				memcpy(lbc->start+(lbc_data_length-dh_to_tail), &data[da_tail], data_length - da_tail);
			} else {
				memcpy(lbc->start, &data[da_tail], data_length - da_tail);
			}*/

			if (da_tail > 0) {
				memcpy(lbc->data_head + lbc_data_length, data, da_tail);
			}

			memcpy(lbc->start, data + da_tail, data_length - da_tail);
		}
	} else {
		memcpy(lbc->start, data, data_length);
	}
	lbc->data_length += data_length;

	return LBC_OK;
}

/*
 * read loopback cache data (ascii/hex)
 */
int lbc_read(LBCache *lbc, byte *buff, uint *buff_length)
{
	if (*buff_length < 1)
		return LBC_ERR_DATA_INVALID;

	//+ cache length = data length + data available length
	uint lbc_length, lbc_data_length;
	lbc_length = lbc->length;
	lbc_data_length = lbc->data_length;

	//+ cache length = data head to start + data head to tail
	uint dh_to_head, dh_to_tail;
	dh_to_head = lbc->data_head - lbc->start;
	dh_to_tail = lbc_length - dh_to_head;

	//+ calc bytes to read
	int b2read = MIN(*buff_length, lbc_data_length);
	*buff_length = b2read;

	LBC_DBG("length/data length = %d/%d\n",
			lbc_length, lbc_data_length);
	LBC_DBG("data head/tail = %d/%d, bytes to read = %d\n",
			dh_to_start, dh_to_tail, b2read);

	if (dh_to_tail >= b2read) {
		memcpy(buff, lbc->data_head, b2read);
	} else {
		memcpy(buff, lbc->data_head, dh_to_tail);
		memcpy(&buff[dh_to_tail], lbc->start, b2read - dh_to_tail);
	}

#ifdef LBC_CLEAR_WHEN_READ
	lbc_move(lbc, *buff_length);
#endif

	return LBC_OK;
}

/*
 * discard data of b2move bytes
 * - data length <= b2move, init
 * -
 */
int lbc_move(LBCache *lbc, uint move)
{
	if (move < 1)
		return LBC_OK;

	//+ cache length = data length + data available length
	unsigned int lbc_length, lbc_data_length;
	lbc_length = lbc->length;
	lbc_data_length = lbc->data_length;

	//+ cache length = data head to start + data head to tail
	unsigned int dh_to_head, dh_to_tail;
	dh_to_head = lbc->data_head - lbc->start;
	dh_to_tail = lbc_length - dh_to_head;

	LBC_DBG("length/data length = %d/%d\n",
			lbc_length, lbc_data_length);
	LBC_DBG("data head/tail = %d/%d, bytes to read = %d\n",
			dh_to_start, dh_to_tail, b2read);

	if (lbc_data_length > move) {
		if (dh_to_tail > move) {
#ifdef LBC_CLEAR_WHEN_MOVE
			int i;
			for(i = 0; i < move; i ++)
				*(lbc->data_head+i) = '\0';
#endif
			lbc->data_head += move;
		} else {
#ifdef LBC_CLEAR_WHEN_MOVE
			int i;
			for(i = 0; i <= dh_to_tail; i ++)
				*(lbc->data_head + i) = '\0';
			for(i = 0; i < move - dh_to_tail; i ++)
				*(lbc->start + i) = '\0';
#endif
			lbc->data_head = lbc->start + (move - dh_to_tail);
		}
		lbc->data_length -= move;
	} else {
		lbc_init(lbc);
	}

	return LBC_OK;
}

