#pragma once

#include <cstring>
#include <string>

#define DEBUG_INVALID_MESSAGE_DATA

#define GC_byte char
#define GC_ubyte unsigned char

#define DIR_N 	0
#define DIR_NE 	1
#define DIR_E 	2
#define DIR_SE 	3
#define DIR_S 	4
#define DIR_SW 	5
#define DIR_W 	6
#define DIR_NW 	7

#define USER_ID_LEN 32

#define USER_NAME_SIZE 	32
#define USER_PASSWD_SIZE 32
#define MOTD_LEN        256 // NOT USED ANYMORE!!!

#define NULL_USER User("", nullptr, 0, false, 0, 0)

#define USER_OBSERVE_RADIUS 15
#define USER_OBSERVE_WIDTH (15 * 2 + 1)
#define USER_OBSERVE_AREA (USER_OBSERVE_WIDTH * USER_OBSERVE_WIDTH)

#define UUID_SIZE 32

#define MAX_FACTION_COUNT 1024


namespace gamecommon
{
    class User
    {
    private:
        // When user logged in this is used to identify its' db record
        std::string _id = "";

        GC_byte _nameData[USER_NAME_SIZE];
        std::string _nameStr = "";
        bool _isLoggedIn = false;
        bool _isAdmin = false;

        int _xPos = 0;
        int _zPos = 0;
        int _observeRadius = 15;

        // Key used to identify the user's faction in "Game"
        // NOTE: Used std::string here, since this data is not supposed to be netw data
        std::string _factionName = "";

    public:
        User() {}
        User(
            const std::string& id,
            const GC_byte* nameData,
            size_t nameSize,
            bool isAdmin,
            int tileX,
            int tileZ
        );
        User(const User& other);

        void updateObserveProperties(int x, int z, int radius);
        bool operator==(const User& other) const;
        bool operator!=(const User& other) const;

        inline const int& getX() const { return _xPos; }
        inline const int& getZ() const { return _zPos; }
        inline const int& getObserveRadius() const { return _observeRadius; }

        inline bool isLoggedIn() const { return _isLoggedIn; }
        inline bool isAdmin() const { return _isAdmin; }

        inline const std::string& getID() const { return _id; }
        inline const GC_byte* getNameData() const { return _nameData; }
        inline const std::string& getName() const { return _nameStr; }
        inline const std::string& getFactionName() const { return _factionName; }
        inline void setFactionName(const std::string& name) { _factionName = name; }
    };
}
