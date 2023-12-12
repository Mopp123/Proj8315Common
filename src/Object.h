#pragma once

#include <cstring>
#include <string>
#include <cstdint>
#include <vector>
#include "Tile.h"


#define OBJECT_DATA_STRLEN_NAME 32
#define OBJECT_DATA_STRLEN_DESCRIPTION 64
#define OBJECT_DATA_STRLEN_ACTION_NAME 16

#define OBJECT_DATA_COUNT_STATS 1
#define OBJECT_DATA_COUNT_TOTAL ((1 + 1) + (TILE_STATE_MAX_action + 1) + OBJECT_DATA_COUNT_STATS)


namespace gamecommon
{
    // Contains static info of a game object type (prev. this was called "thing")
    struct ObjectInfo
    {
        char name[OBJECT_DATA_STRLEN_NAME];
        char description[OBJECT_DATA_STRLEN_DESCRIPTION];

        char actionSlot[TILE_STATE_MAX_action + 1][OBJECT_DATA_STRLEN_ACTION_NAME];

        // stats
        GC_ubyte speed;

        uint64_t initialState = 0;

        ObjectInfo(
            const std::string& objName,
            const std::string& objDescription,
            std::vector<std::string>& actionSlots,
            GC_ubyte speedVal,
            uint64_t beginState
        );

        ObjectInfo(const ObjectInfo& other);
    };

    // Returns the size of data moving accross netw (excludes server and client specific data)
    size_t get_netw_objinfo_size();
}

