#pragma once

#include <stdint.h>
#include <string>
#include <vector>
#include <array>
#include <type_traits>
#include <iterator>
#include <cassert>

namespace IsoPeer { namespace Common {
    
    // Contains methods that allow for Base58 encoding similar to what's used
    // for BitCoin wallet addresses.
    namespace Base58Encoder
    {
        std::string Encode(const std::vector<uint8_t>& source);
        bool Validate(const std::string& encoded);
        bool Decode(const std::string& encoded, std::vector<uint8_t>& dest);

    };

} }
