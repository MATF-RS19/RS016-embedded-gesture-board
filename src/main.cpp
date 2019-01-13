#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "diag/Trace.h"
#include "i2c.h"
#include "cGest.h"
#include "cUart.h"

// automatski generisano, za handlovanje warninga
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

// ukljucujemo HAL(Hardware apstraction layer) biblioteku
#include <stm32f4xx_hal.h>

// instanca klase cGest
cGest cg;


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


	  cg.setTrigger(0x00); // force trigger 0 - nateraj gesture da se re-kalibrise
	  HAL_Delay(10);
	  cg.setEnableAllGestures();  // posalji komandu da se omoguci prepoznavanje svih pokreta
	  HAL_Delay(100);


	  // citamo stanje RST pina, ako je 0, setujemo na 1 da bismo resetovali gesture
	  // i cekamo 100 milisekndi
	  if (cg.readRSTpin() == 0) {
		  cg.setRSTpin(1);
		  HAL_Delay(100);
	  }

	  // Citaju se podaci koji stizu i parsiraju se
	  while (1) {
	  	 cg.updateGestureData();  // uzmi nove podatke o pokretima
	  	 cg.parseData();			// parsiraj podatke i posalji na uart
	  }

}

#pragma GCC diagnostic pop
