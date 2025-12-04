#include "Menu/snowprimitives.hpp"
#include "main.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/Color.hpp"
#include "UnityEngine/PrimitiveType.hpp"
#include "UnityEngine/SphereCollider.hpp"
#include "UnityEngine/MeshCollider.hpp"
#include "UnityEngine/MeshRenderer.hpp"
#include "UnityEngine/Material.hpp"

//using namespace GlobalNamespace;
using namespace UnityEngine;

namespace Christmas::snowPrimitives {

    SafePtrUnity<GameObject> snowPrimitives;

    void CreateSnowPrimitives() {
        // Don't create snow primitives if already created
        if(snowPrimitives) return;

        // Create an object to contain all of the spheres
        snowPrimitives = GameObject::New_ctor("SnowPrimitives");
        snowPrimitives->transform->parent = GameObject::Find("DefaultMenuEnvironment")->transform;

        // Create a white sphere template
        GameObject* whiteSphere = GameObject::CreatePrimitive(PrimitiveType::Sphere);
        whiteSphere->transform->parent = snowPrimitives->transform;
        whiteSphere->GetComponent<MeshRenderer*>()->material = GameObject::Find("Note")->GetComponent<MeshRenderer*>()->material;
        Object::DestroyImmediate(whiteSphere->GetComponent<SphereCollider*>());
        MeshCollider* whiteSphereCollider = whiteSphere->AddComponent<MeshCollider*>();
        whiteSphereCollider->convex = true;

        // Create a black sphere template
        GameObject* blackSphere = GameObject::CreatePrimitive(PrimitiveType::Sphere);
        blackSphere->transform->parent = snowPrimitives->transform;
        Material* blackMaterial = blackSphere->GetComponent<MeshRenderer*>()->material;
        blackMaterial->SetColor("_Color", Color(0.0f, 0.0f, 0.0f, 1.0f));
        blackMaterial->SetFloat("_Glossiness", 0.0f);
        blackMaterial->SetFloat("_Metallic", 1.0f);

        // Create a function that automatically duplicated a sphere template based on a position and size
        std::function<void(GameObject*, Vector3, Vector3)> CreateSphere = [](GameObject* templateSphere, Vector3 position, Vector3 size){
            GameObject* newSphere = GameObject::Instantiate(templateSphere);
            newSphere->transform->parent = snowPrimitives->transform;
            newSphere->transform->position = Vector3(position.x / 2.0f, position.y / 2.0f, position.z / 2.0f); // Division by 2 is to fix the mistake of not realizing that Blender's cube is 2x2x2 while Unity's is 1x1x1 without retyping all the coordinates. It's not lazy, it's called taking shortcuts because this mod is supposed to be released in just a few hours
            newSphere->transform->localScale = size;
        };

        // Create a bunch of lumps of snow on the ground
        CreateSphere(whiteSphere, Vector3(-5.5f, -1.3f, 16.1f), Vector3(10.0f, 2.0f, 10.0f)); // 0
        CreateSphere(whiteSphere, Vector3(16.4f, -1.3f, 0.0f), Vector3(10.0f, 2.0f, 10.0f)); // 1
        CreateSphere(whiteSphere, Vector3(6.5f, -1.3f, 16.4f), Vector3(10.0f, 2.0f, 10.0f)); // 2
        CreateSphere(whiteSphere, Vector3(15.9f, -1.0f, 10.8f), Vector3(10.0f, 2.0f, 10.0f)); // 3
        CreateSphere(whiteSphere, Vector3(-18.3f, -0.8f, -11.4f), Vector3(10.0f, 2.0f, 10.0f)); // 4
        CreateSphere(whiteSphere, Vector3(-9.0f, -1.7f, -7.7f), Vector3(10.0f, 2.0f, 10.0f)); // 5
        CreateSphere(whiteSphere, Vector3(-18.1f, -1.3f, 2.7f), Vector3(10.0f, 2.0f, 10.0f)); // 6
        CreateSphere(whiteSphere, Vector3(-2.5f, -1.3f, -14.2f), Vector3(10.0f, 2.0f, 10.0f)); // 7
        CreateSphere(whiteSphere, Vector3(-15.7f, -1.3f, 12.0f), Vector3(10.0f, 2.0f, 10.0f)); // 8
        CreateSphere(whiteSphere, Vector3(10.0f, -1.3f, -10.5f), Vector3(10.0f, 2.0f, 10.0f)); // 9
        CreateSphere(whiteSphere, Vector3(-15.1f, -1.3f, 26.5f), Vector3(14.7f, 3.0f, 14.7f)); // 10
        CreateSphere(whiteSphere, Vector3(25.4f, -0.9f, -15.5f), Vector3(14.7f, 3.7f, 14.7f)); // 11
        CreateSphere(whiteSphere, Vector3(7.0f, -1.3f, 29.5f), Vector3(14.7f, 3.0f, 14.7f)); // 12
        CreateSphere(whiteSphere, Vector3(29.9f, -1.3f, 19.2f), Vector3(14.7f, 3.0f, 14.7f)); // 13
        CreateSphere(whiteSphere, Vector3(34.4f, -1.3f, 0.5f), Vector3(14.7f, 3.0f, 14.7f)); // 14
        CreateSphere(whiteSphere, Vector3(-34.3f, -0.9f, 16.6f), Vector3(14.7f, 3.7f, 14.7f)); // 15
        CreateSphere(whiteSphere, Vector3(-36.0f, -1.3f, -6.0f), Vector3(14.7f, 3.0f, 14.7f)); // 16
        CreateSphere(whiteSphere, Vector3(-15.2f, -1.3f, -25.3f), Vector3(14.7f, 3.0f, 14.7f)); // 17
        CreateSphere(whiteSphere, Vector3(7.9f, -1.3f, -30.2f), Vector3(14.7f, 3.0f, 14.7f)); // 18
        CreateSphere(whiteSphere, Vector3(-25.8f, -0.7f, 7.0f), Vector3(10.0f, 2.0f, 10.0f)); // 19

        // Remove the template spheres
        GameObject::Destroy(whiteSphere);
        GameObject::Destroy(blackSphere);

    }

    void DestroySnowPrimitives() {
        GameObject::Destroy(snowPrimitives->gameObject);
    }

}