#pragma once

#include <raylib.h>

#include <memory>
#include <vector>

#include "entity.h"
#include "fire.h"
#include "player.h"
#include "util.h"

using namespace std;

#define UPGRADE_TYPE_BULLET 0
#define UPGRADE_TYPE_HEALTH 1
#define UPGRADE_TYPE_COUNT 2

#define UPGRADE_SPEED 2

struct Upgrade : Entity {
  int type;

  int v1;
  int v2;

  Upgrade(int type, Vector2 pos)
      : Entity(Vector2(30.0, 30.0), pos, Vector2{0.0, UPGRADE_SPEED}),
        type(type) {
    init();
  }

  Upgrade(int type, Vector2 pos, int v1, int v2)
      : Entity(Vector2(30.0, 30.0), pos, Vector2{0.0, UPGRADE_SPEED}),
        type(type),
        v1(v1),
        v2(v2) {
    init();
  }

  void init() {
    switch (type) {
      case UPGRADE_TYPE_BULLET:
        setTexture(RESRC_UPGRADE_BULLET);
        break;
      case UPGRADE_TYPE_HEALTH:
        setTexture(RESRC_UPGRADE_HEALTH);
        break;
      default:
        TraceLog(LOG_ERROR, "Invalid type");
        exit(EXIT_FAILURE);
    }
  }

  void update() {
    Entity::update();

    if (pos.y >= GetScreenHeight()) deactivate();
  }

  void apply(Player* player) {
    switch (type) {
      case UPGRADE_TYPE_BULLET:
        player->bullet_manager.capacity[v1] += v2;
        break;
      case UPGRADE_TYPE_HEALTH:
        player->health++;
        break;
      default:
        TraceLog(LOG_ERROR, "Invalid upgrade type on apply");
        exit(EXIT_FAILURE);
    }
  }
};

struct UpgradeManager : UIElement {
  vector<unique_ptr<Upgrade>> upgrades{};
  const float upgrade_chances[2] = {
      0.002,  // Bullet.
      0.001,  // Life.
  };

  void reset() { upgrades.clear(); }

  void update() {
    for (int i = 0; i < UPGRADE_TYPE_COUNT; i++) {
      if (randf() < upgrade_chances[i]) {
        switch (i) {
          case UPGRADE_TYPE_BULLET:
            // Preferrably this would not be hardcoded here. Fire manager or
            // Fire classes should own this via a virtual interface, and here
            // we would just iterate through -> so adding a new Fire type
            // automatically enables the upgrade.
            upgrades.emplace_back(make_unique<Upgrade>(
                UPGRADE_TYPE_BULLET, Vector2(randi(0, GetScreenWidth()), 0.0),
                FIRE_ROCKET, 2));
            break;
          case UPGRADE_TYPE_HEALTH:
            upgrades.emplace_back(make_unique<Upgrade>(
                UPGRADE_TYPE_HEALTH, Vector2(randi(0, GetScreenWidth()), 0.0),
                1, 0));
            break;
          default:
            TraceLog(LOG_ERROR, "Invalid upgrade type");
            exit(EXIT_FAILURE);
        }
      }
    }

    for (auto& upgrade : upgrades) {
      upgrade->update();
    }

    remove_inactive(upgrades);
  }

  void draw() {
    for (auto& upgrade : upgrades) {
      upgrade->draw();
    }
  }
};
