#pragma once

#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

struct UIElement {
  bool active{true};

  UIElement() {}
  virtual ~UIElement() {}

  virtual void draw() = 0;
  virtual void update() = 0;

  void deactivate() { active = false; }
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

  void tick() { ticker++; }
  void reset() { ticker = 0; }
};
