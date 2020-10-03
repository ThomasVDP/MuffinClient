#ifndef POTATO_BUFFER_HPP
#define POTATO_BUFFER_HPP

#include <Common/interface/RefCntAutoPtr.hpp>
#include <Graphics/GraphicsEngine/interface/InputLayout.h>
#include <Graphics/GraphicsEngine/interface/Buffer.h>

#include <vector>

namespace Potato
{
	class BufferLayout
	{
	public:
		BufferLayout(const std::initializer_list<Diligent::LayoutElement>& elements) :
			m_Elements(elements)
		{
		}

		const std::vector<Diligent::LayoutElement>& GetElements() const { return this->m_Elements; }

	private:
		std::vector<Diligent::LayoutElement> m_Elements;
	};

	enum class BufferUsage
	{
		STATIC = 0,
		DEFAULT,
		DYNAMIC
	};

	class VertexBuffer
	{
	public:
		VertexBuffer() {}

		void Bind();

		void Create(BufferUsage t_BufferUsage, uint32_t t_BufferSize, void* t_BufferData);

	private:
		Diligent::RefCntAutoPtr<Diligent::IBuffer> m_Buffer;
	};

	class IndexBuffer
	{
	public:
		IndexBuffer() {}

		void Bind();

		uint32_t GetCount() const { return m_Count; }

		void Create(uint32_t t_BufferSize, uint32_t* t_Indices);

	private:
		Diligent::RefCntAutoPtr<Diligent::IBuffer> m_Buffer;
		uint32_t m_Count;
	};
}	// namespace Potato

#endif