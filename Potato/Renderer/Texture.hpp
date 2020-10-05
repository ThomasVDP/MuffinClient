#ifndef POTATO_TEXTURE_HPP
#define POTATO_TEXTURE_HPP

#include <TextureLoader/interface/TextureUtilities.h>
#include <Common/interface/RefCntAutoPtr.hpp>

namespace Potato
{
	class Texture
	{
	public:
		Texture() = default;

		Texture(const std::string& t_FileName, const std::string& t_TextureName);

		const std::string& GetTextureName() const { return m_TextureName; }
		Diligent::RefCntAutoPtr<Diligent::ITextureView> GetTextureSRV() const { return m_TextureSRV; }

	private:
		std::string m_TextureName;

		Diligent::RefCntAutoPtr<Diligent::ITexture> m_Texture;
		Diligent::RefCntAutoPtr<Diligent::ITextureView> m_TextureSRV;
	};
}	// namespace Potato

#endif