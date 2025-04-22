#ifndef __POKEROBO_LAB_MPU_EVENT_TO_KEYBOARD_H__
#define __POKEROBO_LAB_MPU_EVENT_TO_KEYBOARD_H__

#if defined(ARDUINO_UNOR4_WIFI)

#include "JumDino_Lib_MPU_JumpingDetector.h"

// inheritance
class JumpingToKeyboardLauncher: public JumpingLauncher {
  public:
    void onJumpingBegin();
    void onJumpingEnd();
    void onSquattingBegin();
    void onSquattingEnd();
};

#endif

#endif
