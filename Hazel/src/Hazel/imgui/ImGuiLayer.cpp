//
// Created by rui ding on 2025/7/2.
//

#include "Hazel/imgui/ImGuiLayer.h"

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>

#include "hzpch.h"
#include "imgui_impl_glfw.h"
#include "Hazel/Application.h"
#include "Hazel/Event/MouseEvent.h"
#include "Hazel/Core/KeyCodes.h"

namespace Hazel {

// glfw和imgui的键位映射
ImGuiKey KeyCodeToImGuiKey(KeyCode code) {
    static const std::unordered_map<KeyCode, ImGuiKey> map {
        { Key::Tab, ImGuiKey_Tab },
        { Key::Left, ImGuiKey_LeftArrow },
        { Key::Right, ImGuiKey_RightArrow },
        { Key::Up, ImGuiKey_UpArrow },
        { Key::Down, ImGuiKey_DownArrow },
        { Key::PageUp, ImGuiKey_PageUp },
        { Key::PageDown, ImGuiKey_PageDown },
        { Key::Home, ImGuiKey_Home },
        { Key::End, ImGuiKey_End },
        { Key::Insert, ImGuiKey_Insert },
        { Key::Delete, ImGuiKey_Delete },
        { Key::Backspace, ImGuiKey_Backspace },
        { Key::Space, ImGuiKey_Space },
        { Key::Enter, ImGuiKey_Enter },
        { Key::Escape, ImGuiKey_Escape },
        { Key::A, ImGuiKey_A },
        { Key::C, ImGuiKey_C },
        { Key::V, ImGuiKey_V },
        { Key::X, ImGuiKey_X },
        { Key::Y, ImGuiKey_Y },
        { Key::Z, ImGuiKey_Z }
    };
    // 零散键位
    if (auto it = map.find(code); it != map.end()) return it->second;
    // A‑Z
    if (code >= Key::A && code <= Key::Z)
        return static_cast<ImGuiKey>(ImGuiKey_A + (static_cast<int>(code) - static_cast<int>(Key::A)));
    // 0‑9
    if (code >= Key::D0 && code <= Key::D9)
        return static_cast<ImGuiKey>(ImGuiKey_0 + (static_cast<int>(code) - static_cast<int>(Key::D0)));
    // F1‑F12
    if (code >= Key::F1 && code <= Key::F12)
        return static_cast<ImGuiKey>(ImGuiKey_F1 + (static_cast<int>(code) - static_cast<int>(Key::F1)));
    // 没有映射
    return ImGuiKey_None;
}

ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") { }

ImGuiLayer::~ImGuiLayer() { }

void ImGuiLayer::OnAttach() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark();
    Application& app = Application::Get();
    GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void ImGuiLayer::OnDetach()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiLayer::OnUpdate() {
    ImGuiIO& io = ImGui::GetIO();
    Application& app = Application::Get();
    io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

    float time = (float)glfwGetTime();
    io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
    m_Time = time;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::OnEvent(Event& e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<MouseButtonPressedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
    dispatcher.Dispatch<MouseButtonReleasedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
    dispatcher.Dispatch<MouseMovedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
    dispatcher.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
    dispatcher.Dispatch<KeyPressedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
    dispatcher.Dispatch<KeyTypedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
    dispatcher.Dispatch<KeyReleasedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
    dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
}

void ImGuiLayer::OnImGuiRender()
{
    static bool show = true;
    ImGui::ShowDemoWindow(&show);
}

void ImGuiLayer::Begin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiLayer::End()
{
    ImGuiIO& io = ImGui::GetIO();
    Application& app = Application::Get();
    io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent &e) {
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[e.GetMouseButton()] = true;
    return false;
}

bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &e) {
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[e.GetMouseButton()] = false;
    return false;
}

bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent &e) {
    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2(e.GetX(), e.GetY());
    return false;
}

bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent &e) {
    ImGuiIO& io = ImGui::GetIO();
    io.MouseWheelH += e.GetXOffset();
    io.MouseWheel += e.GetYOffset();
    return false;
}

bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent &e) {
    ImGuiIO& io = ImGui::GetIO();
    ImGuiKey k = KeyCodeToImGuiKey(e.GetKeyCode());
    if (k != ImGuiKey_None) io.AddKeyEvent(k, true);
    return false;
}

bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent &e) {
    ImGuiIO& io = ImGui::GetIO();
    ImGuiKey k = KeyCodeToImGuiKey(e.GetKeyCode());
    if (k != ImGuiKey_None) io.AddKeyEvent(k, false);
    return false;
}

bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent &e) {
    ImGuiIO& io = ImGui::GetIO();
    KeyCode keycode = e.GetKeyCode();
    io.AddInputCharacter(keycode);
    return false;
}

bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent &e) {
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float)e.GetWidth(), (float)e.GetHeight());
    io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
    return false;
}
}
