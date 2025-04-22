#ifndef __POKEROBO_LAB_MPU_JUMPING_PROGRAM_H__
#define __POKEROBO_LAB_MPU_JUMPING_PROGRAM_H__

#include "JumDino_Lib_MPU_JumpingDetector.h"
#include "JumDino_Lib_BLE_Central.h"


class JumpingReceiver: public PokeroboBLEReceiver {
  public:
    JumpingReceiver(JumpingDetector *detector) {
      _detector = detector;
    }
    void onReceive(int32_t value) {
      _detector->update(0, 0, value);
    }
  private:
    JumpingDetector *_detector = NULL;
};

#endif
