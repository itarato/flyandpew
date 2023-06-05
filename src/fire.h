#pragma once

#include <raylib.h>

#include <optional>

#include "entity.h"
#include "util.h"

using namespace std;

/**
 * All fire POS is top-center.
 */

#define FIRE_DEFAULT_SPEED 10.0
#define FIRE_DEFAULT_POWER 10

struct Fire : Entity {
  int power{FIRE_DEFAULT_POWER};

  Fire(Vector2 pos) : Entity({4.0, 12.0}, pos, {0.0, -FIRE_DEFAULT_SPEED}) {}
  Fire(Vector2 pos, Vector2 v) : Entity({4.0, 12.0}, pos, v) {}
  Fire(Vector2 dim, Vector2 pos, Vector2 v) : Entity(dim, pos, v) {}

  ~Fire() {}

  Rectangle frame() const {
    return Rectangle{pos.x - (dim.x / 2), pos.y, dim.x, dim.y};
  }

  virtual optional<Circle> explosionFrame() const { return nullopt; }

  void update() {
    pos.x += v.x;
    pos.y += v.y;

    if (pos.x < 0.0 || pos.x > GetScreenWidth() || pos.y < 0.0 ||
        pos.y > GetScreenHeight()) {
      deactivate();
    }
  }

  void draw() { DrawRectangleRec(frame(), BLUE); }
};

struct SmallLaserFire : Fire {
  SmallLaserFire(Vector2 pos) : Fire(pos) {}
  SmallLaserFire(Vector2 pos, Vector2 v) : Fire(pos, v) {}
  ~SmallLaserFire() {}
};

struct Rocket : Fire {
  const int hit_rad{256};

  Rocket(Vector2 pos) : Fire(Vector2(8, 16), pos, Vector2(0, -5)) {}
  ~Rocket() {}

  optional<Circle> explosionFrame() const {
    return Circle(pos.x, pos.y + (dim.x / 2), hit_rad);
  }
};
