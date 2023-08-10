#include "Object.h"


namespace gamecommon
{
    ObjectInfo::ObjectInfo(
        const std::string& objName,
        const std::string& objDescription,
        std::vector<std::string>& actionSlots,
        GC_ubyte speedVal,
        uint64_t beginState
    ) :
        speed(speedVal),
        initialState(beginState)
    {
        memset(name, 0, sizeof(char) * OBJECT_DATA_STRLEN_NAME);
        memset(description, 0, sizeof(char) * OBJECT_DATA_STRLEN_DESCRIPTION);

        size_t nameLen = objName.size();
        size_t descriptionLen = objDescription.size();

        if (nameLen > OBJECT_DATA_STRLEN_NAME)
            nameLen = OBJECT_DATA_STRLEN_NAME;
        if (descriptionLen > OBJECT_DATA_STRLEN_DESCRIPTION)
            descriptionLen = OBJECT_DATA_STRLEN_DESCRIPTION;

        memcpy(name, objName.c_str(), sizeof(char) * nameLen);
        memcpy(description, objDescription.c_str(), sizeof(char) * descriptionLen);

        for (size_t i = 0; i < TILE_STATE_MAX_action + 1; ++i)
        {
            memset(actionSlot[i], 0, sizeof(char) * OBJECT_DATA_STRLEN_ACTION_NAME);
            if (i < actionSlots.size())
            {
                const std::string& slotName = actionSlots[i];
                size_t slotLen = slotName.size();
                if (slotLen > OBJECT_DATA_STRLEN_ACTION_NAME)
                    slotLen = OBJECT_DATA_STRLEN_ACTION_NAME;

                memcpy(actionSlot[i], slotName.c_str(), sizeof(char) * slotLen);
            }
        }
    }

    ObjectInfo::ObjectInfo(const ObjectInfo& other) :
        speed(other.speed),
        initialState(other.initialState)
    {
        memcpy(name, other.name, OBJECT_DATA_STRLEN_NAME);
        memcpy(description, other.description, OBJECT_DATA_STRLEN_DESCRIPTION);
        for (int i = 0; i < TILE_STATE_MAX_action + 1; ++i)
            memcpy(actionSlot[i], other.actionSlot[i], OBJECT_DATA_STRLEN_ACTION_NAME);
    }


    size_t get_netw_objinfo_size()
    {
        size_t combinedStrLen = (OBJECT_DATA_STRLEN_NAME + OBJECT_DATA_STRLEN_DESCRIPTION);
        for (int i = 0; i < TILE_STATE_MAX_action + 1; ++i)
            combinedStrLen += OBJECT_DATA_STRLEN_ACTION_NAME;
        return combinedStrLen + 1;
    }
}

