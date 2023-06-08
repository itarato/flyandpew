#pragma once

#include <raylib.h>

#include <algorithm>
#include <memory>
#include <vector>

#include "config.h"
#include "entity.h"
#include "fire.h"
#include "move.h"
#include "resource.h"
#include "util.h"

using namespace std;

#define ENEMY_DEFAULT_HEALTH 10

struct Enemy : Entity {
  int health{ENEMY_DEFAULT_HEALTH};
  unique_ptr<Mover> mover{nullptr};
  bool is_static{false};
  float fire_chance{0.0};

  Enemy(Vector2 pos, unique_ptr<Mover> _mover)
      : Entity(Vector2{60.0, 40.0}, pos, Vector2{0.0, 1.0}) {
    mover.swap(_mover);
  }

  ~Enemy() {}

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

  virtual void hit(Fire* fire) {
    health -= fire->power;
    if (health <= 0) {
      deactivate();
    }
  }
};

const char* meteor_file_names[] = {
    "meteorBrown_big1.png",   "meteorBrown_big2.png",   "meteorBrown_big3.png",
    "meteorBrown_big4.png",   "meteorBrown_med1.png",   "meteorBrown_med3.png",
    "meteorBrown_small1.png", "meteorBrown_small2.png", "meteorBrown_tiny1.png",
    "meteorBrown_tiny2.png",  "meteorGrey_big1.png",    "meteorGrey_big2.png",
    "meteorGrey_big3.png",    "meteorGrey_big4.png",    "meteorGrey_med1.png",
    "meteorGrey_med2.png",    "meteorGrey_small1.png",  "meteorGrey_small2.png",
    "meteorGrey_tiny1.png",   "meteorGrey_tiny2.png",
};

const int meteor_sizes[] = {
    4, 4, 4, 4, 3, 3, 2, 2, 1, 1, 4, 4, 4, 4, 3, 3, 2, 2, 1, 1,
};

struct Meteor : Enemy {
  Meteor(Vector2 pos) : Enemy(pos, nullptr) {
    is_static = true;

    v.y = 3;

    const int rnd = randi(0, (sizeof(meteor_file_names) / sizeof(char*)) - 1);
    setTexture(meteor_file_names[rnd]);
    health = meteor_sizes[rnd] * 5;
  }

  ~Meteor() {}
};

// 5 pieces X 4 color.
const char* enemy_file_names[] = {
    "enemyBlack1.png", "enemyBlack2.png", "enemyBlack3.png", "enemyBlack4.png",
    "enemyBlack5.png", "enemyBlue1.png",  "enemyBlue2.png",  "enemyBlue3.png",
    "enemyBlue4.png",  "enemyBlue5.png",  "enemyGreen1.png", "enemyGreen2.png",
    "enemyGreen3.png", "enemyGreen4.png", "enemyGreen5.png", "enemyRed1.png",
    "enemyRed2.png",   "enemyRed3.png",   "enemyRed4.png",   "enemyRed5.png",
};

struct BaseEnemy : Enemy {
  BaseEnemy(Vector2 pos, int enemy_index)
      : Enemy(pos, make_unique<ClassicArcadeMove>()) {
    health = ENEMY_DEFAULT_HEALTH;
    fire_chance = 0.001;

    setTexture(enemy_file_names[enemy_index]);
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
    const int non_static_enemy_count =
        count_if(enemies.begin(), enemies.end(),
                 [](const auto& enemy) { return !enemy->is_static; });

    if (non_static_enemy_count == 0) {
      makeZigZagGrid(6, 4);
    }

    if (randf() < 0.001) {
      enemies.emplace_back(
          make_unique<Meteor>(Vector2(randi(0, GetScreenWidth()), 0.0)));
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
      if (enemy->is_static) enemy.get()->draw();
    }
    for (auto& enemy : enemies) {
      if (!enemy->is_static) enemy.get()->draw();
    }

    for (auto& bullet : bullets) {
      bullet->draw();
    }
  }

  void makeZigZagGrid(int x, int y) {
    const int piece_idx = randi(0, 4);

    int spacing = GetScreenWidth() / (x + 1);
    for (int j = 0; j < y; j++) {
      for (int i = 0; i < x; i++) {
        enemies.emplace_back(make_unique<BaseEnemy>(
            Vector2{(float)((i + 1) * spacing), (float)((j - y + 1) * spacing)},
            (j % 4) * 5 + piece_idx));
      }
    }
  }
};
