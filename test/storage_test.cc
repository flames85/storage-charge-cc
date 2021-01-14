#include "gtest/gtest.h"
#include "storage.h"

namespace
{

struct StorageTest : testing::Test
{
protected:
    Storage s1{1024, ST_BLOCK_STORAGE};
    Storage s2{512, ST_FILE_STORAGE};
    Storage s3{128, ST_OBJECT_STORAGE};

    Lease l1{3,  &s1};
    Lease l2{4,  &s2};
    Lease l3{14, &s3};
};

TEST_F(StorageTest, total_price_and_levels)
{
    Tenant tenant;

    tenant.add(&l1);
    tenant.add(&l2);
    tenant.add(&l3);

    double total = 0.0;
    int levels = 0;
    tenant.charge(&total, &levels);

    ASSERT_EQ(2185.0, total);
    ASSERT_EQ(1, levels);
}

} // namespace

