#pragma once

#include <algorithm>
#include <cstdlib>
#include <memory>
#include <vector>

using namespace std;

inline void bound(float* what, float min, float max) {
  if (*what < min) {
    *what = min;
  } else if (*what > max) {
    *what = max;
  }
}

template <typename T>
void remove_inactive(vector<unique_ptr<T>>& items) {
  items.erase(remove_if(items.begin(), items.end(),
                        [](const auto& e) { return !e.get()->active; }),
              items.end());
}

struct Ticker {
  uint64_t ticker{0};

  Ticker() {}

  int tick() { return ticker++; }
  void reset() { ticker = 0; }
};

struct ModTicker : Ticker {
  int mod;

  ModTicker(int mod) : Ticker(), mod(mod) {}

  bool tick_and_test() {
    tick();
    if (ticker == (uint64_t)mod) {
      reset();
      return true;
    } else {
      return false;
    }
  }
};

// [min, max]
int randi(int min, int max) { return (rand() % (max - min + 1)) + min; }
// [0.0, 1.0]
float randf() { return (float)(rand() & 0xFFFF) / 0xFFFF; }
// [min, max]
float randf(float min, float max) { return randf() * (max - min) + min; }
