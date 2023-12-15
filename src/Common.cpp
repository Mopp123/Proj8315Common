#include "Common.h"

namespace gamecommon
{
    User::User(const std::string& id,  const GC_byte* nameData, size_t nameSize, int tileX, int tileZ) :
        _id(id),
        _xPos(tileX),
        _zPos(tileZ)
    {
        if (nameSize > USER_NAME_SIZE)
            nameSize = USER_NAME_SIZE;
        memset(_nameData, 0, USER_NAME_SIZE);
        memset(_passwordData, 0, USER_PASSWD_SIZE);
        if (nameData != nullptr)
            memcpy(_nameData, nameData, nameSize);
        _nameStr = std::string(nameData, nameSize);
    }

    User::User(const User& other) :
        _id(other._id),
        _nameStr(other._nameStr),
        _passwordStr(other._passwordStr),
        _isLoggedIn(other._isLoggedIn),
        _xPos(other._xPos),
        _zPos(other._zPos),
        _observeRadius(other._observeRadius),
        _factionName(other._factionName)
    {
        memset(_nameData, 0, USER_NAME_SIZE);
        memset(_passwordData, 0, USER_PASSWD_SIZE);
        memcpy(_nameData, other._nameData, USER_NAME_SIZE);
        memcpy(_passwordData, other._passwordData, USER_PASSWD_SIZE);
    }

    void User::updateObserveProperties(int x, int z, int radius)
    {
        _xPos = x;
        _zPos = z;
        _observeRadius = radius;
    }

    bool User::operator==(const User& other) const
    {
        return _id == other._id;
    }

    bool User::operator!=(const User& other) const
    {
        return _id != other._id;
    }
}
