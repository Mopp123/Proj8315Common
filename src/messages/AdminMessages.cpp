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


    TerrainModRequest::TerrainModRequest(const GC_byte* pData, size_t dataSize) :
        Message(pData, dataSize, MESSAGE_REQUIRED_SIZE__TerrainModRequest)
    {
        if (_isValid)
        {
            memcpy(&_radius, _pData + MESSAGE_ENTRY_SIZE__header, TILE_STATE_SIZE_thingID);
            memcpy(&_targetX, _pData + MESSAGE_ENTRY_SIZE__header + 1, sizeof(int32_t));
            memcpy(&_targetY, _pData + MESSAGE_ENTRY_SIZE__header + 1 + sizeof(int32_t), sizeof(int32_t));

            const size_t terrainPropertiesStartOffset = MESSAGE_ENTRY_SIZE__header + 1 + sizeof(int32_t) * 2;
            memcpy(&_elevation, _pData + terrainPropertiesStartOffset, 1);
            memcpy(&_temperature, _pData + terrainPropertiesStartOffset + 1, 1);
            memcpy(&_terrainType, _pData + terrainPropertiesStartOffset + 1 + 1, 1);
        }
    }

    TerrainModRequest::TerrainModRequest(
        GC_ubyte radius,
        int32_t targetX,
        int32_t targetY,
        GC_ubyte elevation,
        GC_ubyte temperature,
        GC_ubyte terrainType
    ) :
        Message(MESSAGE_TYPE__TerrainModRequest, MESSAGE_REQUIRED_SIZE__TerrainModRequest)
    {
        if (_isValid)
        {
            addData(&radius, 1);
            addData(&targetX, sizeof(int32_t));
            addData(&targetY, sizeof(int32_t));
            addData(&elevation, 1);
            addData(&temperature, 1);
            addData(&terrainType, 1);

            _radius = radius;
            _targetX = targetX;
            _targetY = targetY;
            _elevation = elevation;
            _temperature = temperature;
            _terrainType = terrainType;
        }
    }

    TerrainModRequest::TerrainModRequest(const TerrainModRequest& other) :
        Message(other._pData, other._dataSize, MESSAGE_REQUIRED_SIZE__TerrainModRequest)
    {
        if (_isValid)
        {
            _radius = other._radius;
            _targetX = other._targetX;
            _targetY = other._targetY;
            _elevation = other._elevation;
            _temperature = other._temperature;
            _terrainType = other._terrainType;
        }
    }
}
