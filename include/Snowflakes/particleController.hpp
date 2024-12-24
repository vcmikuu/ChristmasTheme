#pragma once

#include "custom-types/shared/macros.hpp"

#include "UnityEngine/MonoBehaviour.hpp"

#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Mesh.hpp"
#include "UnityEngine/MeshRenderer.hpp"
#include "UnityEngine/SkinnedMeshRenderer.hpp"
#include "UnityEngine/Sprite.hpp"
#include "UnityEngine/SpriteRenderer.hpp"
#include "UnityEngine/Texture2D.hpp"
#include "UnityEngine/LayerMask.hpp"
#include "UnityEngine/Component.hpp"
#include "UnityEngine/Light.hpp"
#include "UnityEngine/AnimationCurve.hpp"
#include "UnityEngine/Gradient.hpp"
#include "UnityEngine/Color.hpp"
#include "UnityEngine/ParticleSystem.hpp" // MinMaxCurve & MinMaxGradient (may recreate as a ParticleController struct)

namespace UnityEngine::Rendering {
    enum UVChannelFlags {UV0 = 1, UV1 = 2, UV2 = 4, UV3 = 8};
}

#define DECLARE_FIELD_SETGET(type, name) \
static type get_##name(UnityEngine::ParticleSystem* particleSystem); \
static void set_##name(UnityEngine::ParticleSystem* particleSystem, type value);

// DECLARE_CLASS_CODEGEN(Flair, ParticleSystemForceField, UnityEngine::Behaviour, 
//     public:
//         enum class ForceFieldShape {Sphere, Hemisphere, Cylinder, Box};

//         DECLARE_FIELD_SETGET(UnityEngine::Vector2, rotationRandomness);
//         DECLARE_FIELD_SETGET(UnityEngine::ParticleSystem::MinMaxCurve, directionX);
//         DECLARE_FIELD_SETGET(UnityEngine::ParticleSystem::MinMaxCurve, directionY);
//         DECLARE_FIELD_SETGET(UnityEngine::ParticleSystem::MinMaxCurve, directionZ);
//         DECLARE_FIELD_SETGET(UnityEngine::ParticleSystem::MinMaxCurve, gravity);
//         DECLARE_FIELD_SETGET(UnityEngine::ParticleSystem::MinMaxCurve, rotationSpeed);
//         DECLARE_FIELD_SETGET(UnityEngine::ParticleSystem::MinMaxCurve, rotationAttraction);
//         DECLARE_FIELD_SETGET(UnityEngine::ParticleSystem::MinMaxCurve, drag);
//         DECLARE_FIELD_SETGET(UnityEngine::ParticleSystem::MinMaxCurve, vectorFieldSpeed);
//         DECLARE_FIELD_SETGET(UnityEngine::ParticleSystem::MinMaxCurve, vectorFieldAttraction);
// );

// DECLARE_CLASS_CODEGEN(Flair, ParticleController, UnityEngine::MonoBehaviour,
namespace Flair {

    class ParticleController {
        public:
            enum class GravitySource {Physics3D, Physics2D};
            enum class SimulationSpace {Local, World, Custom};
            enum class ScalingMode {Hierarchy, Local, Shape};
            enum class EmitterVelocityMode {Transform, Rigidbody, Custom};
            enum class StopAction {None, Disable, Destroy, Callback};
            enum class RingBufferMode {Disabled, PauseUntilReplaced, LoopUntilReplaced};
            enum class CullingMode {Automatic, PauseAndCatchup, Pause, AlwaysSimulate};
            enum class ShapeType {Sphere = 0, Hemisphere = 2, Cone = 4, Box = 5, Mesh = 6, ConeVolume = 8, Circle = 10, SingleSidedEdge = 12, MeshRenderer = 13, SkinnedMeshRenderer = 14, BoxShell = 15, BoxEdge = 16, Donut = 17, Rectangle = 18, Sprite = 19, SpriteRenderer = 20};
            enum class ShapeMultiModeValue {Random, Loop, PingPong, BurstSpread};
            enum class MeshShapeType {Vertex, Edge, Triangle};
            enum class ShapeTextureChannel {Red, Green, Blue, Alpha};
            enum class CollisionType {Planes, World};
            enum class CollisionMode {Collision2D, Collision3D};
            enum class CollisionQuality {High, Medium, Low};
            enum class OverlapAction {Ignore, Kill, Callback};
            enum class ColliderQueryMode {Disabled, One, All};
            enum class SubEmitterType {Birth, Collision, Death, Trigger, Manual};
            enum class SubEmitterProperties {InheritNothing = 0, InheritEverything = 0x1f, InheritColor = 1, InheritSize = 2, InheritRotation = 4, InheritLifetime = 8, InheritDuration = 0x10};
            enum class AnimationMode {Grid, Sprites};
            enum class AnimationTimeMode {Lifetime, Speed, FPS};
            enum class AnimationType {WholeSheet, SingleRow};
            enum class AnimationRowMode {Custom, Random, MeshIndex};
            enum class InheritVelocityMode {Initial, Current};
            enum class GameObjectFilter {LayerMask, List, LayerMaskAndList};
            enum class NoiseQuality {Low, Medium, High};
            enum class TrailMode {PerParticle, Ribbon};
            enum class TrailTextureMode {Stretch, Tile, DistributePerSegment, RepeatPerSegment, Static};
            enum class CustomData {Custom1, Custom2};
            enum class CustomDataMode {Disabled, Vector, Color};
            enum class CurveMode {Constant, Curve, TwoCurves, TwoConstants};
            enum class GradientMode {Color, Gradient, TwoColors, TwoGradients, RandomColor};

            struct MinMaxCurve {
                CurveMode mode = CurveMode::Constant;
                float curveMultiplier = 0.0f;
                UnityEngine::AnimationCurve* curveMin = nullptr;
                UnityEngine::AnimationCurve* curveMax = nullptr;
                float constantMin = 0.0f;
                float constantMax = 0.0f;

                MinMaxCurve() {}

                MinMaxCurve(float constant) {
                    mode = CurveMode::Constant;
                    constantMax = constant;
                }

                MinMaxCurve(float multiplier, UnityEngine::AnimationCurve* curve) {
                    mode = CurveMode::Curve;
                    curveMultiplier = multiplier;
                    curveMax = curve;
                }

                MinMaxCurve(float multiplier, UnityEngine::AnimationCurve* min, UnityEngine::AnimationCurve* max) {
                    mode = CurveMode::TwoCurves;
                    curveMultiplier = multiplier;
                    curveMin = min;
                    curveMax = max;
                }

                MinMaxCurve(float min, float max) {
                    mode = CurveMode::TwoConstants;
                    constantMin = min;
                    constantMax = max;
                }
            };

            struct MinMaxGradient {
                GradientMode mode;
                UnityEngine::Gradient* gradientMin;
                UnityEngine::Gradient* gradientMax;
                UnityEngine::Color colorMin;
                UnityEngine::Color colorMax;
            };

            struct Burst {
                float time;
                MinMaxCurve count;
                int repeatCount;
                float repeatInterval;
                float invProbability;
            };

            struct MainModule {
                DECLARE_FIELD_SETGET(UnityEngine::Vector3, emitterVelocity);
                DECLARE_FIELD_SETGET(float, duration);
                DECLARE_FIELD_SETGET(bool, loop);
                DECLARE_FIELD_SETGET(bool, prewarm);
                DECLARE_FIELD_SETGET(MinMaxCurve, startDelay);
                DECLARE_FIELD_SETGET(float, startDelayMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, startLifetime);
                DECLARE_FIELD_SETGET(float, startLifetimeMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, startSpeed);
                DECLARE_FIELD_SETGET(float, startSpeedMultiplier);
                DECLARE_FIELD_SETGET(bool, startSize3D);
                DECLARE_FIELD_SETGET(MinMaxCurve, startSize);
                DECLARE_FIELD_SETGET(float, startSizeMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, startSizeX);
                DECLARE_FIELD_SETGET(float, startSizeXMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, startSizeY);
                DECLARE_FIELD_SETGET(float, startSizeYMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, startSizeZ);
                DECLARE_FIELD_SETGET(float, startSizeZMultiplier);
                DECLARE_FIELD_SETGET(bool, startRotation3D);
                DECLARE_FIELD_SETGET(MinMaxCurve, startRotation);
                DECLARE_FIELD_SETGET(float, startRotationMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, startRotationX);
                DECLARE_FIELD_SETGET(float, startRotationXMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, startRotationY);
                DECLARE_FIELD_SETGET(float, startRotationYMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, startRotationZ);
                DECLARE_FIELD_SETGET(float, startRotationZMultiplier);
                DECLARE_FIELD_SETGET(float, flipRotation);
                DECLARE_FIELD_SETGET(MinMaxGradient, startColor);
                DECLARE_FIELD_SETGET(GravitySource, gravitySource);
                DECLARE_FIELD_SETGET(MinMaxCurve, gravityModifier);
                DECLARE_FIELD_SETGET(float, gravityModifierMultiplier);
                DECLARE_FIELD_SETGET(SimulationSpace, simulationSpace);
                DECLARE_FIELD_SETGET(UnityEngine::Transform*, customSimulationSpace);
                DECLARE_FIELD_SETGET(float, simulationSpeed);
                DECLARE_FIELD_SETGET(bool, useUnscaledTime);
                DECLARE_FIELD_SETGET(ScalingMode, scalingMode);
                DECLARE_FIELD_SETGET(bool, playOnAwake);
                DECLARE_FIELD_SETGET(int, maxParticles);
                DECLARE_FIELD_SETGET(EmitterVelocityMode, emitterVelocityMode);
                DECLARE_FIELD_SETGET(StopAction, stopAction);
                DECLARE_FIELD_SETGET(RingBufferMode, ringBufferMode);
                DECLARE_FIELD_SETGET(UnityEngine::Vector2, ringBufferLoopRange);
                DECLARE_FIELD_SETGET(CullingMode, cullingMode);
            };

            struct EmissionModule {
                DECLARE_FIELD_SETGET(bool, enabled);
                DECLARE_FIELD_SETGET(MinMaxCurve, rateOverTime);
                DECLARE_FIELD_SETGET(float, rateOverTimeMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, rateOverDistance);
                DECLARE_FIELD_SETGET(float, rateOverDistanceMultiplier);
                Burst GetBurst(UnityEngine::ParticleSystem* particleSystem, int index);
                void SetBurst(UnityEngine::ParticleSystem* particleSystem, int index, Burst burst);
                DECLARE_FIELD_SETGET(int, burstCount);
            };

            struct ShapeModule {
                DECLARE_FIELD_SETGET(bool, enabled);
                DECLARE_FIELD_SETGET(ShapeType, shapeType);
                DECLARE_FIELD_SETGET(float, randomDirectionAmount);
                DECLARE_FIELD_SETGET(float, sphericalDirectionAmount);
                DECLARE_FIELD_SETGET(float, randomPositionAmount);
                DECLARE_FIELD_SETGET(bool, alignToDirection);
                DECLARE_FIELD_SETGET(float, radius);
                DECLARE_FIELD_SETGET(ShapeMultiModeValue, radiusMode);
                DECLARE_FIELD_SETGET(float, radiusSpread);
                DECLARE_FIELD_SETGET(MinMaxCurve, radiusSpeed);
                DECLARE_FIELD_SETGET(float, radiusSpeedMultiplier);
                DECLARE_FIELD_SETGET(float, radiusThickness);
                DECLARE_FIELD_SETGET(float, angle);
                DECLARE_FIELD_SETGET(float, length);
                DECLARE_FIELD_SETGET(UnityEngine::Vector3, boxThickness);
                DECLARE_FIELD_SETGET(MeshShapeType, meshShapeType);
                DECLARE_FIELD_SETGET(UnityEngine::Mesh*, mesh);
                DECLARE_FIELD_SETGET(UnityEngine::MeshRenderer*, meshRenderer);
                DECLARE_FIELD_SETGET(UnityEngine::SkinnedMeshRenderer*, skinnedMeshRenderer);
                DECLARE_FIELD_SETGET(UnityEngine::Sprite*, sprite);
                DECLARE_FIELD_SETGET(UnityEngine::SpriteRenderer*, spriteRenderer);
                DECLARE_FIELD_SETGET(bool, useMeshMaterialIndex);
                DECLARE_FIELD_SETGET(int, meshMaterialIndex);
                DECLARE_FIELD_SETGET(bool, useMeshColors);
                DECLARE_FIELD_SETGET(float, normalOffset);
                DECLARE_FIELD_SETGET(ShapeMultiModeValue, meshSpawnMode);
                DECLARE_FIELD_SETGET(float, meshSpawnSpread);
                DECLARE_FIELD_SETGET(MinMaxCurve, meshSpawnSpeed);
                DECLARE_FIELD_SETGET(float, meshSpawnSpeedMultiplier);
                DECLARE_FIELD_SETGET(float, arc);
                DECLARE_FIELD_SETGET(ShapeMultiModeValue, arcMode);
                DECLARE_FIELD_SETGET(float, arcSpread);
                DECLARE_FIELD_SETGET(MinMaxCurve, arcSpeed);
                DECLARE_FIELD_SETGET(float, arcSpeedMultiplier);
                DECLARE_FIELD_SETGET(float, donutRadius);
                DECLARE_FIELD_SETGET(UnityEngine::Vector3, position);
                DECLARE_FIELD_SETGET(UnityEngine::Vector3, rotation);
                DECLARE_FIELD_SETGET(UnityEngine::Vector3, scale);
                DECLARE_FIELD_SETGET(UnityEngine::Texture2D*, texture);
                DECLARE_FIELD_SETGET(ShapeTextureChannel, textureClipChannel);
                DECLARE_FIELD_SETGET(float, textureClipThreshold);
                DECLARE_FIELD_SETGET(bool, textureColorAffectsParticles);
                DECLARE_FIELD_SETGET(bool, textureAlphaAffectsParticles);
                DECLARE_FIELD_SETGET(bool, textureBilinearFiltering);
                DECLARE_FIELD_SETGET(int, textureUVChannel);
            };

            struct CollisionModule {
                DECLARE_FIELD_SETGET(bool, enabled);
                DECLARE_FIELD_SETGET(CollisionType, type);
                DECLARE_FIELD_SETGET(CollisionMode, mode);
                DECLARE_FIELD_SETGET(MinMaxCurve, dampen);
                DECLARE_FIELD_SETGET(float, dampenMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, bounce);
                DECLARE_FIELD_SETGET(float, bounceMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, lifetimeLoss);
                DECLARE_FIELD_SETGET(float, lifetimeLossMultiplier);
                DECLARE_FIELD_SETGET(float, minKillSpeed);
                DECLARE_FIELD_SETGET(float, maxKillSpeed);
                DECLARE_FIELD_SETGET(UnityEngine::LayerMask, collidesWith);
                DECLARE_FIELD_SETGET(bool, enableDynamicColliders);
                DECLARE_FIELD_SETGET(int, maxCollisionShapes);
                DECLARE_FIELD_SETGET(CollisionQuality, quality);
                DECLARE_FIELD_SETGET(float, voxelSize);
                DECLARE_FIELD_SETGET(float, radiusScale);
                DECLARE_FIELD_SETGET(bool, sendCollisionMessages);
                DECLARE_FIELD_SETGET(float, colliderForce);
                DECLARE_FIELD_SETGET(bool, multiplyColliderForceByCollisionAngle);
                DECLARE_FIELD_SETGET(bool, multiplyColliderForceByParticleSpeed);
                DECLARE_FIELD_SETGET(bool, multiplyColliderForceByParticleSize);
                void AddPlane(UnityEngine::ParticleSystem* particleSystem, UnityEngine::Transform* transform);
                void RemovePlane(UnityEngine::ParticleSystem* particleSystem, int index);
                void RemovePlaneObject(UnityEngine::ParticleSystem* particleSystem, UnityEngine::Transform* transform);
                void SetPlane(UnityEngine::ParticleSystem* particleSystem, int index, UnityEngine::Transform* transform);
                UnityEngine::Transform* GetPlane(UnityEngine::ParticleSystem* particleSystem, int index);
                int get_planeCount(UnityEngine::ParticleSystem* particleSystem);
                DECLARE_FIELD_SETGET(bool, enableInteriorCollisions);
            };

            struct TriggerModule {
                DECLARE_FIELD_SETGET(bool, enabled);
                DECLARE_FIELD_SETGET(OverlapAction, inside);
                DECLARE_FIELD_SETGET(OverlapAction, outside);
                DECLARE_FIELD_SETGET(OverlapAction, enter);
                DECLARE_FIELD_SETGET(OverlapAction, exit);
                DECLARE_FIELD_SETGET(ColliderQueryMode, colliderQueryMode);
                DECLARE_FIELD_SETGET(float, radiusScale);
                void AddCollider(UnityEngine::ParticleSystem* particleSystem, UnityEngine::Component* collider);
                void RemoveCollider(UnityEngine::ParticleSystem* particleSystem, int index);
                void RemoveColliderObject(UnityEngine::ParticleSystem* particleSystem, UnityEngine::Component* component);
                void SetCollider(UnityEngine::ParticleSystem* particleSystem, int index, UnityEngine::Component* collider);
                UnityEngine::Component* GetCollider(UnityEngine::ParticleSystem* particleSystem, int index);
                int get_colliderCount(UnityEngine::ParticleSystem* particleSystem);
            };

            struct SubEmittersModule {
                DECLARE_FIELD_SETGET(bool, enabled);
                int get_subEmittersCount(UnityEngine::ParticleSystem* particleSystem);
                void AddSubEmitter(UnityEngine::ParticleSystem* particleSystem, UnityEngine::ParticleSystem* subEmitter, SubEmitterType type, SubEmitterProperties properties, float emitProbability = 1.0f);
                void RemoveSubEmitter(UnityEngine::ParticleSystem* particleSystem, int index);
                void RemoveSubEmitterObject(UnityEngine::ParticleSystem* particleSystem, UnityEngine::ParticleSystem* subEmitter);
                void SetSubEmitterSystem(UnityEngine::ParticleSystem* particleSystem, int index, UnityEngine::ParticleSystem* subEmitter);
                void SetSubEmitterType(UnityEngine::ParticleSystem* particleSystem, int index, SubEmitterType type);
                void SetSubEmitterProperties(UnityEngine::ParticleSystem* particleSystem, int index, SubEmitterProperties properties);
                void SetSubEmitterEmitProbability(UnityEngine::ParticleSystem* particleSystem, int index, float emitProbability);
                UnityEngine::ParticleSystem* GetSubEmitterSystem(UnityEngine::ParticleSystem* particleSystem, int index);
                SubEmitterType GetSubEmitterType(UnityEngine::ParticleSystem* particleSystem, int index);
                SubEmitterProperties GetSubEmitterProperties(UnityEngine::ParticleSystem* particleSystem, int index);
                float GetSubEmitterEmitProbability(UnityEngine::ParticleSystem* particleSystem, int index);
            };

            struct TextureSheetAnimationModule {
                DECLARE_FIELD_SETGET(bool, enabled);
                DECLARE_FIELD_SETGET(AnimationMode, mode);
                DECLARE_FIELD_SETGET(AnimationTimeMode, timeMode);
                DECLARE_FIELD_SETGET(float, fps);
                DECLARE_FIELD_SETGET(int, numTilesX);
                DECLARE_FIELD_SETGET(int, numTilesY);
                DECLARE_FIELD_SETGET(AnimationType, animation);
                DECLARE_FIELD_SETGET(AnimationRowMode, rowMode);
                DECLARE_FIELD_SETGET(MinMaxCurve, frameOverTime);
                DECLARE_FIELD_SETGET(float, frameOverTimeMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, startFrame);
                DECLARE_FIELD_SETGET(float, startFrameMultiplier);
                DECLARE_FIELD_SETGET(int, cycleCount);
                DECLARE_FIELD_SETGET(int, rowIndex);
                DECLARE_FIELD_SETGET(UnityEngine::Rendering::UVChannelFlags, uvChannelMask);
                int get_spriteCount(UnityEngine::ParticleSystem* particleSystem);
                DECLARE_FIELD_SETGET(UnityEngine::Vector2, speedRange);
                void AddSprite(UnityEngine::ParticleSystem* particleSystem, UnityEngine::Sprite* sprite);
                void RemoveSprite(UnityEngine::ParticleSystem* particleSystem, int index);
                void SetSprite(UnityEngine::ParticleSystem* particleSystem, int index, UnityEngine::Sprite* sprite);
                UnityEngine::Sprite* GetSprite(UnityEngine::ParticleSystem* particleSystem, int index);
            };

            struct VelocityOverLifetimeModule {
                DECLARE_FIELD_SETGET(bool, enabled);
                DECLARE_FIELD_SETGET(MinMaxCurve, x);
                DECLARE_FIELD_SETGET(MinMaxCurve, y);
                DECLARE_FIELD_SETGET(MinMaxCurve, z);
                DECLARE_FIELD_SETGET(float, xMultiplier);
                DECLARE_FIELD_SETGET(float, yMultiplier);
                DECLARE_FIELD_SETGET(float, zMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, orbitalX);
                DECLARE_FIELD_SETGET(MinMaxCurve, orbitalY);
                DECLARE_FIELD_SETGET(MinMaxCurve, orbitalZ);
                DECLARE_FIELD_SETGET(float, orbitalXMultiplier);
                DECLARE_FIELD_SETGET(float, orbitalYMultiplier);
                DECLARE_FIELD_SETGET(float, orbitalZMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, orbitalOffsetX);
                DECLARE_FIELD_SETGET(MinMaxCurve, orbitalOffsetY);
                DECLARE_FIELD_SETGET(MinMaxCurve, orbitalOffsetZ);
                DECLARE_FIELD_SETGET(float, orbitalOffsetXMultiplier);
                DECLARE_FIELD_SETGET(float, orbitalOffsetYMultiplier);
                DECLARE_FIELD_SETGET(float, orbitalOffsetZMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, radial);
                DECLARE_FIELD_SETGET(float, radialMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, speedModifier);
                DECLARE_FIELD_SETGET(float, speedModifierMultiplier);
                DECLARE_FIELD_SETGET(SimulationSpace, space);
            };

            struct LimitVelocityOverLifetimeModule {
                DECLARE_FIELD_SETGET(bool, enabled);
                DECLARE_FIELD_SETGET(MinMaxCurve, limitX);
                DECLARE_FIELD_SETGET(float, limitXMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, limitY);
                DECLARE_FIELD_SETGET(float, limitYMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, limitZ);
                DECLARE_FIELD_SETGET(float, limitZMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, limit);
                DECLARE_FIELD_SETGET(float, limitMultiplier);
                DECLARE_FIELD_SETGET(float, dampen);
                DECLARE_FIELD_SETGET(bool, separateAxes);
                DECLARE_FIELD_SETGET(SimulationSpace, space);
                DECLARE_FIELD_SETGET(MinMaxCurve, drag);
                DECLARE_FIELD_SETGET(float, dragMultiplier);
                DECLARE_FIELD_SETGET(bool, multiplyDragByParticleSize);
                DECLARE_FIELD_SETGET(bool, multiplyDragByParticleVelocity);
            };

            struct InheritVelocityModule {
                DECLARE_FIELD_SETGET(bool, enabled);
                DECLARE_FIELD_SETGET(InheritVelocityMode, mode);
                DECLARE_FIELD_SETGET(MinMaxCurve, curve);
                DECLARE_FIELD_SETGET(float, curveMultiplier);
            };

            struct LifetimeByEmitterSpeedModule {
                DECLARE_FIELD_SETGET(bool, enabled);
                DECLARE_FIELD_SETGET(MinMaxCurve, curve);
                DECLARE_FIELD_SETGET(float, curveMultiplier);
                DECLARE_FIELD_SETGET(UnityEngine::Vector2, range);
            };

            struct ForceOverLifetimeModule {
                DECLARE_FIELD_SETGET(bool, enabled);
                DECLARE_FIELD_SETGET(MinMaxCurve, x);
                DECLARE_FIELD_SETGET(MinMaxCurve, y);
                DECLARE_FIELD_SETGET(MinMaxCurve, z);
                DECLARE_FIELD_SETGET(float, xMultiplier);
                DECLARE_FIELD_SETGET(float, yMultiplier);
                DECLARE_FIELD_SETGET(float, zMultiplier);
                DECLARE_FIELD_SETGET(SimulationSpace, space);
                DECLARE_FIELD_SETGET(bool, randomized);
            };

            struct ColorOverLifetimeModule {
                DECLARE_FIELD_SETGET(bool, enabled);
                DECLARE_FIELD_SETGET(MinMaxGradient, color);
            };

            struct ColorBySpeedModule {
                DECLARE_FIELD_SETGET(bool, enabled);
                DECLARE_FIELD_SETGET(MinMaxGradient, color);
                DECLARE_FIELD_SETGET(UnityEngine::Vector2, range);
            };

            struct SizeOverLifetimeModule {
                DECLARE_FIELD_SETGET(bool, enabled);
                DECLARE_FIELD_SETGET(MinMaxCurve, size);
                DECLARE_FIELD_SETGET(float, sizeMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, x);
                DECLARE_FIELD_SETGET(float, xMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, y);
                DECLARE_FIELD_SETGET(float, yMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, z);
                DECLARE_FIELD_SETGET(float, zMultiplier);
                DECLARE_FIELD_SETGET(bool, separateAxes);
            };

            struct SizeBySpeedModule {
                DECLARE_FIELD_SETGET(bool, enabled);
                DECLARE_FIELD_SETGET(MinMaxCurve, size);
                DECLARE_FIELD_SETGET(float, sizeMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, x);
                DECLARE_FIELD_SETGET(float, xMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, y);
                DECLARE_FIELD_SETGET(float, yMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, z);
                DECLARE_FIELD_SETGET(float, zMultiplier);
                DECLARE_FIELD_SETGET(bool, separateAxes);
                DECLARE_FIELD_SETGET(UnityEngine::Vector2, range);
            };

            struct RotationOverLifetimeModule {
                DECLARE_FIELD_SETGET(bool, enabled);
                DECLARE_FIELD_SETGET(MinMaxCurve, x);
                DECLARE_FIELD_SETGET(float, xMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, y);
                DECLARE_FIELD_SETGET(float, yMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, z);
                DECLARE_FIELD_SETGET(float, zMultiplier);
                DECLARE_FIELD_SETGET(bool, separateAxes);
            };

            struct RotationBySpeedModule {
                DECLARE_FIELD_SETGET(bool, enabled);
                DECLARE_FIELD_SETGET(MinMaxCurve, x);
                DECLARE_FIELD_SETGET(float, xMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, y);
                DECLARE_FIELD_SETGET(float, yMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, z);
                DECLARE_FIELD_SETGET(float, zMultiplier);
                DECLARE_FIELD_SETGET(bool, separateAxes);
                DECLARE_FIELD_SETGET(UnityEngine::Vector2, range);
            };

            // struct ExternalForcesModule {
            //     DECLARE_FIELD_SETGET(bool, enabled);
            //     DECLARE_FIELD_SETGET(float, multiplier);
            //     DECLARE_FIELD_SETGET(MinMaxCurve, multiplierCurve);
            //     DECLARE_FIELD_SETGET(GameObjectFilter, influenceFilter);
            //     DECLARE_FIELD_SETGET(UnityEngine::LayerMask, influenceMask);
            //     int get_influenceCount(UnityEngine::ParticleSystem* particleSystem);
            //     bool IsAffectedBy(UnityEngine::ParticleSystem* particleSystem, ParticleControllerForceField field);
            //     void AddInfluence(UnityEngine::ParticleSystem* particleSystem, ParticleControllerForceField field);
            //     void RemoveInfluenceAtIndex(UnityEngine::ParticleSystem* particleSystem, int index);
            //     void RemoveInfluence(UnityEngine::ParticleSystem* particleSystem, ParticleControllerForceField field);
            //     void RemoveAllInfluences(UnityEngine::ParticleSystem* particleSystem);
            //     void SetInfluence(UnityEngine::ParticleSystem* particleSystem, int index, ParticleControllerForceField field);
            //     ParticleControllerForceField GetInfluence(UnityEngine::ParticleSystem* particleSystem, int index);
            // };

            struct NoiseModule {
                DECLARE_FIELD_SETGET(bool, enabled);
                DECLARE_FIELD_SETGET(bool, separateAxes);
                DECLARE_FIELD_SETGET(MinMaxCurve, strength);
                DECLARE_FIELD_SETGET(float, strengthMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, strengthX);
                DECLARE_FIELD_SETGET(float, strengthXMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, strengthY);
                DECLARE_FIELD_SETGET(float, strengthYMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, strengthZ);
                DECLARE_FIELD_SETGET(float, strengthZMultiplier);
                DECLARE_FIELD_SETGET(float, frequency);
                DECLARE_FIELD_SETGET(bool, damping);
                DECLARE_FIELD_SETGET(int, octaveCount);
                DECLARE_FIELD_SETGET(float, octaveMultiplier);
                DECLARE_FIELD_SETGET(float, octaveScale);
                DECLARE_FIELD_SETGET(NoiseQuality, quality);
                DECLARE_FIELD_SETGET(MinMaxCurve, scrollSpeed);
                DECLARE_FIELD_SETGET(float, scrollSpeedMultiplier);
                DECLARE_FIELD_SETGET(bool, remapEnabled);
                DECLARE_FIELD_SETGET(MinMaxCurve, remap);
                DECLARE_FIELD_SETGET(float, remapMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, remapX);
                DECLARE_FIELD_SETGET(float, remapXMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, remapY);
                DECLARE_FIELD_SETGET(float, remapYMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, remapZ);
                DECLARE_FIELD_SETGET(float, remapZMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, positionAmount);
                DECLARE_FIELD_SETGET(MinMaxCurve, rotationAmount);
                DECLARE_FIELD_SETGET(MinMaxCurve, sizeAmount);
            };

            struct LightsModule {
                DECLARE_FIELD_SETGET(bool, enabled);
                DECLARE_FIELD_SETGET(float, ratio);
                DECLARE_FIELD_SETGET(bool, useRandomDistribution);
                DECLARE_FIELD_SETGET(UnityEngine::Light*, light);
                DECLARE_FIELD_SETGET(bool, useParticleColor);
                DECLARE_FIELD_SETGET(bool, sizeAffectsRange);
                DECLARE_FIELD_SETGET(bool, alphaAffectsIntensity);
                DECLARE_FIELD_SETGET(MinMaxCurve, range);
                DECLARE_FIELD_SETGET(float, rangeMultiplier);
                DECLARE_FIELD_SETGET(MinMaxCurve, intensity);
                DECLARE_FIELD_SETGET(float, intensityMultiplier);
                DECLARE_FIELD_SETGET(int, maxLights);
            };

            struct TrailModule {
                DECLARE_FIELD_SETGET(bool, enabled);
                DECLARE_FIELD_SETGET(TrailMode, mode);
                DECLARE_FIELD_SETGET(float, ratio);
                DECLARE_FIELD_SETGET(MinMaxCurve, lifetime);
                DECLARE_FIELD_SETGET(float, lifetimeMultiplier);
                DECLARE_FIELD_SETGET(float, minVertexDistance);
                DECLARE_FIELD_SETGET(TrailTextureMode, textureMode);
                DECLARE_FIELD_SETGET(UnityEngine::Vector2, textureScale);
                DECLARE_FIELD_SETGET(bool, worldSpace);
                DECLARE_FIELD_SETGET(bool, dieWithParticles);
                DECLARE_FIELD_SETGET(bool, sizeAffectsWidth);
                DECLARE_FIELD_SETGET(bool, sizeAffectsLifetime);
                DECLARE_FIELD_SETGET(bool, inheritParticleColor);
                DECLARE_FIELD_SETGET(MinMaxGradient, colorOverLifetime);
                DECLARE_FIELD_SETGET(MinMaxCurve, widthOverTrail);
                DECLARE_FIELD_SETGET(float, widthOverTrailMultiplier);
                DECLARE_FIELD_SETGET(MinMaxGradient, colorOverTrail);
                DECLARE_FIELD_SETGET(bool, generateLightingData);
                DECLARE_FIELD_SETGET(int, ribbonCount);
                DECLARE_FIELD_SETGET(float, shadowBias);
                DECLARE_FIELD_SETGET(bool, splitSubEmitterRibbons);
                DECLARE_FIELD_SETGET(bool, attachRibbonsToTransform);
            };

            // struct {
            //     DECLARE_FIELD_SETGET(bool, enabled);
            //     void SetMode(CustomData stream, CustomDataMode mode);
            //     CustomDataMode GetMode(CustomData stream);
            //     void SetVectorComponentCount(CustomData stream, int count);
            //     int GetVectorComponentCount(CustomData stream);
            //     void SetVector(CustomData stream, int component, MinMaxCurve curve);
            //     MinMaxCurve GetVector(CustomData stream, int component);
            //     void SetColor(CustomData stream, UnityEngine::ParticleSystem::MinMaxGradient gradient);
            //     UnityEngine::ParticleSystem::MinMaxGradient GetColor(CustomData stream);
            // } customData;

            // // Some fields and methods still need be created
    };

}