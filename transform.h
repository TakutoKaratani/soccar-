#pragma once
#include "main.h"
#include "component.h"

class Transform : public Component
{
public:
	Transform(class GameObject* go) :Component(go) { D3DXQuaternionIdentity(&m_Quaternion); }

	D3DXVECTOR3 m_Position{ 0.0f,0.0f,0.0f };
	D3DXVECTOR3 m_Scale{ 1.0f,1.0f,1.0f };
	D3DXQUATERNION m_Quaternion;

	void SetPosition(D3DXVECTOR3 pos) { m_Position = pos; }
	void SetQuaternion(D3DXQUATERNION q) { m_Quaternion = q; }
	void SetScale(D3DXVECTOR3 scl) { m_Scale = scl; }

	void MulQuaternion(D3DXQUATERNION q) { m_Quaternion *= q; }
	void MulQuaternion(D3DXVECTOR3 axis, float r) {
		D3DXQUATERNION quat;
		D3DXQuaternionRotationAxis(&quat, &axis, r);
		MulQuaternion(quat);
	}


	void SerQuaternionRot(D3DXVECTOR3 rot) {
		D3DXQuaternionRotationYawPitchRoll(&m_Quaternion, rot.y, rot.x, rot.z);
	}

	void Init() { D3DXQuaternionIdentity(&m_Quaternion); }

	static D3DXVECTOR3 up;
	static D3DXVECTOR3 right;
	static D3DXVECTOR3 forward;

private:
};

