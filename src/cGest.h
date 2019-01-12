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
#include "cUart.h"

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

	char setTrigger(char PARAM);

	void setEnableAllGestures();

	void getFWInfo();

	void updateGestureData();
	void start();
	void parseData();

private:
	uint8_t rawData[132];
	s_Gesture mGesture;

	cUart cu;
	unsigned int touchEvent, touchEventOld;
	char gestEvent, gestEventOld;
	unsigned int OLDAirWheelInfo;
};

#endif /* CGEST_H_ */
