#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "diag/Trace.h"
#include "i2c.h"

//#include "Timer.h"
//#include "gesture.h"
//#include "gestureDefs.h"
#include "cGest.h"
#include "cUart.h"


// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

// ukljucujemo HAL(Hardware apstraction layer) biblioteku
#include <stm32f4xx_hal.h>

//ci2c c;
cGest cg;
cUart cu;

// TODO: napraviti System klasu
void initPins() {
	// Inicijalizuje se hal
	// Ukljucujemo clock za pinove koje koristimo - port A, port C i port D
	HAL_Init();
	__GPIOA_CLK_ENABLE();
	__GPIOC_CLK_ENABLE();
	__GPIOD_CLK_ENABLE();

	// postavlja se reset pin na output, i ready pin na input
	cg.setRSTPinToOutput();
	cg.setRDYPinToInput();
}


int
main(int argc, char* argv[]) {

	  // inicijalizuju se pinovi
	  initPins();

	  // rst pin se postavlja na 0 - gesture je resetovan
	  cg.setRSTpin(0);

	  // inicijalizacija i2c modula stm-a
	  initI2c();

	  // pokrece se gesture
	  cg.start();
	  trace_printf("Gesture started\r\n");

	  // TODO
	  cg.setTrigger(0x00);
	  HAL_Delay(10);
	  cg.TransFreqSelect(0x05,0x43210);
	  HAL_Delay(10);
	  cg.setEnableAllGestures();
	  HAL_Delay(10);
	  HAL_Delay(100);
	  // eof TODO

	  // TODO  ODR = otput data register
	  if ((GPIOA->ODR & 0b1000000) == 0)
	  {
	     cg.setRSTpin(1);
	     HAL_Delay(100);
	  }

	  // Citaju se podaci koji stizu i parsiraju se
	  while (1) {
	  	 cg.updateGestureData();
	  	 cg.parseData();
	  }

}


#pragma GCC diagnostic pop

