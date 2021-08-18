///////////////////////////////////////
// Header Datei zu GTI-Versuch 3     //
// Joana Herbst und Jonathan Koeppen //
// Versuchsdatum: 29.06.2021         //
///////////////////////////////////////

#ifndef POS_ANL_H
#define POS_ANL_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
/*
//Definition / Initialisierung von Ports und Channels
//typedef enum {PA=0,PB,PC} PORT;
//typedef enum {K0=0,K1,K2,K3,K4,K5,K6,K7} CHANNEL;
*/
//Kanalzuweisung innerhalb der Ports
#define HPR_POS K0 // Sensoren-ports (B)
#define HPL_POS K1
#define ESR_POS K2
#define ESL_POS K3
#define T2_POS K2 //Button-ports (C)
#define T3_POS K3
#define T5_POS K5
#define Motor_An_POS K0 //Aktor-ports (A)
#define Motor_Direction_POS K1
#define LED_POS K4
#define cnt_clr_POS K7

#endif /* POS_ANL_H */
