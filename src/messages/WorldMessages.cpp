#include "WorldMessages.h"


namespace gamecommon
{
    WorldStateMsg::WorldStateMsg(const GC_byte* pData, size_t dataSize) :
        Message(pData, dataSize, MESSAGE_REQUIRED_SIZE__WorldStateMsg)
    {}

    WorldStateMsg::WorldStateMsg(const WorldStateMsg& other) :
        Message(other._pData, other._dataSize, MESSAGE_REQUIRED_SIZE__WorldStateMsg)
    {}


    UpdateObserverMsg::UpdateObserverMsg(const GC_byte* pData, size_t dataSize) :
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


    CreateFactionRequest::CreateFactionRequest(const GC_byte* pData, size_t dataSize) :
        Message(pData, dataSize, MESSAGE_REQUIRED_SIZE__CreateFactionRequest)
    {}

    CreateFactionRequest::CreateFactionRequest(const CreateFactionRequest& other) :
        Message(other._pData, other._dataSize, MESSAGE_REQUIRED_SIZE__CreateFactionRequest)
    {}

    CreateFactionRequest::CreateFactionRequest(const std::string factionName) :
        Message(MESSAGE_TYPE__CreateFactionRequest, MESSAGE_ENTRY_SIZE__header + MESSAGE_REQUIRED_SIZE__CreateFactionRequest)
    {
        if (_isValid)
            addData(factionName.data(), factionName.size());
    }

    std::string CreateFactionRequest::getName() const
    {
        if (_isValid)
            return std::string(_pData + MESSAGE_ENTRY_SIZE__header, FACTION_NAME_SIZE);
        return "";
    }


    CreateFactionResponse::CreateFactionResponse(const GC_byte* pData, size_t dataSize) :
        Message(pData, dataSize, MESSAGE_REQUIRED_SIZE__CreateFactionResponse)
    {
        if (_isValid)
        {
            _status = _pData[MESSAGE_ENTRY_SIZE__header];
            _errorMessage = std::string(_pData + (MESSAGE_ENTRY_SIZE__header + 1), MESSAGE_ERR_STR_SIZE);
            std::string factionName = std::string(_pData + (MESSAGE_ENTRY_SIZE__header + 1 + MESSAGE_ERR_STR_SIZE), FACTION_NAME_SIZE);
            uint32_t factionID = (uint32_t)*(_pData + (MESSAGE_ENTRY_SIZE__header + 1 + MESSAGE_ERR_STR_SIZE + FACTION_NAME_SIZE));
            _faction = Faction(factionName.data(), factionName.size(), factionID);
        }
    }
    CreateFactionResponse::CreateFactionResponse(const CreateFactionResponse& other) :
        Message(other._pData, other._dataSize, MESSAGE_REQUIRED_SIZE__CreateFactionResponse),
        _status(other._status),
        _errorMessage(other._errorMessage),
        _faction(other._faction)
    {}
    CreateFactionResponse::CreateFactionResponse(bool status, std::string error, Faction faction) :
        Message(MESSAGE_TYPE__CreateFactionResponse, MESSAGE_ENTRY_SIZE__header + MESSAGE_REQUIRED_SIZE__CreateFactionResponse)
    {
        if (_isValid)
        {
            _status = status;
            _errorMessage = error;
            _faction = faction;

            addData((GC_byte*)&status, 1);
            addData(error.data(), MESSAGE_ERR_STR_SIZE);
            addData(faction.getNameData(), FACTION_NAME_SIZE);
            uint32_t factionID = faction.getID();
            addData((GC_byte*)&factionID, sizeof(uint32_t));
        }
    }


    // NOTE: Not sure if this works. Yet to be tested!
    FactionsMsg::FactionsMsg(const GC_byte* pData, size_t dataSize) :
        Message(pData, dataSize, MESSAGE_SIZE_CAP__FactionsMsg)
    {
        if (_isValid)
        {
            const size_t factionSize = Faction::get_netw_size();
            int count = (dataSize - MESSAGE_ENTRY_SIZE__header) / (int)factionSize;
            int ptr = MESSAGE_ENTRY_SIZE__header;
            for (int i = 0; i < count; ++i)
            {
                GC_byte factionName[FACTION_NAME_SIZE];
                memset(factionName, 0, FACTION_NAME_SIZE);
                memcpy(factionName, _pData + ptr, factionSize);
                uint32_t factionID = (uint32_t)*(_pData + ptr + FACTION_NAME_SIZE);
                _factions.push_back(Faction(factionName, FACTION_NAME_SIZE, factionID));
                ptr += factionSize;
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
            {
                uint32_t factionID = faction.getID();
                addData(faction.getNameData(), FACTION_NAME_SIZE);
                addData((GC_byte*)&factionID, sizeof(uint32_t));
            }
        }
    }
}
