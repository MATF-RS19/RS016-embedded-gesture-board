/*
 * cGest.cpp
 *
 *  Created on: Jan 4, 2019
 *      Author: Ana
 */

#include "cGest.h"
#include "i2c.h"
#define GEST_I2CADDRESS 0x42

// makroi za razlicite dogadjaje koji se salju na uart
#define GUART_LEFT_TO_RIGHT 2
#define GUART_RIGHT_TO_LEFT 3
#define GUART_UP 4
#define GUART_DOWN 5
#define GUART_TAP_NORTH 6
#define GUART_TAP_SOUTH 7
#define GUART_TAP_EAST 8
#define GUART_TAP_WEST 9
#define GUART_DOUBLE_TAP_NORTH 10
#define GUART_DOUBLE_TAP_SOUTH 11
#define GUART_DOUBLE_TAP_EAST 12
#define GUART_DOUBLE_TAP_WEST 13
#define GUART_TAP_CENTER 14
#define GUART_DOUBLE_TAP_CENTER 15

#define GUART_CLOCKWISE 16
#define GUART_COUNTER_CLOCKWISE 17


cGest::cGest() {

	OLDAirWheelInfo = 0;
	for (int i = 0; i< 132; i++)
	{
		rawData[i] = 0;
	}

	//memset(&mGesture, 0, sizeof(mGesture));

	touchEvent = 0;
	touchEventOld = 0;
	gestEvent = 0;
	gestEventOld = 0;
	OLDAirWheelInfo = 0;
}

cGest::~cGest() {

}

// funkcija koja postavlja RDY Pin(C1) na mod output
void cGest::setRDYPinToOutput() {
	GPIO_InitTypeDef gpioInitStruct;
	gpioInitStruct.Pin = GPIO_PIN_1;
	gpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpioInitStruct.Speed = GPIO_SPEED_FAST;
	gpioInitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOC, &gpioInitStruct);
}

// funkcija koja postavlja RDY pin (C1) na mod input
void cGest::setRDYPinToInput() {
	GPIO_InitTypeDef gpioInitStruct;
	gpioInitStruct.Pin = GPIO_PIN_1;
	gpioInitStruct.Mode = GPIO_MODE_INPUT;
	gpioInitStruct.Speed = GPIO_SPEED_FAST;
	gpioInitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOC, &gpioInitStruct);
}

// funkcija koja postaclja RST pin(A7) na output
void cGest::setRSTPinToOutput() {

	GPIO_InitTypeDef gpioInitStruct;
	gpioInitStruct.Pin = GPIO_PIN_7;
	gpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpioInitStruct.Speed = GPIO_SPEED_FAST;
	gpioInitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &gpioInitStruct);
}

// postavlja ready pin na 1 ili 0
// rdy pin je C1
void cGest::setRDYpin(uint8_t s) {
	if (s > 1)
		return;

	if (s == 1)
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
}

// postavlja rst pin na 1 ili 0
// rst je A7
void cGest::setRSTpin(uint8_t s) {
	if (s > 1)
		return;
	if (s == 1)
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
}

// cita stanje rdy pina
uint8_t cGest::readRDYpin() {
	uint8_t temp;
	temp = GPIOC->IDR;			// input data registar na portu c
	temp = temp >> 1;			// siftuje se za jedno mesto i onda uporedjuje sa 1
	temp = temp & 0b00000001;	// da bi se dobila vrednost pina na portu c1

	return temp;
}

// cita stanje rst pina
uint8_t cGest::readRSTpin() {
	uint8_t temp;
	temp = GPIOA->ODR;		// otpt data registar na portu a
	temp = temp >> 7;		// siftuje se za 7 mesta da bi bit 7 (pin a7) dosao na bit 0

	return temp;
}

// I2C citanje
void cGest::GestIC_Read(char msgLen){
	i2cApi_read(rawData, msgLen);
}

// I2C pisanje
void cGest::GestIC_Write(uint8_t msgLen) {
	i2cApi_write(rawData, msgLen);
}

// http://ww1.microchip.com/downloads/en/DeviceDoc/40001718E.pdf
// strana 33

// forces a trigger - triggere gesture da uradi jedu od 3 stvari
// 0 re-kalibracija
// 1 ulazak u deep sleep mod 1
// 2 ulazak u deep sleep mod 2
char cGest::setTrigger(char PARAM) {
  //             header
 ]
  rawData[0] = 0x10; //raw data size
  rawData[1] = 0x00; //flags
  rawData[2] = 0x00; //seq
  rawData[3] = 0xA2; //ID

  //             payload
  rawData[4] = 0x00; //Parameter ID
  rawData[5] = 0x10;
  //reserved
  rawData[6] = 0x00;
  rawData[7] = 0x00;
  switch (PARAM) {
    case 1:
      rawData[8] = 0x02;
      break;
    case 2:
      rawData[8] = 0x03;
      break;
    default:
      rawData[8] = 0x00;
  }
  //Argument 0
  rawData[9] = 0x00;
  rawData[10] = 0x00;
  rawData[11] = 0x00;
  //Argument 1
  rawData[12] = 0x00;
  rawData[13] = 0x00;
  rawData[14] = 0x00;
  rawData[15] = 0x00;

  GestIC_Write(0x10); // saljemo 0x10 bajtova preko i2c-a

  return 1;
}


// http://ww1.microchip.com/downloads/en/DeviceDoc/40001718E.pdf
// strana 23
// posalji komandu gesture-u da ukljuci detekticiju svi pokreta
void cGest::setEnableAllGestures() {
  //header
  rawData[0] = 0x10; //raw data size
  rawData[1] = 0x00; //flags
  rawData[2] = 0x00; //seq
  rawData[3] = 0xA2; //ID
  //payload
  rawData[4] = 0x85; //param ID
  rawData[5] = 0x00;

  rawData[6] = 0x00;
  rawData[7] = 0x00;

  rawData[8] = 0x7F; //DATA OUTPUT MASK
  rawData[9] = 0x00;
  rawData[10] = 0x00;
  rawData[11] = 0x00;

  rawData[12] = 0x7F;
  rawData[13] = 0x00;
  rawData[14] = 0x00;
  rawData[15] = 0x00;

  // salji podatke na i2c
  GestIC_Write(0x10);
}


// http://ww1.microchip.com/downloads/en/DeviceDoc/40001718E.pdf
// strana 22
// posalji komandu za zatev innformacija o FW gesture chipa
// podatke smesti u nasu strukturu
void cGest::getFWInfo() {
  unsigned i;

  setRSTpin(0);  // resetuj gesture da dobijemo "sveze" fw podatke

  // napravi poruku za gesture
  rawData[0] = 0x0C;
  rawData[1] = 0x00;
  rawData[2] = 0x00;
  rawData[3] = 0x06;
  rawData[4] = 0x83;
  rawData[5] = 0x00;
  rawData[6] = 0x00;
  rawData[7] = 0x00;
  rawData[8] = 0x00;
  rawData[9] = 0x00;
  rawData[10] = 0x00;
  rawData[11] = 0x00;

  // vrati rst pin na 1
  setRSTpin(1);
  HAL_Delay(10);

  // posalji zahtev za fw version preko i2c-a
  GestIC_Write(0x0C);

  // Tscekaj da gesture signalizira da ia ove podatke spremne
  while(readRDYpin() == 1)
  {}

  // citamo 0x84 bajtova - 132
  GestIC_Read(0x84);
  HAL_Delay(10);

  //smesti podatke u strukturi, nacin objasnjen u datasheetu strana 22
  mGesture.FWVersionInfo.FWValid = rawData[4];
  mGesture.FWVersionInfo.HWRev[0] = rawData[5];
  mGesture.FWVersionInfo.HWRev[1] = rawData[6];
  mGesture.FWVersionInfo.ParameterStartAddr = rawData[7];
  mGesture.FWVersionInfo.LibraryLoaderVersion[0] = rawData[8];
  mGesture.FWVersionInfo.LibraryLoaderVersion[1] = rawData[9];
  mGesture.FWVersionInfo.LibraryLoaderVersion[3] = rawData[10];
  mGesture.FWVersionInfo.FwStartAddr = rawData[11];

  for (i=0; i<120; i++) {
     mGesture.FWVersionInfo.FwVersion[i] = rawData[i+12];
  }
}

// inicijalizuje uart, uzima FW info gesture-a
// ako je FW_valid, uspesna je komunikacija sa gesture-om
// u suprotnom, nesto nije u redu, program staje ovde

void cGest::start() {
	cu.init(); // inicijalizuj uart
	getFWInfo(); // uzmi fw info
	HAL_Delay(2000);

    if((uint8_t)(mGesture.FWVersionInfo.FWValid) == (uint8_t)FW_VALID) {
		  trace_printf("VALID FW!\n");
	}
	else {
		  trace_printf("INVALID FW! HALT PROGRAM!\n");
		  while(1);
	}
}

// uzima gesture podatke
void cGest::updateGestureData() {

	while(readRDYpin())  // cekamo da RDY pin bude 0 - znak da GST ima nove podatke
	{}					// http://ww1.microchip.com/downloads/en/DeviceDoc/40001667E.pdf - strana 31 pasus 5.5.2

	// setujemo RDY pin da bude output da bismo mogli da ga spustimo
    setRDYPinToOutput();

    setRDYpin(0);  // spustamo RDY pin - signalizirao gesturu da ne mozemo primiti jos podataka


    GestIC_Read(32);     // citamo 32 bajta preko i2c-a, smestamo  strukturu
    // nacin smestanja objasnen u datasheetu, strana: 42

    // upisuju se vrednosti
    mGesture.DataOut.Len = rawData[0];
    mGesture.DataOut.Flags = rawData[1];
    mGesture.DataOut.Seq = rawData[2];
    mGesture.DataOut.Id = rawData[3];
    mGesture.DataOut.ConfigMask = (rawData[5] << 8) + rawData[4];
    mGesture.DataOut.TimeStamp = rawData[6];
    mGesture.DataOut.SystemInfo = rawData[7];
    mGesture.DataOut.DSPStatus = (rawData[9] << 8) + rawData[8];
    mGesture.DataOut.GestureInfo = (rawData[13] << 24) + (rawData[12] << 16) + (rawData[11] << 8) + rawData[10];
    mGesture.DataOut.TouchInfo = (rawData[17] << 24) + (rawData[16] << 16) + (rawData[15] << 8) + rawData[14];
    mGesture.DataOut.AirWheelInfo = (rawData[19] << 8) + rawData[18];
    mGesture.DataOut.Position.X = (raw_data[21] << 8) + raw_data[20];
    mGesture.DataOut.Position.Y = (raw_data[23] << 8) + raw_data[22];
    mGesture.DataOut.Position.Z = (raw_data[25] << 8) + raw_data[24];

    setRDYpin(1);   	//vracamo rdy pin na 1, gst ce ga spustiti opet na 0 kad ima nove podatke
    setRDYPinToInput(); // podesavamo rdy na inpt, da citamo kad gst ima nove podatke
}

// pomocna funkcija, printuje gesture podatke na trace
void SendGestureDebug(uint8_t dat) {
    switch (dat) {

      case 1:
        trace_printf("Not valid\r\n");
        break;
      case GUART_LEFT_TO_RIGHT:
        trace_printf("flick left to right\r\n");
        break;
      case GUART_RIGHT_TO_LEFT:
       trace_printf("flick right to left\r\n");
        break;
      case GUART_UP:
        trace_printf("flick up\r\n");
        break;
      case GUART_DOWN:
        trace_printf("flick down\r\n");
        break;
      case GUART_TAP_NORTH:
        trace_printf("Tap north\r\n");
        break;
      case GUART_TAP_SOUTH:
       trace_printf("Tap south\r\n");
        break;
      case GUART_TAP_EAST:
        trace_printf("Tap east\r\n");
        break;
      case GUART_TAP_WEST:
        trace_printf("Tap west\r\n");
        break;
      case GUART_DOUBLE_TAP_NORTH:
        trace_printf("Double Tap north\r\n");
        break;
      case GUART_DOUBLE_TAP_SOUTH:
       trace_printf("Double Tap south\r\n");
        break;
      case GUART_DOUBLE_TAP_EAST:
        trace_printf("Double Tap east\r\n");
        break;
      case GUART_DOUBLE_TAP_WEST:
        trace_printf("Double Tap west\r\n");
        break;
      case GUART_TAP_CENTER:
        trace_printf("Tap center\r\n");
        break;
      case GUART_DOUBLE_TAP_CENTER:
        trace_printf("Double Tap center\r\n");
        break;
      case GUART_CLOCKWISE:
        trace_printf("Clockwise\r\n");
        break;
      case GUART_COUNTER_CLOCKWISE:
        trace_printf("Counter Clockwise\r\n");
        break;
    }

    // HAL funkcija koja salje podatke
    //HAL_UART_Transmit(&s_UARTHandle, &dat, 1, HAL_MAX_DELAY);
}


// parsira gesture podatke
// svaki gesture podatak se uporedjuje sa predefinisanim vrednostima u datasheet-u
// prepoznati gesture se onda salje preko uart-a
void cGest::parseData() {

	uint8_t temp = 0;
	touchEvent = (unsigned int) mGesture.DataOut.TouchInfo; //& 0xFFFF;

		// ako imamo novi touch event
	    if ((touchEvent != 0) && (touchEvent != touchEventOld)) {

	     // http://ww1.microchip.com/downloads/en/DeviceDoc/40001718E.pdf strana 45
	      if(touchEvent < 0x00000201)  {

	        // uporedjujemo touch event sa predefinisanim vrednostima, da vidimo koji event smo dobili
	        if(touchEvent & TapSouth)
	        	temp = GUART_TAP_SOUTH;
	        if(touchEvent & TapWest)
	        	temp = GUART_TAP_WEST;
	        if(touchEvent & TapNorth)
	        	temp = GUART_TAP_NORTH;
	        if(touchEvent & TapEast)
	        	temp = GUART_TAP_EAST;
	        if(touchEvent & TapCenter)
	        	temp = GUART_TAP_CENTER;

	        SendGestureDebug(temp);
	        cu.send(&temp, 1);
	      }
	      else
	      {
	    	// uporedjujemo touch event sa predefinisanim vrednostima, da vidimo koji event smo dobili
	        if(touchEvent & DoubleTapSouth)
	        	temp = GUART_DOUBLE_TAP_SOUTH;


	        if(touchEvent & DoubleTapWest)
	        	temp = GUART_DOUBLE_TAP_WEST;


	        if(touchEvent & DoubleTapNorth)
	        	temp =  GUART_DOUBLE_TAP_NORTH;


	        if(touchEvent & DoubleTapEast)
	        	temp = GUART_DOUBLE_TAP_EAST;


	        if(touchEvent & DoubleTapCenter)
	        	temp = GUART_DOUBLE_TAP_CENTER;

	        SendGestureDebug(temp);
	        cu.send(&temp, 1);  // saljemo na uart
	      }

	      touchEventOld = touchEvent;
	    }

	    // citamo novi gest event
	    gestEvent = (char) mGesture.DataOut.GestureInfo; // & 0xFF;


	    if (gestEvent) {
	    	temp = gestEvent;
	    	SendGestureDebug(gestEvent);
	    	cu.send(&temp, 1);  // saljemo na uart
	    }

	    if (mGesture.DataOut.AirWheelInfo !=0) {

	      // ako se airwheel povecava, clockwise
	      if (mGesture.DataOut.AirWheelInfo > OLDAirWheelInfo)  {
	        temp = GUART_CLOCKWISE;
	      }

	      // ako se smanjuje, counter-clockwise
	      else if  (mGesture.DataOut.AirWheelInfo < OLDAirWheelInfo)  {
	        temp = GUART_COUNTER_CLOCKWISE;
	      }

	      OLDAirWheelInfo=mGesture.DataOut.AirWheelInfo;
	      cu.send(&temp,1);  // saljemo na uart
	      SendGestureDebug(temp);
	    }
}
