/*
 * gti_IO.h
 *
 *  Created on: 1.7.2020
 *      Author: N. Kellersohn
 *
 * Defines the GTI interface which is a simplified digital IO
 *
 * Use of Ports
 * * PA output
 * * PB input
 * * PC input
 */

#ifndef GTI_IO_H_
#define GTI_IO_H_


#include "gti_base.h"
#include "PosAnl.h"

typedef int* DSCB;


extern uint8_t inputByte(DSCB boardHandle, PORT portName, uint8_t *val){

    uint8_t result=0, mask=0;
    int uebrgabe;

    if(portName == PA){
            printf("Eingabe fuer PORT PA\n Nur 1 oder 0\n ");

            printf("Eingabe fuer Motor_an: ");
            scanf("%i",&uebrgabe);

            mask=uebrgabe<<Motor_An_POS;
            result|=mask;

            printf("\nMotor_Direction: ");
            scanf("%i",&uebrgabe);

            mask=uebrgabe<<Motor_Direction_POS;
            result|=mask;

            printf("\nEingabe fuer LED: ");
            scanf("%i",&uebrgabe);
            //uebrgabe = 0;
            mask=uebrgabe<<LED_POS;
            result|=mask;

            printf("\nEingabe fuer cnt_clr: ");
            scanf("%i",&uebrgabe);
            //uebrgabe = 0;
            mask=uebrgabe<<cnt_clr_POS;
            result|=mask;

            return result;
    }

    if(portName == PC){
            printf("Eingabe fuer PORT PC\n Nur 1 oder 0\n ");
            printf("Eingabe fuer Notaus(T2): ");
           scanf("%i",&uebrgabe);
            //uebrgabe = 0;
            mask=uebrgabe<<T2_POS; 
            result|=mask;          

            printf("\nEingabe fuer Notbetrieb(T3): ");
            //uebrgabe = 0;
            scanf("%i",&uebrgabe);
            mask=uebrgabe<<T3_POS;
            result|=mask;

            printf("\nEingabe fuer Reset(T5): ");
            scanf("%i",&uebrgabe);
            //uebrgabe = 0;
            mask=uebrgabe<<T5_POS;
            result|=mask;

            return result;
    }
    if(portName == PB){
            printf("Eingabe für PORT PB\n Nur 1 oder 0\n ");

            printf("Eingabe fuer HPR: ");
            scanf("%i",&uebrgabe);
            //uebrgabe = 1;
            mask=uebrgabe<<HPR_POS;
            result|=mask;

            printf("Eingabe fuer HPL: ");
            scanf("%i",&uebrgabe);
            //uebrgabe = 0;
            mask=uebrgabe<<HPL_POS;
            result|=mask;

            printf("Eingabe fuer ESR: ");
            scanf("%i",&uebrgabe);
            //uebrgabe = 0;
            mask=uebrgabe<<ESR_POS;
            result|=mask;

            printf("Eingabe fuer ESL: ");
            scanf("%i",&uebrgabe);
            //uebrgabe = 0;
            mask=uebrgabe<<ESL_POS;
            result|=mask;

            return result;
    }

    return result;

}

extern uint8_t outputByte(DSCB boardHandle, PORT portName, uint8_t val){

        printf("\n%d",val);
        printf("\n 1.Stelle: K0 Motor An\t 2.Stelle: K1 Motor Direction Pos\t 5.Stelle: K5 LED\t 8.Stelle K7 cnt_clr\n");
        return val;

}

DSCB initIO(){
    DSCB boardHandle = 0;
    return boardHandle;
}



#endif /* GTI_IO_H_ */
