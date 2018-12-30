#include <stm32f4xx_hal.h>
#include <stdint.h>
#include "i2c.h"
#include "gestureDefs.h"
#include "gesture.h"



static uint8_t raw_data[132];
s_Gesture mGesture;
/*
uint8_t MGC_RST;
uint8_t MGC_RDY_IN;
uint8_t MGC_RDY_OUT;
*/

void setRDYPinToOutput() {
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

void setRDYPinToInput() {
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

void setRSTPinToOutput() {

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

void setRDYpin(uint8_t s)
{
	if (s > 1)
		return;

	if (s == 1)
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
}

void setRSTpin(uint8_t s)
{
	if (s > 1)
		return;
	if (s == 1)
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
}



uint8_t readRDYpin()
{
	uint8_t temp;
	temp = GPIOC->IDR;
	temp = temp >> 1;
	temp = temp & 0b00000001;

	return temp;
	//		HAL_GPIO_ReadPin(GPIOC, 1);
}

void GestIC_Read(char msgLen){
 // I2C1_Start();
//  I2C1_Read(MGC_ADDR0, msgData, msgLen , END_MODE_STOP);
//  delay_us(200);
//	raw_data[0] = 0;
	i2cApi_read(raw_data, msgLen);
}

void GestIC_Write( uint8_t msgLen) {
//  I2C1_Start();
//  I2C1_Write(MGC_ADDR0,raw_data,msgLen,END_MODE_STOP);
//  delay_us(200);
	//i2cWrite(msgData+1, msgLen, msgData);
//	i2cWrite(1, 2, 3);
	i2cApi_write(raw_data, msgLen);

}

char setAirWheel(char ENABLE) {
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

char setTouchDetection(char ENABLE) {
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

char setApproachDetection(char ENABLE) {
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
char setApproachDetection2(char ENABLE) {
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
char setGestureProcessingHMM(char PARAM) {
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

char setCalibrationOperationMode(char ENABLE) {
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
char setDataOutputEnableMask(char PARAM) {
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
char setDataOutputLockMask(char PARAM) {
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
char setDataOutputRequestkMask(char PARAM) {
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

char setGestureInProgressFlag(char ENABLE) {
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
char setMakePersistent(char PARAM) {
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
char setTrigger(char PARAM) {
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

void setElectrodeMap(char Electrode, char Channel) {
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

void TransFreqSelect(char FreqCnt, unsigned long FreqOrder) {
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

void setEnableAllGestures() {
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

void getFWInfo() {
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
void updateRawData() {
  GestIC_Read(64);
}



void updateGestureData() {
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










