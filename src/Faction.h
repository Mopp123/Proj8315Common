#pragma once

#include "Common.h"
#include <cstring>
#include <string>


#define FACTION_NAME_SIZE 32
#define FACTION_MAX_DEPLOY_COUNT 16

#define FACTION_NETW_SIZE (FACTION_NAME_SIZE + sizeof(uint32_t))

#define NULL_FACTION Faction("", 0, 0)


namespace gamecommon
{
    class Faction
    {
    private:
        GC_byte _nameData[FACTION_NAME_SIZE];

        // Contains what objects faction spawns, when spawning to the map
        GC_byte _deployments[FACTION_MAX_DEPLOY_COUNT];

        // Index in Game -object's factions list
        uint32_t _id = 0;

        // If faction's data is changed -> broadcast its new data to all clients
        bool _updated = true;
        std::string _name;

    public:
        Faction();
        Faction(const GC_byte* nameData, size_t nameSize, uint32_t id);
        Faction(const Faction& other);

        void setDeployments(GC_byte* deployments, size_t count);
        // const GC_byte* getNetwData() const;
        static size_t get_netw_size();

        inline const GC_byte* getNameData() const { return _nameData; }
        inline const std::string& getName() const { return _name; }
        inline const GC_byte* getDeploymens() { return _deployments; }
        inline uint32_t getID() const { return _id; }
        inline bool isUpdated() const { return _updated; }
        inline void markUpdated(bool arg) { _updated = arg; }

        bool operator==(const Faction& other) { return memcmp(_nameData, other._nameData, FACTION_NAME_SIZE) == 0; }
        bool operator!=(const Faction& other) { return memcmp(_nameData, other._nameData, FACTION_NAME_SIZE) != 0; }
    };
}
