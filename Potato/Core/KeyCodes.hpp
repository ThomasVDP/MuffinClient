#ifndef POTATO_KEY_CODES_HPP
#define POTATO_KEY_CODES_HPP

#include <stdint.h>
#include <ostream>

namespace Potato
{
	typedef enum class KeyCode : uint16_t
	{
		// clang-format off
        // From glfw3.h
		Space               = 32,
		Apostrophe          = 39, /* ' */
		Comma               = 44, /* , */
		Minus               = 45, /* - */
		Period              = 46, /* . */
		Slash               = 47, /* / */

		D0                  = 48, /* 0 */
		D1                  = 49, /* 1 */
		D2                  = 50, /* 2 */
		D3                  = 51, /* 3 */
		D4                  = 52, /* 4 */
		D5                  = 53, /* 5 */
		D6                  = 54, /* 6 */
		D7                  = 55, /* 7 */
		D8                  = 56, /* 8 */
		D9                  = 57, /* 9 */

		Semicolon           = 59, /* ; */
		Equal               = 61, /* = */

		A                   = 65,
		B                   = 66,
		C                   = 67,
		D                   = 68,
		E                   = 69,
		F                   = 70,
		G                   = 71,
		H                   = 72,
		I                   = 73,
		J                   = 74,
		K                   = 75,
		L                   = 76,
		M                   = 77,
		N                   = 78,
		O                   = 79,
		P                   = 80,
		Q                   = 81,
		R                   = 82,
		S                   = 83,
		T                   = 84,
		U                   = 85,
		V                   = 86,
		W                   = 87,
		X                   = 88,
		Y                   = 89,
		Z                   = 90,

		LeftBracket         = 91,  /* [ */
		Backslash           = 92,  /* \ */
		RightBracket        = 93,  /* ] */
		GraveAccent         = 96,  /* ` */

		World1              = 161, /* non-US #1 */
		World2              = 162, /* non-US #2 */

		/* Function keys */
		Escape              = 256,
		Enter               = 257,
		Tab                 = 258,
		Backspace           = 259,
		Insert              = 260,
		Delete              = 261,
		Right               = 262,
		Left                = 263,
		Down                = 264,
		Up                  = 265,
		PageUp              = 266,
		PageDown            = 267,
		Home                = 268,
		End                 = 269,
		CapsLock            = 280,
		ScrollLock          = 281,
		NumLock             = 282,
		PrintScreen         = 283,
		Pause               = 284,
		F1                  = 290,
		F2                  = 291,
		F3                  = 292,
		F4                  = 293,
		F5                  = 294,
		F6                  = 295,
		F7                  = 296,
		F8                  = 297,
		F9                  = 298,
		F10                 = 299,
		F11                 = 300,
		F12                 = 301,
		F13                 = 302,
		F14                 = 303,
		F15                 = 304,
		F16                 = 305,
		F17                 = 306,
		F18                 = 307,
		F19                 = 308,
		F20                 = 309,
		F21                 = 310,
		F22                 = 311,
		F23                 = 312,
		F24                 = 313,
		F25                 = 314,

		/* Keypad */
		KP0                 = 320,
		KP1                 = 321,
		KP2                 = 322,
		KP3                 = 323,
		KP4                 = 324,
		KP5                 = 325,
		KP6                 = 326,
		KP7                 = 327,
		KP8                 = 328,
		KP9                 = 329,
		KPDecimal           = 330,
		KPDivide            = 331,
		KPMultiply          = 332,
		KPSubtract          = 333,
		KPAdd               = 334,
		KPEnter             = 335,
		KPEqual             = 336,

		LeftShift           = 340,
		LeftControl         = 341,
		LeftAlt             = 342,
		LeftSuper           = 343,
		RightShift          = 344,
		RightControl        = 345,
		RightAlt            = 346,
		RightSuper          = 347,
		Menu                = 348
		// clang-format on
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}	// namespace Potato

// clang-format off
// From glfw3.h
#define POTATO_KEY_SPACE           ::Potato::Key::Space
#define POTATO_KEY_APOSTROPHE      ::Potato::Key::Apostrophe    /* ' */
#define POTATO_KEY_COMMA           ::Potato::Key::Comma         /* , */
#define POTATO_KEY_MINUS           ::Potato::Key::Minus         /* - */
#define POTATO_KEY_PERIOD          ::Potato::Key::Period        /* . */
#define POTATO_KEY_SLASH           ::Potato::Key::Slash         /* / */
#define POTATO_KEY_0               ::Potato::Key::D0
#define POTATO_KEY_1               ::Potato::Key::D1
#define POTATO_KEY_2               ::Potato::Key::D2
#define POTATO_KEY_3               ::Potato::Key::D3
#define POTATO_KEY_4               ::Potato::Key::D4
#define POTATO_KEY_5               ::Potato::Key::D5
#define POTATO_KEY_6               ::Potato::Key::D6
#define POTATO_KEY_7               ::Potato::Key::D7
#define POTATO_KEY_8               ::Potato::Key::D8
#define POTATO_KEY_9               ::Potato::Key::D9
#define POTATO_KEY_SEMICOLON       ::Potato::Key::Semicolon     /* ; */
#define POTATO_KEY_EQUAL           ::Potato::Key::Equal         /* = */
#define POTATO_KEY_A               ::Potato::Key::A
#define POTATO_KEY_B               ::Potato::Key::B
#define POTATO_KEY_C               ::Potato::Key::C
#define POTATO_KEY_D               ::Potato::Key::D
#define POTATO_KEY_E               ::Potato::Key::E
#define POTATO_KEY_F               ::Potato::Key::F
#define POTATO_KEY_G               ::Potato::Key::G
#define POTATO_KEY_H               ::Potato::Key::H
#define POTATO_KEY_I               ::Potato::Key::I
#define POTATO_KEY_J               ::Potato::Key::J
#define POTATO_KEY_K               ::Potato::Key::K
#define POTATO_KEY_L               ::Potato::Key::L
#define POTATO_KEY_M               ::Potato::Key::M
#define POTATO_KEY_N               ::Potato::Key::N
#define POTATO_KEY_O               ::Potato::Key::O
#define POTATO_KEY_P               ::Potato::Key::P
#define POTATO_KEY_Q               ::Potato::Key::Q
#define POTATO_KEY_R               ::Potato::Key::R
#define POTATO_KEY_S               ::Potato::Key::S
#define POTATO_KEY_T               ::Potato::Key::T
#define POTATO_KEY_U               ::Potato::Key::U
#define POTATO_KEY_V               ::Potato::Key::V
#define POTATO_KEY_W               ::Potato::Key::W
#define POTATO_KEY_X               ::Potato::Key::X
#define POTATO_KEY_Y               ::Potato::Key::Y
#define POTATO_KEY_Z               ::Potato::Key::Z
#define POTATO_KEY_LEFT_BRACKET    ::Potato::Key::LeftBracket   /* [ */
#define POTATO_KEY_BACKSLASH       ::Potato::Key::Backslash     /* \ */
#define POTATO_KEY_RIGHT_BRACKET   ::Potato::Key::RightBracket  /* ] */
#define POTATO_KEY_GRAVE_ACCENT    ::Potato::Key::GraveAccent   /* ` */
#define POTATO_KEY_WORLD_1         ::Potato::Key::World1        /* non-US #1 */
#define POTATO_KEY_WORLD_2         ::Potato::Key::World2        /* non-US #2 */

/* Function keys */
#define POTATO_KEY_ESCAPE          ::Potato::Key::Escape
#define POTATO_KEY_ENTER           ::Potato::Key::Enter
#define POTATO_KEY_TAB             ::Potato::Key::Tab
#define POTATO_KEY_BACKSPACE       ::Potato::Key::Backspace
#define POTATO_KEY_INSERT          ::Potato::Key::Insert
#define POTATO_KEY_DELETE          ::Potato::Key::Delete
#define POTATO_KEY_RIGHT           ::Potato::Key::Right
#define POTATO_KEY_LEFT            ::Potato::Key::Left
#define POTATO_KEY_DOWN            ::Potato::Key::Down
#define POTATO_KEY_UP              ::Potato::Key::Up
#define POTATO_KEY_PAGE_UP         ::Potato::Key::PageUp
#define POTATO_KEY_PAGE_DOWN       ::Potato::Key::PageDown
#define POTATO_KEY_HOME            ::Potato::Key::Home
#define POTATO_KEY_END             ::Potato::Key::End
#define POTATO_KEY_CAPS_LOCK       ::Potato::Key::CapsLock
#define POTATO_KEY_SCROLL_LOCK     ::Potato::Key::ScrollLock
#define POTATO_KEY_NUM_LOCK        ::Potato::Key::NumLock
#define POTATO_KEY_PRINT_SCREEN    ::Potato::Key::PrintScreen
#define POTATO_KEY_PAUSE           ::Potato::Key::Pause
#define POTATO_KEY_F1              ::Potato::Key::F1
#define POTATO_KEY_F2              ::Potato::Key::F2
#define POTATO_KEY_F3              ::Potato::Key::F3
#define POTATO_KEY_F4              ::Potato::Key::F4
#define POTATO_KEY_F5              ::Potato::Key::F5
#define POTATO_KEY_F6              ::Potato::Key::F6
#define POTATO_KEY_F7              ::Potato::Key::F7
#define POTATO_KEY_F8              ::Potato::Key::F8
#define POTATO_KEY_F9              ::Potato::Key::F9
#define POTATO_KEY_F10             ::Potato::Key::F10
#define POTATO_KEY_F11             ::Potato::Key::F11
#define POTATO_KEY_F12             ::Potato::Key::F12
#define POTATO_KEY_F13             ::Potato::Key::F13
#define POTATO_KEY_F14             ::Potato::Key::F14
#define POTATO_KEY_F15             ::Potato::Key::F15
#define POTATO_KEY_F16             ::Potato::Key::F16
#define POTATO_KEY_F17             ::Potato::Key::F17
#define POTATO_KEY_F18             ::Potato::Key::F18
#define POTATO_KEY_F19             ::Potato::Key::F19
#define POTATO_KEY_F20             ::Potato::Key::F20
#define POTATO_KEY_F21             ::Potato::Key::F21
#define POTATO_KEY_F22             ::Potato::Key::F22
#define POTATO_KEY_F23             ::Potato::Key::F23
#define POTATO_KEY_F24             ::Potato::Key::F24
#define POTATO_KEY_F25             ::Potato::Key::F25

/* Keypad */
#define POTATO_KEY_KP_0            ::Potato::Key::KP0
#define POTATO_KEY_KP_1            ::Potato::Key::KP1
#define POTATO_KEY_KP_2            ::Potato::Key::KP2
#define POTATO_KEY_KP_3            ::Potato::Key::KP3
#define POTATO_KEY_KP_4            ::Potato::Key::KP4
#define POTATO_KEY_KP_5            ::Potato::Key::KP5
#define POTATO_KEY_KP_6            ::Potato::Key::KP6
#define POTATO_KEY_KP_7            ::Potato::Key::KP7
#define POTATO_KEY_KP_8            ::Potato::Key::KP8
#define POTATO_KEY_KP_9            ::Potato::Key::KP9
#define POTATO_KEY_KP_DECIMAL      ::Potato::Key::KPDecimal
#define POTATO_KEY_KP_DIVIDE       ::Potato::Key::KPDivide
#define POTATO_KEY_KP_MULTIPLY     ::Potato::Key::KPMultiply
#define POTATO_KEY_KP_SUBTRACT     ::Potato::Key::KPSubtract
#define POTATO_KEY_KP_ADD          ::Potato::Key::KPAdd
#define POTATO_KEY_KP_ENTER        ::Potato::Key::KPEnter
#define POTATO_KEY_KP_EQUAL        ::Potato::Key::KPEqual

#define POTATO_KEY_LEFT_SHIFT      ::Potato::Key::LeftShift
#define POTATO_KEY_LEFT_CONTROL    ::Potato::Key::LeftControl
#define POTATO_KEY_LEFT_ALT        ::Potato::Key::LeftAlt
#define POTATO_KEY_LEFT_SUPER      ::Potato::Key::LeftSuper
#define POTATO_KEY_RIGHT_SHIFT     ::Potato::Key::RightShift
#define POTATO_KEY_RIGHT_CONTROL   ::Potato::Key::RightControl
#define POTATO_KEY_RIGHT_ALT       ::Potato::Key::RightAlt
#define POTATO_KEY_RIGHT_SUPER     ::Potato::Key::RightSuper
#define POTATO_KEY_MENU            ::Potato::Key::Menu
// clang-format on

#endif