#pragma once

#include <raylib.h>

struct Input {
  Input() {}

  const float x() {
    if (IsKeyDown(KEY_LEFT)) {
      return -1.0;
    } else if (IsKeyDown(KEY_RIGHT)) {
      return 1.0;
    }

    return 0.0;
  }

  const float y() {
    if (IsKeyDown(KEY_UP)) {
      return -1.0;
    } else if (IsKeyDown(KEY_DOWN)) {
      return 1.0;
    }

    return 0.0;
  }
};
