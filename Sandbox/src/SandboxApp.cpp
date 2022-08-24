/*  SandboxApp.cpp
*   Version: 1.1 (2022.08.24)
*
*   Contributor
*       Arime-chan
*/

#include <ExWorkshop.h>

class SandboxLayer : public exw::Layer
{
public:
    SandboxLayer()
        : exw::Layer("SandboxLayer")
    {}

    virtual void attach()
    {}

    virtual void detach()
    {}

    virtual void update(float _deltaTime)
    {
        using namespace exw;

        if (Input::is_key_pressed(Keys::A))
            EXW_LOG_DEBUG("Å©");
        else if (Input::is_key_pressed(Keys::D))
            EXW_LOG_DEBUG("Å®");

        if (Input::is_key_pressed(Keys::W))
            EXW_LOG_DEBUG("Å™");
        else if (Input::is_key_pressed(Keys::S))
            EXW_LOG_DEBUG("Å´");

        if (Input::is_mouse_btn_pressed(MouseBtn::Button0))
        {
            auto cursorPos = Input::get_cursor_pos();
            EXW_LOG_DEBUG("Pressed ({0}, {1})", cursorPos.x, cursorPos.y);
        }


        graphics::OrthographicCamera camera = graphics::OrthographicCamera(-1.0f, 1.0f, -1.0f, 1.0f);

        refs::Ref<graphics::Shader> shader;
        refs::Ref<graphics::VertexArray> vertexArray = graphics::VertexArray::create();

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
             0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f
        };

        refs::Ref<graphics::VertexBuffer> vertexBuffer = graphics::VertexBuffer::create(vertices, sizeof(vertices));

        graphics::BufferLayout layout = {
            { graphics::ShaderDataType::Float3, "l_Position" },
            { graphics::ShaderDataType::Float4, "l_Color" }
        };

        refs::Ref<graphics::IndexBuffer> indexBuffer = graphics::IndexBuffer::create(new uint32_t[] { 0, 1, 2 }, 3);

        vertexBuffer->set_layout(layout);
        vertexArray->add_vertex_buffer(vertexBuffer);
        vertexArray->set_index_buffer(indexBuffer);


        shader = graphics::Shader::create("assets/shaders/light.glsl");


        {
            using namespace graphics;

            Renderer::set_clear_color({ 0.1f, 0.1f, 0.1f, 1.0f });
            Renderer::clear();

            Renderer::begin_scene(camera);

            shader->bind();

            Renderer::submit(shader, vertexArray, maths::matrix4(1.0f));


            graphics::Renderer::end_scene();
        }






    }

    virtual void on_event(exw::events::Event& _event)
    {}
};

class Sandbox : public exw::Application
{
public:
    Sandbox(std::string _name, std::string _workingDir, exw::AppCommandLineArgs _args)
        : exw::Application(_name, _workingDir, _args)
    {
        push_layer(new SandboxLayer());
    }

    ~Sandbox()
    {}
};

exw::Application* exw::create_application(exw::AppCommandLineArgs _args)
{
    return new Sandbox("Sandbox", ".", _args);
}
