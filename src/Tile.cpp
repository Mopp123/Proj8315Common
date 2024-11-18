#include "Tile.h"
#include <cstring>

#include "BitShit.hpp"

#include <iostream>


namespace gamecommon
{
    void set_tile_terrelevation(uint64_t& tile, GC_ubyte value)
    {
        bitshit::set_area<uint64_t, GC_ubyte>(
            tile, value,
            TILE_STATE_POS_properties + TILE_STATE_POS_terrElevation,
            TILE_STATE_SIZE_terrElevation
        );
    }

    void set_tile_terrtype(uint64_t& tile, GC_ubyte value)
    {
        bitshit::set_area<uint64_t, GC_ubyte>(
            tile, value,
            TILE_STATE_POS_properties + TILE_STATE_POS_terrType,
            TILE_STATE_SIZE_terrType
        );
    }

    void set_tile_temperature(uint64_t& tile, GC_ubyte value)
    {
        bitshit::set_area<uint64_t, GC_ubyte>(
            tile, value,
            TILE_STATE_POS_properties + TILE_STATE_POS_temperature,
            TILE_STATE_SIZE_temperature
        );
    }

    void set_tile_effect(uint64_t& tile, GC_ubyte value)
    {
        bitshit::set_area<uint64_t, GC_ubyte>(
            tile, value,
            TILE_STATE_POS_properties + TILE_STATE_POS_effect,
            TILE_STATE_SIZE_effect
        );
    }


    void set_tile_thingid(uint64_t& tile, GC_ubyte value)
    {
        bitshit::set_area<uint64_t, GC_ubyte>(
            tile, value,
            TILE_STATE_POS_properties + TILE_STATE_POS_thingID,
            TILE_STATE_SIZE_thingID
        );
    }

    void set_tile_action(uint64_t& tile, GC_ubyte value)
    {
        bitshit::set_area<uint64_t, GC_ubyte>(
            tile, value,
            TILE_STATE_POS_properties + TILE_STATE_POS_action,
            TILE_STATE_SIZE_action
        );
    }

    void set_tile_facingdir(uint64_t& tile, GC_ubyte value)
    {
        bitshit::set_area<uint64_t, GC_ubyte>(
            tile, value,
            TILE_STATE_POS_properties + TILE_STATE_POS_dir,
            TILE_STATE_SIZE_dir
        );
    }

    void set_tile_customvar(uint64_t& tile, GC_ubyte value)
    {
        bitshit::set_area<uint64_t, GC_ubyte>(
            tile, value,
            TILE_STATE_POS_properties + TILE_STATE_POS_customVar,
            TILE_STATE_SIZE_customVar
        );
    }

    // TODO: Some error handling/signaling if these fails?
    void set_tile_factionid(uint64_t& tile, uint32_t id)
    {
        if (id <= TILE_STATE_MAX_factionid)
        {
            bitshit::set_area<uint64_t, uint32_t>(
                tile, id,
                TILE_STATE_POS_properties + TILE_STATE_POS_factionID,
                TILE_STATE_SIZE_factionID
            );
        }
    }

    void set_tile_faction_objid(uint64_t& tile, uint32_t id)
    {
        if (id <= TILE_STATE_MAX_factionid)
        {
            bitshit::set_area<uint64_t, uint32_t>(
                tile, id,
                TILE_STATE_POS_properties + TILE_STATE_POS_factionObjectID,
                TILE_STATE_SIZE_factionObjectID
            );
        }
    }

    void transfer_obj_to(uint64_t& from, uint64_t& to)
    {
        uint64_t objState = from;
        // Grab the bits containing only the info of the "object"
        bitshit::set_area<uint64_t, uint64_t>(
            objState,
            0x0,
            0,
            TILE_STATE_SIZE - TILE_STATE_SIZE_objProperties
        );
        // Remove the "object" bits from the "from-tile"
        bitshit::set_area<uint64_t, uint64_t>(
            from,
            0x0,
            TILE_STATE_POS_properties + TILE_STATE_POS_objProperties,
            TILE_STATE_SIZE_objProperties
        );
        // Add the "object" bits to the "to-tile"
        to |= objState;
    }


    GC_ubyte get_tile_terrelevation(uint64_t tile)
    {
        GC_ubyte output = 0;
        bitshit::convert_area<uint64_t, GC_ubyte>(
            tile, output,
            TILE_STATE_POS_properties + TILE_STATE_POS_terrElevation,
            TILE_STATE_SIZE_terrElevation
        );
        return output;
    }

    GC_ubyte get_tile_terrtype(uint64_t tile)
    {
        GC_ubyte output = 0;
        bitshit::convert_area<uint64_t, GC_ubyte>(
            tile, output,
            TILE_STATE_POS_properties + TILE_STATE_POS_terrType,
            TILE_STATE_SIZE_terrType
        );
        return output;
    }

    GC_ubyte get_tile_temperature(uint64_t tile)
    {
        GC_ubyte output = 0;
        bitshit::convert_area<uint64_t, GC_ubyte>(
            tile, output,
            TILE_STATE_POS_properties + TILE_STATE_POS_temperature,
            TILE_STATE_SIZE_temperature
        );
        return output;
    }

    GC_ubyte get_tile_effect(uint64_t tile)
    {
        GC_ubyte output = 0;
        bitshit::convert_area<uint64_t, GC_ubyte>(
            tile, output,
            TILE_STATE_POS_properties + TILE_STATE_POS_effect,
            TILE_STATE_SIZE_effect
        );
        return output;
    }


    GC_ubyte get_tile_thingid  (uint64_t tile)
    {
        GC_ubyte output = 0;
        bitshit::convert_area<uint64_t, GC_ubyte>(
            tile, output,
            TILE_STATE_POS_properties + TILE_STATE_POS_thingID,
            TILE_STATE_SIZE_thingID
        );
        return output;
    }
    GC_ubyte get_tile_action         (uint64_t tile)
    {
        GC_ubyte output = 0;
        bitshit::convert_area<uint64_t, GC_ubyte>(
            tile, output,
            TILE_STATE_POS_properties + TILE_STATE_POS_action,
            TILE_STATE_SIZE_action
        );
        return output;
    }
    GC_ubyte get_tile_facingdir      (uint64_t tile)
    {
        GC_ubyte output = 0;
        bitshit::convert_area<uint64_t, GC_ubyte>(
            tile, output,
            TILE_STATE_POS_properties + TILE_STATE_POS_dir,
            TILE_STATE_SIZE_dir
        );
        return output;
    }
    GC_ubyte get_tile_customvar      (uint64_t tile)
    {
        GC_ubyte output = 0;
        bitshit::convert_area<uint64_t, GC_ubyte>(
            tile, output,
            TILE_STATE_POS_properties + TILE_STATE_POS_customVar,
            TILE_STATE_SIZE_customVar
        );
        return output;
    }

    uint16_t get_tile_factionid(uint64_t tile)
    {
        uint16_t output = 0;
        bitshit::convert_area<uint64_t, uint16_t>(
            tile,
            output,
            TILE_STATE_POS_properties + TILE_STATE_POS_factionID,
            TILE_STATE_SIZE_factionID
        );
        return output;
    }

    uint16_t get_tile_faction_objid(uint64_t tile)
    {
        uint16_t output = 0;
        bitshit::convert_area<uint64_t, uint16_t>(
            tile,
            output,
            TILE_STATE_POS_properties + TILE_STATE_POS_factionObjectID,
            TILE_STATE_SIZE_factionObjectID
        );
        return output;
    }

    uint32_t get_tile_uid(uint64_t tile)
    {
        uint32_t output = 0;
        bitshit::convert_area<uint64_t, uint32_t>(
            tile,
            output,
            TILE_STATE_POS_properties + TILE_STATE_POS_ID,
            TILE_STATE_SIZE_factionID + TILE_STATE_SIZE_factionObjectID
        );
        return output;
    }
}
