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

unsigned int touch_evt, touch_evt_old;
char gest_evt, gest_evt_old, gest_class, gest_recognition, gest_edge_flick;
unsigned int color, flag, clk, cclk;
unsigned int OLDAirWheelInfo=0;

extern s_Gesture mGesture;

void Display_Values();
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

int
main(int argc, char* argv[]) {

  initPins();
  //initUart();
  setRSTpin(0);
  initI2c();
  trace_puts("Hello ARM World!");

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

  setTrigger(0x00);
  HAL_Delay(10);
  TransFreqSelect(0x05,0x43210);
  HAL_Delay(10);
  setEnableAllGestures();
  HAL_Delay(10);
  HAL_Delay(100);

  if ((GPIOA->ODR & 0b1000000) == 0) {
      setRSTpin(1);
      HAL_Delay(100);
   }

  while (1) {
     updateGestureData();
     Display_Values();

   }

  while(1);
  // At this stage the system clock should have already been configured
  // at high speed.
  trace_printf("System clock: %u Hz\n", SystemCoreClock);

  Timer timer;
  timer.start ();

}


void gestureDisplayValues()
{
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


void Display_Values() {

	//trace_printf("%u \r\n",mGesture.DataOut.Position.X);

    //Touch Info
    touch_evt = (unsigned int) mGesture.DataOut.TouchInfo & 0xFFFF;
    if ((touch_evt != 0) && (touch_evt != touch_evt_old)) {
      //TFT_Rectangle(80,60,320,240);
      if(touch_evt < 0x00000201) {
        flag=1;
/*
        if(touch_evt & TouchSouth) trace_printf("touch south\r\n");
        if(touch_evt & TouchWest) trace_printf("touch west\r\n");
        if(touch_evt & TouchNorth) trace_printf("touch north\r\n");
        if(touch_evt & TouchEast) trace_printf("touch east\r\n");
        //if(touch_evt & TouchSouth) TFT_WRITE_TEXT("TOUCH SOUTH",120,90);
        if(touch_evt & TouchCenter) trace_printf("touch center\r\n");
*/
        if(touch_evt & TapSouth) trace_printf("tap south\r\n");
        if(touch_evt & TapWest) trace_printf("tap west\r\n");
        if(touch_evt & TapNorth) trace_printf("tap north\r\n");
        if(touch_evt & TapEast) trace_printf("tap east\r\n");
        if(touch_evt & TapCenter) trace_printf("tap center\r\n");

      }else{
        if(touch_evt & DoubleTapSouth) trace_printf("double tap south\r\n");
        if(touch_evt & DoubleTapWest) trace_printf("double tap west\r\n");
        if(touch_evt & DoubleTapNorth) trace_printf("double tap north\r\n");
        if(touch_evt & DoubleTapEast) trace_printf("double tap east\r\n");
        if(touch_evt & DoubleTapCenter) trace_printf("double tap center\r\n");
      }
      touch_evt_old = touch_evt;
    }


    //Gesture info
    gest_evt = (char) mGesture.DataOut.GestureInfo & 0xFF;
    gest_class = (char) (mGesture.DataOut.GestureInfo >> 12) & 0x0F;
    gest_edge_flick = (char) (mGesture.DataOut.GestureInfo >> 16) & 0x01;
    gest_recognition = (char) (mGesture.DataOut.GestureInfo >> 31) & 0x01;

      if (gest_evt) {
        flag=2;
          switch (gest_evt) {
            case 1:

              trace_printf("GARBAGE\r\n");
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
          }

      }


    //Air Wheel info
     if (mGesture.DataOut.AirWheelInfo !=0) {
      if (flag!=3) {                                                                     // check if the air wheel has been toggled the first time
                                                            // if so, display the circle image on TFT
       if (mGesture.DataOut.AirWheelInfo > OLDAirWheelInfo)                              // if the airwheel counter increments,
       {
    	 clk=1;
         trace_printf("Clockwise\r\n");
		                                            // it is a clockwise rotation
         }
       else if  (mGesture.DataOut.AirWheelInfo < OLDAirWheelInfo)                       // if it decrements,
       {
    	  cclk=1;

    	  trace_printf("Counter-Clockwise\r\n");
		                                   // it is counter-clokwise
       }
                                                    // print out the airwheel counter info
         flag=3;
       }

       else if (flag==3) {                                                            // if the previous gesture is already the airwheel
        if ((clk==1) & (mGesture.DataOut.AirWheelInfo > OLDAirWheelInfo))             // if the rotation was clockwise and now is incrementing,
        {

        }

        else if  ((clk==1) & (mGesture.DataOut.AirWheelInfo < OLDAirWheelInfo)) {    // if the rotation was clockwise and now is decrementing,
          cclk=1;                                                                    // print out counter-clokwise, and update airwheel info
          clk=0;

          trace_printf("counter-clockwise\r\n");
        }

        else if ((cclk==1) & (mGesture.DataOut.AirWheelInfo < OLDAirWheelInfo)) {   //if the rotation was counter-clokwise and now is decrementing,

        }

        else if ((cclk==1) & (mGesture.DataOut.AirWheelInfo > OLDAirWheelInfo)) {   //if the rotation was counter-clockwise and now is incrementing,
          cclk=0;                                                                   // print out clockwise, and update airwheel counter info
          clk=1;

         trace_printf("Clockwise\r\n");

        }
       }

       OLDAirWheelInfo=mGesture.DataOut.AirWheelInfo;
     }
    HAL_Delay(50);


}


#pragma GCC diagnostic pop

