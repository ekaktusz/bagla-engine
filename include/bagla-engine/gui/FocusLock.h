#pragma once

#include "gui/Widget.h"

namespace bgl
{
class FocusLock
{
public:
	static void lockFocus(const Widget* widget);
	static void unlockFocus();

	static bool isLocked();
	static bool isWidgetInFocus(const Widget* widget);

private:
	static const Widget* LOCKED_WIDGET;
};
}