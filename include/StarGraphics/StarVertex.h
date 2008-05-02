#ifndef STARVERTEX_H
#define STARVERTEX_H

#include <StarMath/StarVec3.h>
#include <StarMath/StarVec2.h>

namespace Star
{
  /**
   * Define a vertex as a 3d coordinate and a normal
   */
  struct VertexCN 
  {
    float3 coord;
    float3 normal;
  };

  /**
   * Define a vertex as a 3d coordinate, a normal, a texcoord
   */
  struct VertexCNT
  {
    float3 coord;
    float3 normal;
    float2 uv;
  };
}

#endif
