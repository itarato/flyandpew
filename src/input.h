#pragma once

#include <raylib.h>

struct Input {
  Input() {}

  const float x() {
    if (IsGamepadAvailable(0)) {
      return GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X);
    } else {
      if (IsKeyDown(KEY_LEFT)) {
        return -1.0;
      } else if (IsKeyDown(KEY_RIGHT)) {
        return 1.0;
      }
    }

    return 0.0;
  }

  const float y() {
    if (IsGamepadAvailable(0)) {
      return GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y);
    } else {
      if (IsKeyDown(KEY_UP)) {
        return -1.0;
      } else if (IsKeyDown(KEY_DOWN)) {
        return 1.0;
      }
    }

    return 0.0;
  }

  const bool fire() {
    if (IsKeyPressed(KEY_SPACE)) {
      return true;
    }
    if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) {
      return true;
    }

    return false;
  }
};
