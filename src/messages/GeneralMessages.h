#pragma once

#include "Message.h"

#define SERVER_INFO_MESSAGE_SIZE 200
#define MESSAGE_REQUIRED_SIZE__ServerInfo (MESSAGE_ENTRY_SIZE__header + SERVER_INFO_MESSAGE_SIZE)

#define MESSAGE_REQUIRED_SIZE__LoginRequest (MESSAGE_ENTRY_SIZE__header + USER_NAME_SIZE + USER_PASSWD_SIZE)
#define MESSAGE_REQUIRED_SIZE__LoginResponse (MESSAGE_ENTRY_SIZE__header + 1 + 1 + sizeof(int32_t) * 2 + FACTION_NETW_SIZE + MESSAGE_ERR_STR_SIZE)
#define MESSAGE_REQUIRED_SIZE__UserRegisterRequest (MESSAGE_ENTRY_SIZE__header + USER_NAME_SIZE + USER_PASSWD_SIZE * 2)
#define MESSAGE_REQUIRED_SIZE__UserRegisterResponse (MESSAGE_ENTRY_SIZE__header + 1 + MESSAGE_ERR_STR_SIZE)


namespace gamecommon
{
    class ServerInfoResponse : public Message
    {
    private:
        GC_byte _message[SERVER_INFO_MESSAGE_SIZE];

    public:
        ServerInfoResponse(const GC_byte* pData, size_t dataSize);
        ServerInfoResponse(const std::string& message);
        ServerInfoResponse(const ServerInfoResponse& other);
        ~ServerInfoResponse() {}
        inline std::string getMessage() const { return std::string(_message, USER_NAME_SIZE); }
        inline const GC_byte* getMessageData() const { return _message; }
    };


    class LoginRequest : public Message
    {
    private:
        GC_byte _username[USER_NAME_SIZE];
        GC_byte _password[USER_PASSWD_SIZE];

    public:
        LoginRequest(const GC_byte* pData, size_t dataSize);
        LoginRequest(GC_byte* username, size_t usernameSize, GC_byte* password, size_t passwordSize);
        LoginRequest(const LoginRequest& other);
        ~LoginRequest() {}
        inline std::string getUsername() const { return std::string(_username, USER_NAME_SIZE); }
        inline std::string getPassword() const { return std::string(_password, USER_PASSWD_SIZE); }
        inline const GC_byte* getUsernameData() const { return _username; }
        inline const GC_byte* getPasswordData() const { return _password; }
    };


    class LoginResponse : public Message
    {
    private:
        bool _success = false;
        bool _isAdmin = false;
        int32_t _tileX = 0;
        int32_t _tileZ = 0;
        Faction _faction = NULL_FACTION;
        std::string _error;

    public:
        LoginResponse(const GC_byte* pData, size_t dataSize);
        LoginResponse(
            bool success,
            bool isAdmin,
            int32_t tileX,
            int32_t tileZ,
            Faction faction,
            const std::string error
        );
        LoginResponse(const LoginResponse& other);
        ~LoginResponse() {}
        inline bool getSuccess() const { return _success; }
        inline bool isAdmin() const { return _isAdmin; }
        inline int32_t getTileX() const { return _tileX; }
        inline int32_t getTileZ() const { return _tileZ; }
        inline const Faction& getFaction() const { return _faction; }
        inline const std::string& getError() const { return _error; }
    };


    // NOTE: UserRegisterRequest - messages are only temporary before db integration
    class UserRegisterRequest : public Message
    {
    private:
        GC_byte _username[USER_NAME_SIZE];
        GC_byte _password[USER_PASSWD_SIZE];
        GC_byte _repassword[USER_PASSWD_SIZE];

    public:
        UserRegisterRequest(const GC_byte* pData, size_t dataSize);
        UserRegisterRequest(GC_byte* username, size_t usernameSize, GC_byte* password, size_t passwordSize, GC_byte* repassword, size_t repasswordSize);
        UserRegisterRequest(const UserRegisterRequest& other);
        ~UserRegisterRequest() {}
        inline std::string getUsername() const { return std::string(_username, USER_NAME_SIZE); }
        inline std::string getPassword() const { return std::string(_password, USER_PASSWD_SIZE); }
        inline std::string getRePassword() const { return std::string(_repassword, USER_PASSWD_SIZE); }
        inline const GC_byte* getUsernameData() const { return _username; }
        inline const GC_byte* getPasswordData() const { return _password; }
        inline const GC_byte* getRePasswordData() const { return _repassword; }
    };


    // NOTE: UserRegisterResponse - messages are only temporary before db integration
    class UserRegisterResponse : public Message
    {
    private:
        bool _success = false;
        GC_byte _error[MESSAGE_ERR_STR_SIZE];

    public:
        UserRegisterResponse(const GC_byte* pData, size_t dataSize);
        UserRegisterResponse(bool success, const std::string error);
        UserRegisterResponse(const UserRegisterResponse& other);
        ~UserRegisterResponse() {}
        inline std::string getError() const { return std::string(_error, MESSAGE_ERR_STR_SIZE); }
    };
}

