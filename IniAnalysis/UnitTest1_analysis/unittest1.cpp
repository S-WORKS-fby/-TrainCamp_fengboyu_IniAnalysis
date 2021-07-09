#include "stdafx.h"
#include "CppUnitTest.h"
#include "config.h"
#include "my_ini_analysis.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1_analysis
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		LPCTSTR filePath1 = "../../fengboyu.ini"; 
		LPCTSTR filePath2 = "../../feng.ini";

		LPTSTR strCompany = new char[LINEMAXSIZE];
		int intSalary = 0; 

		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(1, My_Ini_Analysis_GetSectionNames(filePath1));
			Assert::AreEqual(0, My_Ini_Analysis_GetSectionNames(filePath2));
		}

		TEST_METHOD(TestMethod2)
		{
			Assert::AreEqual(1, My_Ini_Analysis_GetSection("[hobbies", filePath1));
			Assert::AreEqual(0, My_Ini_Analysis_GetSection("[hobbies", filePath2));
			Assert::AreEqual(0, My_Ini_Analysis_GetSection("hobbies", filePath1));
		}

		TEST_METHOD(TestMethod3)
		{
			Assert::AreEqual(1, My_Ini_Analysis_GetString("job&work", "company", "XinJe", strCompany, LINEMAXSIZE, filePath1));
			Assert::AreEqual(0, My_Ini_Analysis_GetString("job&work", "company", "XinJe", strCompany, LINEMAXSIZE, filePath2));
			Assert::AreEqual(0, My_Ini_Analysis_GetString("job&", "company", "XinJe", strCompany, LINEMAXSIZE, filePath1));
			Assert::AreEqual(0, My_Ini_Analysis_GetString("job&work", "comp", "XinJe", strCompany, LINEMAXSIZE, filePath1));
			Assert::AreEqual(0, My_Ini_Analysis_GetString("ceshi", "unitest1", "0", strCompany, LINEMAXSIZE, filePath1));
		}

		TEST_METHOD(TestMethod4)
		{
			Assert::AreEqual(1, My_Ini_Analysis_GetInt("job&work", "salary", &intSalary, filePath1));
			Assert::AreEqual(0, My_Ini_Analysis_GetInt("job&work", "salary", &intSalary, filePath2));
			Assert::AreEqual(0, My_Ini_Analysis_GetInt("job&", "salary", &intSalary, filePath1));
			Assert::AreEqual(0, My_Ini_Analysis_GetInt("job&work", "sal", &intSalary, filePath1));
		}

	};
}