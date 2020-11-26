// ;
#include "expch.h"
#include "exw\gui\ImGuiLayer.h"

#include "exw\Application.h"

#include <imgui.h>
#include <backends\imgui_impl_opengl3.h>
#include <backends\imgui_impl_glfw.h>
#include <GLFW\glfw3.h>

namespace exw
{
    namespace gui
    {
        ImGuiLayer::ImGuiLayer()
            : GuiLayer("ImGuiLayer")
        {}

        void ImGuiLayer::begin()
        {
            EXW_PROFILE_FUNCTION();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
        }

        void ImGuiLayer::end()
        {
            EXW_PROFILE_FUNCTION();

            ImGuiIO& io = ImGui::GetIO();
            Application& app = Application::get();
            io.DisplaySize = ImVec2((float)app.get_window().get_width(), (float)app.get_window().get_height());

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            if (IS_FLAG_SET(io.ConfigFlags, ImGuiConfigFlags_ViewportsEnable))
            {
                GLFWwindow* currentContext = glfwGetCurrentContext();
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
                glfwMakeContextCurrent(currentContext);
            }
        }

        void ImGuiLayer::set_dark_theme_colors()
        {

            /*
		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

		// Headers
		colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		
		// Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Frame BG
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

		// Title
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };*/
        }

        void ImGuiLayer::attach()
        {
            EXW_PROFILE_FUNCTION();

            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); //(void)io;
            io.ConfigFlags |= (
                ImGuiConfigFlags_NavEnableKeyboard |
                ImGuiConfigFlags_DockingEnable |
                ImGuiConfigFlags_ViewportsEnable
                );

            //io.Fonts->AddFontFromFileTTF("res/fonts/OpenSans/OpenSans-Bold.ttf", 18.0f);
            //io.FontDefault = io.Fonts->AddFontFromFileTTF("res/fonts/OpenSans/OpenSans-Regular.ttf", 18.0f);

            ImGui::StyleColorsDark();
            ImGuiStyle& style = ImGui::GetStyle();
            if (IS_FLAG_SET(io.ConfigFlags, ImGuiConfigFlags_ViewportsEnable))
            {
                style.WindowRounding = 0.0f;
                style.Colors[ImGuiCol_WindowBg].w = 1.0f;
            }
            set_dark_theme_colors();

            GLFWwindow* window = static_cast<GLFWwindow*>(Application::get().get_window().get_native_window());
            ImGui_ImplGlfw_InitForOpenGL(window, true);
            ImGui_ImplOpenGL3_Init("#version 410");
        }

        void ImGuiLayer::detach()
        {
            EXW_PROFILE_FUNCTION();

            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        }

        //void ImGuiLayer::update(Timestep _ts)
        //{
        //    //begin();
        //    //render_gui();
        //    //end();
        //}

        void ImGuiLayer::render_gui()
        {
            // TODO: remove this;
            static bool show = true;
            ImGui::ShowDemoWindow(&show);
        }

        void ImGuiLayer::on_event(event::Event& _event)
        {
            if (m_Block_events)
            {
                ImGuiIO& io = ImGui::GetIO();
                _event.Handled |= _event.is_category(event::EventCategoryMouse) & io.WantCaptureMouse;
                _event.Handled |= _event.is_category(event::EventCategoryKeyboard) & io.WantCaptureKeyboard;
            }
        }
    }
}
