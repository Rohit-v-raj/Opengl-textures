#pragma once
#include "Test.h"
#include <vector>
#include "Texture.h"

#include <memory>

using namespace glm;

namespace test {
	class TestTexture2D:public Test{
	public:
		TestTexture2D();
		~TestTexture2D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		vec3 m_TranslationA, m_TranslationB;
		mat4 proj;
		mat4 view;
		unique_ptr<VertexArray> va;
		unique_ptr<Shader> shader;
		unique_ptr<IndexBuffer> ib;
		unique_ptr<VertexBuffer> vb;
		unique_ptr<Texture> texture;
		unique_ptr<VertexBufferLayout> layout;
	
	};
}