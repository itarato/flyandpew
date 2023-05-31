#pragma once

#include <cstdint>

struct Config {
  int win_w;
  int win_h;
  int fps;
  // Generic velocity adjustment (related to FPS);
  inline constexpr float v() { return 60.0f / (float)fps; }
} config;
