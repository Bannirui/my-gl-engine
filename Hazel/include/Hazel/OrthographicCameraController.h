//
// Created by rui ding on 2025/7/11.
//

#pragma once
#include "Hazel/Event/Event.h"
#include "Hazel/renderer/OrthographicCamera.h"
#include "Hazel/Core/Timestep.h"

namespace Hazel
{
    class WindowResizeEvent;
    class MouseScrolledEvent;

    class OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio, bool rotation = false);

        void OnUpdate(Timestep ts);
        void OnEvent(Event& e);

        OrthographicCamera&       GetCamera() { return m_Camera; }
        const OrthographicCamera& GetCamera() const { return m_Camera; }

        float GetZoomLevel() const { return m_ZoomLevel; }
        void  SetZoomLevel(float level) { m_ZoomLevel = level; }

    private:
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);

    private:
        float              m_AspectRatio;
        float              m_ZoomLevel{1.0f};
        OrthographicCamera m_Camera;
        bool               m_Rotation;
        glm::vec3          m_CameraPosition         = {0.0f, 0.0f, 0.0f};
        float              m_CameraRotation         = 0.0f;
        float              m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
    };
}  // namespace Hazel