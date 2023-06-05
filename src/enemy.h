#pragma once

#include <memory>
#include <vector>

#include "config.h"
#include "entity.h"
#include "fire.h"
#include "move.h"
#include "util.h"

using namespace std;

#define ENEMY_DEFAULT_HEALTH 10

struct Enemy : Entity {
  int health{ENEMY_DEFAULT_HEALTH};
  unique_ptr<Mover> mover{nullptr};
  float fire_chance{0.001};

  Enemy(Vector2 pos, unique_ptr<Mover> _mover)
      : Entity(Vector2{60.0, 40.0}, pos, Vector2{0.0, 1.0}) {
    mover.swap(_mover);
  }

  ~Enemy() {}

  Rectangle frame() const {
    return Rectangle{pos.x - (dim.x / 2), pos.y - (dim.y / 2), dim.x, dim.y};
  }

  void update() {}

  void update(vector<unique_ptr<Fire>>* bullet_collector) {
    if (mover) {
      mover.get()->visit(this);
    }

    pos.x += v.x * config.v();
    pos.y += v.y * config.v();

    if (pos.x < 0 || pos.x > GetScreenWidth() || pos.y > GetScreenHeight()) {
      deactivate();
    }

    if (randf() < fire_chance) {
      // TODO: Add fire (to app).
      bullet_collector->emplace_back(
          make_unique<SmallLaserFire>(pos, Vector2(0.0, FIRE_DEFAULT_SPEED)));
    }
  }

  void draw() { DrawRectangleRec(frame(), GREEN); }

  void hit(Fire* fire) {
    health -= fire->power;
    if (health <= 0) {
      deactivate();
    }
  }
};

struct BaseEnemy : Enemy {
  BaseEnemy(Vector2 pos) : Enemy(pos, make_unique<SinMove>()) {
    health = ENEMY_DEFAULT_HEALTH;
  }
  ~BaseEnemy() {}
};

struct EnemyManager {
  vector<unique_ptr<Enemy>> enemies{};
  Ticker ticker{};
  vector<unique_ptr<Fire>> bullets{};

  EnemyManager() {}

  void reset() {
    enemies.clear();
    ticker.reset();
    bullets.clear();
  }

  void update() {
    if (enemies.empty()) {
      makeZigZagGrid(6, 4);
    }

    for (auto& enemy : enemies) {
      enemy.get()->update(&bullets);
    }

    for (auto& bullet : bullets) {
      bullet->update();
    }

    remove_inactive(enemies);
    remove_inactive(bullets);
  }

  void draw() {
    for (auto& enemy : enemies) {
      enemy.get()->draw();
    }

    for (auto& bullet : bullets) {
      bullet->draw();
    }
  }

  void makeZigZagGrid(int x, int y) {
    int spacing = GetScreenWidth() / (x + 1);
    for (int j = 0; j < y; j++) {
      for (int i = 0; i < x; i++) {
        enemies.emplace_back(make_unique<BaseEnemy>(Vector2{
            (float)((i + 1) * spacing), (float)((j - y + 1) * spacing)}));
      }
    }
  }
};
