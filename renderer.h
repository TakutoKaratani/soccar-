#pragma once





struct VERTEX_3D
{
    D3DXVECTOR3 Position;
    D3DXVECTOR3 Normal;
    D3DXVECTOR4 Diffuse;
    D3DXVECTOR2 TexCoord;
};

struct MATERIAL
{
	D3DXCOLOR	Ambient;
	D3DXCOLOR	Diffuse;
	D3DXCOLOR	Specular;
	D3DXCOLOR	Emission;
	float		Shininess;
	float		Dummy[3];
};



struct LIGHT
{
	BOOL		Enable;
	BOOL		Dummy[3];
	D3DXVECTOR4	Direction;
	D3DXCOLOR	Diffuse;
	D3DXCOLOR	Ambient;
	D3DXMATRIX ViewMatrix;
	D3DXMATRIX ProjectionMatrix;
};



class Renderer
{
private:

	D3D_FEATURE_LEVEL       m_FeatureLevel = D3D_FEATURE_LEVEL_11_0;
	
	ID3D11Device*           m_Device = nullptr;
	ID3D11DeviceContext*    m_DeviceContext = nullptr;
	IDXGISwapChain*         m_SwapChain = nullptr;
	ID3D11RenderTargetView* m_RenderTargetView = nullptr;
	ID3D11DepthStencilView* m_DepthStencilView = nullptr;
	
	ID3D11Buffer*			m_WorldBuffer = nullptr;
	ID3D11Buffer*			m_ViewBuffer = nullptr;
	ID3D11Buffer*			m_ProjectionBuffer = nullptr;
	ID3D11Buffer*			m_MaterialBuffer = nullptr;
	ID3D11Buffer*			m_LightBuffer = nullptr;
	ID3D11Buffer*			m_ParameterBuffer = nullptr;
	ID3D11Buffer*			m_CameraBuffer = nullptr;
	
	ID3D11DepthStencilState* m_DepthStateEnable = nullptr;
	ID3D11DepthStencilState* m_DepthStateDisable = nullptr;

	ID3D11DepthStencilView* m_ShadowDepthStencilView = nullptr;
	ID3D11ShaderResourceView* m_ShadowDepthShaderResourceView = nullptr;

public:
	void Init();
	void Uninit();
	void Begin();
	void End();

	static Renderer* GetInstance() {
		return s_pInstance;
	}

	static void Create()
	{
		if (!s_pInstance)
		{
			s_pInstance = new Renderer();
		}
	}
	static void Destroy()
	{
		delete s_pInstance;
		s_pInstance = nullptr;
	}

	void SetDepthEnable(bool Enable);
	void SetWorldViewProjection2D();
	void SetWorldMatrix(D3DXMATRIX* WorldMatrix);
	void SetViewMatrix(D3DXMATRIX* ViewMatrix);
	void SetProjectionMatrix(D3DXMATRIX* ProjectionMatrix);
	void SetMaterial(MATERIAL Material);
	void SetLight(LIGHT Light);
	void SetParameter(D3DXVECTOR4 Parameter);
	void SetCameraPosition(D3DXVECTOR3 CameraPosition);

	ID3D11Device* GetDevice( void ){ return m_Device; }
	ID3D11DeviceContext* GetDeviceContext( void ){ return m_DeviceContext; }
	
	ID3D11ShaderResourceView* GetShadowDepthTexture(void) { return m_ShadowDepthShaderResourceView; }
	void BeginDepth(void)
	{
		m_DeviceContext->OMSetRenderTargets(0, NULL, m_ShadowDepthStencilView);
		m_DeviceContext->ClearDepthStencilView(m_ShadowDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	}

	void CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName);
	void CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName);

private:
	static Renderer* s_pInstance;
	Renderer() {}
};
