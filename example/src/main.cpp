#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "application.h"
#include "baselayer.h"
#include "grasslayer.h"
#include "imguiexample.h"
#include "window.h"

int main(void) {
  LZ::ApplicationSpec spec;
  spec.mouseLock = true;

  LZ::Application app(spec);

#ifdef BASEEXAMPLE
  app.pushLayer<AppLayer>();
#endif
#ifdef GRASSEXAMPLE
  app.pushLayer<GrassLayer>();
#endif

  app.run();
}
