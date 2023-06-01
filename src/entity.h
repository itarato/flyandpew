#pragma once

#include <raylib.h>

#include "util.h"

struct Entity : UIElement {
  Vector2 dim{0.0, 0.0};
  Vector2 pos{0.0, 0.0};
  Vector2 v{0.0, 0.0};

  Entity() : UIElement() {}
  Entity(Vector2 dim, Vector2 pos, Vector2 v)
      : UIElement(), dim(dim), pos(pos), v(v){};
};
