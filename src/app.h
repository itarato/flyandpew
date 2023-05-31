#pragma once

#include <raylib.h>

#include "config.h"

struct App {
  App() {}

  void init(Config conf) {
    int win_flags = FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT;
    SetConfigFlags(win_flags);

    InitWindow(conf.win_w, conf.win_h, "Fly & Pew");
    SetTargetFPS(conf.fps);
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

  void handle_state() {}

  void draw() {}
};
