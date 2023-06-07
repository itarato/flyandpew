#pragma once

#include <raylib.h>

#include <map>
#include <string>

using namespace std;

#define RESRC_PLAYER "player"
#define RESRC_LASER_BLUE_SMALL "laser_blue_small"

struct ResourceManager {
  map<string, Texture2D> textures{};

  ~ResourceManager() {
    TraceLog(LOG_INFO, "Resource manager dtor");
    for (auto& [k, v] : textures) {
      UnloadTexture(v);
    }
  }
} resource_manager;
