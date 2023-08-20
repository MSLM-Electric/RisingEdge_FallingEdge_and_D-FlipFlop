#include "triggers16bit/DTrigger16bitV2_osm.h"

#define ON 1
#define OFF 0

static void YourINIT(void) {return;};
static int ds18b20ReadTemp(int*, int*, int*);
static void DrawSettinsMenuByLCD(void) { return; };

/* Register some signals to RiseEdgeTriggerReg as you want :
DI_RUNMotor - tBIT0
DI_RUNPummp - tBIT5
ReadTSensorOnce command - tBIT4
DI_STOPMotor - tBIT1
Draw something by LCD only once at begining - tBIT15

  Register/allocate some signals to D_TriggerRegisterForSomeButtons :
DI_cmdButtonPress - tBIT0
DI_StartStopPress - tBIT5
*/

unsigned char DI_RUNMotor = 0;
unsigned char DI_RUNPump = 0;
unsigned char DI_STOPMotor = 0;
unsigned char DQ_RUNMotor = 0;
unsigned char DQ_RUNPummp = 0;
unsigned char ReadTSensorOnce_cmd = 0;

uint8_t DI_cmdButtonPress = 0;
uint8_t buttonPressSwitchedStateTo = 0;
uint16_t incrementWhenButtonPressSwitched = 0;
uint8_t DI_StartStopPress;
uint8_t DQ_ProcesStarted = 0;
struct D_TriggersInternalRegs16bit_t D_TriggerRegisterForSomeButtons;

struct RisingEdgesTrigInternalRegs16bit_t RiseEdgeTriggerReg;
int main(void)
{
	YourINIT();
	while (1)
	{
		RisingEdgeTrigger16bit((DI_RUNMotor * tBIT0) | (DI_RUNPump * tBIT5) | (ReadTSensorOnce_cmd * tBIT4) | (1 * tBIT15), tBIT0 | tBIT5 | tBIT4 | tBIT15, &RiseEdgeTriggerReg);
		if((RiseEdgeTriggerReg.Qre & tBIT0) == tBIT0)
		{
			DQ_RUNMotor = ON;
		}
		if((RiseEdgeTriggerReg.Qre & tBIT5) == tBIT5)
		{
			DQ_RUNPummp = ON;
		}
		if((RiseEdgeTriggerReg.Qre & tBIT4) == tBIT4)
		{
			int ds18b20_1wireUnit, Tsensor2Address, data;
			ds18b20ReadTemp(&ds18b20_1wireUnit, &Tsensor2Address, &data);
		}
		if((RiseEdgeTriggerReg.Qre & tBIT15) == tBIT15)
		{
			DrawSettinsMenuByLCD();
		}
		D_Trigger16bit((DI_cmdButtonPress * tBIT0) | (DI_StartStopPress * tBIT5), tBIT0 | tBIT5, &D_TriggerRegisterForSomeButtons);
		if (D_TriggerRegisterForSomeButtons.Q_Dtrig & tBIT0)
		{
			buttonPressSwitchedStateTo = 1;
			incrementWhenButtonPressSwitched++;
		}else{
			buttonPressSwitchedStateTo = 0;
		}
		if (D_TriggerRegisterForSomeButtons.Q_Dtrig & tBIT5) {
			DQ_ProcesStarted = 1;
		}else {
			DQ_ProcesStarted = 0;
		}
	}
}

int ds18b20ReadTemp(int* ds18b20_1wireUnit, int* TsensorAddress, int* data)
{
	return 1;
}