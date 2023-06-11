#pragma once

#include <vector>

#include "entity.h"
#include "util.h"

using namespace std;

#define PARTICLE_SIZE 8
#define PARTICLE_FIREWORK_SLOWDOWN 0.95
#define PARTICLE_LIFETIME 60

struct Firework : UIElement {
  vector<Entity> particles{};
  Countdown countdown{PARTICLE_LIFETIME};
  const int count{48};
  const float max_v{8.0};
  Color color;

  Firework(Vector2 pos, Color color) : color(color) {
    for (int i = 0; i < count; i++) {
      particles.emplace_back(
          Vector2{PARTICLE_SIZE, PARTICLE_SIZE}, pos,
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
      Color alpha_color =
          ColorAlpha(color, static_cast<float>(countdown.counter + 30) /
                                static_cast<float>(PARTICLE_LIFETIME + 30));
      DrawRectangleV(particle.pos, particle.dim, alpha_color);
    }
  }
};
