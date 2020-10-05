#include "Texture.hpp"

#include "Potato/Application.hpp"

namespace Potato
{
	Texture::Texture(const std::string& t_FileName, const std::string& t_TextureName) :
		m_TextureName(t_TextureName)
	{
		Diligent::TextureLoadInfo loadInfo;
		loadInfo.IsSRGB = true;
		CreateTextureFromFile(t_FileName.c_str(), loadInfo, Application::Get().GetWindow()->GetRenderContext()->GetRenderDevice(), &m_Texture);
		m_TextureSRV = m_Texture->GetDefaultView(Diligent::TEXTURE_VIEW_SHADER_RESOURCE);
	}
}	// namespace Potato
