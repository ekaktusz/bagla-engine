#include "gui/FocusLock.h"

namespace bgl
{
const Widget* FocusLock::LOCKED_WIDGET = nullptr;

void FocusLock::lockFocus(const Widget* widget)
{
	LOCKED_WIDGET = widget;
}

void FocusLock::unlockFocus()
{
	LOCKED_WIDGET = nullptr;
}

bool FocusLock::isLocked()
{
	return LOCKED_WIDGET != nullptr;
}

bool FocusLock::isWidgetInFocus(const Widget* widget)
{
	return widget == LOCKED_WIDGET;
}
}