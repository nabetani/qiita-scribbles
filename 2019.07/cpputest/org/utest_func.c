#include <CppUTest/CommandLineTestRunner.h>
#ifdef __cplusplus
extern "C" {
extern int static_func(int);
}
#endif

TEST_GROUP(TestFuncGroup)
{
    TEST_SETUP()
    {
    }

    TEST_TEARDOWN()
    {
    }
};

TEST(TestFuncGroup, static_func)
{
    int ret = static_func(1);
    CHECK_EQUAL(1, ret);
}

int main(int argc, char **argv)
{
    return CommandLineTestRunner::RunAllTests(argc, argv);
}