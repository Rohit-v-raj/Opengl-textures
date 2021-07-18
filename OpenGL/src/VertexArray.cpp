#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_Renderer_Id));
	
}

VertexArray::~VertexArray()

{
	glDeleteVertexArrays(1, &m_Renderer_Id);

}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	vb.Bind();
	Bind();
	auto elements = layout.GetElements();
	unsigned int offset=0;
	for (unsigned int i = 0; i < elements.size(); ++i)
	{
		auto element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(),(const void*) offset);
		offset += element.count* VertexBufferElement::GetSizeOfType(element.type);

	}


}
void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_Renderer_Id));
}
void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}