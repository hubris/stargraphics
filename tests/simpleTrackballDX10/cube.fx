matrix World;
matrix View;
matrix Projection;

struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR0;
    float3 Normal : NORMAL;
    float3 LightVec : LIGHTVEC;
};

VS_OUTPUT VS( float4 Pos : POSITION, float3 normal : NORMAL )
{
  VS_OUTPUT output = (VS_OUTPUT)0;
  matrix mv = mul(World, View);
  matrix mvp = mul(mv, Projection);
  //output.Pos = mul(Pos, World);
  //output.Pos = mul(output.Pos, View);
  output.Pos = mul(Pos, mvp);
  output.Color = float4( 1.0f, 1.0f, 0.0f, 1.0f );
  output.Normal = mul(normal, mv);
  output.LightVec = Pos.xyz-float3(0, 0, -3);

  return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
  float d = dot(input.Normal, -normalize(input.LightVec));
  //return input.Color;
  return float4(d,d,d,1);
}

// Technique Definition
technique10 Render
{
  pass P0
  {
    SetVertexShader( CompileShader( vs_4_0, VS() ) );
    SetGeometryShader( NULL );
    SetPixelShader( CompileShader( ps_4_0, PS() ) );
  }
}

