#include <gtest/gtest.h>

#include <stdint.h>
#include <Common\Base58Encoder.h>
#include <array>

using namespace IsoPeer::Common;

TEST(Base58EncoderTests, Instantiation) {

    std::vector<uint8_t> inputArray = { 0, 127, 255 };
    auto result = Base58Encoder::Encode(inputArray);

    std::vector<uint8_t> decodeResult;
    Base58Encoder::Decode(result, decodeResult);
}

