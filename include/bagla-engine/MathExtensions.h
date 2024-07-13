#pragma once

namespace bgl
{
	template<typename T>
	static T mid(T a, T b, T c)
	{
		// Checking for b
		if ((a < b && b < c) || (c < b && b < a))
			return b;

		// Checking for a
		else if ((b < a && a < c) || (c < a && a < b))
			return a;

		else
			return c;
	}

	template <typename T>
	static T mapValue(T x, T in_min, T in_max, T out_min, T out_max) {
    	return out_min + ((x - in_min) * (out_max - out_min)) / (in_max - in_min);
	}
}
