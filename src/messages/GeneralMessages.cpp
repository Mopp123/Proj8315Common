#include "GeneralMessages.h"


namespace gamecommon
{
    LoginRequest::LoginRequest(const GC_byte* pData, size_t dataSize) :
        Message(pData, dataSize, MESSAGE_REQUIRED_SIZE__LoginRequest)
    {
        if (_isValid)
        {
            memcpy(_username, _pData + MESSAGE_ENTRY_SIZE__header, USER_NAME_SIZE);
            memcpy(_password, _pData + MESSAGE_ENTRY_SIZE__header + USER_NAME_SIZE, USER_PASSWD_SIZE);
        }
    }

    LoginRequest::LoginRequest(GC_byte* username, size_t usernameSize, GC_byte* password, size_t passwordSize) :
        Message(MESSAGE_TYPE__LoginRequest, MESSAGE_REQUIRED_SIZE__LoginRequest)
    {
        if (_isValid)
        {
            addData(username, USER_NAME_SIZE);
            addData(password, USER_PASSWD_SIZE);

            memcpy(_username, username, USER_NAME_SIZE);
            memcpy(_password, password, USER_PASSWD_SIZE);
        }
    }

    LoginRequest::LoginRequest(const LoginRequest& other) :
        Message(other._pData, other._dataSize, MESSAGE_REQUIRED_SIZE__LoginRequest)
    {
        if (_isValid)
        {
            memset(_username, 0, USER_NAME_SIZE);
            memset(_password, 0, USER_NAME_SIZE);
            memcpy(_username, _pData + MESSAGE_ENTRY_SIZE__header, USER_NAME_SIZE);
            memcpy(_password, _pData + MESSAGE_ENTRY_SIZE__header + USER_NAME_SIZE, USER_PASSWD_SIZE);
        }
    }


    LoginResponse::LoginResponse(const GC_byte* pData, size_t dataSize) :
        Message(pData, dataSize, MESSAGE_REQUIRED_SIZE__LoginResponse)
    {
        if (_isValid)
        {
            const size_t factionSize = Faction::get_netw_size();
            memcpy(&_success, _pData + MESSAGE_ENTRY_SIZE__header, 1);

            std::string factionID = std::string(_pData + (MESSAGE_ENTRY_SIZE__header + 1 + MESSAGE_ERR_STR_SIZE), UUID_SIZE);
            std::string factionName = std::string(_pData + (MESSAGE_ENTRY_SIZE__header + 1 + MESSAGE_ERR_STR_SIZE + UUID_SIZE), FACTION_NAME_SIZE);
            _faction = Faction(factionID, factionName);

            _error = std::string(_pData + MESSAGE_ENTRY_SIZE__header + 1 + factionSize, MESSAGE_ERR_STR_SIZE);
            //memcpy(&_error, _pData + MESSAGE_ENTRY_SIZE__header + 1 + factionSize, MESSAGE_ERR_STR_SIZE);
        }
    }

    LoginResponse::LoginResponse(bool success, Faction faction, const std::string error) :
        Message(MESSAGE_TYPE__LoginResponse, MESSAGE_REQUIRED_SIZE__LoginResponse)
    {
        if (_isValid)
        {
            _success = success;
            _faction = faction;
            _error = error;

            GC_byte successByte = (GC_byte)success;
            addData(&successByte, 1);
            // NOTE: Works only bacause of alignment of Faction class and FACTION_NETW_SIZE
            // TODO: Make more proper!!
            addData((GC_byte*)&faction, FACTION_NETW_SIZE);

            addStr(_error, MESSAGE_ERR_STR_SIZE);
        }
    }

    LoginResponse::LoginResponse(const LoginResponse& other) :
        Message(other._pData, other._dataSize, MESSAGE_REQUIRED_SIZE__LoginResponse)
    {
        if (_isValid)
        {
            _success = other._success;
            _faction = other._faction;
            _error = other._error;
        }
    }


    UserRegisterRequest::UserRegisterRequest(const GC_byte* pData, size_t dataSize) :
        Message(pData, dataSize, MESSAGE_REQUIRED_SIZE__UserRegisterRequest)
    {
        if (_isValid)
        {
            memcpy(_username, _pData + MESSAGE_ENTRY_SIZE__header, USER_NAME_SIZE);
            memcpy(_password, _pData + MESSAGE_ENTRY_SIZE__header + USER_NAME_SIZE, USER_PASSWD_SIZE);
            memcpy(_repassword, _pData + MESSAGE_ENTRY_SIZE__header + USER_NAME_SIZE + USER_PASSWD_SIZE, USER_PASSWD_SIZE);
        }
    }

    UserRegisterRequest::UserRegisterRequest(GC_byte* username, size_t usernameSize, GC_byte* password, size_t passwordSize, GC_byte* repassword, size_t repasswordSize) :
        Message(MESSAGE_TYPE__UserRegisterRequest, MESSAGE_REQUIRED_SIZE__UserRegisterRequest)
    {
        if (_isValid)
        {
            addData(username, USER_NAME_SIZE);
            addData(password, USER_PASSWD_SIZE);
            addData(repassword, USER_PASSWD_SIZE);

            memcpy(_username, username, USER_NAME_SIZE);
            memcpy(_password, password, USER_PASSWD_SIZE);
            memcpy(_repassword, repassword, USER_PASSWD_SIZE);
        }
    }

    UserRegisterRequest::UserRegisterRequest(const UserRegisterRequest& other) :
        Message(other._pData, other._dataSize, MESSAGE_REQUIRED_SIZE__UserRegisterRequest)
    {
        if (_isValid)
        {
            memset(_username, 0, USER_NAME_SIZE);
            memset(_password, 0, USER_PASSWD_SIZE);
            memset(_repassword, 0, USER_PASSWD_SIZE);

            memcpy(_username, _pData + MESSAGE_ENTRY_SIZE__header, USER_NAME_SIZE);
            memcpy(_password, _pData + MESSAGE_ENTRY_SIZE__header + USER_NAME_SIZE, USER_PASSWD_SIZE);
            memcpy(_repassword, _pData + MESSAGE_ENTRY_SIZE__header + USER_NAME_SIZE + USER_PASSWD_SIZE, USER_PASSWD_SIZE);
        }
    }


    UserRegisterResponse::UserRegisterResponse(const GC_byte* pData, size_t dataSize) :
        Message(pData, dataSize, MESSAGE_REQUIRED_SIZE__UserRegisterResponse)
    {
        if (_isValid)
        {
            memcpy(&_success, _pData + MESSAGE_ENTRY_SIZE__header, 1);
            memcpy(&_error, _pData + MESSAGE_ENTRY_SIZE__header + 1, MESSAGE_ERR_STR_SIZE);
        }
    }

    UserRegisterResponse::UserRegisterResponse(bool success, const std::string error) :
        Message(MESSAGE_TYPE__UserRegisterResponse, MESSAGE_REQUIRED_SIZE__UserRegisterResponse)
    {
        if (_isValid)
        {
            GC_byte successByte = (GC_byte)success;
            addData(&successByte, 1);

            // Make sure error message data doesn't contain any funny bytes
            // (if message smaller than max size -> make sure all bytes = 0)
            memset(_error, 0, MESSAGE_ERR_STR_SIZE);
            size_t errDataSize = error.size();
            if (errDataSize > MESSAGE_ERR_STR_SIZE)
                errDataSize = MESSAGE_ERR_STR_SIZE;
            memcpy(_error, error.data(), errDataSize);
            addData(_error, MESSAGE_ERR_STR_SIZE);

            _success = success;
        }
    }

    UserRegisterResponse::UserRegisterResponse(const UserRegisterResponse& other) :
        Message(other._pData, other._dataSize, MESSAGE_REQUIRED_SIZE__UserRegisterResponse)
    {
        if (_isValid)
        {
            _success = other._success;
            memcpy(_error, other._error, MESSAGE_ERR_STR_SIZE);
        }
    }
}

