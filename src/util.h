#pragma once

inline void bound(float* what, float min, float max) {
  if (*what < min) {
    *what = min;
  } else if (*what > max) {
    *what = max;
  }
}
