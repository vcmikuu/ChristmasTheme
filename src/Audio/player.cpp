#include "Audio/player.hpp"
#include "paper/shared/logger.hpp"
#include <random>
#include "main.hpp"
#include <array>
#include "custom-types/shared/delegate.hpp"
#include "UnityEngine/Audio/AudioMixer.hpp"


std::vector<std::string> songList = {
    "/sdcard/ModData/com.beatgames.beatsaber/Mods/Christmas/carolofthebells.ogg",
    "/sdcard/ModData/com.beatgames.beatsaber/Mods/Christmas/jinglebells.ogg",
    "/sdcard/ModData/com.beatgames.beatsaber/Mods/Christmas/christmasspirit.ogg",
    "/sdcard/ModData/com.beatgames.beatsaber/Mods/Christmas/deckthehalls.ogg"
};

void PlayRandomSong(GlobalNamespace::SongPreviewPlayer* songPreviewPlayer) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, songList.size() - 1);
    std::string selectedSong = songList[dis(gen)];

    if (!fileexists(selectedSong)) {
        return;
    }

    auto loadAudioFileTask = GlobalNamespace::MediaAsyncLoader::New_ctor()->LoadAudioClipFromFilePathAsync(selectedSong);
    loadAudioFileTask->GetAwaiter().OnCompleted(custom_types::MakeDelegate<System::Action*>(std::function([songPreviewPlayer, selectedSong, loadAudioFileTask]() {
        songPreviewPlayer->_defaultAudioClip = loadAudioFileTask->get_Result();
        
                
        UnityEngine::AudioSource* audioSource = songPreviewPlayer->GetComponent<UnityEngine::AudioSource*>();

        UnityEngine::Audio::AudioMixer* audioMixer = songPreviewPlayer->GetComponent<UnityEngine::Audio::AudioMixer*>();

    })));
}


