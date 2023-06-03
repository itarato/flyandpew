#pragma once

#include <memory>
#include <vector>

#include "config.h"
#include "entity.h"
#include "fire.h"
#include "input.h"
#include "util.h"

using namespace std;

#define PLAYER_VELOCITY 5.0
#define PLAYER_MAX_V 12.0
#define PLAYER_SPACE_FRIC 0.8

struct Player : Entity {
  Input input{};
  vector<unique_ptr<Fire>> bullets{};

  Player() : Entity(Vector2{60.0, 60.0}) { reset(); }

  void reset() {
    pos.x = GetScreenWidth() >> 1;
    pos.y = GetScreenHeight() >> 1;
    v.x = 0.0;
    v.y = 0.0;
    bullets.clear();
    active = true;
  }

  Rectangle frame() const {
    return Rectangle{pos.x - (dim.x / 2.0f), pos.y - (dim.y / 2.0f), dim.x,
                     dim.y};
  }

  void update() {
    {  // Movement.
      const float ix = input.x();
      if (ix != 0.0) {
        v.x += ix * PLAYER_VELOCITY * config.v();
      } else {
        v.x = 0;
      }

      const float iy = input.y();
      if (iy != 0.0) {
        v.y += iy * PLAYER_VELOCITY * config.v();
      } else {
        v.y = 0;
      }
      bound(&v.x, -PLAYER_MAX_V * config.v(), PLAYER_MAX_V * config.v());
      bound(&v.y, -PLAYER_MAX_V * config.v(), PLAYER_MAX_V * config.v());

      pos.x += v.x;
      pos.y += v.y;
      bound(&pos.x, 0.0, GetScreenWidth());
      bound(&pos.y, 0.0, GetScreenHeight());
    }

    {  // Fire.
      if (input.fire()) {
        bullets.emplace_back(make_unique<Rocket>(pos));
      }

      for (auto &fire : bullets) {
        fire.get()->update();
      }

      remove_inactive(bullets);
    }
  }

  void draw() {
    DrawRectangleRec(frame(), RED);

    for (auto &fire : bullets) {
      fire.get()->draw();
    }
  }
};
