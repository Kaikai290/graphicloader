#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "examplelayer.h"
#include "application.h"
#include "window.h"

int main(void) {
  ApplicationSpec spec;
  spec.mouseLock = true;
  Application app(spec);
  AppLayer *example = new AppLayer(app.getMainCamera());
  app.pushLayer(example);
  app.run();
  delete example;
}
