#pragma once

#include <stdint.h>
#include <cstring>
#include <string>
#include <array>

namespace IsoPeer { namespace Substrate { namespace Dht {

    // A simple 160bit key that serves as a building block for identifiers in the
    // DHT. It is used for node identification, message sender authentication, and
    // object storage. The key, if it were to be represented as an integer, is stored
    // in big-endian network byte order and this is the convention used when doing
    // comparisons.
    class UniqueId 
    {
    public:
        UniqueId()
            : m_bytes()
        {}

        UniqueId(const std::array<uint8_t, 20>& bytes)
        {
            memcpy(m_bytes.data(), bytes.data(), m_bytes.size());
        }

        UniqueId(const UniqueId& other)
        {
            memcpy(m_bytes.data(), other.m_bytes.data(), m_bytes.size());
        }

        UniqueId& operator=(const UniqueId& other)
        {
            memcpy(m_bytes.data(), other.m_bytes.data(), m_bytes.size());
            return *this;
        }

        bool operator ==(const UniqueId& other) const
        {
            return memcmp(m_bytes.data(), other.m_bytes.data(), m_bytes.size()) == 0;
        }

        bool operator!=(const UniqueId& other) const
        {
            return !operator==(other);
        }

        bool operator<(const UniqueId& other) const
        {
            return memcmp(m_bytes.data(), other.m_bytes.data(), m_bytes.size()) < 0;
        }

        bool operator<=(const UniqueId& other) const
        {
            return memcmp(m_bytes.data(), other.m_bytes.data(), m_bytes.size()) <= 0;
        }

        bool operator>(const UniqueId& other) const
        {
            return !operator<=(other);
        }

        bool operator>=(const UniqueId& other) const
        {
            return !operator<(other);
        }

        std::string ToBase58String() const;

        static UniqueId Distance(const UniqueId& first, const UniqueId& second);

    private: 
       std::array<uint8_t, 20> m_bytes;
    };
} } }