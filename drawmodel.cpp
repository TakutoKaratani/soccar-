#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "modelmanager.h"
#include "texturemanager.h"
#include "drawmodel.h"

void DrawModel::Load(const char* filename)
{
	m_pModel = ModelManager::GetInstance()->Load(filename);
}

void DrawModel::Lighting(bool f)
{
	if (m_VertexShader) m_VertexShader->Release();
	if (m_PixelShader)m_PixelShader->Release();

	if (f)
	{
		Renderer::GetInstance()->CreateVertexShader(&m_VertexShader,
			&m_VertexLayout,
			"vertexLightingVS.cso");
		Renderer::GetInstance()->CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
	}
	else
	{
		Renderer::GetInstance()->CreateVertexShader(&m_VertexShader,
			&m_VertexLayout,
			"unlitTextureVS.cso");
		Renderer::GetInstance()->CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");
	}
}

void DrawModel::LoadSubTexture(const char* filename)
{
	m_SubTexture = TextureManager::GetInstance()->Load(filename);
}

void DrawModel::SetShader(const char* vsname, const char* psname)
{
	if (m_VertexShader) m_VertexShader->Release();
	if (m_PixelShader)m_PixelShader->Release();

	Renderer::GetInstance()->CreateVertexShader(&m_VertexShader, &m_VertexLayout, vsname);
	Renderer::GetInstance()->CreatePixelShader(&m_PixelShader, psname);
}

void DrawModel::Init()
{
	Renderer::GetInstance()->CreateVertexShader(&m_VertexShader,
		&m_VertexLayout,
		"vertexLightingVS.cso");
	Renderer::GetInstance()->CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

	m_SetModelMatrix = new SetModelMatrix();
}

void DrawModel::Uninit()
{

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void DrawModel::Update()
{

}

void DrawModel::Draw()
{
	Renderer::GetInstance()->GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	Renderer::GetInstance()->GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetInstance()->GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	if (m_SubTexture)
	{
		Renderer::GetInstance()->GetDeviceContext()->PSSetShaderResources(1, 1, &m_SubTexture);
	}

	ID3D11ShaderResourceView* DepthShadowTexture = Renderer::GetInstance()->GetShadowDepthTexture();
	Renderer::GetInstance()->GetDeviceContext()->PSSetShaderResources(2, 1, &DepthShadowTexture);

	D3DXMATRIX mtxWorld = m_SetModelMatrix->SetMatrix(gameObject->GetTransform());

	Renderer::GetInstance()->SetWorldMatrix(&mtxWorld);

	m_pModel->Draw();
}


D3DXMATRIX DrawModel::SetModelMatrix::SetMatrix(Transform* tf)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	D3DXMatrixScaling(&mtxScl, tf->m_Scale.x, tf->m_Scale.y, tf->m_Scale.z);

	D3DXMatrixRotationQuaternion(&mtxRot, &tf->m_Quaternion);

	D3DXMatrixTranslation(&mtxTranslate, tf->m_Position.x, tf->m_Position.y, tf->m_Position.z);

	mtxWorld = mtxScl * mtxRot * mtxTranslate;

	return mtxWorld;
}

D3DXMATRIX DrawModel::SetModelMatrixBillboard::SetMatrix(Transform* tf)
{
	D3DXMATRIX viewMatrix;
	D3DXVECTOR3 up = Transform::up;
	if (!m_lock){
		D3DXMatrixLookAtLH(&viewMatrix, &tf->m_Position, &m_at->GetTransform()->m_Position, &up);
	}
	else {
		D3DXMatrixLookAtLH(&viewMatrix, &tf->m_Position, &m_atLock, &up);
	}

	D3DXMATRIX invView;
	D3DXMatrixInverse(&invView, NULL, &viewMatrix);
	invView._41 = 0.0f;
	invView._42 = 0.0f;
	invView._43 = 0.0f;

	invView._21 = 0.0f;
	invView._22 = 1.0f;
	invView._23 = 0.0f;


	D3DXMATRIX mtxScl, mtxTranslate, mtxWorld;

	D3DXMatrixScaling(&mtxScl, tf->m_Scale.x, tf->m_Scale.y, tf->m_Scale.z);

	D3DXMatrixTranslation(&mtxTranslate, tf->m_Position.x, tf->m_Position.y, tf->m_Position.z);

	mtxWorld = mtxScl * invView * mtxTranslate;

	return mtxWorld;
}

void DrawModel::SetModelMatrixBillboard::BillLock()
{
	m_lock = true;
	m_atLock = m_at->GetTransform()->m_Position;
}
