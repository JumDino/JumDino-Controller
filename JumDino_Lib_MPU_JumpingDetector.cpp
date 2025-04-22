#include "JumDino_Lib_MPU_JumpingDetector.h"


void JumpingDetector::update(int16_t ax, int16_t ay, int16_t az) {

  // Phát hiện nhảy lên
  // Gia tốc giảm mạnh khi người nhảy lên (cảm biến sẽ cho giá trị âm lớn khi người rời khỏi mặt đất)
  if (isIdle() && isWaitingTimeOver() && az > 32000) {
    logSwitchState_(MOTION_STATE_JUMPING_UP, az);
    if (_launcher != NULL) {
      _launcher->onJumpingBegin();
    }
    _state = MOTION_STATE_JUMPING_UP;
    lastMillis = millis();  // Ghi lại thời gian nhảy bắt đầu
  }

  if (isIdle() && isWaitingTimeOver() && az < 5000) {
    logSwitchState_(MOTION_STATE_SQUATTING_DOWN, az);
    if (_launcher != NULL) {
      _launcher->onSquattingBegin();
    }
    _state = MOTION_STATE_SQUATTING_DOWN;
    lastMillis = millis();  // Ghi lại thời gian nhảy bắt đầu
  }

  // Kiểm tra khi gia tốc theo Z tăng lên (người tiếp đất)
  if (_state == MOTION_STATE_JUMPING_UP && az < 22000) {
    logSwitchState_(MOTION_STATE_JUMPING_DOWN, az);
    _state = MOTION_STATE_JUMPING_DOWN;
  }

  if (_state == MOTION_STATE_SQUATTING_DOWN && az > 16000) {
    logSwitchState_(MOTION_STATE_SQUATTING_UP, az);
    _state = MOTION_STATE_SQUATTING_UP;
  }

  if (_state == MOTION_STATE_JUMPING_DOWN && az < 18000) {
    if (_launcher != NULL) {
      _launcher->onJumpingEnd();
    }
    logSwitchState_(MOTION_STATE_IDLE, az);
    _state = MOTION_STATE_IDLE;
    finishMillis = millis();
  }

  if (_state == MOTION_STATE_SQUATTING_UP && az > 25000) {
    if (_launcher != NULL) {
      _launcher->onSquattingEnd();
    }
    logSwitchState_(MOTION_STATE_IDLE, az);
    _state = MOTION_STATE_IDLE;
    finishMillis = millis();
  }

  if (isJumping() && exceedThresholdTime()) {
    logSwitchState_(MOTION_STATE_IDLE, az, true);
    _state = MOTION_STATE_IDLE;
    finishMillis = millis();
    lastMillis = millis();
  }

  if (isSquatting() && exceedThresholdTime()) {
    logSwitchState_(MOTION_STATE_IDLE, az, true);
    _state = MOTION_STATE_IDLE;
    finishMillis = millis();
    lastMillis = millis();
  }
}


void JumpingDetector::initialize() {
}

void JumpingDetector::showinfo() {
}

bool JumpingDetector::exceedThresholdTime() {
  return millis() - lastMillis > 2*actionThresholdTime;
}

bool JumpingDetector::isWaitingTimeOver() {
  return millis() - finishMillis > 700;
}

bool JumpingDetector::isIdle() {
  return _state == MOTION_STATE_IDLE;
}

bool JumpingDetector::isJumping() {
  return _state == MOTION_STATE_JUMPING_UP || _state == MOTION_STATE_JUMPING_DOWN;
}

bool JumpingDetector::isSquatting() {
  return _state == MOTION_STATE_SQUATTING_UP || _state == MOTION_STATE_SQUATTING_DOWN;
}

motion_state_t JumpingDetector::getState() {
  return _state;
}

void JumpingDetector::logSwitchState_(motion_state_t next_state, int16_t az, bool auto_change) {
}

//-------------------------------------------------------------------------------------------------

void JumpingDetectorSerialLog::logSwitchState_(motion_state_t next_state, int16_t az, bool auto_change) {
  if (auto_change) {
    Serial.print(" auto [");
  } else {
    Serial.print(" [");
  }
  Serial.print(stringify(getState()));
  Serial.print("]->[");
  Serial.print(stringify(next_state));
  Serial.print("] with az: ");
  Serial.println(az);
  if (next_state == MOTION_STATE_IDLE) {
    Serial.println();
  }
}

char* JumpingDetectorSerialLog::stringify(motion_state_t state) {
  switch(state) {
    case MOTION_STATE_IDLE:
      return "idle";
    case MOTION_STATE_JUMPING_UP:
      return "jumping_up";
    case MOTION_STATE_JUMPING_DOWN:
      return "jumping_down";
    case MOTION_STATE_SQUATTING_DOWN:
      return "squatting_down";
    case MOTION_STATE_SQUATTING_UP:
      return "squatting_up";
  }
}
