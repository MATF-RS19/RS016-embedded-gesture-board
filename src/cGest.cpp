/*
 * cGest.cpp
 *
 *  Created on: Jan 4, 2019
 *      Author: Ana
 */

#include "cGest.h"
#define GEST_I2CADDRESS 0x42

cGest::cGest() {
	// TODO Auto-generated constructor stub

}

cGest::~cGest() {
	// TODO Auto-generated destructor stub
}

void cGest::setRDYPinToOutput() {
	GPIO_InitTypeDef gpioInitStruct;
	//HAL_GPIO_StructInit(&gpioInitStruct);
	gpioInitStruct.Pin = GPIO_PIN_1;
	gpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpioInitStruct.Speed = GPIO_SPEED_FAST;
	gpioInitStruct.Pull = GPIO_PULLUP;
//	gpioInitStruct.Pull = GPIO_PULLDOWN;
//	gpioInitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &gpioInitStruct);
}

void cGest::setRDYPinToInput() {
	GPIO_InitTypeDef gpioInitStruct;
	//HAL_GPIO_StructInit(&gpioInitStruct);
	gpioInitStruct.Pin = GPIO_PIN_1;
	gpioInitStruct.Mode = GPIO_MODE_INPUT;
	gpioInitStruct.Speed = GPIO_SPEED_FAST;
//	gpioInitStruct.Pull = GPIO_PULLDOWN;
	gpioInitStruct.Pull = GPIO_PULLUP;
//	gpioInitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &gpioInitStruct);
}

void cGest::setRSTPinToOutput() {

	GPIO_InitTypeDef gpioInitStruct;
	//HAL_GPIO_StructInit(&gpioInitStruct);
	gpioInitStruct.Pin = GPIO_PIN_7;
	gpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpioInitStruct.Speed = GPIO_SPEED_FAST;
//	gpioInitStruct.Pull = GPIO_NOPULL;
	gpioInitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &gpioInitStruct);
}
/*
void setRSTPinToInput() {
	GPIO_InitTypeDef gpioInitStruct;
	//HAL_GPIO_StructInit(&gpioInitStruct);
	gpioInitStruct.Pin = GPIO_PIN_7;
	gpioInitStruct.Mode = GPIO_MODE_INPUT;
	gpioInitStruct.Speed = GPIO_SPEED_FAST;
	gpioInitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &gpioInitStruct);
}
*/

void cGest::setRDYpin(uint8_t s)
{
	if (s > 1)
		return;

	if (s == 1)
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
}

void cGest::setRSTpin(uint8_t s)
{
	if (s > 1)
		return;
	if (s == 1)
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
}



uint8_t cGest::readRDYpin()
{
	uint8_t temp;
	temp = GPIOC->IDR;
	temp = temp >> 1;
	temp = temp & 0b00000001;

	return temp;
	//		HAL_GPIO_ReadPin(GPIOC, 1);
}

void cGest::GestIC_Read(char msgLen){
 // I2C1_Start();
//  I2C1_Read(MGC_ADDR0, msgData, msgLen , END_MODE_STOP);
//  delay_us(200);
//	raw_data[0] = 0;
	//i2cApi_read(raw_data, msgLen);
	c.readData(raw_data, msgLen);
}

void cGest::GestIC_Write( uint8_t msgLen) {
//  I2C1_Start();
//  I2C1_Write(MGC_ADDR0,raw_data,msgLen,END_MODE_STOP);
//  delay_us(200);
	//i2cWrite(msgData+1, msgLen, msgData);
//	i2cWrite(1, 2, 3);
	//i2cApi_write(raw_data, msgLen);
	cGest::c.writeData(raw_data, msgLen);
}

char cGest::setAirWheel(char ENABLE) {
  ////////////////////////////////////////
  //             header
  ////////////////////////////////////////
  raw_data[0] = 0x10; //raw data size
  raw_data[1] = 0x00; //flags
  raw_data[2] = 0x00; //seq
  raw_data[3] = 0xA2; //ID
  ////////////////////////////////////////
  //             payload
  ////////////////////////////////////////
  raw_data[4] = 0x90; //Parameter ID
  raw_data[5] = 0x00;
  //reserved
  raw_data[6] = 0x00;
  raw_data[7] = 0x00;
  //Argument 0
  if (ENABLE) {
    raw_data[8] = 0x20; //MASK
  }else{
    raw_data[8] = 0x00; //MASK
  }
  raw_data[9] = 0x00;
  raw_data[10] = 0x00;
  raw_data[11] = 0x00;
  //Argument 1
  raw_data[12] = 0x20;
  raw_data[13] = 0x00;
  raw_data[14] = 0x00;
  raw_data[15] = 0x00;
  //Send data
  GestIC_Write(0x10);
  //ToDo: Read and parse error
  return 1;
}

char cGest::setTouchDetection(char ENABLE) {
  ////////////////////////////////////////
  //             header
  ////////////////////////////////////////
  raw_data[0] = 0x10; //raw data size
  raw_data[1] = 0x00; //flags
  raw_data[2] = 0x00; //seq
  raw_data[3] = 0xA2; //ID
  ////////////////////////////////////////
  //             payload
  ////////////////////////////////////////
  raw_data[4] = 0x97; //Parameter ID
  raw_data[5] = 0x00;
  //reserved
  raw_data[6] = 0x00;
  raw_data[7] = 0x00;
  //Argument 0
  if (ENABLE) {
    raw_data[8] = 0x08; //MASK
  }else{
    raw_data[8] = 0x00; //MASK
  }
  raw_data[9] = 0x00;
  raw_data[10] = 0x00;
  raw_data[11] = 0x00;
  //Argument 1
  raw_data[12] = 0x08;
  raw_data[13] = 0x00;
  raw_data[14] = 0x00;
  raw_data[15] = 0x00;
  //Send data
  GestIC_Write(0x10);
  //ToDo: Read and parse error
  return 1;
}

char cGest::setApproachDetection(char ENABLE) {
  ////////////////////////////////////////
  //             header
  ////////////////////////////////////////
  raw_data[0] = 0x10; //raw data size
  raw_data[1] = 0x00; //flags
  raw_data[2] = 0x00; //seq
  raw_data[3] = 0xA2; //ID
  ////////////////////////////////////////
  //             payload
  ////////////////////////////////////////
  raw_data[4] = 0x97; //Parameter ID
  raw_data[5] = 0x00;
  //reserved
  raw_data[6] = 0x00;
  raw_data[7] = 0x00;
  //Argument 0
  if (ENABLE) {
    raw_data[8] = 0x01; //MASK
  }else{
    raw_data[8] = 0x00; //MASK
  }
  raw_data[9] = 0x00;
  raw_data[10] = 0x00;
  raw_data[11] = 0x00;
  //Argument 1
  raw_data[12] = 0x01;
  raw_data[13] = 0x00;
  raw_data[14] = 0x00;
  raw_data[15] = 0x00;
  //Send data
  GestIC_Write(0x10);
  //ToDo: Read and parse error
  return 1;
}

/*
This command is not anymore supported starting from V1.0 release.
*/
char cGest::setApproachDetection2(char ENABLE) {
  ////////////////////////////////////////
  //             header
  ////////////////////////////////////////
  raw_data[0] = 0x10; //raw data size
  raw_data[1] = 0x00; //flags
  raw_data[2] = 0x00; //seq
  raw_data[3] = 0xA2; //ID
  ////////////////////////////////////////
  //             payload
  ////////////////////////////////////////
  raw_data[4] = 0x81; //Parameter ID
  raw_data[5] = 0x00;
  //reserved
  raw_data[6] = 0x00;
  raw_data[7] = 0x00;
  //Argument 0
  if (ENABLE) {
    raw_data[8] = 0x01; //MASK
  }else{
    raw_data[8] = 0x00; //MASK
  }
  raw_data[9] = 0x00;
  raw_data[10] = 0x00;
  raw_data[11] = 0x00;
  //Argument 1
  raw_data[12] = 0x01;
  raw_data[13] = 0x00;
  raw_data[14] = 0x00;
  raw_data[15] = 0x00;
  //Send data
  GestIC_Write(0x10);
  //ToDo: Read and parse error
  return 1;
}

/* Parameters:
0 - Enable All Gestures
1 - Enable Only Flick Gestures
2 - Enable in Addition Circles
*/
char cGest::setGestureProcessingHMM(char PARAM) {
  ////////////////////////////////////////
  //             header
  ////////////////////////////////////////
  raw_data[0] = 0x10; //raw data size
  raw_data[1] = 0x00; //flags
  raw_data[2] = 0x00; //seq
  raw_data[3] = 0xA2; //ID
  ////////////////////////////////////////
  //             payload
  ////////////////////////////////////////
  raw_data[4] = 0x85; //Parameter ID
  raw_data[5] = 0x00;
  //reserved
  raw_data[6] = 0x00;
  raw_data[7] = 0x00;
  switch (PARAM) {
    case 1:
      raw_data[8] = 0x1F;
      raw_data[12] = 0x7F;
      break;
    case 2:
      raw_data[8] = 0x60;
      raw_data[12] = 0x60;
      break;
    default:
      raw_data[8] = 0x7F;
      raw_data[12] = 0x7F;
  }
  //Argument 0
  raw_data[9] = 0x00;
  raw_data[10] = 0x00;
  raw_data[11] = 0x00;
  //Argument 1
  raw_data[13] = 0x00;
  raw_data[14] = 0x00;
  raw_data[15] = 0x00;
  //Send data
  GestIC_Write(0x10);
  //ToDo: Read and parse error
  return 1;
}

char cGest::setCalibrationOperationMode(char ENABLE) {
  ////////////////////////////////////////
  //             header
  ////////////////////////////////////////
  raw_data[0] = 0x10; //raw data size
  raw_data[1] = 0x00; //flags
  raw_data[2] = 0x00; //seq
  raw_data[3] = 0xA2; //ID
  ////////////////////////////////////////
  //             payload
  ////////////////////////////////////////
  raw_data[4] = 0x80; //Parameter ID
  raw_data[5] = 0x00;
  //reserved
  raw_data[6] = 0x00;
  raw_data[7] = 0x00;
  //Argument 0
  if (ENABLE) {
    raw_data[8] = 0x00; //MASK
  }else{
    raw_data[8] = 0x3F; //MASK
  }
  raw_data[9] = 0x00;
  raw_data[10] = 0x00;
  raw_data[11] = 0x00;
  //Argument 1
  raw_data[12] = 0x3F;
  raw_data[13] = 0x00;
  raw_data[14] = 0x00;
  raw_data[15] = 0x00;
  //Send data
  GestIC_Write(0x10);
  //ToDo: Read and parse error
  return 1;
}

/* Parameters:
0 - Enable All Data
1 - Enable DSP, Gestures and Noise Power
2 - Enable Only Data: Noise (others not changed)
3 - Disable Only Data: CIC (others not changed)
*/
char cGest::setDataOutputEnableMask(char PARAM) {
  ////////////////////////////////////////
  //             header
  ////////////////////////////////////////
  raw_data[0] = 0x10; //raw data size
  raw_data[1] = 0x00; //flags
  raw_data[2] = 0x00; //seq
  raw_data[3] = 0xA2; //ID
  ////////////////////////////////////////
  //             payload
  ////////////////////////////////////////
  raw_data[4] = 0xA0; //Parameter ID
  raw_data[5] = 0x00;
  //reserved
  raw_data[6] = 0x00;
  raw_data[7] = 0x00;
  switch (PARAM) {
    case 1:
      raw_data[8] = 0x23;
      raw_data[9] = 0x00;
      raw_data[12] = 0x3F;
      raw_data[13] = 0x18;
      break;
    case 2:
      raw_data[8] = 0x10;
      raw_data[9] = 0x00;
      raw_data[12] = 0x10;
      raw_data[13] = 0x00;
      break;
     case 3:
      raw_data[8] = 0x00;
      raw_data[9] = 0x00;
      raw_data[12] = 0x00;
      raw_data[13] = 0x08;
      break;
    default:
      raw_data[8] = 0x3F;
      raw_data[9] = 0x18;
      raw_data[12] = 0x3F;
      raw_data[13] = 0x18;
  }
  //Argument 0
  raw_data[10] = 0x00;
  raw_data[11] = 0x00;
  //Argument 1
  raw_data[14] = 0x00;
  raw_data[15] = 0x00;
  //Send data
  GestIC_Write(0x10);
  //ToDo: Read and parse error
  return 1;
}

/* Parameters:
0 - Lock All Data
1 - Lock DSP, Gestures and Noise Power
2 - Lock Only Data: Noise (others not changed)
3 - UnLock Only Data: CIC (others not changed)
*/
char cGest::setDataOutputLockMask(char PARAM) {
  ////////////////////////////////////////
  //             header
  ////////////////////////////////////////
  raw_data[0] = 0x10; //raw data size
  raw_data[1] = 0x00; //flags
  raw_data[2] = 0x00; //seq
  raw_data[3] = 0xA2; //ID
  ////////////////////////////////////////
  //             payload
  ////////////////////////////////////////
  raw_data[4] = 0xA1; //Parameter ID
  raw_data[5] = 0x00;
  //reserved
  raw_data[6] = 0x00;
  raw_data[7] = 0x00;
  switch (PARAM) {
    case 1:
      raw_data[8] = 0x23;
      raw_data[9] = 0x00;
      raw_data[12] = 0x3F;
      raw_data[13] = 0x18;
      break;
    case 2:
      raw_data[8] = 0x10;
      raw_data[9] = 0x00;
      raw_data[12] = 0x10;
      raw_data[13] = 0x00;
      break;
     case 3:
      raw_data[8] = 0x00;
      raw_data[9] = 0x00;
      raw_data[12] = 0x00;
      raw_data[13] = 0x08;
      break;
    default:
      raw_data[8] = 0x3F;
      raw_data[9] = 0x18;
      raw_data[12] = 0x3F;
      raw_data[13] = 0x18;
  }
  //Argument 0
  raw_data[10] = 0x00;
  raw_data[11] = 0x00;
  //Argument 1
  raw_data[14] = 0x00;
  raw_data[15] = 0x00;
  //Send data
  GestIC_Write(0x10);
  //ToDo: Read and parse error
  return 1;
}

/* Parameters:
0 - Request All Data
1 - Request DSP, Gestures and Noise Power
2 - Request Only Data: Noise
*/
char cGest::setDataOutputRequestkMask(char PARAM) {
  ////////////////////////////////////////
  //             header
  ////////////////////////////////////////
  raw_data[0] = 0x10; //raw data size
  raw_data[1] = 0x00; //flags
  raw_data[2] = 0x00; //seq
  raw_data[3] = 0xA2; //ID
  ////////////////////////////////////////
  //             payload
  ////////////////////////////////////////
  raw_data[4] = 0xA2; //Parameter ID
  raw_data[5] = 0x00;
  //reserved
  raw_data[6] = 0x00;
  raw_data[7] = 0x00;
  switch (PARAM) {
    case 1:
      raw_data[8] = 0x23;
      raw_data[9] = 0x00;
      raw_data[12] = 0x3F;
      raw_data[13] = 0x18;
      break;
    case 2:
      raw_data[8] = 0x10;
      raw_data[9] = 0x00;
      raw_data[12] = 0x10;
      raw_data[13] = 0x00;
      break;
    default:
      raw_data[8] = 0x3F;
      raw_data[9] = 0x18;
      raw_data[12] = 0x3F;
      raw_data[13] = 0x18;
  }
  //Argument 0
  raw_data[10] = 0x00;
  raw_data[11] = 0x00;
  //Argument 1
  raw_data[14] = 0x00;
  raw_data[15] = 0x00;
  //Send data
  GestIC_Write(0x10);
  //ToDo: Read and parse error
  return 1;
}

char cGest::setGestureInProgressFlag(char ENABLE) {
  ////////////////////////////////////////
  //             header
  ////////////////////////////////////////
  raw_data[0] = 0x10; //raw data size
  raw_data[1] = 0x00; //flags
  raw_data[2] = 0x00; //seq
  raw_data[3] = 0xA2; //ID
  ////////////////////////////////////////
  //             payload
  ////////////////////////////////////////
  raw_data[4] = 0xA3; //Parameter ID
  raw_data[5] = 0x00;
  //reserved
  raw_data[6] = 0x00;
  raw_data[7] = 0x00;
  //Argument 0
  if (ENABLE) {
    raw_data[8] = 0x01; //MASK
  }else{
    raw_data[8] = 0x00; //MASK
  }
  raw_data[9] = 0x00;
  raw_data[10] = 0x00;
  raw_data[11] = 0x00;
  //Argument 1
  raw_data[12] = 0x01;
  raw_data[13] = 0x00;
  raw_data[14] = 0x00;
  raw_data[15] = 0x00;
  //Send data
  GestIC_Write(0x10);
  //ToDo: Read and parse error
  return 1;
}

/* Parameters:
0 - Store RTPs for AFE
1 - Store RTPs for DSP
2 - Store RTPs for System
*/
char cGest::setMakePersistent(char PARAM) {
  ////////////////////////////////////////
  //             header
  ////////////////////////////////////////
  raw_data[0] = 0x10; //raw data size
  raw_data[1] = 0x00; //flags
  raw_data[2] = 0x00; //seq
  raw_data[3] = 0xA2; //ID
  ////////////////////////////////////////
  //             payload
  ////////////////////////////////////////
  raw_data[4] = 0x00; //Parameter ID
  raw_data[5] = 0xFF;
  //reserved
  raw_data[6] = 0x00;
  raw_data[7] = 0x00;
  switch (PARAM) {
    case 1:
      raw_data[8] = 0x01;
      break;
    case 2:
      raw_data[8] = 0x02;
      break;
    default:
      raw_data[8] = 0x00;
  }
  //Argument 0
  raw_data[9] = 0x00;
  raw_data[10] = 0x00;
  raw_data[11] = 0x00;
  //Argument 1
  raw_data[12] = 0x00;
  raw_data[13] = 0x00;
  raw_data[14] = 0x00;
  raw_data[15] = 0x00;
  //Send data
  GestIC_Write(0x10);
  //ToDo: Read and parse error
  return 1;
}

/* Parameters:
0 - Force Calibration
1 - Enter Deep Sleep 1
2 - Enter Deep Sleep 2
*/
char cGest::setTrigger(char PARAM) {
  ////////////////////////////////////////
  //             header
  ////////////////////////////////////////
  raw_data[0] = 0x10; //raw data size
  raw_data[1] = 0x00; //flags
  raw_data[2] = 0x00; //seq
  raw_data[3] = 0xA2; //ID
  ////////////////////////////////////////
  //             payload
  ////////////////////////////////////////
  raw_data[4] = 0x00; //Parameter ID
  raw_data[5] = 0x10;
  //reserved
  raw_data[6] = 0x00;
  raw_data[7] = 0x00;
  switch (PARAM) {
    case 1:
      raw_data[8] = 0x02;
      break;
    case 2:
      raw_data[8] = 0x03;
      break;
    default:
      raw_data[8] = 0x00;
  }
  //Argument 0
  raw_data[9] = 0x00;
  raw_data[10] = 0x00;
  raw_data[11] = 0x00;
  //Argument 1
  raw_data[12] = 0x00;
  raw_data[13] = 0x00;
  raw_data[14] = 0x00;
  raw_data[15] = 0x00;
  //Send data
  GestIC_Write(0x10);
  //ToDo: Read and parse error
  return 1;
}

void cGest::setElectrodeMap(char Electrode, char Channel) {
  ////////////////////////////////////////
  //             header
  ////////////////////////////////////////
  raw_data[0] = 0x10; //raw data size
  raw_data[1] = 0x00; //flags
  raw_data[2] = 0x00; //seq
  raw_data[3] = 0xA2; //ID
  ////////////////////////////////////////
  //             payload
  ////////////////////////////////////////
  raw_data[4] = Electrode; //Parameter ID
  raw_data[5] = 0x00;
  //reserved
  raw_data[6] = 0x00;
  raw_data[7] = 0x00;
  //Argument 0
  raw_data[8] = Channel;
  raw_data[9] = 0x00;
  raw_data[10] = 0x00;
  raw_data[11] = 0x00;
  //Argument 1
  raw_data[12] = 0x00;
  raw_data[13] = 0x00;
  raw_data[14] = 0x00;
  raw_data[15] = 0x00;
  //Send data
  GestIC_Write(0x10);

}

void cGest::TransFreqSelect(char FreqCnt, unsigned long FreqOrder) {
  ////////////////////////////////////////
  //             header
  ////////////////////////////////////////
  raw_data[0] = 0x10; //raw data size
  raw_data[1] = 0x00; //flags
  raw_data[2] = 0x00; //seq
  raw_data[3] = 0xA2; //ID
  ////////////////////////////////////////
  //             payload
  ////////////////////////////////////////
  raw_data[4] = 0x82; //Parameter ID
  raw_data[5] = 0x00;
  //reserved
  raw_data[6] = 0x00;
  raw_data[7] = 0x00;
  //Argument 0
  raw_data[8] = FreqCnt;
  raw_data[9] = 0x00;
  raw_data[10] = 0x00;
  raw_data[11] = 0x00;
  //Argument 1
  raw_data[12] = (char)(FreqOrder & 0x000000FF);
  raw_data[13] = (char)((FreqOrder >> 8) & 0x000000FF);
  raw_data[14] = (char)((FreqOrder >> 16) & 0x000000FF);
  raw_data[15] = (char)((FreqOrder >> 24) & 0x000000FF);
  //Send data
  GestIC_Write(0x10);
}

void cGest::setEnableAllGestures() {
  //header
  raw_data[0] = 0x10; //raw data size
  raw_data[1] = 0x00; //flags
  raw_data[2] = 0x00; //seq
  raw_data[3] = 0xA2; //ID
  //payload
  raw_data[4] = 0x85; //param ID
  raw_data[5] = 0x00;

  raw_data[6] = 0x00;
  raw_data[7] = 0x00;

  raw_data[8] = 0x7F; //DATA OUTPUT MASK
  raw_data[9] = 0x00;
  raw_data[10] = 0x00;
  raw_data[11] = 0x00;

  raw_data[12] = 0x7F;
  raw_data[13] = 0x00;
  raw_data[14] = 0x00;
  raw_data[15] = 0x00;

  GestIC_Write(0x10);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                           REQUEST FW_VERSION_INFO FROM MGC3130
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void cGest::getFWInfo() {
  char i;
  //MGC_RST = 0;
  setRSTpin(0);
  //send msg to request fw info
  raw_data[0] = 0x0C;
  raw_data[1] = 0x00;
  raw_data[2] = 0x00;
  raw_data[3] = 0x06;
  raw_data[4] = 0x83;
  raw_data[5] = 0x00;
  raw_data[6] = 0x00;
  raw_data[7] = 0x00;
  raw_data[8] = 0x00;
  raw_data[9] = 0x00;
  raw_data[10] = 0x00;
  raw_data[11] = 0x00;
  //MGC_RST = 1;
  setRSTpin(1);
  HAL_Delay(10);
  GestIC_Write(0x0C);
//  while(MGC_RDY_IN);
  while(readRDYpin() == 1)
  {}
  //raw_data[0] = 0x00;
  GestIC_Read(0x84);
  HAL_Delay(10);
  //Parse values
  mGesture.FWVersionInfo.FWValid = raw_data[4];
  mGesture.FWVersionInfo.HWRev[0] = raw_data[5];
  mGesture.FWVersionInfo.HWRev[1] = raw_data[6];
  mGesture.FWVersionInfo.ParameterStartAddr = raw_data[7];
  mGesture.FWVersionInfo.LibraryLoaderVersion[0] = raw_data[8];
  mGesture.FWVersionInfo.LibraryLoaderVersion[1] = raw_data[9];
  mGesture.FWVersionInfo.LibraryLoaderVersion[3] = raw_data[10];
  mGesture.FWVersionInfo.FwStartAddr = raw_data[11];
  //
  for (i=0; i<120; i++) {
     mGesture.FWVersionInfo.FwVersion[i] = raw_data[i+12];
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                     READ AND PARSE VALUES FROM GESTURE BOARD
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void cGest::updateRawData() {
  GestIC_Read(64);
}

void cGest::start()
{
	c.init(GEST_I2CADDRESS);
	getFWInfo();
	HAL_Delay(2000);
    if((uint8_t)(mGesture.FWVersionInfo.FWValid) == (uint8_t)FW_VALID)
	{
		  trace_printf("VALID FW!");
	}
	else
	{
		  trace_printf("INVALID FW! HALT PROGRAM!");
		  while(1);
	}
}

void cGest::updateGestureData() {
    //while (MGC_RDY_IN);
	while(readRDYpin())
	{}
    //GPIO_Digital_Output (&GPIOD_BASE, _GPIO_PINMASK_10);
    setRDYPinToOutput();
    //MGC_RDY_OUT = 0;                                    //Assert TS
    setRDYpin(0);
    GestIC_Read(32);
    //Parse values
    mGesture.DataOut.Len = raw_data[0];
    mGesture.DataOut.Flags = raw_data[1];
    mGesture.DataOut.Seq = raw_data[2];
    mGesture.DataOut.Id = raw_data[3];
    mGesture.DataOut.ConfigMask = (raw_data[5] << 8) + raw_data[4];
    mGesture.DataOut.TimeStamp = raw_data[6];
    mGesture.DataOut.SystemInfo = raw_data[7];
    mGesture.DataOut.DSPStatus = (raw_data[9] << 8) + raw_data[8];
    mGesture.DataOut.GestureInfo = (raw_data[13] << 24) + (raw_data[12] << 16) + (raw_data[11] << 8) + raw_data[10];
    mGesture.DataOut.TouchInfo = (raw_data[17] << 24) + (raw_data[16] << 16) + (raw_data[15] << 8) + raw_data[14];
    mGesture.DataOut.AirWheelInfo = (raw_data[19] << 8) + raw_data[18];
    mGesture.DataOut.Position.X = (raw_data[21] << 8) + raw_data[20];
    mGesture.DataOut.Position.Y = (raw_data[23] << 8) + raw_data[22];
    mGesture.DataOut.Position.Z = (raw_data[25] << 8) + raw_data[24];
    //MGC_RDY_OUT = 1;                                  //Release TS to new measurement
    setRDYpin(1);
    //GPIO_Digital_Input (&GPIOD_BASE, _GPIO_PINMASK_10);
    setRDYPinToInput();
}

void cGest::parseData()
{
	uint8_t temp = 0;
	touch_evt = (unsigned int) mGesture.DataOut.TouchInfo & 0xFFFF;
	    if ((touch_evt != 0) && (touch_evt != touch_evt_old))
	    {

	      if(touch_evt < 0x00000201)
	      {
	        flag=1;

	/*
	        if(touch_evt & TouchSouth) trace_printf("touch south\r\n");
	        if(touch_evt & TouchWest) trace_printf("touch west\r\n");
	        if(touch_evt & TouchNorth) trace_printf("touch north\r\n");
	        if(touch_evt & TouchEast) trace_printf("touch east\r\n");
	        //if(touch_evt & TouchSouth) TFT_WRITE_TEXT("TOUCH SOUTH",120,90);
	        if(touch_evt & TouchCenter) trace_printf("touch center\r\n");
	*/
	        if(touch_evt & TapSouth)  temp = 7; //uartSendGestureData(7);     //trace_printf("tap south\r\n");
	        if(touch_evt & TapWest)   temp = 9; //uartSendGestureData(9);     //trace_printf("tap west\r\n");
	        if(touch_evt & TapNorth)  temp = 6; //uartSendGestureData(6);     //trace_printf("tap north\r\n");
	        if(touch_evt & TapEast)   temp = 8; //uartSendGestureData(8);     //trace_printf("tap east\r\n");
	        if(touch_evt & TapCenter) temp = 14; //uartSendGestureData(14);    //trace_printf("tap center\r\n");
	        cu.send(&temp, 1);
	      }
	      else
	      {
	        if(touch_evt & DoubleTapSouth)  temp = 11; //uartSendGestureData(11); //trace_printf("double tap south\r\n");
	        if(touch_evt & DoubleTapWest)   temp = 7; //uartSendGestureData(7); //trace_printf("double tap west\r\n");
	        if(touch_evt & DoubleTapNorth)  temp = 13;//uartSendGestureData(13);  //trace_printf("double tap north\r\n");
	        if(touch_evt & DoubleTapEast)   temp = 12;//uartSendGestureData(12);  //trace_printf("double tap east\r\n");
	        if(touch_evt & DoubleTapCenter) temp = 15;//uartSendGestureData(15);//trace_printf("double tap center\r\n");
	      }
	      touch_evt_old = touch_evt;
	    }


	    gest_evt = (char) mGesture.DataOut.GestureInfo & 0xFF;
	    gest_class = (char) (mGesture.DataOut.GestureInfo >> 12) & 0x0F;
	    gest_edge_flick = (char) (mGesture.DataOut.GestureInfo >> 16) & 0x01;
	    gest_recognition = (char) (mGesture.DataOut.GestureInfo >> 31) & 0x01;

	    if (gest_evt)
	    {
	    	temp = gest_evt;//uartSendGestureData(gest_evt);
	    	cu.send(&temp, 1);
	    }



	    if (mGesture.DataOut.AirWheelInfo !=0)
	    {

	      if (mGesture.DataOut.AirWheelInfo > OLDAirWheelInfo)            // if the airwheel counter increments,// it is a clockwise rotation
	      {
	        temp = 16;//uartSendGestureData(16);
	      }
	      else if  (mGesture.DataOut.AirWheelInfo < OLDAirWheelInfo)                       // if it decrements, // it is counter-clokwise
	      {
	        temp = 17;//uartSendGestureData(17);
	      }
	                                                        // print out the airwheel counter info
	      OLDAirWheelInfo=mGesture.DataOut.AirWheelInfo;
	      cu.send(&temp,1);
	    }
}
