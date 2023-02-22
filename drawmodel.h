#pragma once
#include "component.h"
class DrawModel : public Component
{
public:
	DrawModel(class GameObject* go) :Component(go) {}

	void Load(const char* filename);
	void Lighting(bool f);
	void LoadSubTexture(const char* filename);

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetParameter(D3DXVECTOR4 para) { m_Parameter = para; }
	D3DXVECTOR4 GetParameter() { return m_Parameter; }

	void SetShader(const char* vsname, const char* psname);

	void Billboard(GameObject* at) {
		delete m_SetModelMatrix;
		m_SetModelMatrix = new SetModelMatrixBillboard(at);
	}

	void UnBill() {
		delete m_SetModelMatrix;
		m_SetModelMatrix = new SetModelMatrix();
	}

	void Lock() { m_SetModelMatrix->BillLock(); }
	void Unlock() { m_SetModelMatrix->BillUnlock(); }

private:
	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;
	ID3D11ShaderResourceView* m_SubTexture = NULL;

	class Model* m_pModel = nullptr;

	D3DXVECTOR4 m_Parameter = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);

	class SetModelMatrix
	{
	public:
		virtual D3DXMATRIX SetMatrix(class Transform* tf);

		virtual void BillUnlock(){}
		virtual void BillLock(){}
	};

	class SetModelMatrixBillboard : public SetModelMatrix
	{
	public:
		SetModelMatrixBillboard(GameObject* at):m_at(at){}

		D3DXMATRIX SetMatrix(class Transform* tf) override;

		void BillUnlock() override { m_lock = false; }
		void BillLock() override;

	private:
		GameObject* m_at = nullptr;
		D3DXVECTOR3 m_atLock;
		bool m_lock = false;
	};

	SetModelMatrix* m_SetModelMatrix = nullptr;
};

