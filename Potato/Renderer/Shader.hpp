#ifndef POTATO_SHADER_HPP
#define POTATO_SHADER_HPP

#include <Graphics/GraphicsEngine/interface/Shader.h>
#include <Common/interface/RefCntAutoPtr.hpp>

namespace Potato
{
	enum class ShaderTypeEnum
	{
		VERTEX = 0,
		PIXEL
	};

	class Shader
	{
	public:
		Shader(const std::string& t_ShaderPath, ShaderTypeEnum t_ShaderType, const char* t_EntryPoint = "main");

		inline Diligent::RefCntAutoPtr<Diligent::IShader> GetShader() const { return m_Shader; };

		inline ShaderTypeEnum GetShaderType() const { return m_ShaderType; }

	private:
		Diligent::RefCntAutoPtr<Diligent::IShader> m_Shader;
		ShaderTypeEnum m_ShaderType;
	};
}	// namespace Potato

#endif