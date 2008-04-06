#include "emptyApp.h"

#include <StarUtils/StarExceptions.h>

int main()
{
  EmptyApp* app = NULL;
  try
  {
    app = new EmptyApp(800, 600, "EmptyApp");
    app->run();
  } catch(Star::Exception& e)
  {
    e.show();
  }

  delete app;
}
