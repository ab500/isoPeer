
#include "Dht/UniqueId.h"

namespace IsoPeer { namespace Substrate { namespace Dht {

    UniqueId UniqueId::Distance(const UniqueId& first, const UniqueId& second)
    {
        UniqueId returnId;
        for (int i = 0; i < first.m_bytes.size(); i++)
        {
            returnId.m_bytes[i] = first.m_bytes[i] ^ second.m_bytes[i];
        }
        return returnId;
    }

} } }