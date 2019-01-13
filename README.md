# RS016-embedded-gesture-board
Hardverski deo: Implementirane opcije nad gesture pločom koristeći HAL (hardware apstract layer) biblioteku, kao i dokumentaciju za kontroler [MGC3130](https://www.microchip.com/wwwproducts/en/MGC3130) <br/>
Mogući pokreti : 
* Flick left to right
* Flick right to left
* Flick up
* Flick down
* Tap up
* Tap down
* Tap left
* Tap right 
* Tap center
* Double tap up
* Double tap down 
* Double tap left
* Double tap right
* Double tap center
* Clockwise
* Counter-clockwise

Hardver je povezan sa PC-jem preko UART klika koji preko serijskog porta šalje bajtove koji se čitaju u aplikaciji. <br/>
PC deo : Implementirane su 3 mini aplikacije koje se kontrolišu pokretima nad Gesture pločom: <br/>
* Space Glider - TODO
* Slideshow - album sa slikama koje se mogu listati, rotirati, uveličavati i smanjivati pokretima.
* Tetris - klasična tetris igrica kojom se upravlja pomoću pokreta iznad ploče. 


## Korišćen hardver:
[Gesture Board](https://www.mikroe.com/gesture-board) <br/>
[Mikromedia za STM32F4](https://www.mikroe.com/mikromedia-7-stm32f4) <br/>
[UART klik](https://www.mikroe.com/usb-uart-click) <br/>
[Mikroprog za STM32F4 ](https://www.mikroe.com/mikroprog-stm32) <br/>
[Shield za mikromedia plocu] (https://www.mikroe.com/mikromedia-3-mikrobus-shield) <br/>

## Potrebno instalirati:
* [GNU ARM ECLIPSE](https://gnu-mcu-eclipse.github.io/toolchain/arm/install/) - svi potrebni paketi i alati za rad u eclipsu sa STM32F4 kontrolerima 
* Qt Creator
* Qt 5.12
