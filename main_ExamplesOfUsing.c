#include "triggers16bit/DTrigger16bitV2_osm.h"

#define ON 1
#define OFF 0

struct RisingEdgesTrigInternalRegs16bit_t RisingEdgeTriggerReg, RisEdgeTReg;
struct D_TriggersInternalRegs16bit_t DTriggersReg;
unsigned char DI_RUNMotor = 0;
unsigned char DI_RUNPump = 0;
unsigned char DI_STOPMotor = 0;
unsigned char DQ_RUNMotor = 0;
unsigned char DQ_RUNPummp = 0;
unsigned char rotation = 0;
unsigned char doOnceSmthg = 0, doOnceSmthg2 = 0, doOnceSmthgBad = 0;
char testLaunchOfBad = 0;
char testLaunchOfGood = 0;
char ResetCmd = 0;
char i = 0;
char a = 0;
char b = 0;
char c = 0;
int BITs = 0;

int main(void)
{
	while (1)
	{
		BITs = tBIT0;
		BITs = tBIT7;
		BITs = tBIT5;
		BITs = tBIT4;
		BITs = tBIT6;
		RisingEdgeTrigger16bit((DI_RUNMotor * tBIT0) | (DI_RUNPump * tBIT5) | (DI_STOPMotor * tBIT4) | ((rotation == 1) * tBIT15) | ((a == 20) * tBIT6), tBIT0 | tBIT5 | tBIT4 | tBIT15 | tBIT6, &RisingEdgeTriggerReg);
		if ((RisingEdgeTriggerReg.Qre & tBIT0) == tBIT0)
		{
			DQ_RUNMotor = ON;
			a++;
		}
		if (RisingEdgeTriggerWithoutAffectToOtherbits(tBIT1 * doOnceSmthg, tBIT1, &RisingEdgeTriggerReg) == tBIT1) { //RisingEdgeTriggerOnlySpecBits //+! good name for func 
			b = 0;
		}
		if (RisingEdgeTriggerWithoutAffectToOtherbits(tBIT2 * doOnceSmthg2, tBIT2, &RisingEdgeTriggerReg) == tBIT2) {
			b = 33;
		}
		if (testLaunchOfBad)
		{
			RisingEdgeTrigger16bit(doOnceSmthgBad * tBIT7, tBIT7, &RisingEdgeTriggerReg);
			if ((RisingEdgeTriggerReg.Qre & tBIT7) == tBIT7) {
				b = 255;
			}
		}
		if ((RisingEdgeTriggerReg.Qre & tBIT1) == tBIT1)
		{
			b = 200;
		}
		if (testLaunchOfGood)
		{
			RisingEdgeTriggerWithoutAffectToOtherbits/*ForwardFrontTriggerWithoutAffectToOtherbits*/(!doOnceSmthgBad * tBIT7, tBIT7, &RisingEdgeTriggerReg);
			if (RisingEdgeTriggerWithoutAffectToOtherbits(tBIT3, tBIT3, &RisingEdgeTriggerReg) == tBIT3)
			{
				b = 3;
			}
			if ((RisingEdgeTriggerReg.Qre & tBIT7) == tBIT7) {
				b = 255;
			}
		}
		if (ResetCmd)
		{
			Reset_RisingEdgeTrigger16bit(tBIT3, &RisingEdgeTriggerReg);
			ResetCmd = 0;
		}
		if ((RisingEdgeTriggerReg.Qre & tBIT5) == tBIT5)
		{
			DQ_RUNPummp = ON;
			b++;
		}
		if ((RisingEdgeTriggerReg.Qre & tBIT4) == tBIT4)
		{
			i++;
			__noop();
		}
		if ((RisingEdgeTriggerReg.Qre & tBIT15) == tBIT15)
		{
			i = 0;
			__noop();
		}
		if ((RisingEdgeTriggerReg.Qre & tBIT6) == tBIT6)
		{
			a = 55;
		}
		D_Trigger16bit((DI_RUNMotor * tBIT13) | (DI_RUNPump * tBIT14) | (DI_STOPMotor * tBIT15), tBIT13 | tBIT14 | tBIT15, &DTriggersReg);
		if ((DTriggersReg.Q_Dtrig & tBIT13) == tBIT13)
		{
			DQ_RUNMotor = ON;
			a += 10;
		}
		if ((DTriggersReg.Q_Dtrig & tBIT14) == tBIT14)
		{
			DQ_RUNPummp = ON;
			b += 10;
		}
		if ((DTriggersReg.Q_Dtrig & tBIT15) == tBIT15)
		{
			i += 10;
			__noop();
		}
		int res;
		res = 0;
	}
	return 1;
}