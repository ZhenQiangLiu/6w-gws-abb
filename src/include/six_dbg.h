/*
 * six_dbg.h
 *
 *  Created on: Jan 19, 2017
 *  Updated on: Feb 14, 2017
 *      Author: Qige
 */

#ifndef SIX_DBG_H_
#define SIX_DBG_H_


#ifdef _ENABLE_DEBUG_OUTPUT
#define _DBG(fmt, ...)		{printf("debug> "fmt, ##__VA_ARGS__);}
#else
#define _DBG(fmt, ...)      {}
#endif

// call syslog()
// #include <stdio.h>
// #include <syslog.h>
// eg. 	_LOG("started (%s, pid=%d)\n", APP_DESC, getpid());
#define _LOG(fmt, ...) 	{ char _bf[1024] = {0}; snprintf(_bf, sizeof(_bf) - 1, fmt, ##__VA_ARGS__); \
						fprintf(stderr, "> %s", _bf); syslog(LOG_INFO, "%s", _bf); }


#endif /* SIX_DBG_H_ */
