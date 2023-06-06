#pragma once

#include <vector>

#include "entity.h"
#include "util.h"

using namespace std;

struct Firework : UIElement {
  vector<Entity> particles{};
  Countdown countdown{60};
  const int count{16};
  const float max_v{2.0};

  Firework(Vector2 pos) {
    for (int i = 0; i < count; i++) {
      particles.emplace_back(
          Vector2{4.0, 4.0}, pos,
          Vector2{randf(-max_v, max_v), randf(-max_v, max_v)});
    }
  }
  ~Firework() {}

  void update() {
    for (auto& particle : particles) {
      particle.pos.x += particle.v.x;
      particle.pos.y += particle.v.y;
    }

    if (countdown.tick()) {
      deactivate();
    }
  }

  void draw() {
    for (auto& particle : particles) {
      DrawRectangleV(particle.pos, particle.dim, WHITE);
    }
  }
};
