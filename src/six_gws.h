/*
 * _gws.h
 *
 *  Created on: Feb 1, 2017
 *      Author: Qige Zhao <qige@6harmonics.com>
 */

#ifndef SIX_GWS_H_
#define SIX_GWS_H_

// decide ARCHITECTURE
#ifndef _ABB_SRC_IWINFO
#define _ABB_SRC_IWINFO
#endif

// default use USE_GETOPT
#if (!defined(USE_GETOPT_LONG) && !defined(USE_GETOPT))
#define USE_GETOPT
#endif


// common define within GWS products
#define GWS_APP_KEY_LENGTH		16

// shm key file path for ftok()
#define GWS_SHM_ABB_KEY			"/usr/sbin/gws_abb"
#define GWS_SHM_RADIO_KEY		"/usr/sbin/gws_radio"
#define GWS_MSG_RADIO_KEY		"/usr/sbin/gws"

#endif /* SIX_GWS_H_ */
