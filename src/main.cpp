#include <GLFW/glfw3.h>
#include "application.h"
#include "window.h"



int main(void) {
  WindowSpec spec;
  Application app(spec);
  app.run();
}
  /*Window window;
  window.init(spec);

  while (!glfwWindowShouldClose(window.window
                                )) {
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window.window);

    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
*/
