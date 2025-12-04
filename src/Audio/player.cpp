#include "Audio/player.hpp"
#include "main.hpp"

#include "GlobalNamespace/MediaAsyncLoader.hpp"

#include "System/Threading/Tasks/Tasks.hpp"

#include "custom-types/shared/delegate.hpp"

#include <random>
#include <array>


std::vector<std::string> songPathList = {
    "/sdcard/ModData/com.beatgames.beatsaber/Mods/Christmas/carolofthebells.ogg",
    "/sdcard/ModData/com.beatgames.beatsaber/Mods/Christmas/jinglebells.ogg",
    "/sdcard/ModData/com.beatgames.beatsaber/Mods/Christmas/christmasspirit.ogg",
    "/sdcard/ModData/com.beatgames.beatsaber/Mods/Christmas/deckthehalls.ogg"
};

void PlayRandomSong(GlobalNamespace::SongPreviewPlayer* songPreviewPlayer) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, songPathList.size() - 1);
    std::string selectedSongPath = songPathList[dis(gen)];

    if (!fileexists(selectedSongPath)) {
        return;
    }

    auto loadSongTask = GlobalNamespace::MediaAsyncLoader::New_ctor()->LoadAudioClipFromFilePathAsync(selectedSongPath);
    loadSongTask->GetAwaiter().OnCompleted(custom_types::MakeDelegate<System::Action*>(std::function([songPreviewPlayer, loadSongTask]() {
        songPreviewPlayer->_defaultAudioClip = loadSongTask->get_Result();
    })));
}


