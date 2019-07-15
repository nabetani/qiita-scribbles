#include <CppUTest/CommandLineTestRunner.h>
#include "backdoor.h"

TEST_GROUP(TestFuncGroup)
{
};

TEST(TestFuncGroup, static_func)
{
    int ret = static_func_backdoor(1);
    CHECK_EQUAL(1, ret);
}

int main(int argc, char **argv)
{
    return CommandLineTestRunner::RunAllTests(argc, argv);
}