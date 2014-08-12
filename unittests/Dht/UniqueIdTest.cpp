#include <gtest/gtest.h>
#include <Dht/UniqueId.h>

using namespace IsoPeer::Substrate::Dht;

// Most classes won't need such extensive tests, but the closer we move to both the core
// implementation and to the more harder to reason about parts of the program the more
// value tests like these will provide for correctness.

static UniqueId s_noOnes(
    std::array<uint8_t, 20> {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }});
static UniqueId s_evenOnes(
    std::array<uint8_t, 20> {{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 }});
static UniqueId s_oddOnes(
    std::array<uint8_t, 20> {{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 }});
static UniqueId s_allOnes(
    std::array<uint8_t, 20> {{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }});

TEST(UniqueIdTests, Instantiation) {
    UniqueId id;
}

TEST(UniqueIdTests, ZeroInitialized) {
    UniqueId id1;
    ASSERT_TRUE(s_noOnes == id1);
}

TEST(UniqueIdTests, Comparison) {
    ASSERT_TRUE(UniqueId() == UniqueId());
    ASSERT_TRUE(s_evenOnes == s_evenOnes);
    ASSERT_FALSE(s_evenOnes == s_oddOnes);
    ASSERT_FALSE(s_evenOnes != s_evenOnes);
    ASSERT_TRUE(s_evenOnes != s_oddOnes);
    ASSERT_TRUE(s_oddOnes > s_evenOnes);
    ASSERT_TRUE(s_evenOnes < s_oddOnes);
    ASSERT_TRUE(s_evenOnes >= s_evenOnes);
    ASSERT_TRUE(s_evenOnes <= s_evenOnes);
    ASSERT_TRUE(s_allOnes >= s_noOnes);
    ASSERT_TRUE(s_noOnes <= s_allOnes);
}

TEST(UniqueIdTests, Distance) {
    ASSERT_TRUE(UniqueId::Distance(s_noOnes, s_noOnes) == UniqueId());
    ASSERT_TRUE(UniqueId::Distance(s_allOnes, s_allOnes) == UniqueId());
    ASSERT_TRUE(UniqueId::Distance(s_evenOnes, s_oddOnes) == s_allOnes);
    ASSERT_TRUE(UniqueId::Distance(s_evenOnes, s_allOnes) == s_oddOnes);
    ASSERT_TRUE(UniqueId::Distance(s_oddOnes, s_allOnes) == s_evenOnes);
}

TEST(UniqueIdTests, Assignment) {
    UniqueId assigned = s_allOnes;
    ASSERT_TRUE(assigned == s_allOnes);
    assigned = s_noOnes;
    ASSERT_TRUE(assigned == s_noOnes);
}

TEST(UnqiueIdTests, Copy) {
    UniqueId copied(s_allOnes);
    ASSERT_TRUE(copied == s_allOnes);
}
