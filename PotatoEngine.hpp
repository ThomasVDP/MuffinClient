#ifndef POTATO_ENGINE_HPP
#define POTATO_ENGINE_HPP

// For use by Potato applications

#include "Potato/Application.hpp"
#include "Potato/Layer.hpp"

#define POTAT_ENABLE_ASSERTS
#include "Potato/Core.hpp"

#include "Potato/TimeStep.hpp"

#include "Potato/Core/Input.hpp"
#include "Potato/Core/MouseCodes.hpp"
#include "Potato/Core/KeyCodes.hpp"

#include "Potato/Camera/OrthographicCameraController.hpp"
#include "Potato/Camera/PerspectiveCameraController.hpp"

// -----RENDERER----------------------
#include "Potato/Renderer/Renderer.hpp"
#include "Potato/Renderer/RenderCommand.hpp"
#include "Potato/Renderer/BlockRenderer.hpp"

#endif