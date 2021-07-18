#pragma once
#include <functional>
#include "Renderer.h"

using namespace std;

namespace test
{
	class Test
	{
	public:
		Test() {};
		virtual ~Test() {};

		virtual void OnUpdate(float deltatime) {};
		virtual void OnRender() {};
		virtual void OnImGuiRender() {};
	};

	class TestMenu : public Test
	{
	public:
		TestMenu(Test*& currentTestPointer);
		~TestMenu();

		void OnImGuiRender() override;
		
		template<typename T>
		void RegisterTest(const string& name)
		{
			cout<<"Registering Test:"<<name<<endl;
			m_Test.push_back(make_pair(name, []() {return new T(); }));
		}

	private:
		Test*& m_CurrentTest;
		vector<pair<string, function<Test*()>>> m_Test;



	};
}
