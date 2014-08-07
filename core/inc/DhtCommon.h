
#pragma once

#include <stdint.h>

namespace Iso { namespace Dht {

    // A simple 160-bit key that serves as a building block for identifiers in the
    // DHT. It is used for node identification, message sender authentication, and
    // object storage.
    class UniqueId 
    {
    public:
        UniqueId()
            : m_bytes({ 0 })
        {}

        UniqueId(const UniqueId& other)
        {
            memcpy(m_bytes, other.m_bytes, sizeof(m_bytes));
        }

        UniqueId& operator=(const UniqueId& other)
        {
            memcpy(m_bytes, other.m_bytes, sizeof(m_bytes));
            return *this;
        }

        std::wstring ToString()
        {

        }

        static UniqueId Distance(UniqueId& first, UniqueId& second);
        static UniqueId GenerateRandom();

    private:
        uint8_t m_bytes[20];
    };
} }