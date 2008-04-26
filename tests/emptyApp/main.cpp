#include "emptyApp.h"

#include <StarUtils/StarExceptions.h>

Star::Application*
createApplication(int argc, char** argv, HINSTANCE hInst)
{ 
  return new EmptyApp(800, 600, "EmptyApp");   
}
