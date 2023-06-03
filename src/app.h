#pragma once

#include <raylib.h>

#include "config.h"
#include "enemy.h"
#include "player.h"

struct App {
  Player player{};
  EnemyManager enemy_manager{};

  App() {}

  void init() {
    int win_flags = FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT;
    SetConfigFlags(win_flags);

    InitWindow(config.win_w, config.win_h, "Fly & Pew");
    SetTargetFPS(config.fps);

    reset();
  }

  void reset() {
    player.reset();
    enemy_manager.reset();
  }

  void run() {
    while (!WindowShouldClose()) {
      handle_state();

      HideCursor();

      BeginDrawing();

      ClearBackground(RAYWHITE);

      draw();

      EndDrawing();
    }
  }

  void handle_state() {
    player.update();
    enemy_manager.update();

    handle_enemy_player_collisions();

    if (!player.active) {
      reset();
    }
  }

  void draw() {
    player.draw();
    enemy_manager.draw();

    DrawFPS(4, 4);
  }

  void handle_enemy_player_collisions() {
    vector<Fire*> exploding_bullets{};

    for (auto& p_enemy : enemy_manager.enemies) {
      auto enemy = p_enemy.get();

      for (auto& bullet : player.bullets) {
        if (enemy->collide(bullet.get())) {
          enemy->hit(bullet.get());
          bullet->deactivate();

          exploding_bullets.push_back(bullet.get());
        }
      }

      if (enemy->collide(&player)) {
        enemy->deactivate();
        player.deactivate();
      }
    }

    for (auto bullet : exploding_bullets) {
      optional<Circle> blast = bullet->explosionFrame();
      if (!blast.has_value()) {
        continue;
      }

      for (auto& enemy : enemy_manager.enemies) {
        if (!enemy->active) {
          continue;
        }

        if (CheckCollisionCircleRec(blast.value().center, blast.value().rad,
                                    enemy->frame())) {
          enemy->deactivate();
        }
      }
    }
  }
};
