#pragma once

#include "Message.h"
#include "Common.h"
#include "Object.h"
#include <vector>

#define MESSAGE_SIZE_CAP_ObjInfoLib (MESSAGE_ENTRY_SIZE__header + sizeof(int32_t) + gamecommon::get_netw_objinfo_size() * 256)


namespace gamecommon
{
    class ObjInfoLibResponse : public Message
    {
    private:
        std::vector<ObjectInfo> _objects;

    public:
        ObjInfoLibResponse(const GC_byte* pData, size_t dataSize);
        ObjInfoLibResponse(const std::vector<ObjectInfo>& objInfoLib);
        ObjInfoLibResponse(const ObjInfoLibResponse& other);
        ~ObjInfoLibResponse() {}

        inline std::vector<ObjectInfo> getObjects() const { return _objects; }
    };
}
