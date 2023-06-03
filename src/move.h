#pragma once

#include <cmath>

#include "entity.h"
#include "util.h"

struct Mover {
  Mover() {}
  ~Mover() {}

  virtual void visit(Entity* entity) = 0;
};

struct ZigZagMove : Mover {
  ModTicker ticker{32};
  int v{2};
  bool init{false};

  ZigZagMove() {}
  ZigZagMove(int ticker, int v) : ticker(ModTicker(ticker)), v(v) {}

  ~ZigZagMove() {}

  void visit(Entity* entity) {
    if (!init) {
      init = true;
      entity->v.x = v;
    }

    if (ticker.tick_and_test()) {
      entity->v.x *= -1;
    }
  }
};

struct SinMove : Mover {
  Ticker ticker{};
  int v{4};
  const int steps{255};
  bool init{false};

  SinMove() {}
  SinMove(int v) : v(v) {}

  ~SinMove() {}

  void visit(Entity* entity) {
    // 0..1
    float deg_v = (float)(ticker.tick() % (steps + 1)) / (float)steps;
    // 360
    float deg = deg_v * PI * 2.0;
    entity->v.x = sinf(deg) * (float)v;
  }
};
