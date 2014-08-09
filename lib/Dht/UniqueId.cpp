
#include "Dht/UniqueId.h"

namespace IsoPeer { namespace Dht {

    UniqueId UniqueId::Distance(const UniqueId& first, const UniqueId& second)
    {
        UniqueId returnId;
        for (int i = 0; i < sizeof(m_bytes); i++)
        {
            returnId.m_bytes[i] = first.m_bytes[i] ^ second.m_bytes[i];
        }

        return returnId;
    }

} }