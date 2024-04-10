#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestMethod1)
        {
            int shuliang = 5, m, a[10] = { 1,2,3,4,5 }, i, b[10];
            int sum = 0, max = 0;
            b[0] = a[0];
            for (i = 1; i < shuliang; i++) // 修正循环边界
            {
                if (b[i - 1] > 0)
                {
                    b[i] = b[i - 1] + a[i];
                }
                else
                    b[i] = a[i];
                if (b[i] > max)
                {
                    max = b[i];
                }
            }
            int real = 15; // 修正预期值
            Assert::AreEqual(max, real);
        }
        TEST_METHOD(TestMethod2)
        {
            int shuliang = 5, m, a[10] = { -20,-11,-5,-6,-7 }, i, b[10];
            int sum = 0, max = 0;
            b[0] = a[0];
            for (i = 1; i < shuliang; i++) 
            {
                if (b[i - 1] > 0)
                {
                    b[i] = b[i - 1] + a[i];
                }
                else
                    b[i] = a[i];
                if (b[i] > max)
                {
                    max = b[i];
                }
            }
            int real = -5;
            Assert::AreEqual(max, real);
        }
    };
}
