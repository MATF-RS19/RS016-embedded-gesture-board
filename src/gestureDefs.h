// DEfinicije registara i komandi za gesture
// moze se naci u datasheetu za gesture

#ifndef _GESTURE_DEFS
#define _GESTURE_DEFS

// I2C slave adrese gesture-a
#define MGC_ADDR0           0x42
#define MGC_ADDR1           0x43

// vrednosti koje gesture daje kad se cita firmware verzija
#define FW_EMPTY            0x00
#define FW_INVALID          0x0A
#define FW_VALID            0xAA

//Electrode mapping
/*
#define Channelmapping_S    0x65
#define Channelmapping_W    0x66
#define Channelmapping_N    0x67
#define Channelmapping_E    0x68
#define Channelmapping_C    0x69
#define Rx0                 0x00
#define Rx1                 0x01
#define Rx2                 0x02
#define Rx3                 0x03
#define Rx4                 0x04
*/

// moguce vrednosti gesture dogadjaja
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

// TODO ovo nam ne treba
typedef struct {
 unsigned int X;
 unsigned int Y;
 unsigned int Z;
}s_Position;

// TODO
typedef struct {
 char FWValid;
 char HWRev[2];                   //2 bytes decimal format interpreter xx.xx
 char ParameterStartAddr;
 char LibraryLoaderVersion[3];    //3 bytes decimal format interpreter xx.xx.xx
 char FwStartAddr;
 char FwVersion[120];             //za slabije kontrolere izbaciti ovaj parametar
}s_FWVersionInfo;

// TODO
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

// TODO
typedef struct {
 s_DataOut DataOut;
 s_FWVersionInfo FWVersionInfo;
}s_Gesture;

#endif
