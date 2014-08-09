#include "gtest/gtest.h"
#include "Dht/UniqueId.h"

using namespace IsoPeer::Dht;

TEST(UniqueIdTests, Instantiation) {
    UniqueId id;
}

TEST(UniqueIdTests, Distance) {
    UniqueId id1;
    UniqueId id2;

    ASSERT_TRUE(UniqueId::Distance(id1, id2) == UniqueId());
}
