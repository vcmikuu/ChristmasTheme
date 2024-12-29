#include "Snowflakes/snowflakes.hpp"
#include "main.hpp"
#include "assets.hpp"

#include "Snowflakes/particleController.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Quaternion.hpp"
#include "UnityEngine/ParticleSystemRenderer.hpp"
#include "UnityEngine/Material.hpp"

#include "bsml/shared/Helpers/utilities.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;
using namespace Flair;

namespace Christmas::snowflakes {

    SafePtrUnity<GameObject> dustGo;
    SafePtrUnity<GameObject> snowflakesGo;

    void CreateSnowflakes() {
        // Don't create if already created
        if(snowflakesGo) return;
        // Don't create if the template dust can't be found
        if(GameObject::Find("DustPS") == nullptr) return;

        // Create the snowflakes GameObject from the dust
        dustGo = GameObject::Find("DustPS");
        dustGo->active = false;
        snowflakesGo = GameObject::Instantiate(dustGo->gameObject);
        snowflakesGo->name = "SnowflakePS";
        snowflakesGo->active = true;
        // GameObject::DontDestroyOnLoad(snowflakesGo->gameObject); // This line will enable snowflakes in game

        // Get components from the snowflakes
        UnityEngine::ParticleSystem* snowflakes = snowflakesGo->GetComponent<ParticleSystem*>();
        UnityEngine::ParticleSystemRenderer* particleRenderer = snowflakesGo->GetComponent<UnityEngine::ParticleSystemRenderer*>();
        
        // Set up snowflakesGo where it needs to be
        snowflakesGo->transform->parent = nullptr;
        snowflakesGo->transform->position = UnityEngine::Vector3(0.0f, 7.0f, 0.0f);
        snowflakesGo->transform->rotation = UnityEngine::Quaternion::Euler(UnityEngine::Vector3(0.0f, 0.0f, 0.0f));

        // Use Flair's ParticleController to modify ParticleSystem properties to warp the dust into snowflakes
        ParticleController::MainModule::set_startLifetime(snowflakes, 10.0f);
        ParticleController::MainModule::set_startSize(snowflakes, 0.05);
        ParticleController::MainModule::set_maxParticles(snowflakes, 100000);
        ParticleController::MainModule::set_gravityModifier(snowflakes, 0.1f);
        ParticleController::EmissionModule::set_enabled(snowflakes, true); // ParticleTuner compatibility
        ParticleController::EmissionModule::set_rateOverTime(snowflakes, 1000);
        ParticleController::ShapeModule::set_shapeType(snowflakes, ParticleController::ShapeType::Box);
        ParticleController::ShapeModule::set_position(snowflakes, UnityEngine::Vector3(0.0f, 0.0f, 0.0f));
        ParticleController::ShapeModule::set_rotation(snowflakes, UnityEngine::Vector3(0.0f, 0.0f, 0.0f));
        ParticleController::ShapeModule::set_scale(snowflakes, UnityEngine::Vector3(20.0f, 1.0f, 20.0f));
        ParticleController::CollisionModule::set_enabled(snowflakes, true);
        ParticleController::CollisionModule::set_type(snowflakes, ParticleController::CollisionType::World);
        ParticleController::CollisionModule::set_collidesWith(snowflakes, UnityEngine::LayerMask(0xffffffff));
        ParticleController::CollisionModule::set_dampen(snowflakes, 0.08f);
        ParticleController::CollisionModule::set_bounce(snowflakes, 0.0f);
        ParticleController::CollisionModule::set_lifetimeLoss(snowflakes, 0.02);
        const int numSnowflakeSprites = 5;
        particleRenderer->material->mainTexture = BSML::Utilities::LoadTextureRaw(static_cast<ArrayW<uint8_t>>(IncludedAssets::snowflakes_png));
        ParticleController::TextureSheetAnimationModule::set_enabled(snowflakes, true);
        ParticleController::TextureSheetAnimationModule::set_mode(snowflakes, ParticleController::AnimationMode::Grid);
        ParticleController::TextureSheetAnimationModule::set_numTilesX(snowflakes, numSnowflakeSprites);
        ParticleController::TextureSheetAnimationModule::set_numTilesY(snowflakes, 1);
        ParticleController::TextureSheetAnimationModule::set_frameOverTime(snowflakes, ParticleController::MinMaxCurve(0.0f, numSnowflakeSprites));
        ParticleController::TextureSheetAnimationModule::set_startFrame(snowflakes, ParticleController::MinMaxCurve(0.0f, numSnowflakeSprites));
        ParticleController::TextureSheetAnimationModule::set_cycleCount(snowflakes, 0);
    }

    void DestroySnowflakes() {
        if(snowflakesGo) GameObject::Destroy(snowflakesGo->gameObject);
        if(dustGo) dustGo->active = true;
    }

}