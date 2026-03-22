#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "application.h"
#include "baselayer.h"
#include "grasslayer.h"
#include "instancelayer.h"
#include "springlayer.h"
#include "heightmaplayer.h"
#include "flockinglayer.h"
#include "imguiexample.h"
#include "window.h"

int main(void) {
  LZ::ApplicationSpec spec;
  spec.mouseLock = true;

  LZ::Application app(spec);

#ifdef BASEEXAMPLE
  app.pushLayer<BaseLayer>();
#endif
#ifdef GRASSEXAMPLE
  app.pushLayer<GrassLayer>();
#endif
#ifdef INSTANCEEXAMPLE
  app.pushLayer<InstanceLayer>();
#endif
#ifdef SPRINGEXAMPLE 
  app.pushLayer<SpringLayer>();
#endif
#ifdef HEIGHTMAPEXAMPLE 
  app.pushLayer<HeightMapLayer>();
#endif
#ifdef FLOCKINGEXAMPLE 
  app.pushLayer<FlockingLayer>();
#endif

  app.run();
}
