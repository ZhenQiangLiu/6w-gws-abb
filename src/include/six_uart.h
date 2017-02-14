/*
 * six_uart.h
 *
 *  Created on: July 13, 2016
 *  Updated on: Jan 22, 2017; Feb 14, 2017
 *      Author: YY Wang, Qige
 *  Maintainer: Qige
 */

#ifndef SIX_UART_H_
#define SIX_UART_H_

// data types
typedef unsigned int			uint;
typedef unsigned char			uchar;
typedef char					byte;
typedef unsigned short 			ushort;

// empty debug print out
#ifdef _ENABLE_UART_DEBUG
#define UART_DBG(format, ...)	{printf("UART dbg> "format, ##__VA_ARGS__);}
#else
#define UART_DBG(fmt, ...)		{}
#endif

// pre defines
#define UART_SPEED_DEFAULT		B9600
#define UART_FD_INVALID_BAR		2

enum UART_ERR {
	UART_OK = 0,
	UART_ERR_OPEN = 1,
};

int  uart_open(const char *dev);
int  uart_read(const int fd, char *buff, const uint buff_length);
int  uart_write(const int fd, const char *data, const uint data_length);
void uart_close(int *fd);


#endif /* SIX_UART_H_ */
