#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_TextureNormal : register(t1);
SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	float4 normalMap = g_TextureNormal.Sample(g_SamplerState, In.TexCoord);
	normalMap = float4((normalMap.r - 0.5) * 2, (normalMap.g - 0.5) * 2, (normalMap.b - 0.5) * 2, normalMap.a);

	float4 normal;
	normal.x = -normalMap.r;
	normal.y = normalMap.b;
	normal.z = normalMap.g;
	normal.w = 0.0f;
	normal = normalize(normal);

	float light = -dot(normal.xyz, Light.Direction.xyz);

	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
	eyev = normalize(eyev);

	float3 refv = reflect(Light.Direction.xyz, normal.xyz);
	refv = normalize(refv);

	float specular = -dot(eyev, refv);
	specular = saturate(specular);
	specular = pow(specular, 20);

	outDiffuse =
		g_Texture.Sample(g_SamplerState, In.TexCoord);

	outDiffuse.rgb *=
		In.Diffuse.rgb * light;
	outDiffuse.a *=
		In.Diffuse.a;

	outDiffuse.rgb += specular;

}