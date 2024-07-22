#include "Test3DCube.h"

#include "Renderer.h"



namespace test
{

    test::Test3DCube::Test3DCube()
        : m_TranslationA(0, 0, -1.0f), m_Rotation(0.0f),
            m_Proj(glm::perspective(glm::radians(45.0f), 960.0f / 540.0f, 0.1f, 1000.0f)),
             m_View(glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f))),
              bAutoRotate (false), bAutoTranslate(false), m_RotationSpeedX(30.0f), m_RotationSpeedY(45.0f), m_RotationSpeedZ(60.0f),
                m_MovementSpeedX(0.75f), m_MovementSpeedY(0.75f), m_MovementSpeedZ(0.75f), m_MoveDirectionX(1), m_MoveDirectionY(1), m_MoveDirectionZ(1)

	{

        float vertices[] = {
            // Positions           // Colors
            -1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, // Red
             1.0f, -1.0f, -1.0f,  0.0f, 1.0f, 0.0f, // Green
             1.0f,  1.0f, -1.0f,  0.0f, 0.0f, 1.0f, // Blue
            -1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 0.0f, // Yellow

            -1.0f, -1.0f,  1.0f,  0.0f, 1.0f, 1.0f, // Cyan
             1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 1.0f, // Magenta
             1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 1.0f, // White
            -1.0f,  1.0f,  1.0f,  0.5f, 0.5f, 0.5f  // Gray
        };

        unsigned int indices[] = {
             0, 1, 2, 2, 3, 0,
             4, 5, 6, 6, 7, 4,
             0, 1, 5, 5, 4, 0,
             2, 3, 7, 7, 6, 2,
             0, 3, 7, 7, 4, 0,
             1, 2, 6, 6, 5, 1
        };


        glDisable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);

        m_VAO = std::make_unique<VertexArray>();
        m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));

        VertexBufferLayout layout;
        layout.Push<float>(3); // Position
        layout.Push<float>(3); // Color
        m_VAO->AddBuffer(*m_VertexBuffer, layout);

        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(unsigned int));




        m_Shader = std::make_unique<Shader>("Resources/Shaders/BasicCube.shader");
        m_Shader->Bind();
        m_Shader->SetUniform4f("u_Colour", 1.0f, 0.0f, 0.0f, 1.0f);



        clear_color = ImVec4(0.45f, 0.5f, 0.60f, 1.00f);

	}

	test::Test3DCube::~Test3DCube()
	{
	}

	void test::Test3DCube::Update(float deltaTime)
	{

        if (bAutoRotate)
        {
            // Increment the rotation angles based on speed and elapsed time
            m_Rotation.x += m_RotationSpeedX * deltaTime;
            m_Rotation.y += m_RotationSpeedY * deltaTime;
            m_Rotation.z += m_RotationSpeedZ * deltaTime;

            // Ensure rotation values stay within 0 to 360 degrees
            if (m_Rotation.x >= 360.0f) m_Rotation.x -= 360.0f;
            if (m_Rotation.y >= 360.0f) m_Rotation.y -= 360.0f;
            if (m_Rotation.z >= 360.0f) m_Rotation.z -= 360.0f;

        }

        if (bAutoTranslate)
        {
            // Increment the translation values based on speed, elapsed time, and direction
            m_TranslationA.x += m_MovementSpeedX * deltaTime * m_MoveDirectionX;
            m_TranslationA.y += m_MovementSpeedY * deltaTime * m_MoveDirectionY;
            m_TranslationA.z += m_MovementSpeedZ * deltaTime * m_MoveDirectionZ;

            // Ensure translation values stay within -7.0 to 7.0 and reverse direction if needed
            if (m_TranslationA.x >= 1.0f || m_TranslationA.x <= -1.0f) m_MoveDirectionX *= -1;
            if (m_TranslationA.y >= 1.0f || m_TranslationA.y <= -1.0f) m_MoveDirectionY *= -1;
            if (m_TranslationA.z >= 1.0f || m_TranslationA.z <= -1.0f) m_MoveDirectionZ *= -1;

        }

	}

	void test::Test3DCube::OnRender()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);


        Renderer renderer;
        m_Shader->Bind();

      
        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
        model = glm::rotate(model, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 mvp = m_Proj * m_View * model;


        m_Shader->SetUniformMat4f("u_MVP", mvp);
        renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        
       
	}

	void test::Test3DCube::OnImGUIRender()
	{
        ImGui::SliderFloat3("Translation A", &m_TranslationA.x, -1.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::SliderFloat("Rotation X", &m_Rotation.x, 0.0f, 360.0f);                        // Add rotation slider
        ImGui::SliderFloat("Rotation Y", &m_Rotation.y, 0.0f, 360.0f);                        // Add rotation slider
        ImGui::SliderFloat("Rotation Z", &m_Rotation.z, 0.0f, 360.0f);                        // Add rotation slider
        ImGui::Checkbox("Start Auto-Rotate", &bAutoRotate);
        ImGui::Checkbox("Start Auto-Translate", &bAutoTranslate);
        ImGui::ColorEdit3("clear color", (float*)&clear_color);                           // Edit 3 floats representing a color
	}

}