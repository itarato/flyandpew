#pragma once

#include <vector>

#include "entity.h"
#include "util.h"

using namespace std;

#define PARTICLE_FIREWORK_SLOWDOWN 0.96

struct Firework : UIElement {
  vector<Entity> particles{};
  Countdown countdown{42};
  const int count{16};
  const float max_v{4.0};
  Color color;

  Firework(Vector2 pos, Color color) : color(color) {
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

      particle.v.x *= PARTICLE_FIREWORK_SLOWDOWN;
      particle.v.y *= PARTICLE_FIREWORK_SLOWDOWN;
    }

    if (countdown.tick()) {
      deactivate();
    }
  }

  void draw() const {
    for (const auto& particle : particles) {
      DrawRectangleV(particle.pos, particle.dim, color);
    }
  }
};
