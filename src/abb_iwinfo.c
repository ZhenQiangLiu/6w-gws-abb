/*
 * abb_iwinfo.c
 *
 *  Created on: Feb 1, 2017
 *  Updated on: Feb 15, 2017
 *      Author: Qige Zhao <qige@6harmonics.com>
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <syslog.h>

#include "six_def.h"
#include "six_gws.h"
#include "six_app.h"

#include "iwinfo/iwinfo.h"
#include "include/six_ipc_shm.h"
#include "abb_iwinfo.h"

// check in main loop
// 0: continue; 1: break & stop.
static int FLAG_SIG_EXIT = FALSE;

// abb shm id, shm address
static uint ABB_SHM_SEQ = 0;
static int ABB_SHM_ID = -1;
static GWS_ABB *ABB_SHM_ADDR = NULL;
static const struct iwinfo_ops *iw = NULL;

// ...
static int abb_iwinfo_init(const char *ifname);
static void abb_iwinfo_stop(void);

static int abb_iwinfo_update(void *dest, const uint bw, const char *ifname);
static void abb_iwinfo_print(void);

static char *abb_ops_mode(const int nl_mode);


// main loop based on "libiwinfo"
int Abb_iwinfo_run(const void *env)
{
	DBG("Abb_iwinfo_run()\n");

	int _ret = GWS_ABB_OK;

	APP_ENV *conf = (APP_ENV *) env;

	static GWS_ABB abb;
	//const byte flag = conf->flag.debug;
	const uint bw = conf->conf.bw;
	const char *ifname = conf->conf.ifname;

	// set default value when user input not valid
	const uint abb_bw = ( bw > 0 ? bw : GWS_ABB_DFL_CHANBW);
	const char *abb_ifname = ( strlen(ifname) > 0 ? ifname : GWS_ABB_DFL_IFNAME );

	// start init
	if ( abb_iwinfo_init(abb_ifname) ) {
		_ret = GWS_ABB_ERR_INIT;
	}

	// main loop
	// if init failed, will not enter main loop
	int fail_counter = 0;
	for( ; ( ! _ret ); ) {
		if ( FLAG_SIG_EXIT ) break;
		DBG("> loop %d\n", i);

		// read
		if ( abb_iwinfo_update(&abb, abb_bw, abb_ifname) ) {
			fail_counter ++;
			if ( fail_counter >= GWS_ABB_DFL_TIMEOUT ) {
				_ret = GWS_ABB_ERR_DATA; DBG("ABB data update failed.\n");
				break;
			}
		} else {
			fail_counter = 0;
			ABB_SHM_SEQ ++;
		}

		// save
		abb.seq = ABB_SHM_SEQ;
		memcpy(ABB_SHM_ADDR, &abb, sizeof(abb));

		// print when needed
		//if (flag) {
			abb_iwinfo_print();
			printf("------ %05d ------\n\n", ABB_SHM_SEQ);
		//}

		sleep(1);
	}

	abb_iwinfo_stop();

	return _ret;
}

// prepare all parameters
static int abb_iwinfo_init(const char *ifname)
{
	int _ret = GWS_ABB_OK;

	do { // goto
		if ( shm_init((const void *) GWS_SHM_ABB_KEY, &ABB_SHM_ID, \
				(void *) &ABB_SHM_ADDR, sizeof(GWS_ABB_VAL)) )
		{
			_ret = GWS_ABB_ERR_SHM; DBG("ABB init SHM failed.\n");
			break;
		}

		iw = iwinfo_backend(ifname);
		if (! iw) {
			_ret = GWS_ABB_ERR_IWINFO; DBG("ABB init iwinfo failed.\n");
			break;
		}

	} while(FALSE);

	return _ret;
}


static int abb_iwinfo_update(void *dest, const uint bw, const char *ifname)
{
	GWS_ABB *abb = (GWS_ABB *) dest;

	// clean before use
	memset(abb, 0, sizeof(GWS_ABB));

	// TODO: read & save from iwinfo


	return GWS_ABB_OK;
}

static void abb_iwinfo_print(void)
{
	int i;
	GWS_ABB *abb = ABB_SHM_ADDR;
	GWS_ABB_ASSOCLIST *abb_peer = NULL;

	int signal, noise, inactive;
	char *peer_mac = NULL;
	signal = abb->avg.signal, noise = abb->avg.noise;
	if (signal && signal > noise) {
		printf("Average: %d/%d dBm, %d\n", \
				signal, noise, signal - noise);

		for( i = 0; i < GWS_ABB_DFL_STA_QTY_MAX; i ++ ) {
			abb_peer = &abb->peers[i];

			sprintf(peer_mac, "%s", abb_peer->mac);
			signal = abb_peer->signal;
			noise = abb_peer->noise;
			inactive = abb_peer->inactive;

			if (signal && signal > noise) {
				printf("%s > STA %d >  %d/%d dBm (%d), %d ms ago\n", \
						peer_mac, i, signal, noise, signal - noise,
						inactive);
			}
		}
	} else {
		printf(" Status: Not connected.\n");
	}

	char *mode = abb_ops_mode(abb->nl_mode);
	printf("   Mode: %s\n", mode);
}


// clean when exit
static void abb_iwinfo_stop(void)
{
	DBG("abb_iwinfo_stop()\n");
	shm_free(&ABB_SHM_ID, (void *) &ABB_SHM_ADDR);
	iwinfo_close();
}

// mark FLAG, to break main loop
void Abb_iwinfo_signal(void)
{
	DBG("Abb_iwinfo_signal(): mark FLAG_SIG_EXIT\n");
	FLAG_SIG_EXIT = TRUE;
}


static char *abb_ops_mode(const int nl_mode)
{
	if ( nl_mode == NL80211_MODE_MASTER ) {
		return "CAR (bridged)";
	} else if ( nl_mode == NL80211_MODE_CLIENT ) {
		return "EAR (bridged)";
	} else if ( nl_mode == NL80211_MODE_MESH ) {
		return "Mesh (bridged)";
	} else {
		return "(unknown)";
	}
}
