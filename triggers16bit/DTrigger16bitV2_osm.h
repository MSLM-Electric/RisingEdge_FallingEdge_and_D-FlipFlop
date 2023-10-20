//#pragma once
#ifndef DTRIGGER16BITV2_OSM_h
#define DTRIGGER16BITV2_OSM_h

#if DTRIGGERV2_OSM_h
#include "DTriggerV2_osm.h"  //8bit implementation
#endif

#include <stdint.h>

/******************defines********************/
#define tALLBITS (uint16_t)0xFFFF
#define	tBIT15  (uint16_t)0x8000
#define	tBIT14  (uint16_t)0x4000
#define	tBIT13  (uint16_t)0x2000
#define	tBIT12  (uint16_t)0x1000
#define	tBIT11  (uint16_t)0x0800
#define	tBIT10  (uint16_t)0x0400
#define	tBIT9  (uint16_t)0x0200
#define	tBIT8  (uint16_t)0x0100

#ifndef DTRIGGERV2_OSM_h
#define	tBIT7  (uint16_t)0x0080
#define	tBIT6  (uint16_t)0x0040
#define	tBIT5  (uint16_t)0x0020
#define	tBIT4  (uint16_t)0x0010
#define	tBIT3  (uint16_t)0x0008
#define	tBIT2  (uint16_t)0x0004
#define	tBIT1  (uint16_t)0x0002
#define	tBIT0  (uint16_t)0x0001
#endif
/**********************************************/

//typedef enum
//{
//	tBIT15 = 0x8000,
//	tBIT14 = 0x4000,
//	tBIT13 = 0x2000,
//	tBIT12 = 0x1000,
//	tBIT11 = 0x0800,
//	tBIT10= 0x0400,
//	tBIT9 = 0x0200,
//	tBIT8 = 0x0100,
//	tBIT7 = 0x0080,
//	tBIT6 = 0x0040,
//	tBIT5 = 0x0020,
//	tBIT4 = 0x0010,
//	tBIT3 = 0x0008,
//	tBIT2 = 0x0004,
//	tBIT1 = 0x0002,
//	tBIT0 = 0x0001
//}BITxmask_type;

struct RisingEdgesTrigInternalRegs16bit_t
{
    uint16_t inputSignal;
    uint16_t REdgeRegister;
    uint16_t Qre;
};

struct FallingEdgesTrigInternalRegs16bit_t  //Ýòà ñòðóêòóðà ïîõîæà íà âåðõíþþ, òàê ÷òî ìîæíî îáîáùàòü-îáúåäèíÿòü (ò.å ýòî óäàëÿòü è âåðõíåå óíèâåðñàëèçîâàâ ïðèìåíÿòü)
{
    uint16_t inputSignal;
    uint16_t FEdgeRegister;
    uint16_t Qfe;
};

struct D_TriggersInternalRegs16bit_t
{
    uint16_t DtrigRegK1;
    uint16_t DtrigRegK2;
    uint16_t inputSignal;
    uint16_t Q_Dtrig;
};


uint16_t RisingEdgeTrigger16bit(const uint16_t a, const uint16_t tBITx, struct RisingEdgesTrigInternalRegs16bit_t *RERegs);
uint16_t FallingEdgeTrigger16bit(const uint16_t a, const uint16_t tBITx, struct FallingEdgesTrigInternalRegs16bit_t *FERegs);
uint16_t D_Trigger16bit(const uint16_t a, const uint16_t tBITx, struct D_TriggersInternalRegs16bit_t *DTrigRegs);
unsigned char delayedPress16bit(uint16_t *countReg, unsigned char inputBit, unsigned char k);
void Reset_RisingEdgeTrigger16bit(uint16_t tBITx, struct RisingEdgesTrigInternalRegs16bit_t *RERegs);
void Reset_FallingEdgeTrigger16bit(uint16_t tBITx, struct FallingEdgesTrigInternalRegs16bit_t *FERegs);
void Reset_D_Trigger16bit(uint16_t tBITx, struct D_TriggersInternalRegs16bit_t *DTrigRegs);
uint16_t RisingEdgeTriggerWithoutAffectToOtherbits(const uint16_t a, const uint16_t tBITx, struct RisingEdgesTrigInternalRegs16bit_t *RERegs);
uint16_t FallingEdgeTriggerWithoutAffectToOtherbits(const uint16_t a, const uint16_t tBITx, struct FallingEdgesTrigInternalRegs16bit_t* FERegs);
uint16_t D_TriggerWithoutAffectToOtherbits(const uint16_t a, const uint16_t tBITx, struct D_TriggersInternalRegs16bit_t* DTrigRegs);

void Reset_RisingEdgeTriggerOnlySpecBit(uint16_t tBITx, struct RisingEdgesTrigInternalRegs16bit_t* RERegs);
void Reset_FallingEdgeTriggerOnlySpecBit(uint16_t tBITx, struct FallingEdgesTrigInternalRegs16bit_t* FERegs);
void Reset_D_TriggerOnlySpecBit(uint16_t tBITx, struct D_TriggersInternalRegs16bit_t* DTrigRegs);
#endif // !DTRIGGER16BITV2_OSM_h

