/*
 * gti_base.h
 *
 *  Created on: 18.02.2017
 *      Author: lab-gti
 */

#ifndef GTI_BASE_H_
#define GTI_BASE_H_

typedef unsigned char uint8_t;

typedef enum {PA=0, PB, PC} PORT;

typedef enum {K0=0, K1,K2,K3, K4, K5, K6, K7} CHANNEL;

//typedef enum {false = 0, true} bool;

// error codes of IO
#define IO_OK 0
#define IO_ERROR_NOT_INITIALIZED 0x81
#define IO_ERROR_CHANNEL_NOT_CONNECTED 0x82
#define IO_ERROR_CHANNEL_NOT_INTERRUPT_ENABLED 0x83

#endif /* GTI_BASE_H_ */
