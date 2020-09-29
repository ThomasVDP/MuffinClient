#include "Shader.hpp"

#include "Potato/Application.hpp"

namespace Potato
{
	Shader::Shader(const std::string& t_ShaderPath, ShaderTypeEnum t_ShaderType, const char* t_EntryPoint) :
		m_ShaderType(t_ShaderType)
	{
		Diligent::ShaderCreateInfo ShaderCI;
		ShaderCI.SourceLanguage = Diligent::SHADER_SOURCE_LANGUAGE_HLSL;
		ShaderCI.UseCombinedTextureSamplers = true;

		Diligent::RefCntAutoPtr<Diligent::IShaderSourceInputStreamFactory> pShaderSourceFactory;
		Application::Get().GetWindow()->GetRenderContext()->GetEngineFactory()->CreateDefaultShaderSourceStreamFactory(nullptr, &pShaderSourceFactory);
		ShaderCI.pShaderSourceStreamFactory = pShaderSourceFactory;

		switch (t_ShaderType)
		{
		case ShaderTypeEnum::VERTEX: ShaderCI.Desc.ShaderType = Diligent::SHADER_TYPE_VERTEX; break;
		case ShaderTypeEnum::PIXEL: ShaderCI.Desc.ShaderType = Diligent::SHADER_TYPE_PIXEL; break;
		}
		ShaderCI.EntryPoint = t_EntryPoint;
		ShaderCI.FilePath = t_ShaderPath.c_str();
		Application::Get().GetWindow()->GetRenderContext()->GetRenderDevice()->CreateShader(ShaderCI, &m_Shader);
	}
}	// namespace Potato
