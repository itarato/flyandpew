#pragma once

#include <algorithm>
#include <cstdlib>
#include <memory>
#include <vector>

using namespace std;

struct Circle {
  Vector2 center;
  int rad;

  Circle(Vector2 center, int rad) : center(center), rad(rad) {}
  Circle(float x, float y, int rad) : center(Vector2(x, y)), rad(rad) {}
};

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

  virtual uint64_t tick() { return ticker++; }
  void reset() { ticker = 0; }
};

struct ModTicker : Ticker {
  int mod;

  ModTicker(int mod) : Ticker(), mod(mod) {}

  bool tick_and_test() {
    if (tick() == (uint64_t)mod) {
      reset();
      return true;
    } else {
      return false;
    }
  }
};

struct PhaseTicker : Ticker {
  const vector<int> phases;
  int phase{0};

  PhaseTicker(vector<int> phases) : Ticker(), phases(phases) {}

  uint64_t tick() {
    const int res = Ticker::tick();

    if (ticker >= (uint64_t)phases[phase]) {
      phase = (phase + 1) % phases.size();
      reset();
    }

    return res;
  }
};

struct Countdown {
  int counter;
  const int count;

  Countdown(int count) : count(count) { reset(); }

  bool tick() {
    if (counter == 0) {
      return true;
    }

    counter--;
    return false;
  }

  void reset() { counter = count; }
};

// [min, max]
int randi(int min, int max) { return (rand() % (max - min + 1)) + min; }
// [0.0, 1.0]
float randf() { return (float)(rand() & 0xFFFF) / 0xFFFF; }
// [min, max]
float randf(float min, float max) { return randf() * (max - min) + min; }
