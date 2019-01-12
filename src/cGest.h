/*
 * cGest.h
 *
 *  Created on: Jan 4, 2019
 *      Author: Ana
 */

#ifndef CGEST_H_
#define CGEST_H_

#include <stdint.h>
#include "gestureDefs.h"
//#include "gesture.h"

#include "cUart.h"
//#include "uart.h"
#include <stm32f4xx_hal.h>

class cGest {
public:
	cGest();
	virtual ~cGest();

	void setRDYPinToOutput();

	void setRDYPinToInput();

	void setRSTPinToOutput();


	void setRDYpin(uint8_t s);

	void setRSTpin(uint8_t s);

	uint8_t readRSTpin();

	uint8_t readRDYpin();

	void GestIC_Read(char msgLen);

	void GestIC_Write( uint8_t msgLen);

	//char setAirWheel(char ENABLE);

	//char setTouchDetection(char ENABLE);

	//char setApproachDetection(char ENABLE);
	/*
	This command is not anymore supported starting from V1.0 release.
	*/
	//char setApproachDetection2(char ENABLE);

	/* Parameters:
	0 - Enable All Gestures
	1 - Enable Only Flick Gestures
	2 - Enable in Addition Circles
	*/
	char setGestureProcessingHMM(char PARAM);

	char setCalibrationOperationMode(char ENABLE);

	/* Parameters:
	0 - Enable All Data
	1 - Enable DSP, Gestures and Noise Power
	2 - Enable Only Data: Noise (others not changed)
	3 - Disable Only Data: CIC (others not changed)
	*/
	char setDataOutputEnableMask(char PARAM);

	/* Parameters:
	0 - Lock All Data
	1 - Lock DSP, Gestures and Noise Power
	2 - Lock Only Data: Noise (others not changed)
	3 - UnLock Only Data: CIC (others not changed)
	*/
	char setDataOutputLockMask(char PARAM);

	/* Parameters:
	0 - Request All Data
	1 - Request DSP, Gestures and Noise Power
	2 - Request Only Data: Noise
	*/
	char setDataOutputRequestkMask(char PARAM);

	char setGestureInProgressFlag(char ENABLE);

	/* Parameters:
	0 - Store RTPs for AFE
	1 - Store RTPs for DSP
	2 - Store RTPs for System
	*/
	char setMakePersistent(char PARAM);
	/* Parameters:
	0 - Force Calibration
	1 - Enter Deep Sleep 1
	2 - Enter Deep Sleep 2
	*/
	char setTrigger(char PARAM);

	void setElectrodeMap(char Electrode, char Channel);

	void TransFreqSelect(char FreqCnt, unsigned long FreqOrder);

	void setEnableAllGestures();

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                           REQUEST FW_VERSION_INFO FROM MGC3130
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void getFWInfo();

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                     READ AND PARSE VALUES FROM GESTURE BOARD
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void updateRawData();
	void updateGestureData();
	void start();
	void parseData();
	/*  EOF user functions by Ana */

private:
	uint8_t raw_data[132];
	s_Gesture mGesture;

	cUart cu;
	unsigned int touch_evt, touch_evt_old;
	char gest_evt, gest_evt_old;// gest_class, gest_recognition, gest_edge_flick;
	unsigned int flag;
	unsigned int OLDAirWheelInfo=0;

};

#endif /* CGEST_H_ */
