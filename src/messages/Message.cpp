#include "Message.h"
#include <iostream>


#define LS_DEBUG_MESSAGE_TAG__INFO          ""
#define LS_DEBUG_MESSAGE_TAG__WARNING       "(Warning)"
#define LS_DEBUG_MESSAGE_TAG__ERROR         "[ERROR]"
#define LS_DEBUG_MESSAGE_TAG__FATAL_ERROR   "<!FATAL ERROR!>"


namespace gamecommon
{
    Message::Message(const GC_byte* pData, size_t dataSize, size_t requiredSize, bool dynamicSize)
    {
        if (pData != nullptr)
        {
            _isValid = validateSize(
                "Base Message",
                dataSize,
                requiredSize,
                dynamicSize ? MESSAGE_VALIDATION_COMPARISON_LTEQ : MESSAGE_VALIDATION_COMPARISON_EQ
            );
            if (_isValid)
            {
                _dataSize = dataSize;
                _pData = new GC_byte[_dataSize];
                memcpy(_pData, pData, _dataSize);
                memcpy(&_type, pData, sizeof(int32_t));
            }
            #ifdef DEBUG_INVALID_MESSAGE_DATA
            else
            {
                // Try getting possibly message type from pData
                // NOTE: If fucked up msg, this is incorrect type -> interpret it with a grain of salt
                int32_t parsedType = -1;
                if (dataSize > sizeof(int32_t))
                    memcpy(&parsedType, pData, sizeof(int32_t));

                std::string rawStr(pData, dataSize);
                std::string bytesStr = "";
                for (int i = 0; i < dataSize; ++i)
                {
                    int val = (int)pData[i];
                    bytesStr += std::to_string(val);
                    if (i < dataSize - 1)
                        bytesStr += ",";
                }
                MsgDebug::log(
                    "Invalid message parsed type: " + std::to_string(parsedType) +
                    " raw str: " + rawStr +
                    " bytes: " + bytesStr,
                    MsgDebug::MessageType::ERROR
                );
            }
            #endif
        }
    }

    Message::Message(int32_t type, size_t allocSize, size_t dynamicSizeCap) :
        _type(type)
    {
        if (dynamicSizeCap > 0)
            _isValid = validateSize(
                "Base Message",
                allocSize,
                dynamicSizeCap,
                MESSAGE_VALIDATION_COMPARISON_LTEQ
            );
        else
            _isValid = true;

        if (_isValid)
        {
            _dataSize = allocSize;
            _pData = new GC_byte[_dataSize];
            memset(_pData, 0, _dataSize);
            addData((const GC_byte*)&_type, sizeof(int32_t));
        }
    }

    Message::Message(const Message& other) :
        _type(other._type),
        _dataSize(other._dataSize),
        _isValid(other._isValid)
    {
        _pData = new GC_byte[_dataSize];
        memcpy(_pData, other._pData, _dataSize);
        memcpy(&_type, _pData, MESSAGE_ENTRY_SIZE__header);
    }

    Message::~Message()
    {
        delete[] _pData;
    }

    bool Message::validateSize(
        std::string msgClassName,
        size_t left,
        size_t right,
        GC_byte comparison
    ) const
    {
        std::string comparisonInfo = "";
        switch (comparison)
        {
            case MESSAGE_VALIDATION_COMPARISON_EQ:
                if (left == right) return true;
                comparisonInfo = " Required size: " + std::to_string(right);
                break;
            case MESSAGE_VALIDATION_COMPARISON_LT:
                if (left < right) return true;
                comparisonInfo = " Size needs to be less than: " + std::to_string(right);
                break;
            case MESSAGE_VALIDATION_COMPARISON_LTEQ:
                if (left <= right) return true;
                comparisonInfo = " Size needs to be less or equal to: " + std::to_string(right);
                break;
            case MESSAGE_VALIDATION_COMPARISON_GREQ:
                if (left >= right) return true;
                comparisonInfo = " Size needs to be greater or equal to: " + std::to_string(right);
                break;
            default:
                break;
        }
        MsgDebug::log(
            "Invalid data size for: " + msgClassName +
            ". Size was: " + std::to_string(left) +
            comparisonInfo,
            MsgDebug::MessageType::FATAL_ERROR
        );
        return false;
    }

    void Message::addData(const GC_byte* pData, size_t dataSize)
    {
        if (_pData == nullptr)
        {
            MsgDebug::log(
                "Attempted to add data to Message but underlying data buffer was nullptr",
                MsgDebug::MessageType::WARNING
            );
            return;
        }
        if (_writePos + dataSize > _dataSize)
        {
            MsgDebug::log(
                "Attempted to add data to Message but inputted data size went out of bounds of allocated space."
                " Current byte position: " + std::to_string(_writePos) +
                " Size to add: " + std::to_string(dataSize) +
                " Allocated size: " + std::to_string(_dataSize),
                MsgDebug::MessageType::WARNING
            );
            return;
        }
        memcpy(_pData + _writePos, pData, dataSize);
        _writePos += dataSize;
    }

    void Message::addStr(const std::string& str, size_t allocSize)
    {
        if (str.size() > allocSize)
        {
            MsgDebug::log(
                "Attempted to add string to Message but inputted string size was greater than inputted alloc size."
                " String size: " + std::to_string(str.size()) +
                " alloc size: " + std::to_string(allocSize),
                MsgDebug::MessageType::ERROR
            );
            return;
        }
        else if (_writePos + allocSize > _dataSize)
        {
            MsgDebug::log(
                "Attempted to add data(str) to Message but inputted data size went out of bounds of allocated space."
                " Current byte position: " + std::to_string(_writePos) +
                " Size to add: " + std::to_string(allocSize) +
                " Allocated size: " + std::to_string(_dataSize),
                MsgDebug::MessageType::ERROR
            );
            return;
        }
        GC_byte buf[allocSize];
        memset(buf, 0, allocSize);
        memcpy(buf, str.data(), str.size());
        memcpy(_pData + _writePos, buf, allocSize);
        _writePos += allocSize;
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
