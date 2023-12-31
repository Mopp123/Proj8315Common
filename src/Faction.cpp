#include "Faction.h"
#include "messages/Message.h"


namespace gamecommon
{
    Faction::Faction()
    {
        memset(_id, 0, UUID_SIZE);
        memset(_nameData, 0, FACTION_NAME_SIZE);
        memset(_deployments, 0, FACTION_MAX_DEPLOY_COUNT);
    }

    // TODO: Error/warning handling/signaling if id or name size out of bounds
    Faction::Faction(const std::string& id, const std::string& name)
    {
        size_t idSize = id.size();
        size_t nameSize = name.size();
        if (idSize > UUID_SIZE)
            idSize = UUID_SIZE;
        if (nameSize > FACTION_NAME_SIZE)
            nameSize = FACTION_NAME_SIZE;

        memset(_id, 0, UUID_SIZE);
        memset(_nameData, 0, FACTION_NAME_SIZE);

        memcpy(_id, id.data(), idSize);
        memcpy(_nameData, name.data(), nameSize);

        memset(_deployments, 0, FACTION_MAX_DEPLOY_COUNT);
    }

    Faction::Faction(const Faction& other)
    {
        memset(_id, 0, UUID_SIZE);
        memset(_nameData, 0, FACTION_NAME_SIZE);

        memcpy(_id, other._id, UUID_SIZE);
        memcpy(_nameData, other._nameData, FACTION_NAME_SIZE);
        memset(_deployments, 0, FACTION_MAX_DEPLOY_COUNT);
    }

    void Faction::setDeployments(GC_byte* deployments, size_t count)
    {
        if (count <= FACTION_MAX_DEPLOY_COUNT)
            memcpy(_deployments, deployments, sizeof(GC_byte) * count);
    }

    size_t Faction::get_netw_size()
    {
        return UUID_SIZE + FACTION_NETW_SIZE;
    }
}
