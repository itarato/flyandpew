#pragma once

#include <raylib.h>

#include <string>

#include "resource.h"

using namespace std;

struct UIElement {
  bool active{true};

  UIElement(){};
  ~UIElement(){};

  virtual void draw() const = 0;
  virtual void update() = 0;

  void deactivate() { active = false; }
};

struct Entity : UIElement {
  Vector2 dim{0.0, 0.0};
  Vector2 pos{0.0, 0.0};
  Vector2 v{0.0, 0.0};
  Texture2D* texture{nullptr};

  Entity() {}
  Entity(Vector2 dim) : dim(dim) {}
  Entity(Vector2 dim, Vector2 pos, Vector2 v) : dim(dim), pos(pos), v(v) {}

  ~Entity() {}

  virtual Rectangle frame() const {
    return Rectangle{pos.x - (dim.x / 2.0f), pos.y - (dim.y / 2.0f), dim.x,
                     dim.y};
  };

  bool collide(Entity* other) const {
    return CheckCollisionRecs(frame(), other->frame());
  }

  virtual void draw() const {
    if (texture) {
      DrawTexture(*texture, pos.x - (dim.x / 2), pos.y - (dim.y / 2), WHITE);
    } else {
      DrawRectangleRec(frame(), MAGENTA);
    }
  }

  virtual void update() {
    pos.x += v.x;
    pos.y += v.y;
  };

  void setTexture(string texture_name) {
    texture = &resource_manager.textures[texture_name];
    dim.x = texture->width;
    dim.y = texture->height;
  }
};
