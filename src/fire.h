#pragma once

#include <raylib.h>

#include "entity.h"

/**
 * All fire POS is bottom-center.
 */

#define FIRE_SMALL_LASER_FIRE_SPEED -10.0

struct SmallLaserFire : Entity {
  SmallLaserFire(Vector2 pos)
      : Entity({4.0, 12.0}, pos, {0.0, FIRE_SMALL_LASER_FIRE_SPEED}) {}

  ~SmallLaserFire() {}

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
