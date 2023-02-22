#pragma once
#include <string>
#include <unordered_map>

class TextureManager
{
public:
	void Init();
	void Uninit();

	ID3D11ShaderResourceView* Load(const char*);

	static TextureManager* GetInstance() {
		return s_pInstance;
	}

	static void Create()
	{
		if (!s_pInstance)
		{
			s_pInstance = new TextureManager();
		}
	}
	static void Destroy()
	{
		delete s_pInstance;
		s_pInstance = nullptr;
	}

private:
	static TextureManager* s_pInstance;

	std::unordered_map<const char*, ID3D11ShaderResourceView*> m_pTextures;
};
