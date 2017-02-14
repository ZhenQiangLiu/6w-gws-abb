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

int Abb_iwinfo_run(const void *env);
void Abb_iwinfo_signal(void);

#endif /* ABB_IWINFO_H_ */
