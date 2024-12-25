#pragma once

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/AudioClip.hpp"
#include "UnityEngine/AudioSource.hpp"
#include "UnityEngine/Networking/UnityWebRequestMultimedia.hpp"
#include "UnityEngine/Networking/UnityWebRequest.hpp"
#include "UnityEngine/Networking/DownloadHandler.hpp"
#include <vector>
#include <string>

namespace MenuMusic {
    class MusicLoader {
    private:
        UnityEngine::AudioClip* originalClip;
        UnityEngine::AudioClip* customClip;

        void audioClipCompleted(::UnityW<UnityEngine::AudioClip> audioClip);

        std::vector<std::string> songData;

    public:
        void set_OriginalClip(UnityEngine::AudioClip* clip);
        UnityEngine::AudioClip* get_OriginalClip();
        void InitializeSongs();
        void LoadCustomMusic();
        bool isCustomMusicLoaded();
        UnityEngine::GameObject* audioClipGO;
        UnityEngine::AudioSource* audioSource;
        UnityEngine::AudioSource* OriginalAudioSource = nullptr;
        //void set_OriginalClip(UnityEngine::AudioClip* OriginalAudioClip);
        UnityEngine::AudioClip* getClip();
        MusicLoader() : originalClip(nullptr), customClip(nullptr) {}
    };

    extern MusicLoader menuMusicLoader;
}
