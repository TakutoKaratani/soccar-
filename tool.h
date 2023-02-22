#pragma once
#include "main.h"
#include <cmath>
#include <random>
#include "transform.h"

// 当たり判定用クラス
class Obb
{
private:
	Transform const* transform = nullptr;
	Transform const* offset = nullptr;

public:
	Obb(){
		offset = new Transform(nullptr);
	}

	void SetTransform(Transform const* transform)
	{
		this->transform = transform;
	}

	void SetOffset(Transform* o)
	{
		if (!o) return;
		if (offset) delete offset;
		offset = o;
	}

	D3DXVECTOR3 GetPosition() { return transform->m_Position + offset->m_Position; }

	D3DXVECTOR3 GetObbX()
	{
		D3DXMATRIX rot, scale, world;
		D3DXMatrixScaling(&scale, transform->m_Scale.x * offset->m_Scale.x, transform->m_Scale.y * offset->m_Scale.y, transform->m_Scale.z * offset->m_Scale.z);
		D3DXQUATERNION quat = transform->m_Quaternion * offset->m_Quaternion;
		D3DXMatrixRotationQuaternion(&rot, &quat);
		world = scale * rot;

		D3DXVECTOR3 vx;
		vx.x = world._11;
		vx.y = world._12;
		vx.z = world._13;

		return vx * 0.5f;
	}

	D3DXVECTOR3 GetObbZ()
	{
		D3DXMATRIX rot, scale, world;
		D3DXMatrixScaling(&scale, transform->m_Scale.x * offset->m_Scale.x, transform->m_Scale.y * offset->m_Scale.y, transform->m_Scale.z * offset->m_Scale.z);
		D3DXQUATERNION quat = transform->m_Quaternion * offset->m_Quaternion;
		D3DXMatrixRotationQuaternion(&rot, &quat);
		world = scale * rot;

		D3DXVECTOR3 vx;
		vx.x = world._31;
		vx.y = world._32;
		vx.z = world._33;

		return vx * 0.5f;
	}

	D3DXVECTOR3 GetObbY()
	{
		D3DXMATRIX rot, scale, world;
		D3DXMatrixScaling(&scale, transform->m_Scale.x * offset->m_Scale.x, transform->m_Scale.y * offset->m_Scale.y, transform->m_Scale.z * offset->m_Scale.z);
		D3DXQUATERNION quat = transform->m_Quaternion * offset->m_Quaternion;
		D3DXMatrixRotationQuaternion(&rot, &quat);
		world = scale * rot;

		D3DXVECTOR3 vx;
		vx.x = world._21;
		vx.y = world._22;
		vx.z = world._23;

		return vx * 0.5f;
	}

	float GetLenX()
	{
		D3DXVECTOR3 v = GetObbX();
		return D3DXVec3Length(&v);
	}

	float GetLenZ()
	{
		D3DXVECTOR3 v = GetObbZ();
		return D3DXVec3Length(&v);
	}

	float GetLenY()
	{
		D3DXVECTOR3 v = GetObbY();
		return D3DXVec3Length(&v);
	}
};

class Tool
{
public:

	static const D3DXVECTOR3 ORIGIN;
	static const float PI;

	static float RandF(float max = 1.0f, float min = -1.0f)
	{
		std::random_device rand;
		std::mt19937 mt(rand());
		std::uniform_real_distribution<> rd((double)min, (double)max);
		return (float)rd(mt);
	}

	static int RandI(int max = 100, int min = 0)
	{
		std::random_device rand;
		std::mt19937 mt(rand());
		std::uniform_int_distribution<> rd(min, max);
		return rd(mt);
	}

	static D3DXVECTOR3 Leap(D3DXVECTOR3 a, D3DXVECTOR3 b, float p)
	{
		D3DXVECTOR3 dis = a - b;
		D3DXVECTOR3 pDis = dis * p;
		return a - pDis;
	}

	static D3DXCOLOR LeapColor(D3DXCOLOR a, D3DXCOLOR b, float p)
	{
		D3DXCOLOR dis = a - b;
		D3DXCOLOR pDis = dis * p;
		return a - pDis;
	}

	static D3DXVECTOR2 RandVec2D(int divide,float offset)
	{
		if (divide <= 0) return D3DXVECTOR2(0.0f,0.0f);
		float divisionRad = PI * 2 / divide + offset;
		D3DXVECTOR2 vec = D3DXVECTOR2(0.0f, 1.0f);
		int rand = RandI(divide - 1, 0);
		float rad = divisionRad * rand;

		D3DXVECTOR2 returnvec;
		returnvec.x = vec.x * cosf(rad) + vec.y * sinf(rad);
		returnvec.y = vec.x * sinf(rad) + vec.y * cosf(rad);

		return returnvec;
	}

	static D3DXVECTOR3 RandVec3D(float r)
	{
		D3DXVECTOR3 at = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		float rotx = RandF(PI * 2, 0.0f);
		float roty = RandF(PI * 2, 0.0f);

		at.x = at.z * sinf(rotx) * cosf(roty);
		at.z = at.z * cosf(rotx) * cosf(roty);
		at.y = sinf(roty);

		return at * r;
	}

	static void Swap(float* a, float* b)
	{
		float* x = a;
		a = b;
		b = x;
	}

	static float Vec3Length(D3DXVECTOR3 v)
	{
		return sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	}

	static float Vec2Length(D3DXVECTOR2 v)
	{
		return sqrtf((v.x * v.x) + (v.y * v.y));
	}

	static float Vec3Dot(D3DXVECTOR3 a, D3DXVECTOR3 b)
	{
		return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	}

	static D3DXVECTOR3 Vec3Cross(D3DXVECTOR3 a, D3DXVECTOR3 b)
	{
		return D3DXVECTOR3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
	}

	static D3DXVECTOR3 Vec3Normalize(D3DXVECTOR3 v)
	{
		float len = Vec3Length(v);
		return v / len;
	}

	static float Vec3Angle(D3DXVECTOR3 a, D3DXVECTOR3 b, bool rad = true)
	{
		float lenA = Vec3Length(a);
		float lenB = Vec3Length(b);

		float cos = Vec3Dot(a, b) / (lenA * lenB);

		float sita = acosf(cos);

		if (!rad)
		{
			sita = sita * 180.0f / 3.14159f;
		}
		return sita;

	}

	static float PointPlaneLange(D3DXVECTOR3 po, D3DXVECTOR3 pl, D3DXVECTOR3 pln)
	{
		float dot = Vec3Dot(pln, po - pl);
		if (dot < 0) dot *= -1;

		return dot / Vec3Length(pln);
	}

	static D3DXVECTOR3 LineSegmentPlanePenetrationPoint(D3DXVECTOR3 ls1, D3DXVECTOR3 ls2, D3DXVECTOR3 po, D3DXVECTOR3 pf, D3DXVECTOR3 ps, D3DXVECTOR3 pu)
	{
		D3DXVECTOR3 pver = po + pu + ps;
		D3DXVECTOR3 v1 = ls1 - pver;
		D3DXVECTOR3 v2 = ls2 - pver;

		float d1 = PointPlaneLange(ls1, po, pf);
		float d2 = PointPlaneLange(ls2, po, pf);
		float a = d1 / (d1 + d2);

		return ((1 - a) * v1) + (a * v2) + pver;
	}

	
	// collision---------------------------------------------------------------------------------------------

	// point sphere
	static bool CollisionPointAndSphere(D3DXVECTOR3 p, D3DXVECTOR3 so, float r)
	{
		float dis = Vec3Length(p-so);

		if (r >= dis)return true;
		else return false;
	}

	// point polygon
	static bool CollisionPointAndPolygon(D3DXVECTOR3 p, D3DXVECTOR3 pol, D3DXVECTOR3 pols, D3DXVECTOR3 polu)
	{
		D3DXVECTOR3 polv1, polv2, polv3, polv4;

		polv1 = pol + pols + polu;
		polv2 = pol + pols - polu;
		polv3 = pol - pols - polu;
		polv4 = pol - pols + polu;

		bool hit = false;

		if (Vec3Dot(p - polv1, polv2 - polv1) >= 0) {
			if (Vec3Dot(p - polv2, polv3 - polv2) >= 0) {
				if (Vec3Dot(p - polv3, polv4 - polv3) >= 0) {
					if (Vec3Dot(p - polv4, polv1 - polv4) >= 0) {
						hit = true;
					}
				}
			}
		}

		return hit;
	}

	// sphere sphere
	static bool CollisionSphereAndSphere(D3DXVECTOR3 pos1, float r1, D3DXVECTOR3 pos2, float r2)
	{
		if (Vec3Length(pos1 - pos2) <= r1 + r2)
		{
			return true;
		}
		return false;
	}
	
	// senbun heimen
	static bool CollisionLineSegmentAndPlane(D3DXVECTOR3 ls1, D3DXVECTOR3 ls2, D3DXVECTOR3 po, D3DXVECTOR3 pn)
	{
		D3DXVECTOR3 v1 = ls1 - po;
		D3DXVECTOR3 v2 = ls2 - po;

		if (Vec3Dot(v1, pn) * Vec3Dot(v2, pn) <= 0) return true;
		else return false;
	}

	// senbun polygon
	static bool CollisionLineSegmentAndPolygon(D3DXVECTOR3 ls1, D3DXVECTOR3 ls2, D3DXVECTOR3 po, D3DXVECTOR3 pf, D3DXVECTOR3 ps, D3DXVECTOR3 pu)
	{
		if (!CollisionLineSegmentAndPlane(ls1, ls2, po, pf)) return false;

		D3DXVECTOR3 penetP = LineSegmentPlanePenetrationPoint(ls1, ls2, po, pf, ps, pu);

		return CollisionPointAndPolygon(penetP, po, ps, pu);
	}

	// senbun en
	static bool CollisionLineSegmentAndCircle(D3DXVECTOR3 ls1, D3DXVECTOR3 ls2, D3DXVECTOR3 po, D3DXVECTOR3 pf, D3DXVECTOR3 ps, D3DXVECTOR3 pu)
	{
		if (!CollisionLineSegmentAndPlane(ls1, ls2, po, pf)) return false;

		D3DXVECTOR3 penetP = LineSegmentPlanePenetrationPoint(ls1, ls2, po, pf, ps, pu);

		return CollisionPointAndSphere(penetP, po, Vec3Length(ps));
	}

	// OBB vs OBB 
	static bool CollisionOBBs(Transform const* transformA, Transform const* transformB)
	{
		D3DXVECTOR3 a;
		return CollisionOBBs(transformA, transformB, a);
	}

	// OBB vs OBB return めり込み
	static bool CollisionOBBs(Transform const* transformA, Transform const* transformB, D3DXVECTOR3& out)
	{
		return CollisionOBBs(transformA, nullptr, transformB, nullptr, out);
	}

	// OBB vs OBB return めり込み offset
	static bool CollisionOBBs(Transform const* transformA, Transform* offsetA, Transform const* transformB, Transform* offsetB, D3DXVECTOR3& out)
	{
		Obb objA, objB;
		objA.SetTransform(transformA);
		objA.SetOffset(offsetA);
		objB.SetTransform(transformB);
		objB.SetOffset(offsetB);
		D3DXVECTOR3 NAe1 = objA.GetObbX() / objA.GetLenX(), Ae1 = objA.GetObbX();
		D3DXVECTOR3 NAe2 = objA.GetObbY() / objA.GetLenY(), Ae2 = objA.GetObbY();
		D3DXVECTOR3 NAe3 = objA.GetObbZ() / objA.GetLenZ(), Ae3 = objA.GetObbZ();
		D3DXVECTOR3 NBe1 = objB.GetObbX() / objB.GetLenX(), Be1 = objB.GetObbX();
		D3DXVECTOR3 NBe2 = objB.GetObbY() / objB.GetLenY(), Be2 = objB.GetObbY();
		D3DXVECTOR3 NBe3 = objB.GetObbZ() / objB.GetLenZ(), Be3 = objB.GetObbZ();
		D3DXVECTOR3 interval = objA.GetPosition() - objB.GetPosition();

		float diff = 0;

		// Ae1
		{
			float rA = objA.GetLenX();
			float rB = LenSegOnSeparateAxis(NAe1, Be1, Be2, Be3);
			float l = (float)fabs(D3DXVec3Dot(&interval, &NAe1));
			if (l > rA + rB) return false;
			diff = (rA + rB) - l;
			out = NAe1 * diff;
			if (D3DXVec3Dot(&interval, &NAe1) < 0) out *= -1;
		}

		// Ae2
		{
			float rA = objA.GetLenY();
			float rB = LenSegOnSeparateAxis(NAe2, Be1, Be2, Be3);
			float l = (float)fabs(D3DXVec3Dot(&interval, &NAe2));
			if (l > rA + rB) return false;
			else if (diff > (rA + rB) - l)
			{
				diff = (rA + rB) - l;
				out = NAe2 * diff;
				if (D3DXVec3Dot(&interval, &NAe2) < 0) out *= -1;
			}
		}

		// Ae3
		{
			float rA = objA.GetLenZ();
			float rB = LenSegOnSeparateAxis(NAe3, Be1, Be2, Be3);
			float l = (float)fabs(D3DXVec3Dot(&interval, &NAe3));
			if (l > rA + rB) return false;
			else if (diff > (rA + rB) - l)
			{
				diff = (rA + rB) - l;
				out = NAe3 * diff;
				if (D3DXVec3Dot(&interval, &NAe3) < 0) out *= -1;
			}
		}

		// Be1
		{
			float rB = objB.GetLenX();
			float rA = LenSegOnSeparateAxis(NBe1, Ae1, Ae2, Ae3);
			float l = (float)fabs(D3DXVec3Dot(&interval, &NBe1));
			if (l > rA + rB) return false;
			else if (diff > (rA + rB) - l)
			{
				diff = (rA + rB) - l;
				out = NBe1 * diff;
				if (D3DXVec3Dot(&interval, &NBe1) < 0) out *= -1;
			}
		}

		// Be2
		{
			float rB = objB.GetLenY();
			float rA = LenSegOnSeparateAxis(NBe2, Ae1, Ae2, Ae3);
			float l = (float)fabs(D3DXVec3Dot(&interval, &NBe2));
			if (l > rA + rB) return false;
			else if (diff > (rA + rB) - l)
			{
				diff = (rA + rB) - l;
				out = NBe2 * diff;
				if (D3DXVec3Dot(&interval, &NBe2) < 0) out *= -1;
			}
		}

		// Be3
		{
			float rB = objB.GetLenZ();
			float rA = LenSegOnSeparateAxis(NBe2, Ae1, Ae2, Ae3);
			float l = (float)fabs(D3DXVec3Dot(&interval, &NBe2));
			if (l > rA + rB) return false;
			else if (diff > (rA + rB) - l)
			{
				diff = (rA + rB) - l;
				out = NBe3 * diff;
				if (D3DXVec3Dot(&interval, &NBe3) < 0) out *= -1;
			}
		}

		// C11
		{
			D3DXVECTOR3 cross;
			if (Vec3Dot(NAe1, NBe1) == 0)
			{
				D3DXVec3Cross(&cross, &NAe1, &NBe1);
				float rA = LenSegOnSeparateAxis(cross, Ae2, Ae3);
				float rB = LenSegOnSeparateAxis(cross, Be2, Be3);
				float l = (float)fabs(D3DXVec3Dot(&interval, &cross));
				if (l > rA + rB) return false;
				else if (diff > (rA + rB) - l)
				{
					diff = (rA + rB) - l;
					out = cross * diff;
					if (D3DXVec3Dot(&interval, &cross) < 0) out *= -1;
				}
			}
		}

		// C12
		{
			D3DXVECTOR3 cross;
			if (Vec3Dot(NAe1, NBe2) == 0)
			{
				D3DXVec3Cross(&cross, &NAe1, &NBe2);
				float rA = LenSegOnSeparateAxis(cross, Ae2, Ae3);
				float rB = LenSegOnSeparateAxis(cross, Be1, Be3);
				float l = (float)fabs(D3DXVec3Dot(&interval, &cross));
				if (l > rA + rB) return false;
				else if (diff > (rA + rB) - l)
				{
					diff = (rA + rB) - l;
					out = cross * diff;
					if (D3DXVec3Dot(&interval, &cross) < 0) out *= -1;
				}
			}
		}

		// C13
		{
			D3DXVECTOR3 cross;
			if (Vec3Dot(NAe1, NBe3) == 0)
			{
				D3DXVec3Cross(&cross, &NAe1, &NBe3);
				float rA = LenSegOnSeparateAxis(cross, Ae2, Ae3);
				float rB = LenSegOnSeparateAxis(cross, Be1, Be2);
				float l = (float)fabs(D3DXVec3Dot(&interval, &cross));
				if (l > rA + rB) return false;
				else if (diff > (rA + rB) - l)
				{
					diff = (rA + rB) - l;
					out = cross * diff;
					if (D3DXVec3Dot(&interval, &cross) < 0) out *= -1;
				}
			}
		}

		// C21
		{
			D3DXVECTOR3 cross;
			if (Vec3Dot(NAe2, NBe1) == 0)
			{
				D3DXVec3Cross(&cross, &NAe2, &NBe1);
				float rA = LenSegOnSeparateAxis(cross, Ae1, Ae3);
				float rB = LenSegOnSeparateAxis(cross, Be2, Be3);
				float l = (float)fabs(D3DXVec3Dot(&interval, &cross));
				if (l > rA + rB) return false;
				else if (diff > (rA + rB) - l)
				{
					diff = (rA + rB) - l;
					out = cross * diff;
					if (D3DXVec3Dot(&interval, &cross) < 0) out *= -1;
				}
			}
		}

		// C22
		{
			D3DXVECTOR3 cross;
			if (Vec3Dot(NAe2, NBe2) == 0)
			{
				D3DXVec3Cross(&cross, &NAe2, &NBe2);
				float rA = LenSegOnSeparateAxis(cross, Ae1, Ae3);
				float rB = LenSegOnSeparateAxis(cross, Be1, Be3);
				float l = (float)fabs(D3DXVec3Dot(&interval, &cross));
				if (l > rA + rB) return false;
				else if (diff > (rA + rB) - l)
				{
					diff = (rA + rB) - l;
					out = cross * diff;
					if (D3DXVec3Dot(&interval, &cross) < 0) out *= -1;
				}
			}
		}

		// C23
		{
			D3DXVECTOR3 cross;
			if (Vec3Dot(NAe2, NBe3) == 0)
			{
				D3DXVec3Cross(&cross, &NAe2, &NBe3);
				float rA = LenSegOnSeparateAxis(cross, Ae1, Ae3);
				float rB = LenSegOnSeparateAxis(cross, Be1, Be2);
				float l = (float)fabs(D3DXVec3Dot(&interval, &cross));
				if (l > rA + rB) return false;
				else if (diff > (rA + rB) - l)
				{
					diff = (rA + rB) - l;
					out = cross * diff;
					if (D3DXVec3Dot(&interval, &cross) < 0) out *= -1;
				}
			}
		}

		// C31
		{
			D3DXVECTOR3 cross;
			if (Vec3Dot(NAe3, NBe1) == 0)
			{
				D3DXVec3Cross(&cross, &NAe3, &NBe1);
				float rA = LenSegOnSeparateAxis(cross, Ae1, Ae2);
				float rB = LenSegOnSeparateAxis(cross, Be2, Be3);
				float l = (float)fabs(D3DXVec3Dot(&interval, &cross));
				if (l > rA + rB) return false;
				else if (diff > (rA + rB) - l)
				{
					diff = (rA + rB) - l;
					out = cross * diff;
					if (D3DXVec3Dot(&interval, &cross) < 0) out *= -1;
				}
			}
		}

		// C32
		{
			D3DXVECTOR3 cross;
			if (Vec3Dot(NAe3, NBe2) == 0)
			{
				D3DXVec3Cross(&cross, &NAe3, &NBe2);
				float rA = LenSegOnSeparateAxis(cross, Ae1, Ae2);
				float rB = LenSegOnSeparateAxis(cross, Be1, Be3);
				float l = (float)fabs(D3DXVec3Dot(&interval, &cross));
				if (l > rA + rB) return false;
				else if (diff > (rA + rB) - l)
				{
					diff = (rA + rB) - l;
					out = cross * diff;
					if (D3DXVec3Dot(&interval, &cross) < 0) out *= -1;
				}
			}
		}

		// C33
		{
			D3DXVECTOR3 cross;
			if (Vec3Dot(NAe3, NBe3) == 0)
			{
				D3DXVec3Cross(&cross, &NAe3, &NBe3);
				float rA = LenSegOnSeparateAxis(cross, Ae1, Ae2);
				float rB = LenSegOnSeparateAxis(cross, Be1, Be2);
				float l = (float)fabs(D3DXVec3Dot(&interval, &cross));
				if (l > rA + rB) return false;
				else if (diff > (rA + rB) - l)
				{
					diff = (rA + rB) - l;
					out = cross * diff;
					if (D3DXVec3Dot(&interval, &cross) < 0) out *= -1;
				}
			}
		}

		return true;
	}

	// ある線分にobbを押しつぶした時の長さ2d
	static float LenSegOnSeparateAxis(D3DXVECTOR3 a, D3DXVECTOR3 bx, D3DXVECTOR3 by)
	{
		return (float)(fabs(D3DXVec3Dot(&bx, &a)) + fabs(D3DXVec3Dot(&by, &a)));
	}
	//3d
	static float LenSegOnSeparateAxis(D3DXVECTOR3 a, D3DXVECTOR3 bx, D3DXVECTOR3 by, D3DXVECTOR3 bz)
	{
		return (float)(fabs(D3DXVec3Dot(&bx, &a)) + fabs(D3DXVec3Dot(&by, &a)) + fabs(D3DXVec3Dot(&bz, &a)));
	}

	// OBBと点の最短距離
	static float LenOBBtoPoint(Transform const* obbTransform, Transform*obbOffset, D3DXVECTOR3 point)
	{
		Obb obb;
		obb.SetTransform(obbTransform);
		obb.SetOffset(obbOffset);
		D3DXVECTOR3 vec(0, 0, 0);

		float obbLen[3];
		obbLen[0] = obb.GetLenX(), obbLen[1] = obb.GetLenY(), obbLen[2] = obb.GetLenZ();

		D3DXVECTOR3 obbVec[3];
		obbVec[0] = obb.GetObbX() / obbLen[0], obbVec[1] = obb.GetObbY() / obbLen[1], obbVec[2] = obb.GetObbZ() / obbLen[2];

		for (int i = 0; i < 3; i++)
		{
			if (obbLen[i] > 0)
			{
				float t = Vec3Dot(point - obb.GetPosition(), obbVec[i]) / obbLen[i];

				t = fabs(t);
				if (t > 1)
					vec += (1 - t) * obbLen[i] * obbVec[i];
			}
		}

		return Vec3Length(vec);
	}

	// OBB vs Sphere
	static bool CollisionOBBAndSphere(Transform const* obbTransform, D3DXVECTOR3 spherePos, float r, D3DXVECTOR3& out)
	{
		return CollisionOBBAndSphere(obbTransform, nullptr, spherePos, r, out);
	}

	static bool CollisionOBBAndSphere(Transform const* obbTransform, Transform* obbOffset, D3DXVECTOR3 spherePos, float r, D3DXVECTOR3& out)
	{
		float dis = LenOBBtoPoint(obbTransform, obbOffset, spherePos);

		if (dis <= r)
		{
			Obb obb;
			obb.SetTransform(obbTransform);
			obb.SetOffset(obbOffset);

			D3DXVECTOR3 direction = obb.GetPosition() - spherePos;

			float diff;

			D3DXVECTOR3 obbx, obbz, obby;
			{
				float obbLenx;
				float lenX;

				obbx = obb.GetObbX();
				obbLenx = D3DXVec3Length(&obbx);
				obbx /= obbLenx;
				lenX = (float)fabs(D3DXVec3Dot(&obbx, &direction)) - r;
				diff = obbLenx - lenX;
				out = obbx * diff;
				if (D3DXVec3Dot(&obbx, &direction) > 0) out *= -1;
			}
			{
				float obbLenz;
				float lenZ;

				obbz = obb.GetObbZ();
				obbLenz = D3DXVec3Length(&obbz);
				obbz /= obbLenz;
				lenZ = (float)fabs(D3DXVec3Dot(&obbz, &direction)) - r;
				if (diff > obbLenz - lenZ)
				{
					diff = obbLenz - lenZ;
					out = obbz * diff;
					if (D3DXVec3Dot(&obbz, &direction) > 0) out *= -1;
				}

			}
			{
				float obbLeny;
				float lenY;

				obby = obb.GetObbY();
				obbLeny = D3DXVec3Length(&obby);
				obby /= obbLeny;
				lenY = (float)fabs(D3DXVec3Dot(&obby, &direction)) - r;
				if (diff > obbLeny - lenY)
				{
					diff = obbLeny - lenY;
					out = obby * diff;
					if (D3DXVec3Dot(&obby, &direction) > 0) out *= -1;
				}
			}
			return true;
		}
		return false;
	}
};