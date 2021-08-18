/*
GTI Versuch 3 Automat nach vorgabe und Entwickeltem Automat
von Yanneck Haendeler und Valentin Gieraths
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dio.h"
#include "gti_base.h"

using namespace std;

/*Create struct InVector_PosAnlage with bool elements as Input Vector*/
typedef struct{
    bool T1;//unbekannt
	bool T2;//Notaus PC2
	bool T3;//Betriebn
	bool T4;//unbekannt
    bool T5;//Reset PC5
	bool HPR;
	bool HPL;
	bool ESR;
	bool ESL;

} InVector_PosAnlage;

/*Create struct OutVector_PosAnlage with bool elements as Output Vector*/
typedef struct {
	bool MotorAn;
	bool Motor_Direction;//left = 0 right=1
    bool cnt_clr;//P_A 7 
} OutVector_PosAnlage;


/*Pointer on Structures from type struct*/
typedef InVector_PosAnlage* PtrInVector_PosAnlage;
typedef OutVector_PosAnlage* PtrOutVector_PosAnlage;

/*create Basic functions*/
unsigned char getModelButtons(DSCB boardHandle, PtrInVector_PosAnlageInV);
unsigned char getModelSensors(DSCB boardHandle, PtrInVector_PosAnlageInV);
unsigned char setMotorVal(DSCB boardHandle,PtrOutVector_PosAnlageoutV);

/*
    function get ModelButtons
    reads Buttons and saves them into Struct InVector_PosAnlage


*/
unsigned char getModelButtons(DSCB boardHandle, PtrInVector_PosAnlage InV)
{
    unsigned char result,PC_val;
    /*get result from function inputByte with Input Port PC*/
    result= inputByte(boardHandle,PC,&PC_val)
    if (result == 0 ){
        printf("Error in function getModelButtons from function inputByte");
        return result;
    }
    /*Set T1 from InputBytes with PC_val*/
    /*get Bitset from PC_Val shift Another Bitset to left, compare both, if !=0 set true*/
    /*True=Button "works" False = Buttons does not "work"*/
    
    /*
    XXXXXXXX
    00000010 (und operator mit 1<<1)
    000000X0 <- output byte X
    */
    InV->T1 = ((PC_val & (1<<1))!=0 )? true:false;
    
    /*
    XXXXXXXX
    00000100 (und operator mit 1<<2)
    00000X00 <- output byte X
    */
    InV->T2 = ((PC_val & (1<<2))!=0 )? true:false;
    
    /*
    XXXXXXXX
    00001000 (und operator mit 1<<3)
    0000X000 <- output byte X
    */
    InV->T3 = ((PC_val & (1<<3))!=0 )? true:false;
    
    //InV->T4 = ((PC_val & (1<<4))!=0 )? true:false;
    
    /*
    XXXXXXXX
    00100000 (und operator mit 1<<5)
    00X00000 <- output byte X
    */
    InV->T5 = ((PC_val & (1<<5))!=0 )? true:false;

    return 1 //Modell OK
}

/*
    function get getModelSensors
    reads Sensors and saves them into Struct InVector_PosAnlage
*/
unsigned char getModelSensors(DSCB boardHandle, PtrInVector_PosAnlage InV)
{
    unsigned char result,PB_val;
    result = inputByte(boardHandle, PB, &PB_val);
	if (result == 0)
    printf("Error in function getModelSensors from function inputByte");
		return result;
	//InV->ESL = ((PB_Val & (1 << 3)) != 0) ? true : false;<-Warum nicht relevant?
	//InV->ESR = ((PB_Val & (1 << 2)) != 0) ? true : false;<-Warum nicht relevant?
    
    /*
    XXXXXXXX
    00000010 (und operator mit 1<<1)
    000000X0
    */
	InV->HPL = ((PB_val & (1 << 1)) != 0) ? true : false;

    /*
    XXXXXXXX
    00000001 (und operator mit 1)
    0000000X
    */
	InV->HPR = ((PB_val & 1) != 0) ? true : false;
    return 1 //Modell OK
}

/*
    function get setMotorVal
    reads and writes Values from outV to controll Motor State and driving direction
*/
unsigned int setMotorVal(DSCB boardHandle,PtrOutVector_PosAnlage outV)
{
    /*
    Bitset with format [PA7,PA6,PA5,PA4,PA3,PA2,PA1,PA0]
            refering [cnt_clr,reserved,LED2,reserved,reserved,MotorDirection,Motor An]
    */
    
    unsigned char result,PA_val;

    result=inputByte(boardHandle,PA,&PA_val);

    if (result==0){
        printf("Error in function setMotorVal from function inputByte");
        return result;
    }
    /*
   ( Engine on OR off and change direction
    */
    /*Engine should be on*/
    if((outV->MotorAn)==TRUE){
        /*If Engine should go right set right, else set left */
        //result=(outV->Motor_Direction == 1) ? (PA_val | 3)) : (PA_val|1),(PA_val&253) ;
        if (outV->Motor_Direction == 1){
            /* 
            XXXXXXXX
            00000011 (oder operator mit 3)
            XXXXXX11 <- ausgabe
            */
            result=(PA_val | 3);
        }
        
        else{
            /*
            XXXXXXXX
            00000001 (oder operator mit 1)
            XXXXXXX1 <- ausgabe
            */
            result=(PA_val|1);
            /*
            XXXXXXXX
            11111101 (und operator mit 253)
    	    XXXXXX0X <- ausgabe
            */
            result=(PA_val&253);
        }
        
    }
    /*Engine should be off*/
    else{
        /*
        XXXXXXXX
        11111110 (und operator mit 254)
        XXXXXXX0 <- ausgabe
        */
       result=(PA_val&254);
    }
    /*Set counter clear*/
    //result=(outV->cnt_clr==TRUE) ? (PA_val | 1 << 7) : (PA_val & 127) ;
    if(outV->cnt_clr==TRUE){
        /*
        XXXXXXXX
        10000000 (oder operator mit 128 (128=1<<7))
        1XXXXXXX <- ausgabe
        */
        result=(PA_val | 1 << 7);
    }
    else{
        /*
        XXXXXXXX
        01111111 (und operator mit 127)
        1XXXXXXX <- ausgabe
        */
        result=(PA_val & 127);
    }
    /*Set output with new information*/
    outputByte(boardHandle,PA,result);
    return 1; //Motor OK
}

/*
function to track time from given period
if given period passed return true else false
*/
bool checkTime(bool init, clock_t period){
    /*var for Static time*/
    static clock_t initTime
    
    if (inti==true){
    initTime=clock();
    return false;
    }
    else{
    if((clock()-initTime)<=period){
        return false;
    }
    else{
        return true;
    }
    }
    
}


/*
function to simulate create moore automate
*/
unsigned char Automat(DSCB boardHandle, bool reset, PtrOutVector_PosAnlage outV, PtrInVector_PosAnlage InV) {
/*Initialise Start State (Start->Ruhemodus)*/
static bool initialise==TRUE;
static enum {
    Ruhemodus,
    Init_Fahrt_Links,
    Init_Fahrt_Rechts,
    Fahre_Start_Pos,
    Fahre_Links,
    Fahre_Rechts,
    Notaus
}States;
switch (States){
    /*Output=[0,0,0,1]*/
    case Ruhemodus:
        outV->MotorAn=0;
        outV->Motor_Direction=0;
        outV->cnt_clr=1;
        /*Sets engine with given Value and return if Error*/
        if (setMotorVal(boardHandle,outV)==0){
            return 0;
        }
        /*T2 = Notaus = 0*/
        if ((InV->T2)==0){
            States=Init_Fahrt_Links;
        }
        break;
    /*Output=[1,1,0,1]*/
    case Init_Fahrt_Links:
        outV->MotorAn=1;
        outV->Motor_Direction=0;
        outV->cnt_clr=1;
        /*T2 = Notaus = 1*/
        if ((InV->T2)==1){
            States=Notaus;
        }
        /*Sets engine with given Value and return if Error*/
        else (setMotorVal(boardHandle,outV)){
            return 0;
        }
        if ((reset)==1&&(InV->T2!=1)){
            States=Init_Fahrt_Links;
        }
        if ((InV->ESL)==1&&(InV->T2!=1)){
        States=Init_Fahrt_Rechts
        }
        break;
    /*Output=[1,0,1,0]*/
    case Init_Fahrt_Rechts:
        outV->MotorAn=1;
        outV->Motor_Direction=1;
        outV->cnt_clr=0;
        /*T2 = Notaus = 1*/
        if ((InV->T2)==1){
            States=Notaus;
        }
        /*Sets engine with given Value and return if Error*/
        else (setMotorVal(boardHandle,outV)==0){
            return 0;
        }     
        
        if ((reset)==1&&(InV->T2!=1)){
            States=Init_Fahrt_Links;
        }  
        if ((InV->ESR)==1&&(InV->T2!=1)){
            States=Fahre_Start_Pos;
        }
        break;
    /*Output=[1,1,0,1]*/
    case Fahre_Start_Pos:
        outV->MotorAn=1;
        outV->Motor_Direction=0;
        outV->cnt_clr=1;
        /*T2 = Notaus = 1*/
        if ((InV->T2)==1){
            States=Notaus;
        }
        /*Sets engine with given Value and return if Error*/
        else(setMotorVal(boardHandle,outV)==0){
            return 0;
        }  
        if ((reset)==1&&(InV->T2!=1)){
            States=Init_Fahrt_Links;
        }    
        if ((InV->HPR)==1&&(InV->T2!=1)){
            States=Fahre_Links;
        } 
        break; 
    /*Output=[1,1,0,0]*/ 
    case Fahre_Links:
        outV->MotorAn=1;
        outV->Motor_Direction=0;
        outV->cnt_clr=0;
        /*T2 = Notaus = 1*/    
        if ((InV->T2)==1){
            States=Notaus;
        }
        /*Sets engine with given Value and return if Error*/
        else (setMotorVal(boardHandle,outV)==0){
            return 0;
        } 
        if ((reset)==1&&(InV->T2!=1)){
            States=Init_Fahrt_Links;
        }    
        if ((InV->HPL)==1&&(InV->T2!=1)){
            States=Fahre_Rechts;
        } 
        break; 
    /*Output=[1,0,1,0]*/ 
    case Fahre_Rechts:
        outV->MotorAn=1;
        outV->Motor_Direction=1;
        outV->cnt_clr=0; 
        /*T2 = Notaus = 1*/ 
        if ((InV->T2)==1){
            States=Notaus;
        }
        /*Sets engine with given Value and return if Error*/
        else (setMotorVal(boardHandle,outV)==0){
            return 0;
        }  
        if ((reset)==1&&(InV->T2!=1)){
            States=Init_Fahrt_Links;
        }    
        if ((InV->HPR)==1&&(InV->T2!=1)){
            States=Fahre_Links;
        }
        break;
    /*Output=[0,0,0,0]*/
    case Notaus:
        outV->MotorAn=0;
        outV->Motor_Direction=0;
        outV->cnt_clr=0;
        /*Sets engine with given Value and return if Error*/
        if (setMotorVal(boardHandle,outV)==0){
            return 0;
        }
        /*T2 = Notaus = 0 and Reset = 1*/
        if(((InV->T2)==0)&&(reset==1)){
            States=Init_Fahrt_Links;
        }
        break;
    default:
        State=Ruhemodus;
        break;
    }
}



int main(void)
{
    DSCB boardHandle = NULL; //Initialise with 0 
    boardHandle = initIO();
    InVector_PosAnlage InV;
    OutVector_PosAnlage outV;
    unsigned char period=0;//????????
    //Infinite Loop 
    while(TRUE){
        if(getModelButtons(boardHandle, &InV)=! 1){
            break;
        }
        if(getModelSensors(boardHandle, &InV)!=1){
           break;
        }

        /*Realise with Treading or Multiprocessing?*/
        getModelButtons(boardHandle, &InV);
        getModelSensors(boardHandle, &InV);
        if (Automat(boardHandle,InV.T5, &outV, &InV)==0){
            printf("Error in Engine Handler");
            break;
        }
        /*Period unknown, */
        checkTime(init, period);
    }
    
}