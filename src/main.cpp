#include <cstdio>
#include <iostream>

#include "app.h"
#include "config.h"

using namespace std;

int main() {
  config.win_w = 1280;
  config.win_h = 1280;
  config.fps = 120;

  App app = App();
  app.init();
  app.run();

  return EXIT_SUCCESS;
}
