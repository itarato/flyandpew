#include <cstdio>
#include <iostream>

#include "app.h"
#include "config.h"

using namespace std;

int main() {
  config.win_w = 1280;
  config.win_h = 1280;
  config.fps = 60;

  App app = App();
  app.init(config);
  app.run();

  return EXIT_SUCCESS;
}
