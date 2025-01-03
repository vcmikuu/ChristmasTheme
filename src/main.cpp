#include "main.hpp"


#include "GlobalNamespace/NoteController.hpp"
#include "GlobalNamespace/NoteData.hpp"
#include "GlobalNamespace/GameNoteController.hpp"
#include "GlobalNamespace/FlickeringNeonSign.hpp"
#include "GlobalNamespace/GameServerLobbyFlowCoordinator.hpp"
#include "GlobalNamespace/MultiplayerModeSelectionFlowCoordinator.hpp"
#include "GlobalNamespace/LightWithIdManager.hpp"
#include "GlobalNamespace/MainMenuViewController.hpp"
#include "GlobalNamespace/MediaAsyncLoader.hpp"


#include "Menu/ObjectInstances.hpp"

#include "Audio/player.hpp"

#include "GlobalNamespace/SongPreviewPlayer.hpp"
#include "UnityEngine/AudioSource.hpp"
#include "UnityEngine/AudioClip.hpp"
#include "custom-types/shared/macros.hpp"

#include "UnityEngine/Time.hpp"
#include "UnityEngine/Renderer.hpp"
#include "UnityEngine/SceneManagement/SceneManager.hpp"
#include "UnityEngine/SceneManagement/SceneManagement.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/SpriteRenderer.hpp"

#include "System/Threading/Tasks/Tasks.hpp"

#include "Block/colorchanger.hpp"
#include "Snowflakes/snowflakes.hpp"
#include "Menu/customlogo.hpp"
#include "Menu/snowprimitives.hpp"



#include "c.hpp"

#include "scotland2/shared/modloader.h"


using namespace GlobalNamespace;
using namespace UnityEngine;


static modloader::ModInfo modInfo{MOD_ID, VERSION, 0};
// Stores the ID and version of our mod, and is sent to
// the modloader upon startup

// static std::shared_ptr<cColor::ColorChanger> colorChanger;

//MAKE_HOOK_MATCH(SongPreviewPlayer_OnEnable, &GlobalNamespace::SongPreviewPlayer::OnEnable, void, GlobalNamespace::SongPreviewPlayer* self) {
//
//   MenuMusic::menuMusicLoader.set_OriginalClip(self->_defaultAudioClip);
//
//    if (!MenuMusic::menuMusicLoader.get_OriginalClip()) {
//        PaperLogger.info("Loading custom menu music...");
//        MenuMusic::menuMusicLoader.LoadCustomMusic();  // Keine Coroutine mehr nötig
//    }
//
//    self->_defaultAudioClip = MenuMusic::menuMusicLoader.get_OriginalClip();
//
//    SongPreviewPlayer_OnEnable(self);
//}

// Called whenever the main menu scene loads
MAKE_HOOK_MATCH(SongPreviewPlayer_OnEnable, &SongPreviewPlayer::OnEnable, void, SongPreviewPlayer* self) {
    if(getModConfig().EnableMenuMusic.GetValue()) PlayRandomSong(self);
    SongPreviewPlayer_OnEnable(self);
}

// Called whenever the SongPreviewPlayer transitions from one song to another
MAKE_HOOK_MATCH(SongPreviewPlayer_CrossfadeTo, static_cast<void(SongPreviewPlayer::*)(AudioClip*, float, float, float, bool, System::Action*)>(&SongPreviewPlayer::CrossfadeTo), void, SongPreviewPlayer* self, AudioClip* audioClip, float musicVolume, float startTime, float duration, bool isDefault, System::Action* onFadeOutCallback) {
    // Choose a new random main menu song when transitioning away from the main menu music
    if(getModConfig().EnableMenuMusic.GetValue() && self->_defaultAudioClip && self->_defaultAudioClip.ptr() != audioClip) PlayRandomSong(self);
    SongPreviewPlayer_CrossfadeTo(self, audioClip, musicVolume, startTime, duration, isDefault, onFadeOutCallback);
}

// float BytesToFloat(uint8_t byte0, uint8_t byte1, uint8_t byte2, uint8_t byte3) {
//     float out = 0;
//     uint8_t* tempPtr = reinterpret_cast<uint8_t*>(&out);
    
//     // Arm processors are usually little endian, so assume this operation is okay
//     tempPtr[0] = byte0;
//     tempPtr[1] = byte1;
//     tempPtr[2] = byte2;
//     tempPtr[3] = byte3;

//     return out;
// }

//MAKE_HOOK_MATCH(GameServerLobbyFlowCoordinator_DidActivate, &GlobalNamespace::GameServerLobbyFlowCoordinator::DidActivate, void, GlobalNamespace::GameServerLobbyFlowCoordinator* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
//    MenuMusic::menuMusicLoader.set_OriginalClip(self->_ambienceAudioClip);
//    
//    self->_ambienceAudioClip = MenuMusic::menuMusicLoader.get_OriginalClip();
//    GameServerLobbyFlowCoordinator_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);
//}

//MAKE_HOOK_MATCH(GameServerLobbyFlowCoordinator_DidDeactivate, &GlobalNamespace::GameServerLobbyFlowCoordinator::DidDeactivate, void, GlobalNamespace::GameServerLobbyFlowCoordinator* self, bool removedFromHierarchy, bool screenSystemDisabling) {
//   self->_ambienceAudioClip = MenuMusic::menuMusicLoader.get_OriginalClip();
//    GameServerLobbyFlowCoordinator_DidDeactivate(self, removedFromHierarchy, screenSystemDisabling);
//}

//MAKE_HOOK_MATCH(MultiplayerModeSelectionFlowCoordinator_DidActivate, &GlobalNamespace::MultiplayerModeSelectionFlowCoordinator::DidActivate, void, GlobalNamespace::MultiplayerModeSelectionFlowCoordinator* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
//    self->_ambienceAudioClip = MenuMusic::menuMusicLoader.get_OriginalClip();
//    MultiplayerModeSelectionFlowCoordinator_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);
//}

//MAKE_HOOK_MATCH(MultiplayerModeSelectionFlowCoordinator_DidDeactivate, &GlobalNamespace::MultiplayerModeSelectionFlowCoordinator::DidDeactivate, void, GlobalNamespace::MultiplayerModeSelectionFlowCoordinator* self, bool removedFromHierarchy, bool screenSystemDisabling) {
//    self->_ambienceAudioClip = MenuMusic::menuMusicLoader.get_OriginalClip();
//    MultiplayerModeSelectionFlowCoordinator_DidDeactivate(self, removedFromHierarchy, screenSystemDisabling);
//}


//MAKE_HOOK_MATCH(NoteControllerInit, &GlobalNamespace::NoteController::Init, void, GlobalNamespace::NoteController *self, GlobalNamespace::NoteData *noteData, float worldRotation, UnityEngine::Vector3 moveStartPos, UnityEngine::Vector3 moveEndPos, UnityEngine::Vector3 jumpEndPos, float moveDuration, float jumpDuration, float jumpGravity) {
    //NoteControllerInit(self, noteData, worldRotation, moveStartPos, moveEndPos, jumpEndPos, moveDuration, jumpDuration, jumpGravity);

    //if (colorChanger) {
    //    colorChanger->UpdateColor(UnityEngine::Time::get_deltaTime());
    //}

    //auto renderers = self->GetComponentInChildren<UnityEngine::Renderer *>();
    //if (renderers) {
    //    for (auto m : renderers->get_materials()) {
    //        m->SetColor("_SimpleColor", colorChanger->currentColor);
     //       m->SetColor("_Color", colorChanger->currentColor);
        //}
    //}
//}


// MAKE_HOOK_MATCH(NoteControllerInit, &GlobalNamespace::NoteController::Init, void, GlobalNamespace::NoteController* self, GlobalNamespace::NoteData* noteData, float worldRotation, UnityEngine::Vector3 moveStartPos, UnityEngine::Vector3 moveEndPos, UnityEngine::Vector3 jumpEndPos, float moveDuration, float jumpDuration, float jumpGravity, float endRotation, float uniformScale, bool rotatesTowardsPlayer, bool useRandomRotation) {
//     NoteControllerInit(self, noteData, worldRotation, moveStartPos, moveEndPos, jumpEndPos, moveDuration, jumpDuration, jumpGravity, endRotation, uniformScale, rotatesTowardsPlayer, useRandomRotation);
//     if(!getModConfig().EnableBlocks.GetValue())
// 		return;

//     if (colorChanger) colorChanger->UpdateColor(UnityEngine::Time::get_deltaTime());


//     for(auto m : self->GetComponentInChildren<Renderer *>()->get_materials()) {
//         //m->SetColor("_SimpleColor", colorChanger->currentColor);
//         m->SetColor("_Color", colorChanger->currentColor);
//     }
// }

MAKE_HOOK_MATCH(CustomLogoInit, &GlobalNamespace::FlickeringNeonSign::Start, void, GlobalNamespace::FlickeringNeonSign* self) {
    CustomLogoInit(self);

    if(getModConfig().EnableCustomLogo.GetValue()) Christmas::customLogo::LoadCustomLogo();
}

// Very quick and dirty way to override the menu light colors
MAKE_HOOK_MATCH(OverrideEnvironmentColors, &GlobalNamespace::LightWithIdManager::SetColorForId, void, GlobalNamespace::LightWithIdManager* self, int lightId, UnityEngine::Color color) {
    if(!getModConfig().EnableWhiteEnv.GetValue() || UnityEngine::SceneManagement::SceneManager::GetActiveScene().name == "GameCore")
        OverrideEnvironmentColors(self, lightId, color);
    else {
        // Force the environment color to be white
        OverrideEnvironmentColors(self, lightId, UnityEngine::Color(1.0f, 1.0f, 1.0f, color.a));
    }
}

MAKE_HOOK_MATCH(SnowInit, &GlobalNamespace::MainMenuViewController::DidActivate, void, GlobalNamespace::MainMenuViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    SnowInit(self, firstActivation, addedToHierarchy, screenSystemEnabling);

    if(!firstActivation) return;

    if(getModConfig().EnableSnowflakes.GetValue()) Christmas::snowflakes::CreateSnowflakes();
    if(getModConfig().EnableSnowPiles.GetValue()) Christmas::snowPrimitives::CreateSnowPrimitives();
}


// Called at the early stages of game loading
MOD_EXTERN_FUNC void setup(CModInfo *info) noexcept {
    *info = modInfo.to_c();

    getModConfig().Init(modInfo);

    // File logging
    Paper::Logger::RegisterFileContextId(PaperLogger.tag);

    PaperLogger.info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
MOD_EXTERN_FUNC void late_load() noexcept {
    il2cpp_functions::Init();


    PaperLogger.info("Installing hooks...");
    //INSTALL_HOOK(PaperLogger, NoteControllerInit);
    INSTALL_HOOK(PaperLogger, CustomLogoInit);
    INSTALL_HOOK(PaperLogger, OverrideEnvironmentColors);
    INSTALL_HOOK(PaperLogger, SnowInit);

    INSTALL_HOOK(PaperLogger, SongPreviewPlayer_OnEnable);
    INSTALL_HOOK(PaperLogger, SongPreviewPlayer_CrossfadeTo);
    //INSTALL_HOOK(PaperLogger, GameServerLobbyFlowCoordinator_DidActivate);
    //INSTALL_HOOK(PaperLogger, GameServerLobbyFlowCoordinator_DidDeactivate);
    //INSTALL_HOOK(PaperLogger, MultiplayerModeSelectionFlowCoordinator_DidActivate);
    //INSTALL_HOOK(PaperLogger, MultiplayerModeSelectionFlowCoordinator_DidDeactivate);



    PaperLogger.info("Installed all hooks!");
}