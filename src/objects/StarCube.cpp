#include <StarGraphics/objects/StarCube.h>
#include <StarGraphics/StarVertex.h>
#include <StarGraphics/StarVertexLayout.h>

#include <StarUtils/StarExceptions.h>
#include <StarGraphics/StarRenderDeviceDX10.h>

namespace Star
{
  /***************************************************************************/
  Cube::Cube(float size)
    : m_size(size)
  {    
    float hsize = m_size/2.f;

    VertexCN vertices[] = {
      //front
      {
        float3( -hsize, -hsize, -hsize ),
        float3( 0, 0, -1 )
      },     
      
      {
        float3( -hsize, hsize, -hsize ),
        float3( 0, 0, -1 )
      },

      {
        float3( hsize, -hsize, -hsize ),
        float3( 0, 0, -1 )
      },

      {
        float3( hsize, -hsize, -hsize ),
        float3( 0, 0, -1 )
      },
      {
        float3( -hsize, hsize, -hsize ),
        float3( 0, 0, -1 )
      },

      {
        float3( hsize, hsize, -hsize ),
        float3( 0, 0, -1 )
      },


      //back
      {float3( -hsize, -hsize, hsize ),      
      float3( 0, 0, 1 )},
      {float3( hsize, -hsize, hsize ),
      float3( 0, 0, 1 )},
      {float3( hsize, hsize, hsize ),
      float3( 0, 0, 1 )},
      {float3( hsize, hsize, hsize ),
      float3( 0, 0, 1 )},
      {float3( -hsize, hsize, hsize ),
      float3( 0, 0, 1 )},
      {float3( -hsize, -hsize, hsize ),
      float3( 0, 0, 1 )},

      //left
      {float3( -hsize, -hsize, -hsize ),
      float3( -1, 0, 0 )},
      {float3( -hsize, -hsize, hsize ),
      float3( -1, 0, 0 )},
      {float3( -hsize, hsize, hsize ),
      float3( -1, 0, 0 )},
      {float3( -hsize, hsize, hsize ),
      float3( -1, 0, 0 )},
      {float3( -hsize, hsize, -hsize ),
      float3( -1, 0, 0 )},
      {float3( -hsize, -hsize, -hsize ),
      float3( -1, 0, 0 )},

      //right
      {float3( hsize, -hsize, -hsize ),
      float3( 1, 0, 0 )},
      {float3( hsize, hsize, -hsize ),
      float3( 1, 0, 0 )},
      {float3( hsize, hsize, hsize ),
      float3( 1, 0, 0 )},
      {float3( hsize, hsize, hsize ),
      float3( 1, 0, 0 )},
      {float3( hsize, -hsize, hsize ),
      float3( 1, 0, 0 )},
      {float3( hsize, -hsize, -hsize ),
      float3( 1, 0, 0 )},

      {float3( -hsize, hsize, -hsize ),
      float3( 0, 1, 0 )},
      {float3( -hsize, hsize, hsize ),
      float3( 0, 1, 0 )},
      {float3( hsize, hsize, hsize ),
      float3( 0, 1, 0 )},
      {float3( hsize, hsize, -hsize ),
      float3( 0, 1, 0 )},

      {float3( -hsize, -hsize, -hsize ),
      float3( 0, -1, 0 )},
      {float3( hsize, -hsize, -hsize ),
      float3( 0, -1, 0 )},
      {float3( hsize, -hsize, hsize ),
       float3( 0, -1, 0 )},
      {float3( -hsize, -hsize, hsize ),
       float3( 0, -1, 0 )}
    };

    D3D10_BUFFER_DESC bd;
    bd.Usage = D3D10_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(vertices);
    bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;

    D3D10_SUBRESOURCE_DATA initData;
    initData.pSysMem = vertices;
    HRESULT hr = g_StarRenderDeviceDX10.getD3dDevice()->CreateBuffer(&bd, &initData, &m_vb); 
    if(FAILED(hr))
      throw Exception("Cube::Cube: can't create vertex buffer");
  }

  /***************************************************************************/
  Cube::~Cube()
  {
    m_vb->Release();
  }

  /***************************************************************************/
  void 
  Cube::begin()
  {
    UINT stride = sizeof(VertexCN);
    UINT offset = 0;
    ID3D10Device* d3d = g_StarRenderDeviceDX10.getD3dDevice();
    d3d->IASetVertexBuffers(0, 1, &m_vb, &stride, &offset);
    d3d->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  }

  /***************************************************************************/
  ID3D10InputLayout* 
  Cube::createInputLayout(const D3D10_PASS_DESC& passDesc)
  {     
    ID3D10Device* d3d = g_StarRenderDeviceDX10.getD3dDevice();

    HRESULT hr;
    ID3D10InputLayout* inputLayout;
    hr = d3d->CreateInputLayout(VertexCNLayout, 
                                sizeof(VertexCNLayout)/sizeof(VertexCNLayout[0]),
                                passDesc.pIAInputSignature, 
                                passDesc.IAInputSignatureSize,
                                &inputLayout);
    if( FAILED(hr) )
      throw Exception("Cube::createInputLayout: can't create input layout");

    return inputLayout;
  }

  /***************************************************************************/
  void 
  Cube::render()
  {
    //g_StarRenderDeviceDX10.getD3dDevice()->Draw(4*6, 0);
    g_StarRenderDeviceDX10.getD3dDevice()->Draw(6*4, 0);
  }

  /***************************************************************************/
  boxf
  Cube::getBoundingBox()
  {
    float half = m_size/2.f;
    return boxf(float3(-half, -half, -half), float3(half, half, half));
  }
}