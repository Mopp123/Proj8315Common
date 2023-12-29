#pragma once

#include "Common.h"
#include <cstring>
#include <string>


#define FACTION_NAME_SIZE 32
#define FACTION_MAX_DEPLOY_COUNT 16

#define FACTION_NETW_SIZE (UUID_SIZE + FACTION_NAME_SIZE)

#define NULL_FACTION Faction("", "")


namespace gamecommon
{
    class Faction
    {
    private:
        GC_byte _id[UUID_SIZE];

        GC_byte _nameData[FACTION_NAME_SIZE];

        // Contains what objects faction spawns, when spawning to the map
        GC_byte _deployments[FACTION_MAX_DEPLOY_COUNT];

        // If faction's data is changed -> broadcast its new data to all clients
        bool _updated = true;

    public:
        Faction();
        Faction(const std::string& id, const std::string& name);
        Faction(const Faction& other);

        void setDeployments(GC_byte* deployments, size_t count);
        static size_t get_netw_size();

        inline const GC_byte* getID() const { return _id; }
        inline const GC_byte* getNameData() const { return _nameData; }
        inline std::string getName() const { return std::string(_nameData); }
        inline const GC_byte* getDeploymens() { return _deployments; }
        inline bool isUpdated() const { return _updated; }
        inline void markUpdated(bool arg) { _updated = arg; }

        // TODO: Take id comparing into account
        bool operator==(const Faction& other) { return memcmp(_nameData, other._nameData, FACTION_NAME_SIZE) == 0; }
        bool operator!=(const Faction& other) { return memcmp(_nameData, other._nameData, FACTION_NAME_SIZE) != 0; }
    };
}
