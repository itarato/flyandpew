#pragma once

#include <memory>
#include <vector>

#include "config.h"
#include "entity.h"
#include "util.h"

using namespace std;

struct BaseEnemy : Entity {
  BaseEnemy()
      : Entity(Vector2{60.0, 40.0}, Vector2{GetScreenWidth() / 2.0f, 0.0},
               Vector2{0.0, 2.0}) {}

  ~BaseEnemy() {}

  Rectangle frame() const {
    return Rectangle{pos.x - (dim.x / 2), pos.y - (dim.y / 2), dim.x, dim.y};
  }

  void update() {
    pos.x += v.x * config.v();
    pos.y += v.y * config.v();

    if (pos.x < 0 || pos.x > GetScreenWidth() || pos.y > GetScreenHeight()) {
      deactivate();
    }
  }

  void draw() { DrawRectangleRec(frame(), GREEN); }
};

struct EnemyManager {
  vector<unique_ptr<Entity>> enemies{};
  Ticker ticker{};

  EnemyManager() {}

  void update() {
    if (ticker.ticker % 1000 == 0) {
      enemies.emplace_back(make_unique<BaseEnemy>());
    }

    for (auto& enemy : enemies) {
      enemy.get()->update();
    }

    remove_inactive(enemies);

    ticker.tick();
  }

  void draw() {
    for (auto& enemy : enemies) {
      enemy.get()->draw();
    }
  }
};
