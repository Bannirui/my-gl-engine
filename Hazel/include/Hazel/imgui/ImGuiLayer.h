//
// Created by rui ding on 2025/7/2.
//

#pragma once

#include "Hazel/Layer.h"
#include "Hazel/Event/MouseEvent.h"
#include "Hazel/Event/KeyEvent.h"
#include "Hazel/Event/ApplicationEvent.h"

namespace Hazel
{

class ImGuiLayer : public Hazel::Layer
{
public:
  ImGuiLayer();
  ~ImGuiLayer();

  virtual void OnAttach();
  virtual void OnDetach();
  virtual void OnUpdate();
  virtual void OnEvent(Event& e);
  virtual void OnImGuiRender();

  void Begin();
  void End();

private:
  bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
  bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
  bool OnMouseMovedEvent(MouseMovedEvent& e);
  bool OnMouseScrolledEvent(MouseScrolledEvent& e);
  bool OnKeyPressedEvent(KeyPressedEvent& e);
  bool OnKeyReleasedEvent(KeyReleasedEvent& e);
  bool OnKeyTypedEvent(KeyTypedEvent& e);
  bool OnWindowResizeEvent(WindowResizeEvent& e);

private:
  float m_Time = 0.0f;
};
}
