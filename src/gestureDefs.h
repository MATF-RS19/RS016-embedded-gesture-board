// DEfinicije registara i komandi za gesture
// moze se naci u datasheetu za gesture

#ifndef _GESTURE_DEFS
#define _GESTURE_DEFS

// I2C slave adrese gesture-a
//http://ww1.microchip.com/downloads/en/DeviceDoc/40001718E.pdf strana 13
#define MGC_ADDR0           0x42
#define MGC_ADDR1           0x43

// vrednosti koje gesture daje kad se cita firmware verzija
// http://ww1.microchip.com/downloads/en/DeviceDoc/40001718E.pdf strana 30
#define FW_EMPTY            0x00
#define FW_INVALID          0x0A
#define FW_VALID            0xAA

// moguce vrednosti gesture dogadjaja
// http://ww1.microchip.com/downloads/en/DeviceDoc/40001718E.pdf
// strana 45
#define  TapSouth           0x00000020
#define  TapWest            0x00000040
#define  TapNorth           0x00000080
#define  TapEast            0x00000100
#define  TapCenter          0x00000200
#define  DoubleTapSouth     0x00000400
#define  DoubleTapWest      0x00000800
#define  DoubleTapNorth     0x00001000
#define  DoubleTapEast      0x00002000
#define  DoubleTapCenter    0x00004000


// http://ww1.microchip.com/downloads/en/DeviceDoc/40001718E.pdf strana 30
typedef struct {
 char FWValid;
 char HWRev[2];                   //2 bytes decimal format interpreter xx.xx
 char ParameterStartAddr;
 char LibraryLoaderVersion[3];    //3 bytes decimal format interpreter xx.xx.xx
 char FwStartAddr;
 char FwVersion[120];
}s_FWVersionInfo;

// http://ww1.microchip.com/downloads/en/DeviceDoc/40001718E.pdf strana 42
typedef struct {
 char Len;
 char Flags;
 char Seq;
 char Id;
 unsigned int ConfigMask;
 char TimeStamp;
 char SystemInfo;
 unsigned int DSPStatus;
 unsigned long GestureInfo;
 unsigned long TouchInfo;
 unsigned int AirWheelInfo;
 s_Position Position;
 float NoisePower;
}s_DataOut;


typedef struct {
 s_DataOut DataOut;
 s_FWVersionInfo FWVersionInfo;
}s_Gesture;

#endif
