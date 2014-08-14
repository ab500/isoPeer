#pragma once

#include <stdint.h>
#include <string>
#include <vector>
#include <array>
#include <type_traits>
#include <iterator>
#include <cassert>

namespace IsoPeer { namespace Common {
    
    namespace Base58Encoder
    {
        // Encodes a given byte vector. This method treats byte arrays as a big-endian
        // integer and will ignore leading zeros.
        std::string Encode(const std::vector<uint8_t>& source);

        // Decodes a given base58 encoding, returning a big-endian byte array. If
        // the string contains non-base58 characters this method will return false,
        // otherwise it will return true.
        bool Decode(const std::string& encoded, std::vector<uint8_t>& dest);
    };

} }
