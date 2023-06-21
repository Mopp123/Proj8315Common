#include "Message.h"
#include <iostream>


#define LS_DEBUG_MESSAGE_TAG__INFO          ""
#define LS_DEBUG_MESSAGE_TAG__WARNING       "(Warning)"
#define LS_DEBUG_MESSAGE_TAG__ERROR         "[ERROR]"
#define LS_DEBUG_MESSAGE_TAG__FATAL_ERROR   "<!FATAL ERROR!>"


namespace gamecommon
{
    Message::Message(GC_byte* pData, size_t dataSize) :
        _dataSize(dataSize)
    {
        if (pData != nullptr && dataSize > 0)
        {
            if (validateSize("Base Message", dataSize, MESSAGE_ENTRY_SIZE__header, MESSAGE_VALIDATION_COMPARISON_GREQ))
            {
                _pData = new GC_byte[dataSize];
                memcpy(_pData, pData, dataSize);
                memcpy(&_type, _pData, sizeof(int32_t));
            }
        }
        else if (dataSize > 0)
        {
            _pData = new GC_byte[_dataSize];
            memset(_pData, 0, _dataSize);
        }
    }

    Message::Message(int32_t type, GC_byte* pData, size_t dataSize) :
        _type(type), _dataSize(sizeof(int32_t) + dataSize)
    {
        if (pData != nullptr && dataSize > 0)
        {
            if (validateSize("Base Message", dataSize, MESSAGE_ENTRY_SIZE__header, MESSAGE_VALIDATION_COMPARISON_GREQ))
            {
                _pData = new GC_byte[dataSize];
                addData((GC_byte*)&type, sizeof(int32_t));
                addData(pData, dataSize);
            }
        }
        else if (dataSize > 0)
        {
            _pData = new GC_byte[_dataSize];
            memset(_pData, 0, _dataSize);
            addData((GC_byte*)&type, sizeof(int32_t));
        }
    }

    Message::Message(const Message& other) :
        _dataSize(other._dataSize)
    {
        if (validateSize("Base Message", other._dataSize, MESSAGE_ENTRY_SIZE__header, MESSAGE_VALIDATION_COMPARISON_LT))
        {
            _pData = new GC_byte[_dataSize];
            memcpy(_pData, other._pData, _dataSize);
            memcpy(&_type, _pData, MESSAGE_ENTRY_SIZE__header);
        }
    }

    Message::~Message()
    {
        delete[] _pData;
    }

    bool Message::validateSize(
        std::string msgClassName,
        size_t inputSize,
        size_t requiredSize,
        GC_byte comparison
    ) const
    {
        bool valid = false;
        std::string comparisonInfo = "";
        switch (comparison)
        {
            case MESSAGE_VALIDATION_COMPARISON_EQ:
                valid = inputSize == requiredSize;
                if (valid) return true;
                comparisonInfo = "Required size: " + std::to_string(requiredSize);
            case MESSAGE_VALIDATION_COMPARISON_LT:
                valid = inputSize < requiredSize;
                if (valid) return true;
                comparisonInfo = "Size needs to be less than: " + std::to_string(requiredSize);
            case MESSAGE_VALIDATION_COMPARISON_GREQ:
                valid = inputSize >= requiredSize;
                if (valid) return true;
                comparisonInfo = "Size needs to be less than: " + std::to_string(requiredSize);
            default:
                break;
        }
        MsgDebug::log(
            "Invalid data size for: " + msgClassName +
            "Size was: " + std::to_string(inputSize) +
            comparisonInfo,
            MsgDebug::MessageType::FATAL_ERROR
        );
        return false;
    }

    void Message::addData(GC_byte* pData, size_t dataSize)
    {
        if (_pData == nullptr)
        {
            MsgDebug::log("Attempted to add data to Message but underlying data buffer was nullptr");
            return;
        }
        if (_writePos + dataSize > _dataSize)
        {
            MsgDebug::log(
                "Attempted to add data to Message but inputted data size went out of bounds of allocated space."
                " Current byte position: " + std::to_string(_writePos) +
                " Size to add: " + std::to_string(dataSize) +
                " Allocated size: " + std::to_string(_dataSize)
            );
            return;
        }
        memcpy(_pData + _writePos, pData, dataSize);
        _writePos += dataSize;
    }


    LoginRequest::LoginRequest(GC_byte* pData, size_t dataSize) :
        Message(MESSAGE_TYPE__LoginRequest, pData, dataSize)
    {
        const size_t requiredSize = MESSAGE_ENTRY_SIZE__header + USER_NAME_SIZE + USER_PASSWD_SIZE;
        if (validateSize("LoginRequest", dataSize, requiredSize, MESSAGE_VALIDATION_COMPARISON_EQ))
        {
            memcpy(_username, _pData + MESSAGE_ENTRY_SIZE__header, USER_NAME_SIZE);
            memcpy(_password, _pData + MESSAGE_ENTRY_SIZE__header + USER_NAME_SIZE, USER_PASSWD_SIZE);
        }
    }

    LoginRequest::LoginRequest(GC_byte* username, size_t usernameSize, GC_byte* password, size_t passwordSize) :
        Message(MESSAGE_TYPE__LoginRequest, nullptr, USER_NAME_SIZE + USER_PASSWD_SIZE)
    {
        addData(username, USER_NAME_SIZE);
        addData(password, USER_PASSWD_SIZE);

        memcpy(_username, username, USER_NAME_SIZE);
        memcpy(_password, password, USER_PASSWD_SIZE);
    }

    LoginRequest::LoginRequest(const LoginRequest& other) :
        Message(MESSAGE_TYPE__LoginRequest, other._pData, other._dataSize)
    {
        const size_t requiredSize = MESSAGE_ENTRY_SIZE__header + USER_NAME_SIZE + USER_PASSWD_SIZE;
        if (validateSize("LoginRequest", other._dataSize, requiredSize, MESSAGE_VALIDATION_COMPARISON_EQ))
        {
            memcpy(_username, _pData + MESSAGE_ENTRY_SIZE__header, USER_NAME_SIZE);
            memcpy(_password, _pData + MESSAGE_ENTRY_SIZE__header + USER_NAME_SIZE, USER_PASSWD_SIZE);
        }
    }


    LoginResponse::LoginResponse(GC_byte* pData, size_t dataSize) :
        Message(MESSAGE_TYPE__LoginResponse, pData, dataSize)
    {
        const size_t factionSize = Faction::get_netw_size();
        const size_t requiredSize = MESSAGE_ENTRY_SIZE__header + 1 + factionSize + MESSAGE_ERR_STR_SIZE;
        if (validateSize("LoginResponse", dataSize, requiredSize, MESSAGE_VALIDATION_COMPARISON_EQ))
        {
            memcpy(&_success, _pData + MESSAGE_ENTRY_SIZE__header, 1);
            memcpy((GC_byte*)&_faction, _pData + MESSAGE_ENTRY_SIZE__header + 1, factionSize);
            memcpy(&_error, _pData + MESSAGE_ENTRY_SIZE__header + 1 + factionSize, MESSAGE_ERR_STR_SIZE);
        }
    }

    LoginResponse::LoginResponse(bool success, Faction faction, GC_byte* error, size_t errorSize) :
        Message(MESSAGE_TYPE__LoginResponse, nullptr, 1 + Faction::get_netw_size() + MESSAGE_ERR_STR_SIZE)
    {
        GC_byte successByte = (GC_byte)success;
        addData(&successByte, 1);
        addData((GC_byte*)&faction, Faction::get_netw_size());
        addData(error, MESSAGE_ERR_STR_SIZE);

        _success = success;
        _faction = faction;
        memcpy(_error, error, MESSAGE_ERR_STR_SIZE);
    }

    LoginResponse::LoginResponse(const LoginResponse& other) :
        Message(MESSAGE_TYPE__LoginResponse, other._pData, other._dataSize)
    {
        const size_t factionSize = Faction::get_netw_size();
        const size_t requiredSize = MESSAGE_ENTRY_SIZE__header + 1 + factionSize + MESSAGE_ERR_STR_SIZE;
        if (validateSize("LoginResponse", other._dataSize, requiredSize, MESSAGE_VALIDATION_COMPARISON_EQ))
        {
            _success = other._success;
            _faction = other._faction;
            memcpy(_error, other._error, MESSAGE_ERR_STR_SIZE);
        }
    }


    void MsgDebug::log(std::string message, MessageType t)
    {
        switch (t)
        {
            case INFO:          std::cout << LS_DEBUG_MESSAGE_TAG__INFO << " " << message << std::endl; break;
            case WARNING:       std::cout << LS_DEBUG_MESSAGE_TAG__WARNING << " " << message << std::endl; break;
            case ERROR:         std::cout << LS_DEBUG_MESSAGE_TAG__ERROR << " " << message << std::endl; break;
            case FATAL_ERROR:   std::cout << LS_DEBUG_MESSAGE_TAG__FATAL_ERROR << " " << message << std::endl; break;
            default:
                break;
        }
    }

    void MsgDebug::print_bytes(const char* data, size_t dataSize, int count, std::string message)
    {
        std::string bytesStr = "";
        for (int i = 0; i < count; ++i)
        {
            if ((int)dataSize <= i)
            {
                MsgDebug::log(
                    "Attempted to print bytes but byte index went out of bounds. Byte index: " +
                    std::to_string(i) + " inputted data size: " + std::to_string(dataSize),
                    MessageType::ERROR
                );
                break;
            }
            int val = (int)data[i];
            bytesStr += std::to_string(val);
            if (i < count - 1)
                bytesStr += ",";
        }
        MsgDebug::log(message + ": " + bytesStr);
    }
}
