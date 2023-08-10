#include "WorldMessages.h"


namespace gamecommon
{
    WorldStateMsg::WorldStateMsg(GC_byte* pData, size_t dataSize) :
        Message(pData, dataSize, MESSAGE_REQUIRED_SIZE__WorldStateMsg)
    {}

    WorldStateMsg::WorldStateMsg(const WorldStateMsg& other) :
        Message(other._pData, other._dataSize, MESSAGE_REQUIRED_SIZE__WorldStateMsg)
    {}


    UpdateObserverMsg::UpdateObserverMsg(GC_byte* pData, size_t dataSize) :
        Message(pData, dataSize, MESSAGE_REQUIRED_SIZE__UpdateObserverMsg)
    {
        if (_isValid)
        {
            const size_t entrySize = sizeof(int32_t);
            memcpy(&_x, _pData + MESSAGE_ENTRY_SIZE__header, entrySize);
            memcpy(&_z, _pData + MESSAGE_ENTRY_SIZE__header + entrySize, entrySize);
            memcpy(&_radius, _pData + MESSAGE_ENTRY_SIZE__header + entrySize * 2, entrySize);
        }
    }

    UpdateObserverMsg::UpdateObserverMsg(int32_t x, int32_t z, int32_t radius) :
        Message(MESSAGE_TYPE__LoginRequest, MESSAGE_REQUIRED_SIZE__UpdateObserverMsg)
    {
        if (_isValid)
        {
            const size_t entrySize = sizeof(int32_t);
            addData((GC_byte*)&_x, entrySize);
            addData((GC_byte*)&_z, entrySize);
            addData((GC_byte*)&_radius, entrySize);
            _x = x;
            _z = z;
            _radius = radius;
        }
    }

    UpdateObserverMsg::UpdateObserverMsg(const UpdateObserverMsg& other) :
        Message(other._pData, other._dataSize, MESSAGE_REQUIRED_SIZE__UpdateObserverMsg)
    {
        if (_isValid)
        {
            _x = other._x;
            _z = other._z;
            _radius = other._radius;
        }
    }

    // NOTE: Not sure if this works. Yet to be tested!
    FactionsMsg::FactionsMsg(GC_byte* pData, size_t dataSize) :
        Message(pData, dataSize, MESSAGE_SIZE_CAP__FactionsMsg)
    {
        if (_isValid)
        {
            const size_t factionSize = Faction::get_netw_size();
            int count = (dataSize - MESSAGE_ENTRY_SIZE__header) / (int)factionSize;
            for (int i = 0; i < count; ++i)
            {
                GC_byte factionName[FACTION_NAME_SIZE];
                memset(factionName, 0, FACTION_NAME_SIZE);
                memcpy(factionName, _pData + MESSAGE_ENTRY_SIZE__header + (i * factionSize), factionSize);
                _factions.push_back(Faction(factionName, FACTION_NAME_SIZE));
            }
        }
    }

    FactionsMsg::FactionsMsg(const FactionsMsg& other):
        Message(other._pData, other._dataSize, MESSAGE_SIZE_CAP__FactionsMsg)
    {}

    FactionsMsg::FactionsMsg(const std::vector<Faction>& factions) :
        Message(MESSAGE_TYPE__Factions, MESSAGE_ENTRY_SIZE__header + factions.size() * Faction::get_netw_size())
    {
        if(_isValid)
        {
            _factions = factions;
            for (const Faction& faction : _factions)
                addData(faction.getNetwData(), Faction::get_netw_size());
        }
    }
}
