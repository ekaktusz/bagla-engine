#include "gui/FocusLock.h"

namespace bgl
{
const Widget* FocusLock::s_LockedWidget = nullptr;

void FocusLock::lockFocus(const Widget* widget)
{
	s_LockedWidget = widget;
}

void FocusLock::unlockFocus()
{
	s_LockedWidget = nullptr;
}

bool FocusLock::isLocked()
{
	return s_LockedWidget != nullptr;
}

bool FocusLock::isWidgetInFocus(const Widget* widget)
{
	return widget == s_LockedWidget;
}
}