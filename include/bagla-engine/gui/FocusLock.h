#pragma once
#include "gui/Widget.h"

namespace bgl
{
	class FocusLock
	{
	public:
		static void lockFocus(const Widget* widget)
		{
			s_LockedWidget = widget;
		}

		static void unlockFocus()
		{
			s_LockedWidget = nullptr;
		}

		static bool isLocked()
		{
			return s_LockedWidget != nullptr;
		}

		static bool isWidgetInFocus(const Widget* widget)
		{
			return widget == s_LockedWidget;
		}

	private:
		static const Widget* s_LockedWidget;
	};

	const Widget* FocusLock::s_LockedWidget = nullptr;
}