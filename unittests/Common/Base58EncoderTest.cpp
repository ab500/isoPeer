#include <gtest/gtest.h>

#include <stdint.h>
#include <Common\Base58Encoder.h>
#include <array>

using namespace IsoPeer::Common;

TEST(Base58EncoderTests, SimpleInput) {
    std::vector<uint8_t> inputArray = { 34, 127, 255 };
    std::vector<uint8_t> decodeResult;
    ASSERT_TRUE(Base58Encoder::Decode(Base58Encoder::Encode(inputArray), decodeResult));
    ASSERT_TRUE(inputArray == decodeResult);
}

TEST(Base58EncoderTests, EmptyInput) {
    std::vector<uint8_t> inputArray;
    std::vector<uint8_t> decodeResult;
    ASSERT_TRUE(Base58Encoder::Decode(Base58Encoder::Encode(inputArray), decodeResult));
    ASSERT_TRUE(inputArray == decodeResult);
    ASSERT_TRUE(decodeResult.size() == 0);
}

TEST(Base58EncoderTests, PrefixedZeros) {
    std::vector<uint8_t> inputArray = { 0, 127, 255 };
    std::vector<uint8_t> decodeResult;
    std::vector<uint8_t> decodeExpectedResult = { 127, 255 };
    ASSERT_TRUE(Base58Encoder::Decode(Base58Encoder::Encode(inputArray), decodeResult));
    ASSERT_TRUE(decodeResult == decodeExpectedResult);
}

TEST(Base58EncoderTests, InvalidInput) {
    std::string badString = " $32 ds";
    std::vector<uint8_t> decodeResult;
    ASSERT_FALSE(Base58Encoder::Decode(badString, decodeResult));
}

TEST(Base58EncoderTests, GroundEncodingTruths) {
    std::vector<uint8_t> sample1 = {0xCC, 0x66, 0xCE, 0x53};
    std::string expected1 = "6E31Jz";
    ASSERT_EQ(expected1, Base58Encoder::Encode(sample1));

    std::vector<uint8_t> sample2 = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF};
    std::string expected2 = "6152VHZY";
    ASSERT_EQ(expected2, Base58Encoder::Encode(sample2));

    std::vector<uint8_t> sample3 = {0xFF, 0x00, 0xFF, 0xFF};
    std::string expected3 = "7X4BLr";
    ASSERT_EQ(expected3, Base58Encoder::Encode(sample3));

    std::vector<uint8_t> sample4 = {0x00};
    std::string expected4 = "";
    ASSERT_EQ(expected4, Base58Encoder::Encode(sample4));
}

