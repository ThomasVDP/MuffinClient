#ifndef POTATO_MOUSE_CODES_HPP
#define POTATO_MOUSE_CODES_HPP

#include <stdint.h>
#include <ostream>

namespace Potato
{
	typedef enum class MouseCode : uint16_t
	{
		// clang-format off
		// From glfw3.h
		Button0                = 0,
		Button1                = 1,
		Button2                = 2,
		Button3                = 3,
		Button4                = 4,
		Button5                = 5,
		Button6                = 6,
		Button7                = 7,

		ButtonLast             = Button7,
		ButtonLeft             = Button0,
		ButtonRight            = Button1,
		ButtonMiddle           = Button2
		// clang-format on
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}	// namespace Potato

// clang-format off
#define POTATO_MOUSE_BUTTON_0      ::Potato::Mouse::Button0
#define POTATO_MOUSE_BUTTON_1      ::Potato::Mouse::Button1
#define POTATO_MOUSE_BUTTON_2      ::Potato::Mouse::Button2
#define POTATO_MOUSE_BUTTON_3      ::Potato::Mouse::Button3
#define POTATO_MOUSE_BUTTON_4      ::Potato::Mouse::Button4
#define POTATO_MOUSE_BUTTON_5      ::Potato::Mouse::Button5
#define POTATO_MOUSE_BUTTON_6      ::Potato::Mouse::Button6
#define POTATO_MOUSE_BUTTON_7      ::Potato::Mouse::Button7
#define POTATO_MOUSE_BUTTON_LAST   ::Potato::Mouse::ButtonLast
#define POTATO_MOUSE_BUTTON_LEFT   ::Potato::Mouse::ButtonLeft
#define POTATO_MOUSE_BUTTON_RIGHT  ::Potato::Mouse::ButtonRight
#define POTATO_MOUSE_BUTTON_MIDDLE ::Potato::Mouse::ButtonMiddle
// clang-format on

#endif