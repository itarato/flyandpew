#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "app.h"
#include "config.h"
#include "resource.h"

using namespace std;

int main() {
  srand(time(nullptr));

  config.win_w = 1280;
  config.win_h = 1280;
  config.fps = 120;

  App app = App();
  app.init();
  app.run();

  return EXIT_SUCCESS;
}
