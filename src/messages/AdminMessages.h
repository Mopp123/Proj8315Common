#pragma once

#include "Message.h"
#include "Tile.h"

// NOTE: Atm each admin message requires having client sending username and password
// kind of like "sudo" command to server...

#define MESSAGE_REQUIRED_SIZE__SpawnRequest (MESSAGE_ENTRY_SIZE__header + USER_NAME_SIZE + USER_PASSWD_SIZE + TILE_STATE_SIZE_thingID + sizeof(int32_t) * 2)


namespace gamecommon
{
    class SpawnRequest : public Message
    {
    private:
        GC_byte _username[USER_NAME_SIZE];
        GC_byte _password[USER_PASSWD_SIZE];
        GC_ubyte _objectType = 0;
        // these are signed atm just because was using signed ints with other positions atm
        // TODO: Maybe in the future force all positions be unsigned
        int32_t _targetX = 0;
        int32_t _targetY = 0;

    public:
        SpawnRequest(const GC_byte* pData, size_t dataSize);
        SpawnRequest(
            GC_byte* username,
            size_t usernameSize,
            GC_byte* password,
            size_t passwordSize,
            GC_ubyte* objectType,
            size_t objectTypeSize,
            int32_t targetX,
            int32_t targetY
        );
        SpawnRequest(const SpawnRequest& other);
        ~SpawnRequest() {}
        inline std::string getUsername() const { return std::string(_username, USER_NAME_SIZE); }
        inline std::string getPassword() const { return std::string(_password, USER_PASSWD_SIZE); }
        inline GC_ubyte getObjectType() const { return _objectType; }
        inline int32_t getTargetX() const { return _targetX; }
        inline int32_t getTargetY() const { return _targetY; }

        inline const GC_byte* getUsernameData() const { return _username; }
        inline const GC_byte* getPasswordData() const { return _password; }
    };
}
