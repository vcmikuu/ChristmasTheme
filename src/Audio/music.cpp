#include "Audio/music.hpp"
#include "UnityEngine/AudioClip.hpp"
#include "UnityEngine/Networking/UnityWebRequestAsyncOperation.hpp"
//#include "UnityEngine/Networking/UnityWebRequestMultimedia.hpp"
#include "UnityEngine/Networking/UnityWebRequest.hpp"
//#include "UnityEngine/Networking/DownloadHandlerAudioClip.hpp"  // Achte darauf, dass dieser Header eingebunden wird
#include "assets.hpp"
#include "custom-types/shared/coroutine.hpp"
#include "custom-types/shared/macros.hpp"
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <cstdint>
#include <coroutine>

// used questsound imports that it works i had trouble O_O

#include "UnityEngine/Networking/DownloadHandlerAudioClip.hpp"
#include "UnityEngine/Networking/UnityWebRequestMultimedia.hpp"
using namespace UnityEngine::Networking;

#include "System/Threading/Tasks/TaskStatus.hpp"
#include "System/Threading/Tasks/Task.hpp"
#include "System/Threading/Tasks/Task_1.hpp"
#include "System/Action_1.hpp"
using namespace System;

#include "UnityEngine/AudioType.hpp"
#include "UnityEngine/AsyncOperation.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/WaitForSeconds.hpp"
using namespace UnityEngine;

std::string to_base64(const std::vector<uint8_t>& data) {
    static const char* chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string base64;
    int val = 0, valb = -6;
    for (uint8_t c : data) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            base64.push_back(chars[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) base64.push_back(chars[((val << 8) >> (valb + 8)) & 0x3F]);
    while (base64.size() % 4) base64.push_back('=');
    return base64;
}

namespace MenuMusic {
    MusicLoader menuMusicLoader;


    bool MusicLoader::isCustomMusicLoaded() {
        return customClip != nullptr;
    }

    //AudioClip* OriginalAudioClip
    //UnityEngine::AudioClip* clip
    void MusicLoader::set_OriginalClip(AudioClip* OriginalAudioClip) {
        if (OriginalAudioClip != nullptr)
        {
            static auto goName = ConstString("OrigAudioClipGO");
            GameObject* audioClipGO = GameObject::New_ctor(goName);
            OriginalAudioSource = audioClipGO->AddComponent<AudioSource*>();
            OriginalAudioSource->set_playOnAwake(false);
            OriginalAudioSource->set_clip(OriginalAudioClip);
            UnityEngine::Object::DontDestroyOnLoad(audioClipGO);
            //getLogger().debug("Saved Original AudioClip");
        }
        // Finished
        //originalClip = clip;
    }

    UnityEngine::AudioClip* MusicLoader::get_OriginalClip() {
        if (OriginalAudioSource != nullptr)
        {
            return OriginalAudioSource->get_clip();
        }
        else
        {
            return nullptr;
        }
        //return customClip ? customClip : originalClip;
    }

    UnityEngine::AudioClip* MusicLoader::getClip() {
        return audioSource->get_clip();
    }


    void MusicLoader::audioClipCompleted(::UnityW<UnityEngine::AudioClip> audioClip)
    {
        //getLogger().info("Starting Stage 2");

        if(audioClip)
        {  
            ///getLogger().info("audioClip is not nullptr setting it to AudioSource for filepath {}", filePath);
            if (!this->audioClipGO) {
                static auto goName = ConstString("AudioClipGO");
                audioClipGO = GameObject::New_ctor(goName);
                audioSource = audioClipGO->AddComponent<AudioSource*>();
                UnityEngine::Object::DontDestroyOnLoad(audioClipGO);
            }
            audioSource->set_playOnAwake(false);
            audioSource->set_clip(audioClip);
            audioSource->set_volume(0.6f);
        }
        else {
            //getLogger().error("Stage 2 failed with audioClip being nullptr {} Object path: {}", fmt::ptr(audioClip.convert()), filePath);
            return;
        }
    }

    void MusicLoader::InitializeSongs() {
        songData.clear();

        songData.emplace_back(to_base64(std::vector<uint8_t>(static_cast<ArrayW<uint8_t>>(IncludedAssets::carolofthebells_ogg).begin(),
                                                          static_cast<ArrayW<uint8_t>>(IncludedAssets::carolofthebells_ogg).end())));

        songData.emplace_back(to_base64(std::vector<uint8_t>(static_cast<ArrayW<uint8_t>>(IncludedAssets::christmasspirit_ogg).begin(),
                                                          static_cast<ArrayW<uint8_t>>(IncludedAssets::christmasspirit_ogg).end())));

        songData.emplace_back(to_base64(std::vector<uint8_t>(static_cast<ArrayW<uint8_t>>(IncludedAssets::deckthehalls_ogg).begin(),
                                                          static_cast<ArrayW<uint8_t>>(IncludedAssets::deckthehalls_ogg).end())));

        songData.emplace_back(to_base64(std::vector<uint8_t>(static_cast<ArrayW<uint8_t>>(IncludedAssets::jinglebells_ogg).begin(),
                                                          static_cast<ArrayW<uint8_t>>(IncludedAssets::jinglebells_ogg).end())));
    }

    void MusicLoader::LoadCustomMusic() {
        if (isCustomMusicLoaded()) {
            return;
        }

        if (songData.empty()) {
            InitializeSongs();
        }

        srand(static_cast<unsigned>(time(nullptr)));
        std::string selectedSong = songData[rand() % songData.size()];

        std::string filePath = "data:audio/ogg;base64," + selectedSong;

        auto webRequest = UnityEngine::Networking::UnityWebRequestMultimedia::GetAudioClip(filePath, UnityEngine::AudioType::OGGVORBIS);

        webRequest->SendWebRequest();

        if (webRequest->get_result() == UnityEngine::Networking::UnityWebRequest::Result::Success) {
            auto downloadHandler = static_cast<UnityEngine::Networking::DownloadHandlerAudioClip*>(webRequest->get_downloadHandler());
            customClip = downloadHandler->GetContent(webRequest);

            if (customClip) {
                customClip->set_name("CustomMenuMusic");
            } else {
                //
            }
        } else {
            //
        }
    }
}

