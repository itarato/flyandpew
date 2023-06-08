#pragma once

#include <raylib.h>

#include <map>
#include <string>

using namespace std;

#define RESRC_PLAYER "player_0.png"
#define RESRC_LASER_BLUE_SMALL "laser_blue_small.png"
#define RESRC_LASER_RED_BIG "laser_red_big.png"
#define RESRC_ENEMY "enemy_0.png"
#define RESRC_UPGRADE_HEALTH "upgrade_health.png"
#define RESRC_UPGRADE_BULLET "upgrade_bullet.png"

struct ResourceManager {
  map<string, Texture2D> textures{};

  ~ResourceManager() {
    TraceLog(LOG_INFO, "Resource manager dtor");
    for (auto& [k, v] : textures) {
      UnloadTexture(v);
    }
  }

  void preload_textures(std::string folder) {
    FilePathList files = LoadDirectoryFiles(folder.c_str());

    for (int i = 0; i < (int)files.count; i++) {
      textures.insert(
          {GetFileName(files.paths[i]), LoadTexture(files.paths[i])});
    }
  }
} resource_manager;
