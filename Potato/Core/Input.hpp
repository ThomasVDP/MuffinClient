#ifndef POTATO_INPUT_HPP
#define POTATO_INPUT_HPP

#include "KeyCodes.hpp"
#include "MouseCodes.hpp"

namespace Potato
{
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}	// namespace Potato

#endif