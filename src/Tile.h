#pragma once

#include <cstdint>
#include "Common.h"

// Size of the full state (in bytes)
// NOTE: It seems this is fucking wrong and not used anywhere?
// TODO: Delete?
#define TILE_STATE_SIZE_BYTES 		8

// Sizes of different portions (exact size in BITS NOT BYTES!)
#define TILE_STATE_SIZE			64

#define TILE_STATE_SIZE_properties	32

#define TILE_STATE_SIZE_terrElevation	5
#define TILE_STATE_SIZE_terrType	    3
#define TILE_STATE_SIZE_terrEffect	    2
#define TILE_STATE_SIZE_thingID		    8
#define TILE_STATE_SIZE_action		    3
#define TILE_STATE_SIZE_dir		        3
#define TILE_STATE_SIZE_customVar	    4
#define TILE_STATE_SIZE_factionID       10
#define TILE_STATE_SIZE_factionObjectID 16
// Atm need to take free bits into account since want to have id stuff at the end
// but also we have some free bits atm between tile data and id stuff..
#define TILE_STATE_SIZE_FREE_BITS 10
#define TILE_STATE_SIZE_objProperties	(TILE_STATE_SIZE_thingID + TILE_STATE_SIZE_action + TILE_STATE_SIZE_dir + TILE_STATE_SIZE_customVar + TILE_STATE_SIZE_factionID + TILE_STATE_SIZE_factionObjectID + TILE_STATE_SIZE_FREE_BITS)


// Bit positions in the "state"
// NOTE: previously properties were defined to start from 32 but factionID was also set to start from 32
//  -> func to get or set tile's faction id was never used but it seems that would have been fucked up
//  because of above. Don't remember was that just some mindfuck or some reason for this...
//  -> ALSO bit stuff were modified -> id stuff takes 26 bits instead of prev 32
//#define TILE_STATE_POS_properties	32
#define TILE_STATE_POS_properties 0
#define TILE_STATE_POS_ID         39
#define TILE_STATE_POS_factionID  39
#define TILE_STATE_POS_factionObjectID 49

#define TILE_STATE_POS_terrElevation 0
#define TILE_STATE_POS_terrType		 5
#define TILE_STATE_POS_terrEffect	 8

#define TILE_STATE_POS_thingID		 10
#define TILE_STATE_POS_action		 19
#define TILE_STATE_POS_dir		     22
#define TILE_STATE_POS_customVar	 25
#define TILE_STATE_POS_objProperties 10

// Max values of specific properties
#define TILE_STATE_MAX_terrElevation 31
#define TILE_STATE_MAX_action 7
#define TILE_STATE_MAX_factionid (uint32_t)0x3FF

namespace gamecommon
{
    enum TileStateTerrElevation
    {
        TILE_STATE_terrElevAbyss = 		0,
        TILE_STATE_terrElevMid1 = 		1,
        TILE_STATE_terrElevMid2 = 		2,
        TILE_STATE_terrElevHighland = 	3,
        TILE_STATE_terrElevHills = 		4,
        TILE_STATE_terrElevMountains = 		5,
        TILE_STATE_terrElevHighMountains = 	6
    };

    enum TileStateTerrEffectFlags
    {
        TILE_STATE_terrEffectRain = 0x01
    };

    enum TileStateAction
    {
        TILE_STATE_actionIdle = 	0,
        TILE_STATE_actionMove = 	1,
        TILE_STATE_actionMoveVertical = 2,
        TILE_STATE_actionClassAction1 = 3,
        TILE_STATE_actionClassAction2 = 4,

        // Not decided yet, what would these be? ( these are also available values to use..)
        TILE_STATE_actionPENDING2 = 5,
        TILE_STATE_actionPENDING3 = 6,
        TILE_STATE_actionPENDING4 = 7,
    };

    enum TileStateDirection
    {
        TILE_STATE_dirN = 	0,
        TILE_STATE_dirNE = 	1,
        TILE_STATE_dirE = 	2,
        TILE_STATE_dirSE = 	3,
        TILE_STATE_dirS = 	4,
        TILE_STATE_dirSW = 	5,
        TILE_STATE_dirW = 	6,
        TILE_STATE_dirNW = 	7
    };

    struct Tile
    {

        uint64_t state = 0;
    };


    void set_tile_terrelevation	(uint64_t& tile, GC_ubyte value);
    void set_tile_terrtype      (uint64_t& tile, GC_ubyte value);
    void set_tile_terreffect	(uint64_t& tile, GC_ubyte value);
    void set_tile_thingid       (uint64_t& tile, GC_ubyte value);
    void set_tile_action        (uint64_t& tile, GC_ubyte value);
    void set_tile_facingdir     (uint64_t& tile, GC_ubyte value);
    void set_tile_customvar     (uint64_t& tile, GC_ubyte value);
    void set_tile_factionid     (uint64_t& tile, uint32_t id);
    void set_tile_faction_objid (uint64_t& tile, uint32_t id);
    // Some more specific custom stuff
    void transfer_obj_to		(uint64_t& from, uint64_t& to); // Transfers object from one tile to another ()

    GC_ubyte get_tile_terrelevation (uint64_t tile);
    GC_ubyte get_tile_terrtype      (uint64_t tile);
    GC_ubyte get_tile_terreffect    (uint64_t tile);
    GC_ubyte get_tile_thingcategory (uint64_t tile);
    GC_ubyte get_tile_thingid   (uint64_t tile);
    GC_ubyte get_tile_action    (uint64_t tile);
    GC_ubyte get_tile_facingdir (uint64_t tile);
    GC_ubyte get_tile_customvar	(uint64_t tile);
    uint16_t get_tile_factionid	(uint64_t tile);
    uint16_t get_tile_faction_objid (uint64_t tile);
    uint32_t get_tile_uid           (uint64_t tile);
}



