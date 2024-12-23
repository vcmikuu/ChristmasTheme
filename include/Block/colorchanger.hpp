#pragma once

#include "main.hpp"
#include "UnityEngine/Color.hpp"

namespace cColor {
    class ColorChanger {
    public:
        ColorChanger();

        void UpdateColor(float deltaTime);
        UnityEngine::Color currentColor;

        bool transitioningToYellow;
        float transitionSpeed;
    };
}