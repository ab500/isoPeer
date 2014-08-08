#pragma once

#include <stdint.h>

namespace IsoPeer { namespace Dht {

    // A simple 160bit key that serves as a building block for identifiers in the
    // DHT. It is used for node identification, message sender authentication, and
    // object storage.
    union UniqueId {
        struct {
            uint32_t A;
            uint32_t B;
            uint32_t C;
            uint32_t D;
            uint32_t E;
        };
        uint8_t Bytes[20];

        UniqueId()
            : Bytes()
        {}

        UniqueId(const UniqueId& other)
        {
            memcpy(Bytes, other.Bytes, sizeof(Bytes));
        }

        UniqueId& operator=(const UniqueId& other)
        {
            memcpy(Bytes, other.Bytes, sizeof(Bytes));
            return *this;
        }
    };
} }