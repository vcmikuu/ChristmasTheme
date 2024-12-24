#pragma once
#include "UnityEngine/AudioClip.hpp"

namespace MenuMusic {
    class MusicLoader {
    public:
        void set_OriginalClip(UnityEngine::AudioClip* clip);
        UnityEngine::AudioClip* getClip();
        UnityEngine::AudioClip* get_OriginalClip();
        void loadEmbeddedOgg();
        void playCustomClip();

    private:
        UnityEngine::AudioClip* originalClip = nullptr;
        UnityEngine::AudioClip* customClip = nullptr;
    };

    extern MusicLoader menuMusicLoader;
}
