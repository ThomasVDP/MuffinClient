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

	class VertexBuffer
	{
	public:
		VertexBuffer() {}

		void Bind();

		const BufferLayout& GetLayout() const { return m_Layout; }
		void SetLayout(const BufferLayout& t_Layout) { m_Layout = t_Layout; }

		void Create(uint32_t t_BufferSize, void* t_BufferData);

	private:
		Diligent::RefCntAutoPtr<Diligent::IBuffer> m_Buffer;
		BufferLayout m_Layout{};
	};

	class IndexBuffer
	{
	public:
		IndexBuffer() {}

		void Bind();

		uint32_t GetCount() const;

		void Create(uint32_t t_BufferSize, uint32_t* t_Indices);

	private:
		Diligent::RefCntAutoPtr<Diligent::IBuffer> m_Buffer;
	};
}	// namespace Potato

#endif