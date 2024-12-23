#include "Block/colorchanger.hpp"
#include "UnityEngine/Renderer.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Material.hpp"
#include "GlobalNamespace/NoteController.hpp"
#include "GlobalNamespace/GameNoteController.hpp"

namespace cColor {

    ColorChanger::ColorChanger()
        : currentColor(1.0f, 0.0f, 0.0f, 1.0f),
          transitioningToYellow(true),
          transitionSpeed(0.5f) {}

    void ColorChanger::UpdateColor(float deltaTime) {
        if (transitioningToYellow) {
            currentColor.g += transitionSpeed * deltaTime;
            if (currentColor.g >= 1.0f) {
                currentColor.g = 1.0f;
                transitioningToYellow = false;
            }
        } else {
            currentColor.g -= transitionSpeed * deltaTime;
            if (currentColor.g <= 0.0f) {
                currentColor.g = 0.0f;
                transitioningToYellow = true;
            }
        }

        auto gameObject = UnityEngine::GameObject::Find("BlockColorRenderer");
        if (gameObject) {
            auto renderer = gameObject->GetComponent<UnityEngine::Renderer*>();
            if (renderer) {
                auto material = renderer->get_material();
                if (material) {
                    material->set_color(currentColor);
                }
            }
        }
    }
}