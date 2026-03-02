#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "examplelayer.h"
#include "application.h"
#include "window.h"

int main(void) {
  LZ::ApplicationSpec spec;
  spec.mouseLock = true;


  LZ::Application app(spec);
  app.pushLayer<AppLayer>();
  app.run();
}
