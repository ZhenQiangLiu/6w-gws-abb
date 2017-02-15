/*
 * abb_iwinfo.h
 *
 *  Created on: Feb 1, 2017
 *      Author: Qige Zhao <qige@6harmonics.com>
 */

#ifndef ABB_IWINFO_H_
#define ABB_IWINFO_H_


typedef struct {
	int signal;
	int noise;
} GWS_ABB_VAL;


enum GWS_ABB_ERR {
	GWS_ABB_OK = 0,
	GWS_ABB_ERR_UNKNOWN = 1,
	GWS_ABB_ERR_SHM,
	GWS_ABB_ERR_IFNAME,
	GWS_ABB_ERR_IWINFO,
	GWS_ABB_ERR_ASSOCLIST = 50,
	GWS_ABB_ERR_ASSOCLIST_STA_INVALID,
	GWS_ABB_ERR_ASSOCLIST_STA_NONE,
	GWS_ABB_ERR_ASSOCLIST_STA_TIMEOUT,
	GWS_ABB_ERR_INIT = 100,
	GWS_ABB_ERR_DATA = 200
};


int Abb_iwinfo_run(const void *env);
void Abb_iwinfo_signal(void);

#endif /* ABB_IWINFO_H_ */
