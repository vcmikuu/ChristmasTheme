#pragma once
#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(ModConfig,

    CONFIG_VALUE(EnableCustomLogo, bool, "Enable Custom Logo", true);
    CONFIG_VALUE(EnableMenuMusic, bool, "Enable Menu Music", true);
    CONFIG_VALUE(EnableSnowflakes, bool, "Enable Snowflakes", true);
    CONFIG_VALUE(EnableWhiteEnv, bool, "Enable White Environment", true);
    CONFIG_VALUE(EnableSnowPiles, bool, "Enable Snow Piles", true);
    // CONFIG_VALUE(EnableBlocks, bool, "Enable Christmas blocks", true);

)