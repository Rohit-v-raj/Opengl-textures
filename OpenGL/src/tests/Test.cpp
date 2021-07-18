#include "Test.h"

namespace test {
	test::TestMenu::TestMenu(Test*& currentTestPointer)
		:m_CurrentTest(currentTestPointer)
	{
	}

	test::TestMenu::~TestMenu()
	{
	}

	//void test::TestMenu::OnUpdate(float deltaTime)
	//{
	//}

	//void test::TestMenu::OnRender()
	//{
	//}

	void test::TestMenu::OnImGuiRender()
	{
		for (auto test : m_Test)
		{
			if (Button(test.first.c_str()))
			{
				m_CurrentTest=test.second();
			}
		}
	}


}