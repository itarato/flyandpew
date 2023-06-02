#pragma once

#include <raylib.h>

struct Entity {
  Vector2 dim{0.0, 0.0};
  Vector2 pos{0.0, 0.0};
  Vector2 v{0.0, 0.0};
  bool active{true};

  Entity() {}
  Entity(Vector2 dim) : dim(dim) {}
  Entity(Vector2 dim, Vector2 pos, Vector2 v) : dim(dim), pos(pos), v(v) {}

  virtual ~Entity() {}

  virtual void draw() = 0;
  virtual void update() = 0;
  virtual Rectangle frame() const = 0;

  void deactivate() { active = false; }

  bool collide(Entity* other) const {
    return CheckCollisionRecs(frame(), other->frame());
  }
};
