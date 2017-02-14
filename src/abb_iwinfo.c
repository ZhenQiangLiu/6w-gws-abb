/*
 * abb_iwinfo.c
 *
 *  Created on: Feb 1, 2017
 *      Author: Qige Zhao <qige@6harmonics.com>
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <syslog.h>

#include "six_def.h"
#include "iwinfo/iwinfo.h"
#include "include/six_ipc_shm.h"
#include "abb_iwinfo.h"

// check in main loop
// 0: continue; 1: break & stop.
static int FLAG_SIG_EXIT = -1;

// abb shm id, shm address
static int ABB_SHM_ID = -1;
static void *ABB_SHM_ADDR = NULL;

static void abb_iwinfo_init();
static void abb_iwinfo_stop(void);

// main loop based on "libiwinfo"
int Abb_iwinfo_run(const void *env)
{
	DBG("Abb_iwinfo_run()\n");

	abb_iwinfo_init();
	int i, sum = 0;
	for(i = 1; i <=10; i ++) {
		if (FLAG_SIG_EXIT)
			break;

		sum += i;
		DBG("> loop %d\n", i);
		sleep(1);
	}

	abb_iwinfo_stop();

	return 0;
}

static void abb_iwinfo_init(void)
{
	int abb_shm_id = -1;
	//ABB_SHM_ID = shm_init((const void *) GWS_APP_ABB_KEY, &abb_shm_id, &ABB_SHM_ADDR, sizeof(GWS_ABB_VAL));
}

static void abb_iwinfo_stop(void)
{
	DBG("abb_iwinfo_stop()\n");
}

// mark FLAG, to break main loop
void Abb_iwinfo_signal(void)
{
	DBG("Abb_iwinfo_signal(): mark FLAG_SIG_EXIT\n");
	FLAG_SIG_EXIT = 1;
}
