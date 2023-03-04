#pragma once

#include "Widget.h"

class Button : public Widget
{
public:

private:
	std::function<void()> actionTodo;
};