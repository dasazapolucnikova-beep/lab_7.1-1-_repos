#include "pch.h"
#include "CppUnitTest.h"
#include "../Project 7.1 (1)/Project 7.1 (1).cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest711
{
	TEST_CLASS(UnitTest711)
	{
	public:

		TEST_METHOD(TestChange)
		{
			const int rowCount = 2;
			const int colCount = 2;

			int** Q = new int* [rowCount];
			for (int i = 0; i < rowCount; i++) {
				Q[i] = new int[colCount];
			}

			// Початкові значення
			Q[0][0] = 10; Q[0][1] = 20;
			Q[1][0] = 30; Q[1][1] = 40;

			// Міняємо 0-й та 1-й стовпчики місцями
			Change(Q, 0, 1, rowCount);

			// Перевіряємо, чи стовпчики обмінялися
			Assert::AreEqual(20, Q[0][0]);
			Assert::AreEqual(10, Q[0][1]);
			Assert::AreEqual(40, Q[1][0]);
			Assert::AreEqual(30, Q[1][1]);

			// Звільнення пам'яті
			for (int i = 0; i < rowCount; i++) {
				delete[] Q[i];
			}
			delete[] Q;
		}
	};
}