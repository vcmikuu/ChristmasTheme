#include "Menu/customlogo.hpp"
#include "assets.hpp"
#include "bsml/shared/BSML.hpp"
#include "bsml/shared/Helpers/utilities.hpp"

#include "GlobalNamespace/TubeBloomPrePassLight.hpp"

#include "UnityEngine/SpriteRenderer.hpp"

namespace Christmas::customLogo {

    SafePtrUnity<UnityEngine::GameObject> saberLogo;
    SafePtrUnity<UnityEngine::GameObject> batLogo;
    SafePtrUnity<UnityEngine::GameObject> eFlickering;
    SafePtrUnity<UnityEngine::GameObject> eNeon;
    SafePtrUnity<UnityEngine::GameObject> saberNeon;
    SafePtrUnity<UnityEngine::GameObject> glowLines1;
    SafePtrUnity<UnityEngine::GameObject> christmasLogo;

    void LoadCustomLogo() {
        // Find each object needed and store it in a variable so it can be used when restoring the original logo
        if(UnityEngine::GameObject::Find("SaberLogo") != nullptr) saberLogo = UnityEngine::GameObject::Find("SaberLogo");
        if(UnityEngine::GameObject::Find("BatLogo") != nullptr) batLogo = UnityEngine::GameObject::Find("BatLogo");
        if(UnityEngine::GameObject::Find("EFlickering") != nullptr) eFlickering = UnityEngine::GameObject::Find("EFlickering");
        if(UnityEngine::GameObject::Find("ENeon") != nullptr) eNeon = UnityEngine::GameObject::Find("ENeon");
        if(UnityEngine::GameObject::Find("SaberNeon") != nullptr) saberNeon = UnityEngine::GameObject::Find("SaberNeon");
        if(UnityEngine::GameObject::Find("GlowLines (1)") != nullptr) glowLines1 = UnityEngine::GameObject::Find("GlowLines (1)");

        // Disable parts of the original logo that are getting replaced
        saberLogo->active = false;
        batLogo->active = false;
        eFlickering->active = false;

        // Recolor parts of the original logo that are still being used
        // The glow helps fill the space around the logo and makes it blend in to the sky instead of looking harshly out of place
        saberNeon->GetComponent<GlobalNamespace::TubeBloomPrePassLight*>()->color = UnityEngine::Color(0.0f, 1.0f, 0.3f, 1.0f);
        glowLines1->GetComponent<UnityEngine::SpriteRenderer*>()->color = UnityEngine::Color(0.0f, 1.0f, 0.3f, 0.25f);

        // Do not create custom logo object if already created
        if(christmasLogo) return;

        // Create object for the custom logo
        christmasLogo = UnityEngine::GameObject::New_ctor("ChristmasLogo");
        christmasLogo->transform->SetParent(UnityEngine::GameObject::Find("DefaultMenuEnvironment")->transform);
        christmasLogo->transform->position = UnityEngine::Vector3(0.0f, 16.6f, 26.1f);
        // Set the texture of the custom logo
        UnityEngine::SpriteRenderer* spriteRenderer = christmasLogo->AddComponent<UnityEngine::SpriteRenderer*>();
        spriteRenderer->sprite = BSML::Utilities::LoadSpriteRaw(static_cast<ArrayW<uint8_t>>(IncludedAssets::logo_png), 32.0f);

        // Fill the gap where the sparking E glow used to be
        UnityEngine::GameObject* replacementENeon = UnityEngine::GameObject::Instantiate(eNeon->gameObject);
        replacementENeon->name = "ReplacementENeon";
        replacementENeon->transform->parent = christmasLogo->transform;
        replacementENeon->transform->position = eNeon->transform->position;

        // Make the snowflakes glow blue
        UnityEngine::GameObject* leftSnowflakeNeon = UnityEngine::GameObject::Instantiate(UnityEngine::GameObject::Find("BNeon"));
        leftSnowflakeNeon->name = "LeftSnowflakeNeon";
        leftSnowflakeNeon->transform->parent = christmasLogo->transform;
        leftSnowflakeNeon->GetComponent<GlobalNamespace::TubeBloomPrePassLight*>()->color = UnityEngine::Color(0.035f, 0.7f, 0.89f, 1.0f);
        leftSnowflakeNeon->transform->position = UnityEngine::Vector3(-10.0f, 16.5f, 25.94f);
        
        UnityEngine::GameObject* rightSnowflakeNeon = UnityEngine::GameObject::Instantiate(leftSnowflakeNeon);
        rightSnowflakeNeon->name = "RightSnowflakeNeon";
        rightSnowflakeNeon->transform->parent = christmasLogo->transform;
        rightSnowflakeNeon->transform->position = UnityEngine::Vector3(
            -leftSnowflakeNeon->transform->position.x,
            leftSnowflakeNeon->transform->position.y,
            leftSnowflakeNeon->transform->position.z
        );
    }

    // Untested, may or may not work or crash
    void LoadOriginalLogo() {
        if(!(saberLogo|| batLogo || eFlickering || saberNeon || glowLines1)) return;

        // Re-enable parts of the original logo that were completely replaced
        saberLogo->active = true;
        batLogo->active = true;
        eFlickering->active = true;

        // Recolor parts of the original logo that were modified
        // The glow helps fill the space around the logo and makes it blend in to the sky instead of looking harshly out of place
        saberNeon->GetComponent<GlobalNamespace::TubeBloomPrePassLight*>()->color = UnityEngine::Color(0.0f, 0.682f, 1.0f, 1.0f);
        glowLines1->GetComponent<UnityEngine::SpriteRenderer*>()->color = UnityEngine::Color(0.0f, 0.753f, 1.0f, 0.251f);

        if(!christmasLogo) return;

        // Destroy the custom logo and all of the other objects that were created and parented to it
        UnityEngine::GameObject::Destroy(christmasLogo->gameObject);
    }

}