#ifndef __POKEROBO_LAB_MPU_JUMPING_DETECTOR_H__
#define __POKEROBO_LAB_MPU_JUMPING_DETECTOR_H__

#include "JumDino_Lib_MPU_JumpingLauncher.h"

typedef enum {
  MOTION_STATE_IDLE = 0,
  MOTION_STATE_JUMPING_UP,
  MOTION_STATE_JUMPING_DOWN,
  MOTION_STATE_SQUATTING_DOWN,
  MOTION_STATE_SQUATTING_UP
} motion_state_t;


class JumpingDetector {
  public:
    JumpingDetector(JumpingLauncher* listener = NULL) {
      _launcher = (listener != NULL) ? listener : new JumpingLauncher();
      finishMillis = millis();
      initialize();
    }
    void update(int16_t ax, int16_t ay, int16_t az);
    virtual void initialize();
    virtual void showinfo();
  protected:
    bool exceedThresholdTime();
    bool isWaitingTimeOver();
    bool isJumping();
    bool isSquatting();
    bool isIdle();
    motion_state_t getState();
    virtual void logSwitchState_(motion_state_t next_state, int16_t az, bool auto_change=false);
  private:
    unsigned long finishMillis = 0;
    unsigned long lastMillis = 0;
    unsigned long actionThresholdTime = 300;
    motion_state_t _state = MOTION_STATE_IDLE;
    JumpingLauncher* _launcher = NULL;
};


class JumpingDetectorSerialLog: public JumpingDetector {
  public:
    using JumpingDetector::JumpingDetector;
  protected:
    char* stringify(motion_state_t state);
    void logSwitchState_(motion_state_t next_state, int16_t az, bool auto_change=false);
};

#endif
