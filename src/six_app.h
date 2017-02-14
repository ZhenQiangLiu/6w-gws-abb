/*
 * six_app.h
 *
 *  Created on: Jul 25, 2016
 *  Updated on: 2016.11.11
 *  Updated on: Jan 31, 2017; Feb 8, 2017; Feb 14, 2017
 *      Author: Qige Zhao <qige@6harmonics.com>
 */

#ifndef SIX_APP_H_
#define SIX_APP_H_

#include "six_gws.h"
#include "six_def.h"


#define APP_DESC				("GWS Analog Baseband")
#define APP_VERSION				("v1.0-1-140217. Buildtime: "__DATE__", "__TIME__)


// size define
#define APP_LIMIT_COMMON_LENGTH			32
#define APP_LIMIT_IFNAME_LENGTH			16


// user input struct
typedef struct {
	struct {
		int version;
		int help;
		int debug;
		int daemon;
	} flag;

	struct {
		int pid;
		char name[APP_LIMIT_COMMON_LENGTH];
		char key[GWS_APP_KEY_LENGTH];
		int idle;
	} app;

#if defined(_ABB_SRC_IWINFO)
	struct {
		int bw;
		char ifname[APP_LIMIT_IFNAME_LENGTH];
	} conf;
#endif

} APP_ENV;

#endif /* SIX_APP_H_ */
