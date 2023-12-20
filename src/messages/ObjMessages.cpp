#include "ObjMessages.h"
#include "messages/Message.h"


namespace gamecommon
{
    ObjInfoLibResponse::ObjInfoLibResponse(const GC_byte* pData, size_t dataSize) :
        Message(pData, dataSize, dataSize, MESSAGE_SIZE_CAP_ObjInfoLib)
    {
        if (_isValid)
        {
            const size_t objCount = (dataSize - MESSAGE_ENTRY_SIZE__header) / get_netw_objinfo_size();
            int currentDataPos = MESSAGE_ENTRY_SIZE__header;
            for (size_t i = 0; i < objCount; ++i)
            {
                GC_byte nameData[OBJECT_DATA_STRLEN_NAME];
                memset(nameData, 0, OBJECT_DATA_STRLEN_NAME);
                memcpy(nameData, pData + currentDataPos, OBJECT_DATA_STRLEN_NAME);
                std::string name_str(nameData, OBJECT_DATA_STRLEN_NAME);

                GC_byte descriptionData[OBJECT_DATA_STRLEN_DESCRIPTION];
                memset(descriptionData, 0, OBJECT_DATA_STRLEN_DESCRIPTION);
                memcpy(
                    descriptionData,
                    pData + currentDataPos + OBJECT_DATA_STRLEN_NAME,
                    OBJECT_DATA_STRLEN_DESCRIPTION
                );
                std::string description(descriptionData, OBJECT_DATA_STRLEN_DESCRIPTION);

                MsgDebug::log("___TEST___CREATING OBJECT INFO FOR: " + name_str + " description = " + description + " | dataPos = " + std::to_string(currentDataPos));

                std::vector<std::string> actions;
                currentDataPos += OBJECT_DATA_STRLEN_NAME + OBJECT_DATA_STRLEN_DESCRIPTION;
                for (int j = 0; j < TILE_STATE_MAX_action + 1; ++j)
                {
                    GC_byte actionData[OBJECT_DATA_STRLEN_ACTION_NAME];
                    memset(actionData, 0, OBJECT_DATA_STRLEN_ACTION_NAME);
                    memcpy(actionData, pData + currentDataPos, OBJECT_DATA_STRLEN_ACTION_NAME);
                    std::string action(actionData, OBJECT_DATA_STRLEN_ACTION_NAME);
                    actions.push_back(action);
                    currentDataPos += OBJECT_DATA_STRLEN_ACTION_NAME;
                }
                GC_ubyte speed = 0;
                memcpy(&speed, pData + currentDataPos, 1);
                currentDataPos += 1; // +1 since the one byte stat
                ObjectInfo objInfo(name_str, description, actions, speed, 0); // NOTE: Client doesn't use begin state -> can be set to 0
                _objects.push_back(objInfo);
            }
        }
    }

    ObjInfoLibResponse::ObjInfoLibResponse(const std::vector<ObjectInfo>& objInfoLib) :
        Message(MESSAGE_TYPE__ObjInfoLibResponse, MESSAGE_ENTRY_SIZE__header + get_netw_objinfo_size() * objInfoLib.size()),
        _objects(objInfoLib)
    {
        const size_t objInfoSize = get_netw_objinfo_size();
        for (const ObjectInfo& objInfo : objInfoLib)
            addData((const GC_byte*)&objInfo, objInfoSize);
    }

    ObjInfoLibResponse::ObjInfoLibResponse(const ObjInfoLibResponse& other) :
        Message(other._pData, other._dataSize, other._dataSize, MESSAGE_SIZE_CAP_ObjInfoLib),
        _objects(other._objects)
    {}
}

