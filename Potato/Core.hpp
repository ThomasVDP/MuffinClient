#ifndef POTATO_ENGINE_CORE_HPP
#define POTATO_ENGINE_CORE_HPP

#include "Potato/Log.hpp"

#ifdef POTATO_ENABLE_ASSERTS
#define POTATO_ASSERT(x, ...)                                   \
	{                                                           \
		if (!(x))                                               \
		{                                                       \
			POTATO_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
			throw std::runtime_exception("Assertion failed!")   \
		}                                                       \
	}
#define POTATO_CORE_ASSERT(x, ...)                                   \
	{                                                                \
		if (!(x))                                                    \
		{                                                            \
			POTATO_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
			throw std::runtime_exception("Assertion failed!")        \
		}                                                            \
	}
#else
#define POTATO_ASSERT(x, ...)
#define POTATO_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define POTATO_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Potato
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename... Args>
	constexpr Scope<T> CreateScope(Args&&... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename... Args>
	constexpr Ref<T> CreateRef(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Cached = std::weak_ptr<T>;
	template<typename T>
	constexpr Cached<T> CreateCached(Ref<T> ref)
	{
		return ref;
	}
}	// namespace Potato

#endif