#pragma once

#include <raylib.h>
#include <raymath.h>

#include <map>
#include <optional>

#include "entity.h"
#include "resource.h"
#include "util.h"

using namespace std;

/**
 * All fire POS is top-center.
 */

#define FIRE_DEFAULT_SPEED 10.0
#define FIRE_DEFAULT_POWER 10
#define FIRE_CAPACITY_UNLIMIED -1

#define FIRE_BASIC 0
#define FIRE_ROCKET 1
#define FIRE_DOUBLE 2

#define FIRE_SELECTION_SIZE 3
#define FIRE_ROCKET_DEFAULT_COUNT 3

struct Fire : Entity {
  int power{FIRE_DEFAULT_POWER};

  Fire(Vector2 pos) : Entity({4.0, 12.0}, pos, {0.0, -FIRE_DEFAULT_SPEED}) {}
  Fire(Vector2 pos, Vector2 v) : Entity({4.0, 12.0}, pos, v) {}
  Fire(Vector2 dim, Vector2 pos, Vector2 v) : Entity(dim, pos, v) {}

  ~Fire() {}

  virtual optional<Circle> explosionFrame() const { return nullopt; }

  void update() {
    pos.x += v.x;
    pos.y += v.y;

    if (pos.x < 0.0 || pos.x > GetScreenWidth() || pos.y < 0.0 ||
        pos.y > GetScreenHeight()) {
      deactivate();
    }
  }
};

struct SmallLaserFire : Fire {
  SmallLaserFire(Vector2 pos) : Fire(pos) { init(); }
  SmallLaserFire(Vector2 pos, Vector2 v) : Fire(pos, v) { init(); }

  ~SmallLaserFire() {}

  void init() { setTexture(RESRC_LASER_BLUE_SMALL); }
};

struct Rocket : Fire {
  const int hit_rad{256};

  Rocket(Vector2 pos) : Fire(Vector2(8, 16), pos, Vector2(0, -5)) {
    setTexture(RESRC_LASER_RED_BIG);
  }
  ~Rocket() {}

  optional<Circle> explosionFrame() const {
    return Circle(pos.x, pos.y + (dim.x / 2), hit_rad);
  }
};

struct BulletManager {
  int capacity[FIRE_SELECTION_SIZE] = {0};

  BulletManager() { reset(); }

  void reset() {
    capacity[FIRE_BASIC] = FIRE_CAPACITY_UNLIMIED;
    capacity[FIRE_ROCKET] = FIRE_ROCKET_DEFAULT_COUNT;
    capacity[FIRE_DOUBLE] = FIRE_CAPACITY_UNLIMIED;
  }

  void make_one(vector<unique_ptr<Fire>>* container, int type, Vector2 pos) {
    if (capacity[type] == FIRE_CAPACITY_UNLIMIED) {
      // Do nothing, it's unlimited.
    } else if (capacity[type] > 0) {
      capacity[type]--;
    } else {
      TraceLog(LOG_ERROR,
               "Cannot create bullet. Always check with `has_capacity`.");
      exit(EXIT_FAILURE);
    }

    switch (type) {
      case FIRE_BASIC:
        container->emplace_back(make_unique<SmallLaserFire>(pos));
        break;
      case FIRE_ROCKET:
        container->emplace_back(make_unique<Rocket>(pos));
        break;
      case FIRE_DOUBLE:
        container->emplace_back(
            make_unique<SmallLaserFire>(Vector2Add(pos, Vector2(45.0, 0.0))));
        container->emplace_back(
            make_unique<SmallLaserFire>(Vector2Add(pos, Vector2(-45.0, 0.0))));
        break;
      default:
        TraceLog(LOG_ERROR, "Invalid fire type");
        exit(EXIT_FAILURE);
    }
  }

  bool has_capacity(int index) const {
    return capacity[index] == FIRE_CAPACITY_UNLIMIED || capacity[index] > 0;
  }
};
