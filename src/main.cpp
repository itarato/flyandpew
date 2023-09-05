#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "app.h"
#include "config.h"
#include "resource.h"

using namespace std;

int main() {
  srand(time(nullptr));

  config.win_w = 1900;
  config.win_h = 1000;
  config.fps = 60;
  config.input_mode_mouse_on = true;

  App app = App();
  app.init();
  app.run();

  return EXIT_SUCCESS;
}
