#pragma once

#include <cstddef>
#include <string.h>
#include "Common.h"
#include "Faction.h"

#define USER_ID_LEN 32
#define MESSAGE_MAX_DATA_SIZE (100*100*8)
#define MESSAGE_MIN_DATA_SIZE sizeof(int32_t)

#define MESSAGE_ENTRY_SIZE__header sizeof(int32_t)

#define NULL_MESSAGE Message(0, nullptr, 0)

#define MESSAGE_INFO_MESSAGE_LEN 256
#define MESSAGE_ERR_STR_SIZE 256

#define MESSAGE_TYPE__GetServerMessage          0x1
#define MESSAGE_TYPE__UserLogin            	0x2
#define MESSAGE_TYPE__UserLogout            	0x3
#define MESSAGE_TYPE__UserRegister            	0x4
#define MESSAGE_TYPE__GetObjInfoLib             0x5
#define MESSAGE_TYPE__CreateFaction             0x6
#define MESSAGE_TYPE__EditFaction               0x7
#define MESSAGE_TYPE__GetWorldState             0x8
#define MESSAGE_TYPE__GetAllFactions            0x9
#define MESSAGE_TYPE__GetChangedFactions        0x10
#define MESSAGE_TYPE__UpdateObserverProperties 	0x11
#define MESSAGE_TYPE__Deploy 	                0x12
//#define MESSAGE_TYPE__ServerShutdown            0x11

// NEW MESSAGE TYPES
#define MESSAGE_TYPE__LoginRequest            	0x2
#define MESSAGE_TYPE__LoginResponse            	0x2


#define MESSAGE_VALIDATION_COMPARISON_EQ 0
#define MESSAGE_VALIDATION_COMPARISON_LT 1
#define MESSAGE_VALIDATION_COMPARISON_GREQ 2 // greater or equal

namespace gamecommon
{
    class Message
    {
    protected:
        int32_t _type = 0;
        GC_byte* _pData = nullptr;
        size_t _dataSize = 0;

        size_t _writePos = 0;

    public:
        Message(GC_byte* pData, size_t dataSize);
        Message(int32_t type, GC_byte* pData, size_t dataSize);
        Message(const Message& other);
        virtual ~Message();
        inline int32_t getType() const { return _type; }
        inline GC_byte* getData() { return _pData; }
        inline size_t getDataSize() const { return _dataSize; }

        bool operator==(const Message& other)
        {
            bool dataEqual = false;
            if (_dataSize == other._dataSize && _pData != nullptr && other._pData != nullptr)
                dataEqual = memcmp(_pData, other._pData, _dataSize) == 0;
            else
                dataEqual = _pData == nullptr && other._pData == nullptr;
            return _dataSize == other._dataSize && dataEqual;
        }

        bool operator!=(const Message& other)
        {
            bool dataEqual = false;
            if (_dataSize == other._dataSize && _pData != nullptr && other._pData != nullptr)
                dataEqual = memcmp(_pData, other._pData, _dataSize) == 0;
            else
                dataEqual = _pData == nullptr && other._pData == nullptr;
            return _dataSize != other._dataSize || !dataEqual;
        }

    protected:
        bool validateSize(
            std::string msgClassName,
            size_t inputSize,
            size_t requiredSize,
            GC_byte comparison
        ) const;

        void addData(GC_byte* pData, size_t dataSize);
    };


    class LoginRequest : public Message
    {
    private:
        GC_byte _username[USER_NAME_SIZE];
        GC_byte _password[USER_PASSWD_SIZE];

    public:
        LoginRequest(GC_byte* pData, size_t dataSize);
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
        Faction _faction = NULL_FACTION;
        GC_byte _error[MESSAGE_ERR_STR_SIZE];

    public:
        LoginResponse(GC_byte* pData, size_t dataSize);
        LoginResponse(bool success, Faction faction, GC_byte* error, size_t errorSize);
        LoginResponse(const LoginResponse& other);
        ~LoginResponse() {}
        inline std::string getError() const { return std::string(_error, MESSAGE_ERR_STR_SIZE); }
    };


    class MsgDebug
    {
    public:
        enum MessageType
        {
            INFO = 0x0,
            WARNING,
            ERROR,
            FATAL_ERROR
        };

        static void log(std::string message, MessageType t = INFO);
        static void print_bytes(const char* data, size_t dataSize, int count, std::string message = "");
    };
}

