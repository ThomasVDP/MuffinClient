#include "BasicRenderer.hpp"

#include "RenderCommand.hpp"

#include "PipelineState.hpp"

namespace Potato
{
	struct BasicRendererData
	{
		Potato::PipelineState pipeline = PipelineState("Triangle pipeline!");
	};

	static BasicRendererData s_Data;

	void BasicRenderer::Init()
	{
		s_Data.pipeline.Create("vertex.vsh", "pixel.vsh");
	}

	void BasicRenderer::DrawTriangle()
	{
		s_Data.pipeline.Bind();
		RenderCommand::DrawVertices(3);
	}
}	// namespace Potato
