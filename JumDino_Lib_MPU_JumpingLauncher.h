#ifndef __JUMDINO_LIB_MPU_JUMPING_LAUNCHER_H__
#define __JUMDINO_LIB_MPU_JUMPING_LAUNCHER_H__

#include <Arduino.h>

class JumpingLauncher {
  public:
    JumpingLauncher(bool serialLog = false);
    virtual void onJumpingBegin();
    virtual void onJumpingEnd();
    virtual void onSquattingBegin();
    virtual void onSquattingEnd();
  private:
    bool _serialLog = false;
};

#endif
