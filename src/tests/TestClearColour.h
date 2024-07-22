#pragma once

#include "Test.h"


namespace test 
{

	class TestClearColour : public Test
	{
	
	
	public:
		TestClearColour();
		~TestClearColour();
	
		void Update(float deltaTime) override;
		void OnRender() override;
		void OnImGUIRender() override;
	
	
	};













}