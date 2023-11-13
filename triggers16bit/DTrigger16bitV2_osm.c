#include "DTrigger16bitV2_osm.h"

/*
  Copyright (c) 2019 Abdulhamidov Osim
  All rights reserved.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/


/*      ______________________________________________________________________________________          __          __________
    ___|                        a (uint) - 16 x IN signals or commandVars                     |________|  |________|
	 This is input signal:
        __                                                                                              __          __
    ___|  |______________ RisEdgeT.Qff  16 x Outs - Calculating process is logical parallel ___________|  |________|  |_______
	 This is output signal of EdgeTrigger:
   --->|--|<--- Tff - 1 cycle fully executed program (if ThisFunc() called once per one full programm cycle/while(1) for instance)
       A  A    or:
       |  |___ 2.Called ThisFunc() again on second time
       |______ 1.Called ThisFunc() time
*/
uint16_t RisingEdgeTrigger16bit(const uint16_t a, const uint16_t tBITx, struct RisingEdgesTrigInternalRegs16bit_t *RERegs)
{
    uint16_t sig = a & tBITx;
    (*RERegs).inputSignal = ((*RERegs).inputSignal & ~tBITx) | sig;
    (*RERegs).Qre = (*RERegs).inputSignal & (~(*RERegs).REdgeRegister);
    (*RERegs).REdgeRegister = (*RERegs).inputSignal;
	return (*RERegs).Qre;        //FFRegs->Qff;
}

// RisingEdgeTrigger16bitCallEverywhere() or name it like RisingEdgeTriggerOnlySpecBits() or RisingEdgeTriggerWithoutAffectToOthers()
// You can call this function anywhere. Safety function for *FFRegs
uint16_t RisingEdgeTriggerWithoutAffectToOtherbits(const uint16_t a, const uint16_t tBITx, struct RisingEdgesTrigInternalRegs16bit_t *RERegs)
{
    //stayAsItWas to don't affect to the another bits except the bits specified on tBITx
    //safely save the current bits states of Trigger
	volatile static struct RisingEdgesTrigInternalRegs16bit_t stayAsItLastRERegs; //or stayAsItWasRERegs
    stayAsItLastRERegs.inputSignal = (*RERegs).inputSignal;
    stayAsItLastRERegs.REdgeRegister = (*RERegs).REdgeRegister;
    stayAsItLastRERegs.Qre = (*RERegs).Qre;

    RisingEdgeTrigger16bit(a, tBITx, RERegs);  //work with specified bits

    //And then safely return back the other current bits states of Trigger mentioned on initial line of func
    (*RERegs).inputSignal |= (~tBITx & stayAsItLastRERegs.inputSignal);
    (*RERegs).Qre |= ((~tBITx) & (stayAsItLastRERegs.Qre));
    (*RERegs).REdgeRegister |= (~tBITx & stayAsItLastRERegs.REdgeRegister);

    return (*RERegs).Qre & tBITx;       //FFRegs->Qff; (as a variant)s
}


/*      __        _____           _           ______
    ___|  |______|     |_________| |_________|      |___ a (uint) - 16 x IN signals or commandVars
        _________                 ___________
    ___|         |_______________|           |__________ DTrig.Q_Dtrig  16 x Outs - Calculating process is logical parallel
*/
uint16_t D_Trigger16bit(const uint16_t a, const uint16_t tBITx, struct D_TriggersInternalRegs16bit_t* DTrigRegs)
{
	uint16_t sig = a & tBITx;
	(*DTrigRegs).inputSignal = ((*DTrigRegs).inputSignal & (~tBITx)) | sig;
	(*DTrigRegs).DtrigRegK1 = (*DTrigRegs).Q_Dtrig & (~(*DTrigRegs).inputSignal | (*DTrigRegs).DtrigRegK1);
	(*DTrigRegs).DtrigRegK2 = ((*DTrigRegs).DtrigRegK1 | (*DTrigRegs).DtrigRegK2) & (*DTrigRegs).inputSignal;
	(*DTrigRegs).Q_Dtrig = ((*DTrigRegs).inputSignal | (*DTrigRegs).Q_Dtrig) & (~(*DTrigRegs).DtrigRegK2);
	return (*DTrigRegs).Q_Dtrig;
}

/*	_______                                                                 __            _______
	       |_____________	a (uint) - 16 x IN signals or commandVars  ____|  |__________|       |_____
	        __                                                                 __                 __
	_______|  |__________	FallEdgeT.Qbf  ___________________________________|  |_______________|  |__

	   --->|--|<--- Tbf = Tff - 1 cycle fully executed program (if ThisFunc() called once per one full programm cycle/while(1) for instance)
	       A  A    or:
	       |  |___ 2.Called ThisFunc() again on second time
	       |______ 1.Called ThisFunc() time
*/
uint16_t FallingEdgeTrigger16bit(const uint16_t a, const uint16_t tBITx, struct FallingEdgesTrigInternalRegs16bit_t* FERegs)
{
	uint16_t sig = a & tBITx;
	(*FERegs).inputSignal = ((*FERegs).inputSignal & (~tBITx)) | sig;
	(*FERegs).FEdgeRegister = ((*FERegs).inputSignal | (*FERegs).FEdgeRegister) & (~(*FERegs).Qfe);
	(*FERegs).Qfe = ~(*FERegs).inputSignal & (*FERegs).FEdgeRegister;
	return (*FERegs).Qfe;
}

uint16_t FallingEdgeTriggerWithoutAffectToOtherbits(const uint16_t a, const uint16_t tBITx, struct FallingEdgesTrigInternalRegs16bit_t* FERegs)
{
	//stayAsItWas to don't affect to the another bits except the bits specified on tBITx
	//safely save the current bits states of Trigger
	volatile static struct FallingEdgesTrigInternalRegs16bit_t stayAsItLastFERegs;
	//just do: memcpy(&stayAsItLastFERegs, FERegs, sizeof(stayAsItLastFERegs);
	stayAsItLastFERegs.inputSignal = FERegs->inputSignal;
	stayAsItLastFERegs.FEdgeRegister = FERegs->FEdgeRegister;
	stayAsItLastFERegs.Qfe = FERegs->Qfe;

	FallingEdgeTrigger16bit(a, tBITx, FERegs);

	//And then safely return back the other current bits states of Trigger mentioned on initial line of func
	FERegs->inputSignal |= (~tBITx & stayAsItLastFERegs.inputSignal);
	FERegs->FEdgeRegister |= (~tBITx & stayAsItLastFERegs.FEdgeRegister);
	FERegs->Qfe |= (~tBITx & stayAsItLastFERegs.Qfe);

	return FERegs->Qfe & tBITx;
}

uint16_t D_TriggerWithoutAffectToOtherbits(const uint16_t a, const uint16_t tBITx, struct D_TriggersInternalRegs16bit_t* DTrigRegs)
{
	//testing in process in a little while.
	//stayAsItWas to don't affect to the another bits except the bits specified on tBITx
	//safely save the current bits states of Trigger
	volatile static struct D_TriggersInternalRegs16bit_t stayAsItLastDTRegs;

	stayAsItLastDTRegs.inputSignal = DTrigRegs->inputSignal;
	stayAsItLastDTRegs.DtrigRegK1 = DTrigRegs->DtrigRegK1;
	stayAsItLastDTRegs.DtrigRegK2 = DTrigRegs->DtrigRegK2;
	stayAsItLastDTRegs.Q_Dtrig = DTrigRegs->Q_Dtrig;
	// just do: memcpy();
	D_Trigger16bit(a, tBITx, DTrigRegs);

	//And then safely return back the other current bits states of Trigger mentioned on initial line of func
	DTrigRegs->inputSignal |= (~tBITx & stayAsItLastDTRegs.inputSignal);
	DTrigRegs->DtrigRegK1 |= (~tBITx & stayAsItLastDTRegs.DtrigRegK1);
	DTrigRegs->DtrigRegK2 |= (~tBITx & stayAsItLastDTRegs.DtrigRegK2);
	DTrigRegs->Q_Dtrig |= (~tBITx & stayAsItLastDTRegs.Q_Dtrig);
	return DTrigRegs->Q_Dtrig & tBITx;
}


unsigned char delayedPress16bit(uint16_t *countReg, unsigned char inputBit, unsigned char k)  //int have not sense
{
	if (inputBit != 0) { *countReg = *countReg + 1; }
	else { *countReg = 0; }
	if (*countReg == k)
	{
		*countReg = 0;
		return 1;
	}
	return 0;
}

/*
Example: ForwardFrontsInternalRegs16bit_t FwdFrTrig_MOTORs_Control;
         ForwardFrontsInternalRegs16bit_t FwdFrTrig_FANs_Control;
         int main(){...
	    ...
            Reset_ForwardFrontTrigger16bit(tBIT15 | tBIT3, &FwdFrTrig_MOTORs_Control);
	    Reset_ForwardFrontTrigger16bit(0xFFFF, &FwdFrTrig_FANs_Control);    //Reset all signals registers; or:
	    Reset_ForwardFrontTrigger16bit(tALLBITS, &FwdFrTrig_FANs_Control);    //Reset all signals registers;
*/
void Reset_RisingEdgeTrigger16bit(uint16_t tBITx, struct RisingEdgesTrigInternalRegs16bit_t *RERegs)
{
	(*RERegs).inputSignal &= ~tBITx;
	(*RERegs).REdgeRegister &= ~tBITx;
	(*RERegs).Qre &= ~tBITx;
	return;
}

void Reset_FallingEdgeTrigger16bit(uint16_t tBITx, struct FallingEdgesTrigInternalRegs16bit_t* FERegs)
{
	FERegs->inputSignal &= ~tBITx;
	FERegs->FEdgeRegister &= ~tBITx;
	FERegs->Qfe &= ~tBITx;
	return;
}

void Reset_D_Trigger16bit(uint16_t tBITx, struct D_TriggersInternalRegs16bit_t  *DTrigRegs)
{
	(*DTrigRegs).inputSignal &= ~tBITx;
	(*DTrigRegs).DtrigRegK1 &= ~tBITx;
	(*DTrigRegs).DtrigRegK2 &= ~tBITx;
	(*DTrigRegs).Q_Dtrig &= ~tBITx;
	return;
}