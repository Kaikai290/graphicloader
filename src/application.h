#include "window.h"
#include <vector>

class Application {
private:
  WindowSpec spec;
  Window window;
  //std::vector<Layer*> layers;
  bool running = false;
public:
  Application(WindowSpec spec);
  ~Application();

  void run();

};
