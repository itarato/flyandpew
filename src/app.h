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

    player.reset();
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
  }

  void draw() {
    player.draw();
    enemy_manager.draw();

    DrawFPS(4, 4);
  }
};
