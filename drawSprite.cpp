#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "drawSprite.h"
#include "texturemanager.h"
#include "transform.h"
#include "gameObject.h"

void DrawSprite::Load(const char* filename)
{
	m_Texture = TextureManager::GetInstance()->Load(filename);
}

void DrawSprite::SubTextureLoad(const char* filename)
{
	m_SubTexture = TextureManager::GetInstance()->Load(filename);
}

void DrawSprite::SetTexture(ID3D11ShaderResourceView* texture)
{
	m_Texture = texture;
}

void DrawSprite::CreateBuffer()
{
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = m_Vertex;

	Renderer::GetInstance()->GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
}

void DrawSprite::CreateBufferEdit()
{
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = m_Vertex;

	Renderer::GetInstance()->GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
}

void DrawSprite::SetMode(DRAW_MODE mode)
{
	if (/*m_DrawMode == mode || */mode == DRAW_MODE::NONE) return;
	m_DrawMode = mode;

	if (m_VertexBuffer != nullptr)
	{
		m_VertexBuffer->Release();
	}

	if (m_SpriteDraw)
	{
		delete m_SpriteDraw;
	}

	switch (m_DrawMode)
	{
	case DRAW_MODE::MODE_2D:

		this->VertexInitTransform();
		this->CreateBuffer();

		m_SpriteDraw = new SpriteDraw();
		break;

	case DRAW_MODE::MODE_2D_LEFTTOP:

		this->VertexInitTransform(true, true);
		this->CreateBuffer();

		m_SpriteDraw = new SpriteDraw();
		break;

	case DRAW_MODE::MODE_2D_LEFTBOTTOM:

		this->VertexInitTransform(true, false);
		this->CreateBuffer();

		m_SpriteDraw = new SpriteDraw();
		break;

	case DRAW_MODE::MODE_2D_EDIT:

		this->VertexInitTransform();
		this->CreateBufferEdit();

		m_SpriteDraw = new SpriteEditDraw();
		break;

	case DRAW_MODE::MODE_2D_EDIT_LEFTTOP:

		this->VertexInitTransform(true, true);
		this->CreateBufferEdit();

		m_SpriteDraw = new SpriteEditDrawLefttop(true,true);
		break;

	case DRAW_MODE::MODE_2D_EDIT_LEFTBOTTOM:

		this->VertexInitTransform(true, false);
		this->CreateBufferEdit();

		m_SpriteDraw = new SpriteEditDrawLefttop(true,false);
		break;

	case DRAW_MODE::MODE_2D_EDIT_RIGHTBOTTOM:

		this->VertexInitTransform(false, false);
		this->CreateBufferEdit();

		m_SpriteDraw = new SpriteEditDrawLefttop(false, false);
		break;

	case DRAW_MODE::MODE_3D:

		this->VertexInit3D();
		this->CreateBuffer();

		m_SpriteDraw = new SpriteDraw3D();
		break;

	case DRAW_MODE::MODE_3D_EDIT:
		
		this->VertexInit3D();
		this->CreateBufferEdit();

		m_SpriteDraw = new SpriteEditDraw3D();
		break;

	case DRAW_MODE::MODE_3D_BILLBOARD:

		this->VertexInit3D();
		this->CreateBuffer();

		m_SpriteDraw = new SpriteDraw3DBillboard();
		break;

	case DRAW_MODE::MODE_3D_BILLBOARD_EDIT:

		this->VertexInit3D();
		this->CreateBufferEdit();

		m_SpriteDraw = new SpriteEditDraw3DBillboard();
		break;
	}
}

void DrawSprite::VertexInit()
{
	Transform* transform = gameObject->GetTransform();
	D3DXVECTOR2 scl = D3DXVECTOR2(transform->m_Scale.x * 0.5f, transform->m_Scale.y * 0.5f);
	D3DXVECTOR4 color = D3DXVECTOR4(m_Color.r, m_Color.g, m_Color.b, m_Color.a);

	m_Vertex[0].Position = D3DXVECTOR3(-scl.x, scl.y, 0.0f);
	m_Vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Vertex[0].Diffuse = color;
	m_Vertex[0].TexCoord = D3DXVECTOR2(m_S, m_T);

	m_Vertex[1].Position = D3DXVECTOR3(scl.x, scl.y, 0.0f);
	m_Vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Vertex[1].Diffuse = color;
	m_Vertex[1].TexCoord = D3DXVECTOR2(m_U, m_T);

	m_Vertex[2].Position = D3DXVECTOR3(-scl.x, -scl.y, 0.0f);
	m_Vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Vertex[2].Diffuse = color;
	m_Vertex[2].TexCoord = D3DXVECTOR2(m_S, m_V);

	m_Vertex[3].Position = D3DXVECTOR3(scl.x, -scl.y, 0.0f);
	m_Vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Vertex[3].Diffuse = color;
	m_Vertex[3].TexCoord = D3DXVECTOR2(m_U, m_V);
}

void DrawSprite::VertexInit3D()
{
	Transform* transform = gameObject->GetTransform();
	D3DXVECTOR4 color = D3DXVECTOR4(m_Color.r, m_Color.g, m_Color.b, m_Color.a);

	m_Vertex[0].Position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	m_Vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Vertex[0].Diffuse = color;
	m_Vertex[0].TexCoord = D3DXVECTOR2(m_S, m_T);

	m_Vertex[1].Position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	m_Vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Vertex[1].Diffuse = color;
	m_Vertex[1].TexCoord = D3DXVECTOR2(m_U, m_T);

	m_Vertex[2].Position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	m_Vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Vertex[2].Diffuse = color;
	m_Vertex[2].TexCoord = D3DXVECTOR2(m_S, m_V);

	m_Vertex[3].Position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	m_Vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Vertex[3].Diffuse = color;
	m_Vertex[3].TexCoord = D3DXVECTOR2(m_U, m_V);

}

void DrawSprite::VertexInitTransform()
{
	Transform* transform = gameObject->GetTransform();
	D3DXVECTOR2 scl = D3DXVECTOR2(transform->m_Scale.x * 0.5f, transform->m_Scale.y * 0.5f);
	D3DXVECTOR4 color = D3DXVECTOR4(m_Color.r, m_Color.g, m_Color.b, m_Color.a);

	m_Vertex[0].Position = D3DXVECTOR3(transform->m_Position.x - scl.x, transform->m_Position.y - scl.y, 0.0f);
	m_Vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Vertex[0].Diffuse = color;
	m_Vertex[0].TexCoord = D3DXVECTOR2(m_S, m_T);

	m_Vertex[1].Position = D3DXVECTOR3(transform->m_Position.x + scl.x, transform->m_Position.y - scl.y, 0.0f);
	m_Vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Vertex[1].Diffuse = color;
	m_Vertex[1].TexCoord = D3DXVECTOR2(m_U, m_T);

	m_Vertex[2].Position = D3DXVECTOR3(transform->m_Position.x - scl.x, transform->m_Position.y + scl.y, 0.0f);
	m_Vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Vertex[2].Diffuse = color;
	m_Vertex[2].TexCoord = D3DXVECTOR2(m_S, m_V);

	m_Vertex[3].Position = D3DXVECTOR3(transform->m_Position.x + scl.x, transform->m_Position.y + scl.y, 0.0f);
	m_Vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Vertex[3].Diffuse = color;
	m_Vertex[3].TexCoord = D3DXVECTOR2(m_U, m_V);
}

void DrawSprite::VertexInitTransform(bool left, bool top)
{
	Transform* transform = gameObject->GetTransform();
	D3DXVECTOR2 scl = D3DXVECTOR2(transform->m_Scale.x, transform->m_Scale.y);
	D3DXVECTOR4 color = D3DXVECTOR4(m_Color.r, m_Color.g, m_Color.b, m_Color.a);

	if (left == true)
	{
		if (top == true)
		{
			m_Vertex[0].Position = D3DXVECTOR3(transform->m_Position.x, transform->m_Position.y, 0.0f);
			m_Vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			m_Vertex[0].Diffuse = color;
			m_Vertex[0].TexCoord = D3DXVECTOR2(m_S, m_T);

			m_Vertex[1].Position = D3DXVECTOR3(transform->m_Position.x + scl.x, transform->m_Position.y, 0.0f);
			m_Vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			m_Vertex[1].Diffuse = color;
			m_Vertex[1].TexCoord = D3DXVECTOR2(m_U, m_T);

			m_Vertex[2].Position = D3DXVECTOR3(transform->m_Position.x, transform->m_Position.y + scl.y, 0.0f);
			m_Vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			m_Vertex[2].Diffuse = color;
			m_Vertex[2].TexCoord = D3DXVECTOR2(m_S, m_V);

			m_Vertex[3].Position = D3DXVECTOR3(transform->m_Position.x + scl.x, transform->m_Position.y + scl.y, 0.0f);
			m_Vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			m_Vertex[3].Diffuse = color;
			m_Vertex[3].TexCoord = D3DXVECTOR2(m_U, m_V);
		}
		else
		{
			m_Vertex[0].Position = D3DXVECTOR3(transform->m_Position.x, transform->m_Position.y - scl.y, 0.0f);
			m_Vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			m_Vertex[0].Diffuse = color;
			m_Vertex[0].TexCoord = D3DXVECTOR2(m_S, m_T);

			m_Vertex[1].Position = D3DXVECTOR3(transform->m_Position.x + scl.x, transform->m_Position.y - scl.y, 0.0f);
			m_Vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			m_Vertex[1].Diffuse = color;
			m_Vertex[1].TexCoord = D3DXVECTOR2(m_U, m_T);

			m_Vertex[2].Position = D3DXVECTOR3(transform->m_Position.x, transform->m_Position.y, 0.0f);
			m_Vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			m_Vertex[2].Diffuse = color;
			m_Vertex[2].TexCoord = D3DXVECTOR2(m_S, m_V);

			m_Vertex[3].Position = D3DXVECTOR3(transform->m_Position.x + scl.x, transform->m_Position.y, 0.0f);
			m_Vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			m_Vertex[3].Diffuse = color;
			m_Vertex[3].TexCoord = D3DXVECTOR2(m_U, m_V);
		}
	}
	else
	{
		if (top == true)
		{
			m_Vertex[0].Position = D3DXVECTOR3(transform->m_Position.x - scl.x, transform->m_Position.y, 0.0f);
			m_Vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			m_Vertex[0].Diffuse = color;
			m_Vertex[0].TexCoord = D3DXVECTOR2(m_S, m_T);

			m_Vertex[1].Position = D3DXVECTOR3(transform->m_Position.x, transform->m_Position.y, 0.0f);
			m_Vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			m_Vertex[1].Diffuse = color;
			m_Vertex[1].TexCoord = D3DXVECTOR2(m_U, m_T);

			m_Vertex[2].Position = D3DXVECTOR3(transform->m_Position.x - scl.x, transform->m_Position.y + scl.y, 0.0f);
			m_Vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			m_Vertex[2].Diffuse = color;
			m_Vertex[2].TexCoord = D3DXVECTOR2(m_S, m_V);

			m_Vertex[3].Position = D3DXVECTOR3(transform->m_Position.x, transform->m_Position.y + scl.y, 0.0f);
			m_Vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			m_Vertex[3].Diffuse = color;
			m_Vertex[3].TexCoord = D3DXVECTOR2(m_U, m_V);
		}
		else
		{
			m_Vertex[0].Position = D3DXVECTOR3(transform->m_Position.x - scl.x, transform->m_Position.y - scl.y, 0.0f);
			m_Vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			m_Vertex[0].Diffuse = color;
			m_Vertex[0].TexCoord = D3DXVECTOR2(m_S, m_T);

			m_Vertex[1].Position = D3DXVECTOR3(transform->m_Position.x, transform->m_Position.y - scl.y, 0.0f);
			m_Vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			m_Vertex[1].Diffuse = color;
			m_Vertex[1].TexCoord = D3DXVECTOR2(m_U, m_T);

			m_Vertex[2].Position = D3DXVECTOR3(transform->m_Position.x - scl.x, transform->m_Position.y, 0.0f);
			m_Vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			m_Vertex[2].Diffuse = color;
			m_Vertex[2].TexCoord = D3DXVECTOR2(m_S, m_V);

			m_Vertex[3].Position = D3DXVECTOR3(transform->m_Position.x, transform->m_Position.y, 0.0f);
			m_Vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			m_Vertex[3].Diffuse = color;
			m_Vertex[3].TexCoord = D3DXVECTOR2(m_U, m_V);
		}
	}
}

void DrawSprite::SetShader(const char* vsname, const char* psname)
{
	if (m_VertexShader) m_VertexShader->Release();
	if (m_PixelShader)m_PixelShader->Release();

	Renderer::GetInstance()->CreateVertexShader(&m_VertexShader, &m_VertexLayout, vsname);
	Renderer::GetInstance()->CreatePixelShader(&m_PixelShader, psname);
}

void DrawSprite::Init()
{
	m_SpriteDraw = new SpriteDraw();

	SetMode(DRAW_MODE::MODE_2D);

	Renderer::GetInstance()->CreateVertexShader(&m_VertexShader,
		&m_VertexLayout,
		"unlitTextureVS.cso");

	Renderer::GetInstance()->CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");
}

void DrawSprite::Uninit()
{
	m_VertexBuffer->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	delete m_SpriteDraw;
}

void DrawSprite::Update()
{

}

void DrawSprite::Draw()
{
	m_SpriteDraw->Draw(this);
}



// SpriteDraw------------------------------------------------------------------------------
void SpriteDraw::Draw(DrawSprite* ds)
{
	Renderer::GetInstance()->GetDeviceContext()->IASetInputLayout(ds->GetLayout());

	Renderer::GetInstance()->GetDeviceContext()->VSSetShader(ds->GetVertexShader(), NULL, 0);
	Renderer::GetInstance()->GetDeviceContext()->PSSetShader(ds->GetPixelShader(), NULL, 0);

	Renderer::GetInstance()->SetWorldViewProjection2D();

	SetTexture(ds);

	Renderer::GetInstance()->GetDeviceContext()->Draw(4, 0);
}

void SpriteDraw::MapVertex(DrawSprite* ds)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetInstance()->GetDeviceContext()->Map(ds->GetBuffer(), 0,
		D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = ((VERTEX_3D*)msr.pData);

	vertex[0].Position = ds->m_Vertex[0].Position;
	vertex[0].Normal = ds->m_Vertex[0].Normal;
	vertex[0].Diffuse = ds->m_Vertex[0].Diffuse;
	vertex[0].TexCoord = ds->m_Vertex[0].TexCoord;

	vertex[1].Position = ds->m_Vertex[1].Position;
	vertex[1].Normal = ds->m_Vertex[1].Normal;
	vertex[1].Diffuse = ds->m_Vertex[1].Diffuse;
	vertex[1].TexCoord = ds->m_Vertex[1].TexCoord;

	vertex[2].Position = ds->m_Vertex[2].Position;
	vertex[2].Normal = ds->m_Vertex[2].Normal;
	vertex[2].Diffuse = ds->m_Vertex[2].Diffuse;
	vertex[2].TexCoord = ds->m_Vertex[2].TexCoord;

	vertex[3].Position = ds->m_Vertex[3].Position;
	vertex[3].Normal = ds->m_Vertex[3].Normal;
	vertex[3].Diffuse = ds->m_Vertex[3].Diffuse;
	vertex[3].TexCoord = ds->m_Vertex[3].TexCoord;

	Renderer::GetInstance()->GetDeviceContext()->Unmap(ds->GetBuffer(), 0);
}

void SpriteDraw::SetMatrix(DrawSprite* ds)
{
	D3DXMATRIX mtxScl, mtxTranslate, mtxRot, mtxWorld;

	Transform* tf = ds->gameObject->GetTransform();

	D3DXMatrixScaling(&mtxScl, tf->m_Scale.x, tf->m_Scale.y, tf->m_Scale.z);

	D3DXMatrixRotationQuaternion(&mtxRot, &tf->m_Quaternion);

	D3DXMatrixTranslation(&mtxTranslate, tf->m_Position.x, tf->m_Position.y, tf->m_Position.z);

	mtxWorld = mtxScl * mtxRot * mtxTranslate;

	Renderer::GetInstance()->SetWorldMatrix(&mtxWorld);
}

void SpriteDraw::SetMatrixBillboard(DrawSprite* ds)
{
	Scene* scene = Manager::GetInstance()->GetScene();
	Camera* camera = scene->GetMainCamera();
	D3DXMATRIX view = camera->GetViewMatrix();

	D3DXMATRIX invView;
	D3DXMatrixInverse(&invView, NULL, &view);
	invView._41 = 0.0f;
	invView._42 = 0.0f;
	invView._43 = 0.0f;

	//invView._21 = 0.0f;
	//invView._22 = 1.0f;
	//invView._23 = 0.0f;


	D3DXMATRIX mtxScl, mtxTranslate, mtxWorld;

	Transform* tf = ds->gameObject->GetTransform();

	D3DXMatrixScaling(&mtxScl, tf->m_Scale.x, tf->m_Scale.y, tf->m_Scale.z);

	D3DXMatrixTranslation(&mtxTranslate, tf->m_Position.x, tf->m_Position.y, tf->m_Position.z);

	mtxWorld = mtxScl * invView * mtxTranslate;

	Renderer::GetInstance()->SetWorldMatrix(&mtxWorld);
}

void SpriteDraw::SetTexture(DrawSprite* ds)
{
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	ID3D11Buffer* b = ds->GetBuffer();
	ID3D11DeviceContext* deviceCon = Renderer::GetInstance()->GetDeviceContext();

	deviceCon->IASetVertexBuffers(0, 1, &b, &stride, &offset);

	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Renderer::GetInstance()->SetMaterial(material);

	ID3D11ShaderResourceView* t = ds->GetTexture();
	deviceCon->PSSetShaderResources(0, 1, &t);

	ID3D11ShaderResourceView* sub = ds->GetSubTexture();
	if (sub)
	{
		deviceCon->PSSetShaderResources(1, 1, &sub);
	}

	ID3D11ShaderResourceView* DepthShadowTexture = Renderer::GetInstance()->GetShadowDepthTexture();
	deviceCon->PSSetShaderResources(2, 1, &DepthShadowTexture);

	Renderer::GetInstance()->SetParameter(ds->GetParameter());

	deviceCon->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
}


// SpriteEditDraw----------------------------------------------------------------------
void SpriteEditDraw::Draw(DrawSprite* ds)
{
	ds->VertexInitTransform();

	Renderer::GetInstance()->GetDeviceContext()->IASetInputLayout(ds->GetLayout());

	SpriteDraw::MapVertex(ds);

	Renderer::GetInstance()->GetDeviceContext()->VSSetShader(ds->GetVertexShader(), NULL, 0);
	Renderer::GetInstance()->GetDeviceContext()->PSSetShader(ds->GetPixelShader(), NULL, 0);

	Renderer::GetInstance()->SetWorldViewProjection2D();

	SpriteDraw::SetTexture(ds);

	Renderer::GetInstance()->GetDeviceContext()->Draw(4, 0);
}




// SpriteEditDrawLefttop----------------------------------------------------------------------
void SpriteEditDrawLefttop::Draw(DrawSprite* ds)
{
	ds->VertexInitTransform(left, top);

	Renderer::GetInstance()->GetDeviceContext()->IASetInputLayout(ds->GetLayout());

	SpriteDraw::MapVertex(ds);

	Renderer::GetInstance()->GetDeviceContext()->VSSetShader(ds->GetVertexShader(), NULL, 0);
	Renderer::GetInstance()->GetDeviceContext()->PSSetShader(ds->GetPixelShader(), NULL, 0);

	Renderer::GetInstance()->SetWorldViewProjection2D();

	SpriteDraw::SetTexture(ds);

	Renderer::GetInstance()->GetDeviceContext()->Draw(4, 0);
}




// SpriteDraw3D-------------------------------------------------------------------------------
void SpriteDraw3D::Draw(DrawSprite* ds)
{
	Renderer::GetInstance()->GetDeviceContext()->IASetInputLayout(ds->GetLayout());

	Renderer::GetInstance()->GetDeviceContext()->VSSetShader(ds->GetVertexShader(), NULL, 0);
	Renderer::GetInstance()->GetDeviceContext()->PSSetShader(ds->GetPixelShader(), NULL, 0);

	SpriteDraw::SetMatrix(ds);

	SpriteDraw::SetTexture(ds);

	Renderer::GetInstance()->GetDeviceContext()->Draw(4, 0);
}



// SpriteEditDraw3D--------------------------------------------------------------------------
void SpriteEditDraw3D::Draw(DrawSprite* ds)
{
	ds->VertexInit3D();

	SpriteDraw::MapVertex(ds);

	Renderer::GetInstance()->GetDeviceContext()->IASetInputLayout(ds->GetLayout());

	Renderer::GetInstance()->GetDeviceContext()->VSSetShader(ds->GetVertexShader(), NULL, 0);
	Renderer::GetInstance()->GetDeviceContext()->PSSetShader(ds->GetPixelShader(), NULL, 0);

	SpriteDraw::SetMatrix(ds);

	SpriteDraw::SetTexture(ds);

	Renderer::GetInstance()->GetDeviceContext()->Draw(4, 0);
}


// SpriteDraw3DBillboard---------------------------------------------------------------------
void SpriteDraw3DBillboard::Draw(DrawSprite* ds)
{

	Renderer::GetInstance()->GetDeviceContext()->IASetInputLayout(ds->GetLayout());


	Renderer::GetInstance()->GetDeviceContext()->VSSetShader(ds->GetVertexShader(), NULL, 0);
	Renderer::GetInstance()->GetDeviceContext()->PSSetShader(ds->GetPixelShader(), NULL, 0);

	SpriteDraw::SetMatrixBillboard(ds);

	SpriteDraw::SetTexture(ds);

	Renderer::GetInstance()->GetDeviceContext()->Draw(4, 0);
}



// SpriteEditDraw3DBillboard-------------------------------------------------------------------
void  SpriteEditDraw3DBillboard::Draw(DrawSprite* ds)
{
	ds->VertexInit3D();

	Renderer::GetInstance()->GetDeviceContext()->IASetInputLayout(ds->GetLayout());

	SpriteDraw::MapVertex(ds);

	Renderer::GetInstance()->GetDeviceContext()->VSSetShader(ds->GetVertexShader(), NULL, 0);
	Renderer::GetInstance()->GetDeviceContext()->PSSetShader(ds->GetPixelShader(), NULL, 0);

	SpriteDraw::SetMatrixBillboard(ds);

	SpriteDraw::SetTexture(ds);

	Renderer::GetInstance()->GetDeviceContext()->Draw(4, 0);
}

