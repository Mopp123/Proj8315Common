#pragma once

#include "Common.h"
#include "Message.h"
#include <vector>

#define MESSAGE_REQUIRED_SIZE__WorldStateMsg (MESSAGE_ENTRY_SIZE__header + (USER_OBSERVE_AREA * sizeof(uint64_t)))
#define MESSAGE_REQUIRED_SIZE__UpdateObserverMsg (MESSAGE_ENTRY_SIZE__header + sizeof(int32_t) * 3)
// TODO: Figure out how to deal with faction count limit!
#define MESSAGE_SIZE_CAP__FactionsMsg (MESSAGE_ENTRY_SIZE__header + Faction::get_netw_size() * 1000)


namespace gamecommon
{
    class WorldStateMsg : public Message
    {
    public:
        WorldStateMsg(const GC_byte* pData, size_t dataSize);
        WorldStateMsg(const WorldStateMsg& other);
        ~WorldStateMsg() {}
    };


    class UpdateObserverMsg : public Message
    {
    private:
        int32_t _x = 0;
        int32_t _z = 0;
        int32_t _radius = 15;

    public:
        UpdateObserverMsg(const GC_byte* pData, size_t dataSize);
        UpdateObserverMsg(int32_t x, int32_t z, int32_t radius);
        UpdateObserverMsg(const UpdateObserverMsg& other);
        ~UpdateObserverMsg() {}
        inline int32_t getX() const { return _x; }
        inline int32_t getZ() const { return _z; }
        inline int32_t getRadius() const { return _radius; }
    };


    class FactionsMsg : public Message
    {
    private:
        std::vector<Faction> _factions;

    public:
        FactionsMsg(const GC_byte* pData, size_t dataSize);
        FactionsMsg(const FactionsMsg& other);
        FactionsMsg(const std::vector<Faction>& factions);
        ~FactionsMsg() {}
        inline const std::vector<Faction>& getFactions() const { return _factions; }
    };
}
