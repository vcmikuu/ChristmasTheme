#pragma once
#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(ModConfig,

    CONFIG_VALUE(EnableCustomLogo, bool, "Enable Custom Logo", true);
    CONFIG_VALUE(EnableMenuMusic, bool, "Enable Menu Music", true);
    CONFIG_VALUE(EnaleSnowfall, bool, "Enable Snowfall", true);
    CONFIG_VALUE(EnableWhiteEnv, bool, "Enable White Environment", true);
    CONFIG_VALUE(EnableSnow, bool, "Enable Snow", true);
    CONFIG_VALUE(EnableBlocks, bool, "Enable Christmas blocks", true);

)