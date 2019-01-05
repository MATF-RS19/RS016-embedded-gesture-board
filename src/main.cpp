#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "diag/Trace.h"
#include "i2c.h"
#include "uart.h"
#include "Timer.h"
#include "BlinkLed.h"
#include "gesture.h"
#include "gestureDefs.h"
#include "cGest.h"
#include "ci2c.h"
#include "cUart.h"

unsigned int touch_evt, touch_evt_old;
char gest_evt, gest_evt_old, gest_class, gest_recognition, gest_edge_flick;
unsigned int color, flag, clk, cclk;
unsigned int OLDAirWheelInfo=0;

extern s_Gesture mGesture;

//void Display_Values();
// ----------------------------------------------------------------------------

namespace {
  // ----- Timing definitions -------------------------------------------------

  // Keep the LED on for 2/3 of a second.
  constexpr Timer::ticks_t BLINK_ON_TICKS = Timer::FREQUENCY_HZ * 3 / 4;
  constexpr Timer::ticks_t BLINK_OFF_TICKS = Timer::FREQUENCY_HZ
      - BLINK_ON_TICKS;
}

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

#include <stm32f4xx_hal.h>
//#include <stm32_hal_legacy.h>

void initPins() {
	HAL_Init();
	__GPIOA_CLK_ENABLE();
	__GPIOC_CLK_ENABLE();
	__GPIOD_CLK_ENABLE();
	setRSTPinToOutput();
	setRDYPinToInput();
}

//ci2c c;
cGest cg;
cUart cu;

void uart_sendValid();
void Display_Values();

int
main(int argc, char* argv[]) {

	  initPins();
	  //initUart();
	  setRSTpin(0);
	  initI2c();

	  //c.init(0x42);
	  cg.start();

	  //cu.init();
	  trace_printf("Gesture started\r\n");

	  cg.setTrigger(0x00);
	  HAL_Delay(10);
	  cg.TransFreqSelect(0x05,0x43210);
	  HAL_Delay(10);
	  cg.setEnableAllGestures();
	  HAL_Delay(10);
	  HAL_Delay(100);

	  if ((GPIOA->ODR & 0b1000000) == 0)
	  {
	     setRSTpin(1);
	     HAL_Delay(100);
	  }

	  while (1)
	  {
	  	 cg.updateGestureData();
	  	 cg.parseData();
	  	 //Display_Values();
	  }

	  uint8_t i = 0;

	  // PROVERA
	  /*
	  while(1)
	  {
		  for(i = 0; i < 17; i++)
		  {
			  //uartSendGestureData(i);
			  cu.send(&i,1);
			  HAL_Delay(2000);
		  }

	  }
	  */

	  cg.setTrigger(0x00);
	  HAL_Delay(10);
	  cg.TransFreqSelect(0x05,0x43210);
	  HAL_Delay(10);
	  cg.setEnableAllGestures();
	  HAL_Delay(10);
	  HAL_Delay(100);

	  if ((GPIOA->ODR & 0b1000000) == 0) {
	      setRSTpin(1);
	      HAL_Delay(100);
	   }


	  while(1)
	  {
		  cg.updateGestureData();
		  cg.parseData();
	  }


	  while(1);
	  // At this stage the system clock should have already been configured
	  // at high speed.
	  trace_printf("System clock: %u Hz\n", SystemCoreClock);

	  Timer timer;
	  timer.start ();

}

/*
void gestureDisplayValues() {
	touch_evt = (unsigned int) mGesture.DataOut.TouchInfo & 0xFFFF;
    if ((touch_evt != 0) && (touch_evt != touch_evt_old))
    {

    	if(touch_evt < 0x00000201)
    	{
    		flag=1;

    		if(touch_evt & TapSouth)  uartSendGestureData(7);     //trace_printf("tap south\r\n");
    		if(touch_evt & TapWest)   uartSendGestureData(9); 	  //trace_printf("tap west\r\n");
    		if(touch_evt & TapNorth)  uartSendGestureData(6);     //trace_printf("tap north\r\n");
    		if(touch_evt & TapEast)   uartSendGestureData(8);     //trace_printf("tap east\r\n");
    		if(touch_evt & TapCenter) uartSendGestureData(14);    //trace_printf("tap center\r\n");
    	}
    	else
    	{
    		if(touch_evt & DoubleTapSouth)  uartSendGestureData(11); //trace_printf("double tap south\r\n");
    		if(touch_evt & DoubleTapWest)   uartSendGestureData(7);	//trace_printf("double tap west\r\n");
    		if(touch_evt & DoubleTapNorth)  uartSendGestureData(13);	//trace_printf("double tap north\r\n");
    		if(touch_evt & DoubleTapEast)   uartSendGestureData(12);	//trace_printf("double tap east\r\n");
    		if(touch_evt & DoubleTapCenter) uartSendGestureData(15);//trace_printf("double tap center\r\n");
    	}
    	touch_evt_old = touch_evt;
    }


    gest_evt = (char) mGesture.DataOut.GestureInfo & 0xFF;
    gest_class = (char) (mGesture.DataOut.GestureInfo >> 12) & 0x0F;
    gest_edge_flick = (char) (mGesture.DataOut.GestureInfo >> 16) & 0x01;
    gest_recognition = (char) (mGesture.DataOut.GestureInfo >> 31) & 0x01;

    if (gest_evt)
    	uartSendGestureData(gest_evt);

    if (mGesture.DataOut.AirWheelInfo !=0)
    {

    	if (mGesture.DataOut.AirWheelInfo > OLDAirWheelInfo)            // if the airwheel counter increments,// it is a clockwise rotation
    	{
    		uartSendGestureData(16);
    	}
    	else if  (mGesture.DataOut.AirWheelInfo < OLDAirWheelInfo)                       // if it decrements, // it is counter-clokwise
    	{
    		uartSendGestureData(17);
    	}
                                                        // print out the airwheel counter info
    	OLDAirWheelInfo=mGesture.DataOut.AirWheelInfo;
    }

}
*/



#pragma GCC diagnostic pop

