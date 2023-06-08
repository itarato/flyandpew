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

struct WaveMove : Mover {
  Ticker ticker{};
  int v{4};
  const int steps{255};
  bool init{false};

  WaveMove() {}
  WaveMove(int v) : v(v) {}

  ~WaveMove() {}

  void visit(Entity* entity) {
    // 0..1
    float deg_v = (float)(ticker.tick() % (steps + 1)) / (float)steps;
    // 360
    float deg = deg_v * PI * 2.0;
    entity->v.x = cosf(deg) * (float)v;
  }
};

struct ClassicArcadeMove : Mover {
  PhaseTicker phase_ticker{{30, 120, 30, 120}};

  ClassicArcadeMove() {}
  ~ClassicArcadeMove() {}

  void visit(Entity* entity) {
    phase_ticker.tick();

    switch (phase_ticker.phase) {
      case 0:
        entity->v.x = 0;
        entity->v.y = 2;
        break;
      case 1:
        entity->v.x = 1;
        entity->v.y = 0;
        break;
      case 2:
        entity->v.x = 0;
        entity->v.y = 2;
        break;
      case 3:
        entity->v.x = -1;
        entity->v.y = 0;
        break;
      default:
        TraceLog(LOG_ERROR, "Bad phase");
        exit(EXIT_FAILURE);
    }
  }
};
