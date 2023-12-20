#pragma once

#include "Message.h"
#include "Common.h"
#include "Object.h"
#include <vector>

#define MESSAGE_SIZE_CAP_ObjInfoLib (MESSAGE_ENTRY_SIZE__header + sizeof(int32_t) + gamecommon::get_netw_objinfo_size() * 256)


namespace gamecommon
{
    class ObjInfoLibMsg : public Message
    {
    private:
        std::vector<ObjectInfo> _objects;

    public:
        ObjInfoLibMsg(const GC_byte* pData, size_t dataSize);
        ObjInfoLibMsg(const std::vector<ObjectInfo>& objInfoLib);
        ObjInfoLibMsg(const ObjInfoLibMsg& other);
        ~ObjInfoLibMsg() {}

        inline std::vector<ObjectInfo> getObjects() const { return _objects; }
    };
}
