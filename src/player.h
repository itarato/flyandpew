#pragma once

#include <cinttypes>
#include <memory>
#include <vector>

#include "config.h"
#include "entity.h"
#include "fire.h"
#include "input.h"
#include "resource.h"
#include "util.h"

using namespace std;

#define PLAYER_VELOCITY 5.0
#define PLAYER_MAX_V 12.0
#define PLAYER_SPACE_FRIC 0.8

#define PLAYER_HEALTH 3

const char *fire_names[] = {"Mini pew", "Bim bam pew", "Double pew"};

struct Player : Entity {
  Input input{};
  vector<unique_ptr<Fire>> bullets{};
  uint8_t fire_type{FIRE_BASIC};
  int health{PLAYER_HEALTH};
  BulletManager bullet_manager{};
  PhaseTicker fire_phase_ticker{{4, 1}};
  bool shield{false};
  Countdown shield_countdown{420};

  Player() : Entity() {}

  void reset() {
    setTexture(RESRC_PLAYER);
    pos.x = GetScreenWidth() >> 1;
    pos.y = GetScreenHeight() >> 1;
    v.x = 0.0;
    v.y = 0.0;
    bullets.clear();
    active = true;
    health = PLAYER_HEALTH;
    bullet_manager.reset();
    shield = false;
    shield_countdown.reset();
  }

  void hit() {
    health--;
    if (health <= 0) {
      deactivate();
    }
  }

  void shield_up() {
    shield = true;
    shield_countdown.reset();
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
      bound(&pos.x, dim.x / 2, GetScreenWidth() - (dim.x / 2));
      bound(&pos.y, dim.y / 2, GetScreenHeight() - (dim.y / 2));
    }

    {  // Fire selection.
      if (input.dpad_left()) fire_type--;
      if (input.dpad_right()) fire_type++;
      fire_type = fire_type % FIRE_SELECTION_SIZE;
    }

    {  // Fire.
      if (input.fire() && bullet_manager.has_capacity(fire_type)) {
        bullet_manager.make_one(&bullets, fire_type, pos);
      }

      for (auto &fire : bullets) {
        fire.get()->update();
      }

      remove_inactive(bullets);
    }

    {  // Shield.
      if (shield_countdown.tick()) {
        shield = false;
      }
    }

    fire_phase_ticker.tick();
  }

  void draw() {
    for (auto &fire : bullets) {
      fire.get()->draw();
    }

    Entity::draw();

    if (shield) {
      Texture2D *shield_texture = &resource_manager.textures[RESRC_SHIELD];
      DrawTexture(*shield_texture, pos.x - (shield_texture->width / 2),
                  pos.y - (shield_texture->height / 2), WHITE);
    }

    const Texture2D *exhaust_texture =
        &resource_manager.textures[RESRC_EFFECT_EXHAUST];

    if (fire_phase_ticker.phase == 0) {
      DrawTexture(*exhaust_texture, pos.x - (exhaust_texture->width / 2),
                  pos.y + (dim.y / 2), WHITE);
    }
  }
};
