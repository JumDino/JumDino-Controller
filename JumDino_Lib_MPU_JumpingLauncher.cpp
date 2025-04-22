#include "JumDino_Lib_MPU_JumpingLauncher.h"

JumpingLauncher::JumpingLauncher(bool serialLog) {
  _serialLog = serialLog;
}

void JumpingLauncher::onJumpingBegin() {
  if (_serialLog) {
    Serial.println("Jumping begin");
  }
}

void JumpingLauncher::onJumpingEnd() {
  if (_serialLog) {
    Serial.println("Jumping end");
  }
}

void JumpingLauncher::onSquattingBegin() {
  if (_serialLog) {
    Serial.println("Squatting begin");
  }
}

void JumpingLauncher::onSquattingEnd() {
  if (_serialLog) {
    Serial.println("Squatting end");
  }
}
