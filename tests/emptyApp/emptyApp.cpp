#include "emptyApp.h"

#include <GL/gl.h>

void EmptyApp::render(double elapsedTime)
{
   glClearColor(0, 1, 0, 1);
   glClear(GL_COLOR_BUFFER_BIT);
}
