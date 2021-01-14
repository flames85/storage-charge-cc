#include "gtest/gtest.h"
#include "storage.h"

namespace
{

struct StorageTest : testing::Test
{
protected:
    Storage s1{3, 1024, Storage::Type::ST_BLOCK_STORAGE};
    Storage s2{4, 512,  Storage::Type::ST_FILE_STORAGE};
    Storage s3{14, 128,  Storage::Type::ST_OBJECT_STORAGE};
};

TEST_F(StorageTest, total_price_and_levels)
{
    Tenant tenant;

    tenant.add(&s1);
    tenant.add(&s2);
    tenant.add(&s3);

    double total = 0.0;
    int levels = 0;
    tenant.charge(&total, &levels);

    ASSERT_EQ(2185.0, total);
    ASSERT_EQ(1, levels);
}

} // namespace

