#include "ObjMessages.h"


namespace gamecommon
{
    ObjInfoLibMsg::ObjInfoLibMsg(const GC_byte* pData, size_t dataSize) :
        Message(pData, dataSize, dataSize, MESSAGE_SIZE_CAP_ObjInfoLib)
    {}

    ObjInfoLibMsg::ObjInfoLibMsg(const std::vector<ObjectInfo>& objInfoLib) :
        Message(MESSAGE_TYPE__ObjInfoLib, MESSAGE_ENTRY_SIZE__header + get_netw_objinfo_size() * objInfoLib.size())
    {
        const size_t objInfoSize = get_netw_objinfo_size();
        for (const ObjectInfo& objInfo : objInfoLib)
            addData((const GC_byte*)&objInfo, objInfoSize);
    }

    ObjInfoLibMsg::ObjInfoLibMsg(const ObjInfoLibMsg& other) :
        Message(other._pData, other._dataSize, other._dataSize, MESSAGE_SIZE_CAP_ObjInfoLib)
    {}
}

