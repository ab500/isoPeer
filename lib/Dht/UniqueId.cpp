
#include "Dht/UniqueId.h"
#include "Common/Base58Encoder.h"

namespace IsoPeer { namespace Substrate { namespace Dht {

    UniqueId UniqueId::Distance(const UniqueId& first, const UniqueId& second)
    {
        UniqueId returnId;
        for (size_t i = 0; i < first.m_bytes.size(); i++)
        {
            returnId.m_bytes[i] = first.m_bytes[i] ^ second.m_bytes[i];
        }
        return returnId;
    }

    std::string UniqueId::ToBase58String() const
    {
        return IsoPeer::Common::Base58Encoder::Encode(std::vector<uint8_t>(m_bytes.begin(), m_bytes.end()));
    }

} } }