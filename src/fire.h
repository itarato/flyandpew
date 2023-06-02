#pragma once

#include <raylib.h>

#include "entity.h"

/**
 * All fire POS is bottom-center.
 */

#define FIRE_DEFAULT_SPEED -10.0
#define FIRE_DEFAULT_POWER 10
struct Fire : Entity {
  int power{FIRE_DEFAULT_POWER};

  Fire(Vector2 pos) : Entity({4.0, 12.0}, pos, {0.0, FIRE_DEFAULT_SPEED}) {}

  ~Fire() {}

  Rectangle frame() const {
    return Rectangle{pos.x - (dim.x / 2), pos.y, dim.x, dim.y};
  }

  void update() {
    pos.x += v.x;
    pos.y += v.y;

    if (pos.x < 0.0 || pos.x > GetScreenWidth() || pos.y < 0.0) {
      deactivate();
    }
  }

  void draw() { DrawRectangleRec(frame(), BLUE); }
};

struct SmallLaserFire : Fire {
  SmallLaserFire(Vector2 pos) : Fire(pos) {}
  ~SmallLaserFire() {}
};
