#include <gtest/gtest.h>

#include <stdint.h>
#include <Common\Base64Encoder.h>
#include <array>

using namespace IsoPeer::Common;

TEST(Base58EncoderTests, Instantiation) {

    std::array<uint8_t, 3> inputArray = { 0, 127, 255 };
    auto resultString = Base58Encoder::Encode(inputArray.begin(), inputArray.end());
}

