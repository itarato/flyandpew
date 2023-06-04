#pragma once

#include <raylib.h>

struct Input {
  Input() {}

  inline int gamepad_id() const { return 0; }

  float x() const {
    if (IsGamepadAvailable(gamepad_id())) {
      return GetGamepadAxisMovement(gamepad_id(), GAMEPAD_AXIS_LEFT_X);
    } else {
      if (IsKeyDown(KEY_LEFT)) {
        return -1.0;
      } else if (IsKeyDown(KEY_RIGHT)) {
        return 1.0;
      }
    }

    return 0.0;
  }

  float y() const {
    if (IsGamepadAvailable(gamepad_id())) {
      return GetGamepadAxisMovement(gamepad_id(), GAMEPAD_AXIS_LEFT_Y);
    } else {
      if (IsKeyDown(KEY_UP)) {
        return -1.0;
      } else if (IsKeyDown(KEY_DOWN)) {
        return 1.0;
      }
    }

    return 0.0;
  }

  bool fire() const {
    if (IsKeyPressed(KEY_SPACE)) {
      return true;
    }
    if (IsGamepadButtonPressed(gamepad_id(), GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) {
      return true;
    }

    return false;
  }

  bool dpad_left() const {
    if (IsGamepadAvailable(gamepad_id())) {
      if (IsGamepadButtonPressed(gamepad_id(), GAMEPAD_BUTTON_LEFT_FACE_LEFT)) {
        return true;
      }
    } else {
      if (IsKeyPressed(KEY_A)) {
        return true;
      }
    }

    return false;
  }

  bool dpad_right() const {
    if (IsGamepadAvailable(gamepad_id())) {
      if (IsGamepadButtonPressed(gamepad_id(),
                                 GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) {
        return true;
      }
    } else {
      if (IsKeyPressed(KEY_D)) {
        return true;
      }
    }

    return false;
  }
};
