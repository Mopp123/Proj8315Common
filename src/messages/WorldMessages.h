#pragma once

#include "Common.h"
#include "Message.h"
#include "Faction.h"
#include <vector>

#define MESSAGE_REQUIRED_SIZE__WorldStateMsg (MESSAGE_ENTRY_SIZE__header + (USER_OBSERVE_AREA * sizeof(uint64_t)))
#define MESSAGE_REQUIRED_SIZE__UpdateObserverMsg (MESSAGE_ENTRY_SIZE__header + sizeof(int32_t) * 3)
#define MESSAGE_REQUIRED_SIZE__CreateFactionRequest (MESSAGE_ENTRY_SIZE__header + FACTION_NAME_SIZE)
#define MESSAGE_REQUIRED_SIZE__CreateFactionResponse (MESSAGE_ENTRY_SIZE__header + 1 + MESSAGE_ERR_STR_SIZE + FACTION_NETW_SIZE)
// TODO: Figure out how to deal with faction count limit!
#define MESSAGE_SIZE_CAP__FactionListResponse (MESSAGE_ENTRY_SIZE__header + FACTION_NETW_SIZE * MAX_FACTION_COUNT)


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

    class CreateFactionRequest : public Message
    {
    public:
        CreateFactionRequest(const GC_byte* pData, size_t dataSize);
        CreateFactionRequest(const CreateFactionRequest& other);
        CreateFactionRequest(const std::string factionName);
        ~CreateFactionRequest() {}
        std::string getName() const;
    };

    class CreateFactionResponse : public Message
    {
    private:
        bool _status = false;
        std::string _errorMessage = "";
        Faction _faction;

    public:
        CreateFactionResponse(const GC_byte* pData, size_t dataSize);
        CreateFactionResponse(const CreateFactionResponse& other);
        CreateFactionResponse(bool status, std::string error, Faction faction);
        ~CreateFactionResponse() {}
        inline bool getStatus() const { return _status; }
        inline const std::string& getErrorMessage() const { return _errorMessage; }
        inline const Faction& getFaction() const { return _faction; }
    };

    class FactionListResponse : public Message
    {
    private:
        std::vector<Faction> _factions;

    public:
        FactionListResponse(const GC_byte* pData, size_t dataSize);
        FactionListResponse(const FactionListResponse& other);
        FactionListResponse(const std::vector<Faction>& factions);
        ~FactionListResponse() {}
        inline const std::vector<Faction>& getFactions() const { return _factions; }
    };
}
