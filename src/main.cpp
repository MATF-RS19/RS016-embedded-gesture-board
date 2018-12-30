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
	setRSTPinToOutput();
	setRDYPinToInput();
}

void test()
{
	GPIO_InitTypeDef gpioInitStruct;
	HAL_Init();
	//__GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	//HAL_GPIO_StructInit(&gpioInitStruct);
	gpioInitStruct.Pin = GPIO_PIN_7;
	gpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpioInitStruct.Speed = GPIO_SPEED_FAST;
	gpioInitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &gpioInitStruct);
}
int a;
uint32_t portRead = 0;
int
main(int argc, char* argv[]) {
  //initUart();
	//test();
  initPins();
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


void Display_Values() {
	/*
    //Position X
    TFT_Rectangle(25,10,80,25);
    WordToStr(mGesture.DataOut.Position.X,txt);
    TFT_WRITE_TEXT(txt,25,10);
    //Position Y
    TFT_Rectangle(25,30,80,45);
    WordToStr(mGesture.DataOut.Position.Y,txt);
    TFT_WRITE_TEXT(txt,25,30);
    //Position Z
    TFT_Rectangle(25,50,80,65);
    WordToStr(mGesture.DataOut.Position.Z,txt);
    TFT_WRITE_TEXT(txt,25,50);
    */

	//trace_printf("%u \r\n",mGesture.DataOut.Position.X);

    //Touch Info
    touch_evt = (unsigned int) mGesture.DataOut.TouchInfo & 0xFFFF;
    if ((touch_evt != 0) && (touch_evt != touch_evt_old)) {
      //TFT_Rectangle(80,60,320,240);
      if(touch_evt < 0x00000201) {
        flag=1;
        if(touch_evt & TouchSouth) trace_printf("touch south\r\n");//TFT_WRITE_TEXT("TOUCH SOUTH",120,90);
        if(touch_evt & TouchWest) trace_printf("touch west\r\n"); //TFT_WRITE_TEXT("TOUCH WEST",120,90);
        if(touch_evt & TouchNorth) trace_printf("touch north\r\n"); //TFT_WRITE_TEXT("TOUCH NORTH",120,90);
        if(touch_evt & TouchEast) trace_printf("touch east\r\n"); //TFT_WRITE_TEXT("TOUCH EAST",120,90);
        //if(touch_evt & TouchSouth) TFT_WRITE_TEXT("TOUCH SOUTH",120,90);
        if(touch_evt & TouchCenter) trace_printf("touch center\r\n"); //TFT_WRITE_TEXT("TOUCH CENTER",120,90);
        if(touch_evt & TapSouth) trace_printf("tap south\r\n"); //TFT_WRITE_TEXT("TAP SOUTH",120,90);
        if(touch_evt & TapWest) trace_printf("tap west\r\n"); //TFT_WRITE_TEXT("TAP WEST",120,90);
        if(touch_evt & TapNorth) trace_printf("tap north\r\n"); //TFT_WRITE_TEXT("TAP NORTH",120,90);
        if(touch_evt & TapEast) trace_printf("tap east\r\n"); //TFT_WRITE_TEXT("TAP EAST",120,90);
        //if(touch_evt & TapSouth) TFT_WRITE_TEXT("TAP SOUTH",120,90);
        if(touch_evt & TapCenter) trace_printf("tap center\r\n"); //TFT_WRITE_TEXT("TAP CENTER",120,90);
      }else{
        if(touch_evt & DoubleTapSouth) trace_printf("double tap south\r\n"); //TFT_WRITE_TEXT("DOUBLE TAP SOUTH",120,90);
        if(touch_evt & DoubleTapWest) trace_printf("double tap west\r\n"); //TFT_WRITE_TEXT("DOUBLE TAP WEST",120,90);
        if(touch_evt & DoubleTapNorth) trace_printf("double tap north\r\n"); //TFT_WRITE_TEXT("DOUBLE TAP NORTH",120,90);
        if(touch_evt & DoubleTapEast) trace_printf("double tap east\r\n"); //TFT_WRITE_TEXT("DOUBLE TAP EAST",120,90);
       // if(touch_evt & DoubleTapSouth) trace_printf("double ta\r\n")TFT_WRITE_TEXT("DOUBLE TAP SOUTH",120,90);
        if(touch_evt & DoubleTapCenter) trace_printf("double tap center\r\n"); //TFT_WRITE_TEXT("DOUBLE TAP CENTER",120,90);
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
         //TFT_Rectangle(80,60,320,240);
          switch (gest_evt) {
            case 1:
             // TFT_Image(90,60, icon_recycle_bin_bmp, 1);
              trace_printf("GARBAGE\r\n");
			  //TFT_WRITE_TEXT("GARBAGE",90,200);                                    // Unprocessed gestures are defined as "garbage"
              break;
            case 2:
              //TFT_Image(90,60, icon_right_bmp, 1);
              trace_printf("flick left to right\r\n");
			  //TFT_WRITE_TEXT("FLICK LEFT TO RIGHT",90,200);
              break;
            case 3:
              //TFT_Image(90,60, icon_left_bmp, 1);
             trace_printf("flick right to left\r\n");
			 //TFT_WRITE_TEXT("FLICK RIGHT TO LEFT",90,200);
              break;
            case 4:
             // TFT_Image(90,60, icon_up_bmp, 1);
              trace_printf("flick up\r\n");
			 // TFT_WRITE_TEXT("FLICK UP",90,200);
              break;
            case 5:
              //TFT_Image(90,60, icon_down_bmp, 1);
              trace_printf("flick down\r\n");
			  //TFT_WRITE_TEXT("FLICK DOWN",90,200);
              break;
          }

      }


    //Air Wheel info
     if (mGesture.DataOut.AirWheelInfo !=0) {
      if (flag!=3) {                                                                     // check if the air wheel has been toggled the first time
       //TFT_Rectangle(80,60,320,240);                                                     // if so, display the circle image on TFT
       if (mGesture.DataOut.AirWheelInfo > OLDAirWheelInfo)                              // if the airwheel counter increments,
       { clk=1;
       //TFT_Image(90,60, icon_rotate_cw_bmp, 1);
         trace_printf("Clockwise\r\n");
		 //TFT_WRITE_TEXT("Clockwise" ,90,200);                                           // it is a clockwise rotation
         }
       else if  (mGesture.DataOut.AirWheelInfo < OLDAirWheelInfo)                       // if it decrements,
       { cclk=1;
        //TFT_Image(90,60, icon_rotate_ccw_bmp, 1);
        trace_printf("Counter-Clockwise\r\n");
		// TFT_WRITE_TEXT("Counter-Clockwise" ,90,200);                                   // it is counter-clokwise
         }
        // LongWordToStr(mGesture.DataOut.AirWheelInfo,txt);
        //TFT_Rectangle(230,10,360,30);
		// TFT_WRITE_TEXT(txt,240,10);                                                   // print out the airwheel counter info
         flag=3;
       }

       else if (flag==3) {                                                            // if the previous gesture is already the airwheel
        if ((clk==1) & (mGesture.DataOut.AirWheelInfo > OLDAirWheelInfo))             // if the rotation was clockwise and now is incrementing,
        {
         // LongWordToStr(mGesture.DataOut.AirWheelInfo,txt);                           // just update the airwheel counter
        // TFT_Rectangle(230,10,360,30);
        // TFT_WRITE_TEXT(txt,240,10);
        }

        else if  ((clk==1) & (mGesture.DataOut.AirWheelInfo < OLDAirWheelInfo)) {    // if the rotation was clockwise and now is decrementing,
          cclk=1;                                                                    // print out counter-clokwise, and update airwheel info
          clk=0;
          //TFT_Rectangle(80,60,320,240);
          //TFT_Image(90,60, icon_rotate_ccw_bmp, 1);
          trace_printf("counter-clockwise\r\n");
		  //TFT_WRITE_TEXT("Counter-Clockwise" ,90,200);

         // LongWordToStr(mGesture.DataOut.AirWheelInfo,txt);
         // TFT_Rectangle(230,10,360,30);
         // TFT_WRITE_TEXT(txt,240,10);
        }

        else if ((cclk==1) & (mGesture.DataOut.AirWheelInfo < OLDAirWheelInfo)) {   //if the rotation was counter-clokwise and now is decrementing,
         // LongWordToStr(mGesture.DataOut.AirWheelInfo,txt);                         // just update the airwheel counter
         //TFT_Rectangle(230,10,360,30);
         //TFT_WRITE_TEXT(txt,240,10);
        }

        else if ((cclk==1) & (mGesture.DataOut.AirWheelInfo > OLDAirWheelInfo)) {   //if the rotation was counter-clockwise and now is incrementing,
          cclk=0;                                                                   // print out clockwise, and update airwheel counter info
          clk=1;
          // TFT_Rectangle(80,60,320,240);
          // TFT_Image(90,60, icon_rotate_cw_bmp, 1);
         trace_printf("Clockwise\r\n");
		 //TFT_WRITE_TEXT("Clockwise" ,90,200);
         // LongWordToStr(mGesture.DataOut.AirWheelInfo,txt);
         // TFT_Rectangle(230,10,360,30);
         // TFT_WRITE_TEXT(txt,240,10);
        }
       }

       OLDAirWheelInfo=mGesture.DataOut.AirWheelInfo;
     }
    HAL_Delay(50);


}


#pragma GCC diagnostic pop

