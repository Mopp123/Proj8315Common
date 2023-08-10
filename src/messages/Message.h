#pragma once

#include <cstddef>
#include <string.h>
#include "Common.h"
#include "Faction.h"
#include "Object.h"
#include <unordered_map>

#define USER_ID_LEN 32
#define MESSAGE_MAX_DATA_SIZE (100*100*8)
#define MESSAGE_MIN_DATA_SIZE sizeof(int32_t)

#define MESSAGE_ENTRY_SIZE__header sizeof(int32_t)

#define NULL_MESSAGE Message{}

#define MESSAGE_INFO_MESSAGE_LEN 256
#define MESSAGE_ERR_STR_SIZE 256

// OLD MESSAGE TYPES! To be changed...
#define MESSAGE_TYPE__ServerMessage             0x1
#define MESSAGE_TYPE__UserLogin            	0x2
#define MESSAGE_TYPE__UserLogout            	0x3
#define MESSAGE_TYPE__UserRegister            	0x4
#define MESSAGE_TYPE__ObjInfoLibRequest         0x5
#define MESSAGE_TYPE__CreateFaction             0x6
#define MESSAGE_TYPE__EditFaction               0x7
#define MESSAGE_TYPE__GetAllFactions            0x9
#define MESSAGE_TYPE__GetChangedFactions        0x10
#define MESSAGE_TYPE__UpdateObserverProperties 	0x11
#define MESSAGE_TYPE__Deploy 	                0x12
//#define MESSAGE_TYPE__ServerShutdown            0x11

// NEW MESSAGE TYPES
#define MESSAGE_TYPE__LoginRequest            	0x2
#define MESSAGE_TYPE__LoginResponse            	0x2
#define MESSAGE_TYPE__UserRegisterRequest       0x4
#define MESSAGE_TYPE__UserRegisterResponse      0x4
#define MESSAGE_TYPE__ObjInfoLib                0x5
// ...
#define MESSAGE_TYPE__WorldState                0x8
#define MESSAGE_TYPE__Factions                  0x9
#define MESSAGE_TYPE__UpdatedFactions           0x10

// TODO: Remove this and create server message class defining the whole thing!!!
#define MESSAGE_SIZE__ServerMessageResponse (MESSAGE_ENTRY_SIZE__header + 256)

#define MESSAGE_MAX_SIZE (MESSAGE_ENTRY_SIZE__header + 128 * 128) // ..this just for now..


#define MESSAGE_VALIDATION_COMPARISON_EQ 0
#define MESSAGE_VALIDATION_COMPARISON_LT 1
#define MESSAGE_VALIDATION_COMPARISON_LTEQ 2 // less or equal
#define MESSAGE_VALIDATION_COMPARISON_GREQ 3 // greater or equal


namespace gamecommon
{
    /*
     * Base class for all client - server messaging.
     * Message does all the validation when constructed based on the data its being contructed out of.
     */
    class Message
    {
    protected:
        int32_t _type = 0;
        GC_byte* _pData = nullptr;
        size_t _dataSize = 0;
        size_t _dynamicSizeCap = 0;

        size_t _writePos = 0;

        bool _isValid = false;

    public:
        Message() {}
        Message(const GC_byte* pData, size_t dataSize, size_t requiredSize, size_t dynamicSizeCap = 0);
        // Creates empty message of size: "allocSize"
        Message(int32_t type, size_t allocSize);
        Message(const Message& other);
        virtual ~Message();
        inline int32_t getType() const { return _type; }
        inline GC_byte* getData() const { return _pData; }
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
            size_t left,
            size_t right,
            GC_byte comparison
        ) const;

        void addData(const GC_byte* pData, size_t dataSize);
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

