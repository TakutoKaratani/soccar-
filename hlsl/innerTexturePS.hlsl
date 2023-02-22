
#include "common.hlsl"


Texture2D		g_Texture : register(t0);
Texture2D		g_SubTexture : register(t1);
SamplerState	g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{

	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);

	float4 subDiffuse = g_SubTexture.Sample(g_SamplerState, In.TexCoord + Parameter.xy);

	if (subDiffuse.a > 0)
		outDiffuse *= In.Diffuse * subDiffuse;

}