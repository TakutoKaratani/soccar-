#pragma once
#include "component.h"

class DrawSprite : public Component
{
public:
	DrawSprite(class GameObject* go) :Component(go) {}

	enum DRAW_MODE {
		MODE_2D,
		MODE_2D_LEFTTOP,
		MODE_2D_LEFTBOTTOM,
		MODE_2D_EDIT,
		MODE_2D_EDIT_LEFTTOP,
		MODE_2D_EDIT_LEFTBOTTOM,
		MODE_2D_EDIT_RIGHTBOTTOM,
		MODE_3D,
		MODE_3D_EDIT,
		MODE_3D_BILLBOARD,
		MODE_3D_BILLBOARD_EDIT,
		NONE,
	};

	void Load(const char* filename);
	void SubTextureLoad(const char* filename);
	void SetMode(DRAW_MODE mode);
	void SetColor(const D3DXCOLOR color) { m_Color = color; }
	D3DXCOLOR GetColor() const { return m_Color; }
	void SetUV(const float s, const float t, const float u, const float v) {
		m_S = s; m_T = t; m_U = u; m_V = v;
	}
	void SetParameter(D3DXVECTOR4 para) { m_Parameter = para; }
	void SetShader(const char* vsname, const char* psname);

	void SetTexture(ID3D11ShaderResourceView* texture);

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void VertexInit();
	void VertexInit3D();
	void VertexInitTransform();
	void VertexInitTransform(bool left, bool top);

	ID3D11Buffer* GetBuffer() const { return m_VertexBuffer; }
	ID3D11ShaderResourceView* GetTexture() const { return m_Texture; }
	ID3D11ShaderResourceView* GetSubTexture() const { return m_SubTexture; }


	ID3D11VertexShader* GetVertexShader() const { return m_VertexShader; }
	ID3D11PixelShader* GetPixelShader() const { return m_PixelShader; }
	ID3D11InputLayout* GetLayout() const { return m_VertexLayout; }

	D3DXVECTOR4 GetParameter() { return m_Parameter; }

	VERTEX_3D m_Vertex[4];

private:
	void CreateBuffer();
	void CreateBufferEdit();

	class SpriteDraw* m_SpriteDraw = nullptr;

	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	ID3D11ShaderResourceView* m_SubTexture = NULL;

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;

	DRAW_MODE m_DrawMode = DRAW_MODE::NONE;

	D3DXCOLOR m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	float m_S = 0.0f, m_T = 0.0f, m_U = 1.0f, m_V = 1.0f;

	D3DXVECTOR4 m_Parameter = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);
};

class SpriteDraw
{
public:
	SpriteDraw(){}
	virtual void Draw(DrawSprite* ds);

protected:
	void MapVertex(DrawSprite* ds);
	void SetMatrix(DrawSprite* ds);
	void SetMatrixBillboard(DrawSprite* ds);
	void SetTexture(DrawSprite* ds);
};

class SpriteEditDraw : public SpriteDraw
{
public:
	void Draw(DrawSprite* ds) override;
};

class SpriteEditDrawLefttop : public SpriteDraw
{
public:
	SpriteEditDrawLefttop(bool l,bool t):SpriteDraw(),left(l),top(t){}

	void Draw(DrawSprite* ds) override;

	bool left = true;
	bool top = true;
};

class SpriteDraw3D : public SpriteDraw
{
public:
	void Draw(DrawSprite* ds) override;
};

class SpriteEditDraw3D : public SpriteDraw
{
public:
	void Draw(DrawSprite* ds) override;
};

class SpriteDraw3DBillboard : public SpriteDraw
{
public:
	void Draw(DrawSprite* ds) override;
};

class SpriteEditDraw3DBillboard : public SpriteDraw
{
public:
	void Draw(DrawSprite* ds) override;
};
