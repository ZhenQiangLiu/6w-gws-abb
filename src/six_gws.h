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


// Channel to Freq
#define GRID_R0FREQ(x)				(473+(x-14)*6)
#define GRID_R1FREQ(x)				(474+(x-21)*8)


// Analog Baseband
#define GWS_ABB_DFL_IFNAME		"wlan0"
#define GWS_ABB_DFL_CHANBW		8
#define GWS_ABB_CHANBW_MIN		1
#define GWS_ABB_CHANBW_MAX		24

#define GWS_ABB_DFL_TIMEOUT		3
#define GWS_ABB_DFL_STA_QTY_MAX	10



enum GWS_ABB_MODE {
	NL80211_MODE_MASTER = 1,
	NL80211_MODE_CLIENT = 3,
	NL80211_MODE_MESH = 7,
	NL80211_MODE_ADHOC
};


typedef struct gws_abb_assoclist {
	char mac[18]; //"00:00:00:00:00:00"; @ 2016.06.07 18:12
	int signal;
	int noise;
	float rx_br;
	float tx_br;
	int rx_mcs;
	int tx_mcs;
	unsigned long long rx_pckts;
	unsigned long long tx_pckts;
	unsigned long long tx_failed;
	unsigned int inactive; //+ unit: ms
} GWS_ABB_ASSOCLIST;


typedef struct gws_abb {
	unsigned long seq;
	char vers[4];			//- "1.0\0"
	char kw[32];			//- "gwsctrlv1: bb data collector"

	int chanbw;			// 10.0 @ 091116
	int nl_mode;				//- 0: mesh, 1: wds sta, 2: wds ap
	struct {
		int signal;
		int noise;
		int br;
	} avg;

	int peers_qty;		//+ peer 0 is average
	struct gws_abb_assoclist peers[GWS_ABB_DFL_STA_QTY_MAX];
} GWS_ABB;



typedef struct gws_radio {
	unsigned long seq;
	char ver[4];			// "1.0\0"
	char kw[32];			// "gwsctrlv1: bb data collector"

	char hw_ver[64];
	char fw_ver[64];
	char hw_sn[32];

	int  region;			// 0: 6 MHz 1: 8 MHz
	int  channel;
	int  freq;
	int  txchain;
	int  txpower;

	int  rxgain;

	int  temp;

	int  adv_agcmode;
	int  adv_ifout;

	int  adv_txcal;
	int  adv_mintxpwr;
	int  adv_maxtxpwr;
	int  adv_brdmaxpwr;
	int  adv_txatten;
	int  adv_maxatten;

	int  adv_rx;
	int  adv_rxcal;
	int  adv_rxmaxgain;
	int  adv_rxfatten;
	int  adv_rxratten;
} GWS_RADIO;


#endif /* SIX_GWS_H_ */
