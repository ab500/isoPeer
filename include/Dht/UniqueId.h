#pragma once

#include <stdint.h>
#include <cstring>

namespace IsoPeer { namespace Dht {

    // A simple 160bit key that serves as a building block for identifiers in the
    // DHT. It is used for node identification, message sender authentication, and
    // object storage.
    class UniqueId 
    {
    public:
        UniqueId()
            : m_bytes()
        {}

        UniqueId(uint8_t bytes[20])
        {
            memcpy(m_bytes, bytes, sizeof(m_bytes));
        }

        UniqueId(const UniqueId& other)
        {
            memcpy(m_bytes, other.m_bytes, sizeof(m_bytes));
        }

        UniqueId& operator=(const UniqueId& other)
        {
            memcpy(m_bytes, other.m_bytes, sizeof(m_bytes));
            return *this;
        }

        bool operator ==(const UniqueId& other)
        {
            return memcmp(m_bytes, other.m_bytes, sizeof(m_bytes)) == 0;
        }

        bool operator!=(const UniqueId& other)
        {
            return !operator==(other);
        }

        static UniqueId Distance(const UniqueId& first, const UniqueId& second);

    private: 
       uint8_t m_bytes[20];
    };
} }