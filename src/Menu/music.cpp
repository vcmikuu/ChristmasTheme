#include "Menu/music.hpp"
#include "UnityEngine/AudioSource.hpp"
#include "UnityEngine/AudioClip.hpp"
#include "UnityEngine/GameObject.hpp"
#include "custom-types/shared/delegate.hpp"
#include "bsml/shared/BSML/SharedCoroutineStarter.hpp"
#include "assets.hpp"

using namespace UnityEngine;

namespace MenuMusic {
    MusicLoader menuMusicLoader;

    void MusicLoader::set_OriginalClip(UnityEngine::AudioClip* clip) {
        if (!originalClip) {
            originalClip = clip;
        }
    }

    UnityEngine::AudioClip* MusicLoader::getClip() {
        return customClip;
    }

    UnityEngine::AudioClip* MusicLoader::get_OriginalClip() {
        return originalClip;
    }

    void MusicLoader::loadEmbeddedOgg() {
        if (customClip) return;

        auto oggData = static_cast<ArrayW<uint8_t>>(IncludedAssets::example_ogg);

        customClip = AudioClip::Create("CustomMenuMusic", oggData.size(), 1, 44100, false);

        customClip->SetData(reinterpret_cast<float*>(oggData.begin()), oggData.size() / sizeof(float));
    }

    void MusicLoader::playCustomClip() {
        if (!customClip) {
            loadEmbeddedOgg();
        }

        GameObject* musicPlayer = GameObject::New_ctor("CustomMusicPlayer");
        AudioSource* audioSource = musicPlayer->AddComponent<AudioSource*>();
        audioSource->set_clip(customClip);
        audioSource->set_playOnAwake(true);
        audioSource->Play();
    }
}
