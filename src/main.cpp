#include "main.hpp"
#include "GlobalNamespace/NoteController.hpp"
#include "GlobalNamespace/GameNoteController.hpp"
#include "GlobalNamespace/FlickeringNeonSign.hpp"
#include "GlobalNamespace/SongPreviewPlayer.hpp"
#include "GlobalNamespace/GameServerLobbyFlowCoordinator.hpp"
#include "GlobalNamespace/MultiplayerModeSelectionFlowCoordinator.hpp"
#include "Menu/ObjectInstances.hpp"
#include "UnityEngine/Time.hpp"
#include "UnityEngine/Renderer.hpp"

#include "Logo/customlogo.hpp"
#include "Block/colorchanger.hpp"
#include "Menu/music.hpp"


#include "c.hpp"

#include "scotland2/shared/modloader.h"


using namespace cOGG;
using namespace GlobalNamespace;


static modloader::ModInfo modInfo{MOD_ID, VERSION, 0};
// Stores the ID and version of our mod, and is sent to
// the modloader upon startup

// Loads the config from disk using our modInfo, then returns it for use
// other config tools such as config-utils don't use this config, so it can be
// removed if those are in use
Configuration &getConfig() {
    static Configuration config(modInfo);
    return config;
}

static std::shared_ptr<cColor::ColorChanger> colorChanger;

namespace cOGG::ObjectInstances {
    GlobalNamespace::SongPreviewPlayer* SPP;
}

MAKE_HOOK_MATCH(SongPreviewPlayer_OnEnable, &GlobalNamespace::SongPreviewPlayer::OnEnable, void, GlobalNamespace::SongPreviewPlayer* self) {
    cOGG::ObjectInstances::SPP = self;

    MenuMusic::menuMusicLoader.set_OriginalClip(self->_defaultAudioClip);

    self->_defaultAudioClip = MenuMusic::menuMusicLoader.get_OriginalClip();

    SongPreviewPlayer_OnEnable(self);
}

MAKE_HOOK_MATCH(GameServerLobbyFlowCoordinator_DidActivate, &GlobalNamespace::GameServerLobbyFlowCoordinator::DidActivate, void, GlobalNamespace::GameServerLobbyFlowCoordinator* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    MenuMusic::menuMusicLoader.set_OriginalClip(self->_ambienceAudioClip);
    
    self->_ambienceAudioClip = MenuMusic::menuMusicLoader.get_OriginalClip();
    GameServerLobbyFlowCoordinator_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);
}

MAKE_HOOK_MATCH(GameServerLobbyFlowCoordinator_DidDeactivate, &GlobalNamespace::GameServerLobbyFlowCoordinator::DidDeactivate, void, GlobalNamespace::GameServerLobbyFlowCoordinator* self, bool removedFromHierarchy, bool screenSystemDisabling) {
    self->_ambienceAudioClip = MenuMusic::menuMusicLoader.get_OriginalClip();
    GameServerLobbyFlowCoordinator_DidDeactivate(self, removedFromHierarchy, screenSystemDisabling);
}

MAKE_HOOK_MATCH(MultiplayerModeSelectionFlowCoordinator_DidActivate, &GlobalNamespace::MultiplayerModeSelectionFlowCoordinator::DidActivate, void, GlobalNamespace::MultiplayerModeSelectionFlowCoordinator* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    self->_ambienceAudioClip = MenuMusic::menuMusicLoader.get_OriginalClip();
    MultiplayerModeSelectionFlowCoordinator_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);
}

MAKE_HOOK_MATCH(MultiplayerModeSelectionFlowCoordinator_DidDeactivate, &GlobalNamespace::MultiplayerModeSelectionFlowCoordinator::DidDeactivate, void, GlobalNamespace::MultiplayerModeSelectionFlowCoordinator* self, bool removedFromHierarchy, bool screenSystemDisabling) {
    self->_ambienceAudioClip = MenuMusic::menuMusicLoader.get_OriginalClip();
    MultiplayerModeSelectionFlowCoordinator_DidDeactivate(self, removedFromHierarchy, screenSystemDisabling);
}


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


MAKE_HOOK_MATCH(NoteControllerInit, &GlobalNamespace::NoteController::Init, void, GlobalNamespace::NoteController* self, GlobalNamespace::NoteData* noteData, float worldRotation, UnityEngine::Vector3 moveStartPos, UnityEngine::Vector3 moveEndPos, UnityEngine::Vector3 jumpEndPos, float moveDuration, float jumpDuration, float jumpGravity, float endRotation, float uniformScale, bool rotatesTowardsPlayer, bool useRandomRotation) {
    NoteControllerInit(self, noteData, worldRotation, moveStartPos, moveEndPos, jumpEndPos, moveDuration, jumpDuration, jumpGravity, endRotation, uniformScale, rotatesTowardsPlayer, useRandomRotation);
    
    if (colorChanger) colorChanger->UpdateColor(UnityEngine::Time::get_deltaTime());

    auto renderers = self->GetComponentInChildren<UnityEngine::Renderer*>();
    if (renderers) for (auto m : renderers->get_materials()) {
        m->SetColor("_SimpleColor", colorChanger->currentColor);
        m->SetColor("_Color", colorChanger->currentColor);
    }
}

MAKE_HOOK_MATCH(CustomLogoInit, &GlobalNamespace::FlickeringNeonSign::Start, void, GlobalNamespace::FlickeringNeonSign* self) {
    CustomLogoInit(self);

    Christmas::customLogo::LoadCustomLogo();
}


// Called at the early stages of game loading
MOD_EXTERN_FUNC void setup(CModInfo *info) noexcept {
    *info = modInfo.to_c();

    getConfig().Load();

    // File logging
    Paper::Logger::RegisterFileContextId(PaperLogger.tag);

    PaperLogger.info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
MOD_EXTERN_FUNC void late_load() noexcept {
    il2cpp_functions::Init();

    PaperLogger.info("Installing hooks...");
    INSTALL_HOOK(PaperLogger, NoteControllerInit);
    INSTALL_HOOK(PaperLogger, CustomLogoInit);

    PaperLogger.info("Installed all hooks!");
}