#pragma once

#include <memory>
#include <vector>

#include "config.h"
#include "entity.h"
#include "fire.h"
#include "input.h"
#include "util.h"

using namespace std;

#define PLAYER_VELOCITY 10.0
#define PLAYER_MAX_V 10.0
#define PLAYER_SPACE_FRIC 0.9

struct Player : Entity {
  const int width{60};
  const int height{60};
  Input input{};
  vector<unique_ptr<UIElement>> bullets{};

  Player() : Entity() { reset(); }

  void reset() {
    pos.x = GetScreenWidth() >> 1;
    pos.y = GetScreenHeight() >> 1;
  }

  void update() {
    {  // Movement.
      const float ix = input.x();
      if (ix != 0.0) {
        v.x += ix * PLAYER_VELOCITY * config.v();
      } else {
        v.x *= PLAYER_SPACE_FRIC;
      }

      const float iy = input.y();
      if (iy != 0.0) {
        v.y += iy * PLAYER_VELOCITY * config.v();
      } else {
        v.y *= PLAYER_SPACE_FRIC;
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
        bullets.emplace_back(make_unique<SmallLaserFire>(pos));
      }

      for (auto &fire : bullets) {
        fire.get()->update();
      }

      remove_inactive(bullets);
    }
  }

  void draw() {
    DrawRectangle(pos.x - (width >> 1), pos.y - (height >> 1), width, height,
                  RED);

    for (auto &fire : bullets) {
      fire.get()->draw();
    }
  }
};
