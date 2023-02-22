#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_TextureShadowDepth : register(t2);
SamplerState g_SamplerState : register(s0);
SamplerState g_SamplerState2 : register(s1);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	float4 normal = normalize(In.Normal);
	float light = 0.4 - 0.6 * dot(normal.xyz, Light.Direction.xyz);

	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
	eyev = normalize(eyev);

	float3 refv = reflect(Light.Direction.xyz, normal.xyz);
	refv = normalize(refv);

	float specular = -dot(eyev, refv);
	specular = saturate(specular);
	specular = pow(specular, 20);

	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
	outDiffuse *= In.Diffuse;
	In.ShadowPosition.xyz /= In.ShadowPosition.w;
	In.ShadowPosition.x = In.ShadowPosition.x * 0.5 + 0.5;
	In.ShadowPosition.y = -In.ShadowPosition.y * 0.5 + 0.5;
	
	if (In.ShadowPosition.y > 1)
	{
		outDiffuse.rgb += specular;
	}
	else if (In.ShadowPosition.y < 0.3)
	{
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
			outDiffuse.rgb += specular;
		}
	}


}