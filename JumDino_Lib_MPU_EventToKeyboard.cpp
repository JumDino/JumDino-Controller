#include "JumDino_Lib_MPU_EventToKeyboard.h"

#if defined(ARDUINO_UNOR4_WIFI)

#include "Keyboard.h"

void JumpingToKeyboardLauncher::onJumpingBegin() {
  Keyboard.press(KEY_UP_ARROW);
}

void JumpingToKeyboardLauncher::onJumpingEnd() {
  Keyboard.release(KEY_UP_ARROW);
}

void JumpingToKeyboardLauncher::onSquattingBegin() {
  Keyboard.press(KEY_DOWN_ARROW);
}

void JumpingToKeyboardLauncher::onSquattingEnd() {
  Keyboard.release(KEY_DOWN_ARROW);
}

#endif
