


cbuffer WorldBuffer : register(b0)
{
	matrix World;
}
cbuffer ViewBuffer : register(b1)
{
	matrix View;
}
cbuffer ProjectionBuffer : register(b2)
{
	matrix Projection;
}



struct MATERIAL
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
	float4 Emission;
	float Shininess;
	float3 Dummy;
};

cbuffer MaterialBuffer : register(b3)
{
	MATERIAL Material;
}




struct LIGHT
{
	bool Enable;
	float3 dummy;
	float4 Direction;
	float4 Diffuse;
	float4 Ambient;

	matrix View;
	matrix Projection;
};

cbuffer LightBuffer : register(b4)
{
	LIGHT Light;
}

// 汎用パラメータ
cbuffer	ParameterBuffer : register(b5)
{
	float4	Parameter;
}


cbuffer CameraBuffer : register(b6)
{
	float4 CameraPosition;
}


struct VS_IN
{
	float4 Position		: POSITION0;
	float4 Normal		: NORMAL0;
	float4 Diffuse		: COLOR0;
	float2 TexCoord		: TEXCOORD0;
};


struct PS_IN
{
	float4 Position		: SV_POSITION;
	float4 WorldPosition: POSITION0;
	float4 Normal		: NORMAL0;
	float4 Diffuse		: COLOR0;
	float2 TexCoord		: TEXCOORD0;

	float4 ShadowPosition	: POSITION1;
};

float4 zero = { 0.0,0.0,0.0,0.0 };


float4 QuaternionAtoB(float3 a, float3 b)
{
	a = normalize(a);
	b = normalize(b);
	float4 q = float4(0.0, 0.0, 0.0, 0.0);

	float3 c = cross(b, a);
	float d = -length(c);
	c = normalize(c);

	float epsilon= 0.0002;
	float ip = dot(a, b);
	if (-epsilon < d || 1.0 < ip)
	{
		if (ip < (epsilon - 1.0))
		{
			float3 a2 = float3(-a.y, a.z, a.x);
			c = normalize(cross(a2, a));
			q.x = 0.0;
			q.y = c.x;
			q.z = c.y;
			q.w = c.z;
		}
		else
		{
			q = float4(1.0, 0.0, 0.0, 0.0);
		}
	}
	else
	{
		float3 e = c * sqrt(0.5 * (1.0 - ip));
		q.x = sqrt(0.5 * (1.0 + ip));
		q.y = e.x;
		q.z = e.y;
		q.w = e.z;
	}

	return q;
}

matrix QuaternionToMatrix(float4 q)
{
	matrix m;

	float4 q2 = q.yzwx;

	float k = q2.w * q2.w + q2.x * q2.x + q2.y * q2.y + q2.z * q2.z;

	m[0][0] = (q2.w * q2.w + q2.x * q2.x - q2.y * q2.y - q2.z * q2.z) / k;
	m[0][1] = (2.0 * q2.x * q2.y - 2.0 * q2.w * q2.z) / k;
	m[0][2] = (2.0 * q2.x * q2.z + 2.0 * q2.w * q2.y) / k;
	m[0][3] = 0.0;

	m[1][0] = (2.0 * q2.x * q2.y + 2.0 * q2.w * q2.z) / k;
	m[1][1] = (q2.w * q2.w - q2.x * q2.x + q2.y * q2.y - q2.z * q2.z) / k;
	m[1][2] = (2.0 * q2.y * q2.z - 2.0 * q2.w * q2.x) / k;
	m[1][3] = 0.0;

	m[2][0] = (2.0 * q2.x * q2.z - 2.0 * q2.w * q2.y) / k;
	m[2][1] = (2.0 * q2.y * q2.z + 2.0 * q2.w * q2.x) / k;
	m[2][2] = (q2.w * q2.w - q2.x * q2.x - q2.y * q2.y + q2.z * q2.z) / k;
	m[2][3] = 0.0;

	m[3][0] = 0.0;
	m[3][1] = 0.0;
	m[3][2] = 0.0;
	m[3][3] = 1.0;

	return m;
}

matrix RotateMatrixAtoB(float3 a, float3 b)
{
	return QuaternionToMatrix(QuaternionAtoB(a, b));
}