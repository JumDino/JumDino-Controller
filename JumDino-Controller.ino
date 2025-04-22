#include "JumDino_Lib_BLE_Central.h"

#include "JumDino_Lib_MPU_JumpingDetector.h"

#if defined(ARDUINO_UNOR4_WIFI)
#include "JumDino_Lib_MPU_EventToKeyboard.h"
#endif

#include "JumDino_Lib_MPU_JumpingReceiver.h"

#if defined(ARDUINO_UNOR4_WIFI)
JumpingToKeyboardLauncher jumpingLauncher;
#else
JumpingLauncher jumpingLauncher;
#endif

JumpingDetectorSerialLog jumpingDetector(&jumpingLauncher);
JumpingReceiver jumpingReceiver(&jumpingDetector);

PokeroboBLECentralDebugLogger serialLogger;
PokeroboBLECentral jumpingBLECentral("2A56", &jumpingReceiver, &serialLogger);

void setup() {
  delay(3000);
  Serial.begin(57600);
  jumpingBLECentral.begin("UNO-R4-BLE");
}

void loop() {
  Serial.println(" - loop() begin");
  jumpingBLECentral.check();
  Serial.println(" - loop() end!");
}
