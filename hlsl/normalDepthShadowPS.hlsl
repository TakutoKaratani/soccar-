#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_TextureNormal : register(t1);
Texture2D g_TextureShadowDepth : register(t2);
SamplerState g_SamplerState : register(s0);
SamplerState g_SamplerState2 : register(s1);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	float4 normalMap = g_TextureNormal.Sample(g_SamplerState, In.TexCoord);
	normalMap = float4((normalMap.r - 0.5) * 2, (normalMap.g - 0.5) * 2, (normalMap.b - 0.5) * 2, normalMap.a);

	matrix rotatematrix = RotateMatrixAtoB(float3(0.0, 1.0, 0.0), In.Normal.xyz);

	float4 normal;
	normal.x = normalMap.r;
	normal.y = normalMap.b;
	normal.z = normalMap.g;
	normal.w = 0.0f;

	float4 rotateNormal;
	rotateNormal = mul(normal, rotatematrix);
	rotateNormal = normalize(rotateNormal);

	float light = 0.4 - 0.6 * dot(rotateNormal.xyz, Light.Direction.xyz);
	light = saturate(light);

	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
	eyev = normalize(eyev);

	float3 refv = reflect(Light.Direction.xyz, rotateNormal.xyz);
	refv = normalize(refv);

	float specular = -dot(eyev, refv);
	specular = saturate(specular);
	specular = pow(specular, 20);

	outDiffuse =
		g_Texture.Sample(g_SamplerState, In.TexCoord);


	outDiffuse.rgb *= light;
	outDiffuse.a *=
		In.Diffuse.a;

	In.ShadowPosition.xyz /= In.ShadowPosition.w;
	In.ShadowPosition.x = In.ShadowPosition.x * 0.5 + 0.5;
	In.ShadowPosition.y = -In.ShadowPosition.y * 0.5 + 0.5;

	if (In.ShadowPosition.y > 1)
	{
		if (light > 0.5)
			outDiffuse.rgb += specular;
	}
	else if (In.ShadowPosition.y < 0.45)
	{
		if (light > 0.5)
			outDiffuse.rgb += specular;
	}
	else
	{
		float4 depth = g_TextureShadowDepth.Sample(g_SamplerState2,
			In.ShadowPosition.xy);

		if (depth.r < In.ShadowPosition.z - 0.01)
		{
			outDiffuse.rgb *= 0.5;
		}
		else
		{
			if (light > 0.5)
				outDiffuse.rgb += specular;
		}
	}



}