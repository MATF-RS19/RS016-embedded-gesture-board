/*
 * cGest.cpp
 *
 *  Created on: Jan 4, 2019
 *      Author: Ana
 */

#include "cGest.h"
#include "i2c.h"
#define GEST_I2CADDRESS 0x42

cGest::cGest() {
	// TODO Auto-generated constructor stub

}

cGest::~cGest() {
	// TODO Auto-generated destructor stub
}

void cGest::setRDYPinToOutput() {
	GPIO_InitTypeDef gpioInitStruct;
	gpioInitStruct.Pin = GPIO_PIN_1;
	gpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpioInitStruct.Speed = GPIO_SPEED_FAST;
	gpioInitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOC, &gpioInitStruct);
}

void cGest::setRDYPinToInput() {
	GPIO_InitTypeDef gpioInitStruct;
	gpioInitStruct.Pin = GPIO_PIN_1;
	gpioInitStruct.Mode = GPIO_MODE_INPUT;
	gpioInitStruct.Speed = GPIO_SPEED_FAST;
	gpioInitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOC, &gpioInitStruct);
}

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
	temp = GPIOC->IDR;		// input data registar na portu c
	temp = temp >> 1;		// siftuje se za jedno mesto i onda uporedjuje sa 1
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
	i2cApi_read(raw_data, msgLen);
}

void cGest::GestIC_Write( uint8_t msgLen) {
	i2cApi_write(raw_data, msgLen);
}


/* Parameters:
0 - Force Calibration
1 - Enter Deep Sleep 1
2 - Enter Deep Sleep 2
*/
// http://ww1.microchip.com/downloads/en/DeviceDoc/40001718E.pdf
// strana 33
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



  GestIC_Write(0x10); // saljemo 0x10 bajtova preko i2c-a

  return 1;
}


// http://ww1.microchip.com/downloads/en/DeviceDoc/40001718E.pdf
// strana 35
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

  //salji podatke na i2c
  GestIC_Write(0x10);
}


// http://ww1.microchip.com/downloads/en/DeviceDoc/40001718E.pdf
// strana 23
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

  // salji podatke na i2c
  GestIC_Write(0x10);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                           REQUEST FW_VERSION_INFO FROM MGC3130
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// http://ww1.microchip.com/downloads/en/DeviceDoc/40001718E.pdf
// strana 22
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

  while(readRDYpin() == 1)
  {}

  GestIC_Read(0x84);
  HAL_Delay(10);
  //smesti podatke u strukturi, nacin objasnjen u datasheetu strana 22
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

// inicijalizuje uart, uzima FW info gesture-a
// ako je FW_valid, uspesna je komunikacija sa gesture-om
// u suprotnom, nesto nije u redu, program staje ovde
void cGest::start()
{
	//c.init(GEST_I2CADDRESS);
	cu.init(); // inicijalizuj uart
	getFWInfo(); // uzmi fw info
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


// uzima gesture podatke
void cGest::updateGestureData() {

	while(readRDYpin())  // cekamo da RDY pin bude 0 - znak da GST ima nove podatke
	{}

    setRDYPinToOutput();

    setRDYpin(0);
    GestIC_Read(32);     // citamo 32 bajta preko i2c-a, smestamo  strukturu
    // nacin smestanja objasnen u datasheetu, strana: 42
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

    setRDYpin(1);   //vracamo rdy pin na 1, gst ce ga spustiti opet na 0 kad ima nove podatke
    setRDYPinToInput(); // podesavamo rdy na inpt, da citamo kad gst ima nove podatke
}


// pomocna funkcija, printuje gesture podatke na trace
void SendGestureDebug(uint8_t dat)
{
    switch (dat)
    {
      case 1:
        trace_printf("Not valid\r\n");
        break;
      case 2:
        trace_printf("flick left to right\r\n");
        break;
      case 3:
       trace_printf("flick right to left\r\n");
        break;
      case 4:
        trace_printf("flick up\r\n");
        break;
      case 5:
        trace_printf("flick down\r\n");
        break;
      case 6:
        trace_printf("Tap north\r\n");
        break;
      case 7:
       trace_printf("Tap south\r\n");
        break;
      case 8:
        trace_printf("Tap east\r\n");
        break;
      case 9:
        trace_printf("Tap west\r\n");
        break;
      case 10:
        trace_printf("Double Tap north\r\n");
        break;
      case 11:
       trace_printf("Double Tap south\r\n");
        break;
      case 12:
        trace_printf("Double Tap east\r\n");
        break;
      case 13:
        trace_printf("Double Tap west\r\n");
        break;
      case 14:
        trace_printf("Tap center\r\n");
        break;
      case 15:
        trace_printf("Double Tap center\r\n");
        break;
      case 16:
        trace_printf("Clockwise\r\n");
        break;
      case 17:
        trace_printf("Counter Clockwise\r\n");
        break;
    }

    // HAL funkcija koja salje podatke
    //HAL_UART_Transmit(&s_UARTHandle, &dat, 1, HAL_MAX_DELAY);
}


// parsira gesture podatke
// svaki gesture podatak se uporedjuje sa predefinisanim vrednostima u datasheet-u
// prepoznati gesture se onda salje preko uart-a
void cGest::parseData()
{
	uint8_t temp = 0;
	touch_evt = (unsigned int) mGesture.DataOut.TouchInfo & 0xFFFF;

	// ako imamo novi touch event
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
	        // uporedjujemo touch event sa predefinisanim vrednostima, da vidimo koji event smo dobili
	        if(touch_evt & TapSouth) {temp = 7;  trace_printf("tap south\r\n");} //uartSendGestureData(7);
	        if(touch_evt & TapWest)   {temp = 9; trace_printf("tap west\r\n");} //uartSendGestureData(9);     //
	        if(touch_evt & TapNorth)  {temp = 6; trace_printf("tap north\r\n");} //uartSendGestureData(6);     //
	        if(touch_evt & TapEast)   {temp = 8; trace_printf("tap east\r\n");} //uartSendGestureData(8);     //
	        if(touch_evt & TapCenter) {temp = 14; trace_printf("tap center\r\n");} //uartSendGestureData(14);    //
	        cu.send(&temp, 1);
	      }
	      else
	      {
	    	  // uporedjujemo touch event sa predefinisanim vrednostima, da vidimo koji event smo dobili
	        if(touch_evt & DoubleTapSouth)  {temp = 11; trace_printf("double tap south\r\n");}  //uartSendGestureData(11); //
	        if(touch_evt & DoubleTapWest)   {temp = 10;  trace_printf("double tap west\r\n");}  //uartSendGestureData(7); //
	        if(touch_evt & DoubleTapNorth)  {temp = 13; trace_printf("double tap north\r\n");}  //uartSendGestureData(13);  //
	        if(touch_evt & DoubleTapEast)   {temp = 12; trace_printf("double tap east\r\n");}  //uartSendGestureData(12);  //
	        if(touch_evt & DoubleTapCenter) {temp = 15; trace_printf("double tap center\r\n");}  //uartSendGestureData(15);//
	        cu.send(&temp, 1);  // saljemo na uart
	      }
	      touch_evt_old = touch_evt;
	    }


	    gest_evt = (char) mGesture.DataOut.GestureInfo & 0xFF;
	   // gest_class = (char) (mGesture.DataOut.GestureInfo >> 12) & 0x0F;
	   // gest_edge_flick = (char) (mGesture.DataOut.GestureInfo >> 16) & 0x01;
	   // gest_recognition = (char) (mGesture.DataOut.GestureInfo >> 31) & 0x01;

	    if (gest_evt)
	    {
	    	temp = gest_evt;
	    	SendGestureDebug(gest_evt);
	    	cu.send(&temp, 1);  // saljemo na uart
	    }



	    if (mGesture.DataOut.AirWheelInfo !=0)
	    {

	      if (mGesture.DataOut.AirWheelInfo > OLDAirWheelInfo)            // ako se airwheel povecava, clockwise
	      {
	        temp = 16;
	      }
	      else if  (mGesture.DataOut.AirWheelInfo < OLDAirWheelInfo)     // u suprotnom, counter-clokwise
	      {
	        temp = 17;
	      }

	      OLDAirWheelInfo=mGesture.DataOut.AirWheelInfo;
	      cu.send(&temp,1);  // saljemo na uart
	      SendGestureDebug(temp);
	    }
}
