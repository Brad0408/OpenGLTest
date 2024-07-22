#pragma once

#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <memory>



namespace test 
{

	class Test3DCube : public Test
	{
	
	
	public:
		Test3DCube();
		~Test3DCube();
	
		void Update(float deltaTime) override;
		void OnRender() override;
		void OnImGUIRender() override;
	
	
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;

		glm::mat4 m_Proj, m_View;
		glm::vec3 m_TranslationA, m_Rotation;
		//float m_Rotation;
		ImVec4 clear_color;

		bool bAutoRotate;
		bool bAutoTranslate;

		float m_RotationSpeedX;  // Speed of rotation around X-axis
		float m_RotationSpeedY;  // Speed of rotation around Y-axis
		float m_RotationSpeedZ;  // Speed of rotation around Z-axis

		float m_MovementSpeedX;  // Speed of rotation around X-axis
		float m_MovementSpeedY;  // Speed of rotation around Y-axis
		float m_MovementSpeedZ;  // Speed of rotation around Z-axis

		float m_MoveDirectionX;  // Speed of rotation around X-axis
		float m_MoveDirectionY;  // Speed of rotation around Y-axis
		float m_MoveDirectionZ;  // Speed of rotation around Z-axis
	};



}