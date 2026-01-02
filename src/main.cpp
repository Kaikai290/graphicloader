#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "applayer.h"
#include "application.h"
#include "window.h"

int main(void) {
  ApplicationSpec spec;
  Application app(spec);
  AppLayer *layer1 = new AppLayer();
  app.pushLayer(layer1);
  app.run();
  delete layer1;
}
