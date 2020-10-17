#ifndef MUFFIN_SKYBOX_HPP
#define MUFFIN_SKYBOX_HPP

#include "PotatoEngine.hpp"

namespace Muffin
{
	class Skybox
	{
	public:
		Skybox(const std::string& skyboxFile);

		void OnRender(const Potato::Camera& t_Camera);

	private:
		Diligent::RefCntAutoPtr<Diligent::ITextureView> CreateSkyboxTextureArr(const std::string& t_FileName);

		Potato::Texture m_Texture;
		Potato::PipelineState m_PipelineState;
		Potato::VertexBuffer m_VertexBuffer;
		Potato::IndexBuffer m_IndexBuffer;
	};
}	// namespace Muffin

#endif