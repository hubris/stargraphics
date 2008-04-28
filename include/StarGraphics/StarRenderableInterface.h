#ifndef STARRENDERABLE_H
#define STARRENDERABLE_H

#include <StarMath/StarBox.h>

namespace Star
{
  class RenderableInterface
  {
  public:
    virtual void render() = 0;        
    virtual boxf getBoundingBox() = 0;
  };
}

#endif