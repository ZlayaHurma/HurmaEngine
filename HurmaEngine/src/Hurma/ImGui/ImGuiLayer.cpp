#include "ImGuiLayer.h"
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
#include "Hurma/IWindow.h"
#include "Hurma/Application.h"
#include "Hurma/Events/MouseEvent.h"
#include "Hurma/Events/ApplicationEvent.h"
#include "GLFW/glfw3.h"
#include "Hurma/Utils/TypeTraits.h"

namespace Hurma
{

    ImGuiLayer::ImGuiLayer() 
        : Layer("ImGuiLayer")
    {}

    void ImGuiLayer::onAttach() 
    {
        IMGUI_CHECKVERSION();
		ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

        ImGui::StyleColorsDark();

        IWindow* wnd = Application::get().getWindow();
        io.DisplaySize = ImVec2(static_cast<float>(wnd->getWidth()), static_cast<float>(wnd->getHeight()));

        ImGui_ImplGlfw_InitForOpenGL(reinterpret_cast<FuncArgTraits<decltype(&ImGui_ImplGlfw_InitForOpenGL)>::arg1>(wnd->getNativeWindow()), true);
		ImGui_ImplOpenGL3_Init("#version 410");
    }
    
    void ImGuiLayer::onDetach() 
    {
        ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
    }
    
    void ImGuiLayer::onUpdate(double deltaTimeSec) 
    {
    }

    void ImGuiLayer::onEvent(Event& event) 
    {
    }

    void ImGuiLayer::begin() 
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
    }

    void ImGuiLayer::onImGuiRender() 
    {
        static bool show = true;
        ImGui::ShowDemoWindow(&show);
    }

    void ImGuiLayer::end() 
    {
        ImGuiIO& io = ImGui::GetIO();
        IWindow* wnd = Application::get().getWindow();
        io.DisplaySize = ImVec2(static_cast<float>(wnd->getWidth()), static_cast<float>(wnd->getHeight()));

        ImGui::Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
		    ImGui::UpdatePlatformWindows();
		    ImGui::RenderPlatformWindowsDefault();
		    glfwMakeContextCurrent(backup_current_context);
        }
    }

}
