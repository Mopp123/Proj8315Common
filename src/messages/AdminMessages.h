#pragma once

#include "Message.h"
#include "Tile.h"

// NOTE: Atm each admin message requires having client sending username and password
// kind of like "sudo" command to server...

#define MESSAGE_REQUIRED_SIZE__SpawnRequest (MESSAGE_ENTRY_SIZE__header + TILE_STATE_SIZE_thingID + sizeof(int32_t) * 2)
#define MESSAGE_REQUIRED_SIZE__TerrainModRequest (MESSAGE_ENTRY_SIZE__header + 1 + sizeof(int32_t) * 2 + 1 + 1 + 1)


namespace gamecommon
{
    class SpawnRequest : public Message
    {
    private:
        GC_ubyte _objectType = 0;
        // these are signed atm just because was using signed ints with other positions atm
        // TODO: Maybe in the future force all positions be unsigned
        int32_t _targetX = 0;
        int32_t _targetY = 0;

    public:
        SpawnRequest(const GC_byte* pData, size_t dataSize);
        SpawnRequest(
            GC_ubyte* objectType,
            size_t objectTypeSize,
            int32_t targetX,
            int32_t targetY
        );
        SpawnRequest(const SpawnRequest& other);
        ~SpawnRequest() {}
        inline GC_ubyte getObjectType() const { return _objectType; }
        inline int32_t getTargetX() const { return _targetX; }
        inline int32_t getTargetY() const { return _targetY; }
    };


    class TerrainModRequest : public Message
    {
    private:
        GC_ubyte _radius = 1;
        int32_t _targetX = 0;
        int32_t _targetY = 0;

        GC_ubyte _elevation = 0;
        GC_ubyte _temperature = 0;
        GC_ubyte _terrainType = 0;

    public:
        TerrainModRequest(const GC_byte* pData, size_t dataSize);
        TerrainModRequest(
            GC_ubyte radius,
            int32_t targetX,
            int32_t targetY,
            GC_ubyte elevation,
            GC_ubyte temperature,
            GC_ubyte terrainType
        );
        TerrainModRequest(const TerrainModRequest& other);
        ~TerrainModRequest() {}

        inline GC_ubyte getRadius() const { return _radius; }
        inline int32_t getTargetX() const { return _targetX; }
        inline int32_t getTargetY() const { return _targetY; }
        inline GC_ubyte getElevation() const { return _elevation; }
        inline GC_ubyte getTemperature() const { return _temperature; }
        inline GC_ubyte getTerrainType() const { return _terrainType; }
    };
}
