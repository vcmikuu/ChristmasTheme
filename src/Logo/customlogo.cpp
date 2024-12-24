#include "Logo/customlogo.hpp"
#include "assets.hpp"
#include "bsml/shared/BSML.hpp"
#include "bsml/shared/Helpers/utilities.hpp"

#include "GlobalNamespace/TubeBloomPrePassLight.hpp"

#include "UnityEngine/SpriteRenderer.hpp"

namespace Christmas::customLogo {

    void LoadCustomLogo() {
        // Disable parts of the original logo that are getting replaced
        UnityEngine::GameObject::Find("SaberLogo")->active = false;
        UnityEngine::GameObject::Find("BatLogo")->active = false;
        UnityEngine::GameObject::Find("EFlickering")->active = false;

        // Recolor parts of the original logo that are still being used
        // The glow helps fill the space around the logo and makes it blend in to the sky instead of looking harshly out of place
        UnityEngine::GameObject::Find("SaberNeon")->GetComponent<GlobalNamespace::TubeBloomPrePassLight*>()->color = UnityEngine::Color(0.0f, 1.0f, 0.3f, 1.0f);
        UnityEngine::GameObject::Find("GlowLines (1)")->GetComponent<UnityEngine::SpriteRenderer*>()->color = UnityEngine::Color(0.0f, 1.0f, 0.3f, 0.25f);

        // Do not create custom logo object if already created
        if(UnityEngine::GameObject::Find("ChristmasLogo") != nullptr) return;

        // Create object for the custom logo
        UnityEngine::GameObject* christmasLogo = UnityEngine::GameObject::New_ctor("ChristmasLogo");
        christmasLogo->transform->SetParent(UnityEngine::GameObject::Find("DefaultMenuEnvironment")->transform);
        christmasLogo->transform->position = UnityEngine::Vector3(0.0f, 16.6f, 26.1f);

        // Set the texture of the custom logo
        UnityEngine::SpriteRenderer* spriteRenderer = christmasLogo->AddComponent<UnityEngine::SpriteRenderer*>();
        spriteRenderer->sprite = BSML::Utilities::LoadSpriteRaw(static_cast<ArrayW<uint8_t>>(IncludedAssets::logo_png), 32.0f);
    }

}