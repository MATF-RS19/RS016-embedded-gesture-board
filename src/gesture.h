void GestIC_Read(char msgLen);
void GestIC_Write( uint8_t msgLen);
char setAirWheel(char ENABLE);
char setTouchDetection(char ENABLE);
char setApproachDetection(char ENABLE);
char setApproachDetection2(char ENABLE);
char setGestureProcessingHMM(char PARAM);
char setCalibrationOperationMode(char ENABLE);
char setDataOutputEnableMask(char PARAM);
char setDataOutputLockMask(char PARAM);
char setDataOutputRequestkMask(char PARAM);
char setGestureInProgressFlag(char ENABLE);
char setMakePersistent(char PARAM);
char setTrigger(char PARAM);
void setElectrodeMap(char Electrode, char Channel);
void TransFreqSelect(char FreqCnt, unsigned long FreqOrder);
void setEnableAllGestures();
void getFWInfo();
void updateRawData();
void updateGestureData();

void setRDYPinToOutput();
void setRDYPinToInput();
void setRDYpin(uint8_t s);
void setRSTpin(uint8_t s);
uint8_t readRDYpin();

void setRSTPinToOutput();
void setRSTPinToInput();

