#include "gtest/gtest.h"
#include "Dht/UniqueId.h"

using namespace IsoPeer::Substrate::Dht;

TEST(UniqueIdTests, Instantiation) {
    UniqueId id;
}

TEST(UniqueIdTests, ZeroInitialized) {
    UniqueId id1;

    std::array<uint8_t, 20> allZerosArray;
    allZerosArray.fill(0);
    UniqueId allZeros(allZerosArray);

    ASSERT_TRUE(allZeros == id1);
}

TEST(UniqueIdTests, Comparison) {
    ASSERT_TRUE(UniqueId() == UniqueId());
}

TEST(UniqueIdTests, Distance) {
    UniqueId zeroDistance1;
    UniqueId zeroDistance2;

    UniqueId evenOnes(
        std::array<uint8_t, 20> {{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 }});
    UniqueId oddOnes(
        std::array<uint8_t, 20> {{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 }});

    std::array<uint8_t, 20> allOnesArray;
    allOnesArray.fill(0);
    UniqueId allOnes(allOnesArray);

    ASSERT_TRUE(UniqueId::Distance(zeroDistance1, zeroDistance2) == UniqueId());
}
