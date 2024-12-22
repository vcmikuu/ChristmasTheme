#pragma once

#include "main.hpp"
#include <string>
#include <vector>

#include "bsml/shared/BSML/FloatingScreen/FloatingScreen.hpp"
#include "bsml/shared/BSML.hpp"
#include "bsml/shared/BSML-Lite.hpp"

#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/GameObject.hpp"

namespace Christmas::chLogo {
    static BSML::FloatingScreen* cLogo = nullptr;
    static SafePtrUnity<UnityEngine::GameObject> logo;

    void DisableOriginalLogo();
    void LoadLogo();
    void ReloadLogo();

}