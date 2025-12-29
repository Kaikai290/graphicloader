#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "applayer.h"
#include "application.h"
#include "window.h"

int main(void) {
  ApplicationSpec spec;
  Application app(spec);
  AppLayer layer1;
  app.pushLayer(&layer1);
  app.run();
}
