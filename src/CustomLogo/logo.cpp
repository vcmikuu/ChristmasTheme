#include "CustomLogo/logo.hpp"
#include "bsml/shared/BSML-Lite/Creation/Image.hpp"

namespace Christmas::chLogo {

    void LoadLogo() {
        // Disable Logo
        DisableOriginalLogo();

        // Wrong position and scale !!
        cLogo = BSML::Lite::CreateFloatingScreen(UnityEngine::Vector2(0, 0), UnityEngine::Vector3(0, 0, 0), UnityEngine::Vector3(0, 0, 0), 0.0f, false, false);

        cLogo->GetComponent<UnityEngine::Canvas*>()->set_sortingOrder(0);

        // Set Image (WE DO NOT HAVE AN IMAGE O_O)
        // HMUI::ImageView* imgFile = BSML::Lite::CreateImage(cLogo->get_transform(), IMAGE HERE, { 0, 0 }, { 0, 0 }); // Scale isn't set !!
    }

    void ReloadLogo() {
        UnityEngine::Object::Destroy(cLogo->get_gameObject());
        LoadLogo();
    }
    
    void DisableOriginalLogo() {
        logo = UnityEngine::GameObject::Find("Logo");
        logo->SetActive(false);
    }

}