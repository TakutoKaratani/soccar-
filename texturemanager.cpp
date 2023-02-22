#include "main.h"
#include "renderer.h"
#include "texturemanager.h"

TextureManager* TextureManager::s_pInstance = nullptr;

void TextureManager::Init()
{

}

void TextureManager::Uninit()
{
	std::unordered_map<const char*, ID3D11ShaderResourceView*>::iterator iterator;

	for (iterator = m_pTextures.begin(); iterator != m_pTextures.end(); iterator++)
	{
		std::pair<const char*, ID3D11ShaderResourceView*> texture = *iterator;
		texture.second->Release();
	}
	m_pTextures.clear();
}

ID3D11ShaderResourceView* TextureManager::Load(const char* filename)
{
	if (!m_pTextures[filename])
	{
		D3DX11CreateShaderResourceViewFromFile(Renderer::GetInstance()->GetDevice(),
			filename,
			NULL,
			NULL,
			&m_pTextures[filename],
			NULL);
		assert(m_pTextures[filename]);
	}
	return m_pTextures[filename];
}