#include "main.h"
#include "simplerotation.h"
#include "gameObject.h"

void SimpleRotation::Update()
{
	D3DXQUATERNION quat;
	D3DXQuaternionRotationAxis(&quat, &m_axis, m_speed);
	gameObject->GetTransform()->m_Quaternion *= quat;
}