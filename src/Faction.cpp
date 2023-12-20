#include "Faction.h"


namespace gamecommon
{
    Faction::Faction() :
        _name("")
    {
        memset(_nameData, 0, FACTION_NAME_SIZE);
        memset(_deployments, 0, FACTION_MAX_DEPLOY_COUNT);
    }

    Faction::Faction(const GC_byte* nameData, size_t nameSize, uint32_t id) :
        _id(id)
    {
        if (nameSize > FACTION_NAME_SIZE)
            nameSize = FACTION_NAME_SIZE;
        memset(_nameData, 0, FACTION_NAME_SIZE);
        memcpy(_nameData, nameData, nameSize);
        memset(_deployments, 0, FACTION_MAX_DEPLOY_COUNT);
        _name = std::string(_nameData, FACTION_NAME_SIZE);
    }

    Faction::Faction(const Faction& other) :
        _id(other._id)
    {
        memset(_nameData, 0, FACTION_NAME_SIZE);
        memcpy(_nameData, other._nameData, FACTION_NAME_SIZE);
        memset(_deployments, 0, FACTION_MAX_DEPLOY_COUNT);
        _name = std::string(_nameData, FACTION_NAME_SIZE);
    }

    void Faction::setDeployments(GC_byte* deployments, size_t count)
    {
        if (count <= FACTION_MAX_DEPLOY_COUNT)
            memcpy(_deployments, deployments, sizeof(GC_byte) * count);
    }

    /*
    const GC_byte* Faction::getNetwData() const
    {
        return _nameData;
    }
    */

    size_t Faction::get_netw_size()
    {
        return FACTION_NETW_SIZE;
    }
}
