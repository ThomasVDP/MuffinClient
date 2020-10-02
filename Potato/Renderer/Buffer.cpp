#include "Buffer.hpp"

#include "Potato/Application.hpp"

namespace Potato
{
	void VertexBuffer::Bind()
	{
		Diligent::Uint32 offset = 0;
		Diligent::IBuffer* pBuffs[] = { m_Buffer };
		Application::Get().GetWindow()->GetRenderContext()->GetImmediateContext()->SetVertexBuffers(0,
																									1,
																									pBuffs,
																									&offset,
																									Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION,
																									Diligent::SET_VERTEX_BUFFERS_FLAG_RESET);
	}

	void VertexBuffer::Create(uint32_t t_BufferSize, void* t_BufferData)
	{
		Diligent::BufferDesc VertBuffDesc;
		VertBuffDesc.Name = "Vertex buffer";
		VertBuffDesc.Usage = Diligent::USAGE_STATIC;
		VertBuffDesc.BindFlags = Diligent::BIND_VERTEX_BUFFER;
		VertBuffDesc.uiSizeInBytes = t_BufferSize;
		Diligent::BufferData VBData;
		VBData.pData = t_BufferData;
		VBData.DataSize = t_BufferSize;
		Application::Get().GetWindow()->GetRenderContext()->GetRenderDevice()->CreateBuffer(VertBuffDesc, &VBData, &m_Buffer);
	}

	void IndexBuffer::Bind()
	{
		Application::Get().GetWindow()->GetRenderContext()->GetImmediateContext()->SetIndexBuffer(m_Buffer,
																								  0,
																								  Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
	}

	void IndexBuffer::Create(uint32_t t_BufferSize, uint32_t* t_Indices)
	{
		m_Count = t_BufferSize / sizeof(uint32_t);

		Diligent::BufferDesc IndBuffDesc;
		IndBuffDesc.Name = "Index buffer";
		IndBuffDesc.Usage = Diligent::USAGE_STATIC;
		IndBuffDesc.BindFlags = Diligent::BIND_INDEX_BUFFER;
		IndBuffDesc.uiSizeInBytes = t_BufferSize;
		Diligent::BufferData IBData;
		IBData.pData = t_Indices;
		IBData.DataSize = t_BufferSize;
		Application::Get().GetWindow()->GetRenderContext()->GetRenderDevice()->CreateBuffer(IndBuffDesc, &IBData, &m_Buffer);
	}
}	// namespace Potato
