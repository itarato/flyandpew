#pragma once

#include <raylib.h>

#include <map>
#include <string>

using namespace std;

#define RESRC_PLAYER "player"
#define RESRC_LASER_BLUE_SMALL "laser_blue_small"
#define RESRC_LASER_RED_BIG "laser_red_big"
#define RESRC_ENEMY "enemy"
#define RESRC_UPGRADE_HEALTH "upgrade_health"
#define RESRC_UPGRADE_BULLET "upgrade_bullet"

struct ResourceManager {
  map<string, Texture2D> textures{};

  ~ResourceManager() {
    TraceLog(LOG_INFO, "Resource manager dtor");
    for (auto& [k, v] : textures) {
      UnloadTexture(v);
    }
  }
} resource_manager;
