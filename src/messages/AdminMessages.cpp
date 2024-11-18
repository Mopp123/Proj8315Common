#include "AdminMessages.h"

namespace gamecommon
{

    SpawnRequest::SpawnRequest(const GC_byte* pData, size_t dataSize) :
        Message(pData, dataSize, MESSAGE_REQUIRED_SIZE__SpawnRequest)
    {
        if (_isValid)
        {
            memcpy(&_objectType, _pData + MESSAGE_ENTRY_SIZE__header, TILE_STATE_SIZE_thingID);
            memcpy(&_targetX, _pData + MESSAGE_ENTRY_SIZE__header + TILE_STATE_SIZE_thingID, sizeof(int32_t));
            memcpy(&_targetY, _pData + MESSAGE_ENTRY_SIZE__header + TILE_STATE_SIZE_thingID + sizeof(int32_t), sizeof(int32_t));
        }
    }

    // *forcing to give obj type as ptr and size of it if in the future want to increase the size
    // of the object type
    SpawnRequest::SpawnRequest(
        GC_ubyte* objectType,
        size_t objectTypeSize,
        int32_t targetX,
        int32_t targetY
    ) :
        Message(MESSAGE_TYPE__SpawnRequest, MESSAGE_REQUIRED_SIZE__SpawnRequest)
    {
        if (_isValid)
        {
            addData(objectType, TILE_STATE_SIZE_thingID);
            addData(&targetX, sizeof(int32_t));
            addData(&targetY, sizeof(int32_t));

            memcpy(&_objectType, objectType, TILE_STATE_SIZE_thingID);
            _targetX = targetX;
            _targetY = targetY;
        }
    }

    SpawnRequest::SpawnRequest(const SpawnRequest& other) :
        Message(other._pData, other._dataSize, MESSAGE_REQUIRED_SIZE__SpawnRequest)
    {
        if (_isValid)
        {
            memcpy(&_objectType, _pData + MESSAGE_ENTRY_SIZE__header, TILE_STATE_SIZE_thingID);
            _targetX = other._targetX;
            _targetY = other._targetY;
        }
    }
}
