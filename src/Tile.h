#pragma once

#include <cstdint>
#include "Common.h"

// Size of the full state (in bytes)
// NOTE: It seems this is fucking wrong and not used anywhere?
// TODO: Delete?
#define TILE_STATE_SIZE_BYTES 		8

// Sizes of different portions (exact size in BITS NOT BYTES!)
#define TILE_STATE_SIZE			64

#define TILE_STATE_SIZE_terrElevation	5
#define TILE_STATE_SIZE_terrType	    3
#define TILE_STATE_SIZE_temperature     3
#define TILE_STATE_SIZE_effect	        2

#define TILE_STATE_SIZE_thingID		    8
#define TILE_STATE_SIZE_action		    3
#define TILE_STATE_SIZE_dir		        3
#define TILE_STATE_SIZE_customVar	    4
#define TILE_STATE_SIZE_factionID       10
#define TILE_STATE_SIZE_factionObjectID 16
// Atm need to take free bits into account since want to have id stuff at the end
// but also we have some free bits atm between tile data and id stuff..
#define TILE_STATE_SIZE_FREE_BITS 7
#define TILE_STATE_SIZE_objProperties	(TILE_STATE_SIZE_thingID + TILE_STATE_SIZE_action + TILE_STATE_SIZE_dir + TILE_STATE_SIZE_customVar + TILE_STATE_SIZE_factionID + TILE_STATE_SIZE_factionObjectID + TILE_STATE_SIZE_FREE_BITS)


// Bit positions in the "state"
// NOTE: previously properties were defined to start from 32 but factionID was also set to start from 32
//  -> func to get or set tile's faction id was never used but it seems that would have been fucked up
//  because of above. Don't remember was that just some mindfuck or some reason for this...
//  -> ALSO bit stuff were modified -> id stuff takes 26 bits instead of prev 32
//#define TILE_STATE_POS_properties	32
#define TILE_STATE_POS_properties 0
#define TILE_STATE_POS_ID         38
#define TILE_STATE_POS_factionID  38
#define TILE_STATE_POS_factionObjectID 48

#define TILE_STATE_POS_terrElevation    0
#define TILE_STATE_POS_terrType		    5
#define TILE_STATE_POS_temperature      8
#define TILE_STATE_POS_effect	        11

#define TILE_STATE_POS_thingID		 13
#define TILE_STATE_POS_action		 21
#define TILE_STATE_POS_dir		     24
#define TILE_STATE_POS_customVar	 27
#define TILE_STATE_POS_objProperties 13

// Max values of specific properties
#define TILE_STATE_MAX_terrElevation 31
#define TILE_STATE_MAX_action 7
#define TILE_STATE_MAX_factionid (uint32_t)0x3FF

namespace gamecommon
{
    enum TileStateTerrType
    {
        TILE_STATE_terrTypeBarren =     0,
        TILE_STATE_terrTypeWater =      1,
        TILE_STATE_terrTypeRock =       2,
        TILE_STATE_terrTypeFertile =    3,
        TILE_STATE_terrTypeSnow =       4,
        TILE_STATE_terrTypePending1 =   5,
        TILE_STATE_terrTypePending2 =   6
    };

    // NOTE: index 0 has to be the most "default" value
    // so cannot use signed values here -> tried that already..
    enum TileStateTemperature
    {
        TILE_STATE_mild =      0,
        TILE_STATE_chilly =    1,
        TILE_STATE_cold =      2,
        TILE_STATE_freezing =  3,
        TILE_STATE_warm =      4,
        TILE_STATE_hot =       5,
        TILE_STATE_burning =   6
    };

    enum TileStateEffect
    {
        TILE_STATE_effectNone = 0
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


    void set_tile_terrelevation (uint64_t& tile, GC_ubyte value);
    void set_tile_terrtype      (uint64_t& tile, GC_ubyte value);
    void set_tile_temperature   (uint64_t& tile, GC_ubyte value);
    void set_tile_effect        (uint64_t& tile, GC_ubyte value);

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
    GC_ubyte get_tile_temperature   (uint64_t tile);
    GC_ubyte get_tile_effect    (uint64_t tile);

    GC_ubyte get_tile_thingcategory (uint64_t tile);
    GC_ubyte get_tile_thingid   (uint64_t tile);
    GC_ubyte get_tile_action    (uint64_t tile);
    GC_ubyte get_tile_facingdir (uint64_t tile);
    GC_ubyte get_tile_customvar	(uint64_t tile);
    uint16_t get_tile_factionid	(uint64_t tile);
    uint16_t get_tile_faction_objid (uint64_t tile);
    uint32_t get_tile_uid           (uint64_t tile);
}



