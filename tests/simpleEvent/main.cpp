#include "simpleEvent.h"

#include <StarUtils/StarExceptions.h>

int main(int argc, char** argv)
{
  SimpleEvent* app = NULL;
  try
  {
    app = new SimpleEvent(800, 600, "EmptyApp");
    app->run();
  } catch(Star::Exception& e)
  {
    e.show();
  }

  delete app;

  return 0;
}
