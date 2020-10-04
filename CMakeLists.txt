cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

set (CMAKE_CXX_STANDARD 17)
project ("Minecraft Bot Client")

set(GLFW_ENABLED ON CACHE BOOL "Whether to use GLFW to create the window surface (Vulkan-specific)" FORCE)
set(DILIGENT_NO_OPENGL ON CACHE BOOL "" FORCE)
add_subdirectory(DiligentCore)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

list(APPEND EDITOR_SRCS "Potato/Application.cpp")
list(APPEND EDITOR_SRCS "MainApp.cpp")
list(APPEND EDITOR_SRCS "Potato/Log.cpp")
list(APPEND EDITOR_SRCS "Potato/Window/GlfwWindow.cpp")
list(APPEND EDITOR_SRCS "Potato/Layer.cpp")
list(APPEND EDITOR_SRCS "Potato/LayerStack.cpp")
list(APPEND EDITOR_SRCS "Layers/GraphicsBaseLayer.cpp")
list(APPEND EDITOR_SRCS "Potato/Vulkan/VulkanContext.cpp")
list(APPEND EDITOR_SRCS "Potato/Renderer/GraphicsContext.cpp")
list(APPEND EDITOR_SRCS "Potato/Renderer/RenderCommand.cpp")
list(APPEND EDITOR_SRCS "Potato/Renderer/RendererAPI.cpp")
list(APPEND EDITOR_SRCS "Potato/Renderer/Renderer.cpp")
list(APPEND EDITOR_SRCS "Potato/Renderer/PipelineState.cpp")
list(APPEND EDITOR_SRCS "Potato/Renderer/Buffer.cpp")
list(APPEND EDITOR_SRCS "Potato/Renderer/Shader.cpp")
list(APPEND EDITOR_SRCS "Potato/Core/Input.cpp")
list(APPEND EDITOR_SRCS "Potato/Camera/OrthographicCamera.cpp")
list(APPEND EDITOR_SRCS "Potato/Camera/OrthographicCameraController.cpp")
list(APPEND EDITOR_SRCS "Potato/Camera/PerspectiveCamera.cpp")
list(APPEND EDITOR_SRCS "Potato/Camera/PerspectiveCameraController.cpp")
list(APPEND EDITOR_SRCS "Potato/Renderer/QuadRenderer.cpp")
list(APPEND EDITOR_SRCS "Potato/Renderer/BlockRenderer.cpp")
#VSCODE-CMAKE-EXT-MARKER

add_executable(MuffinClient ${EDITOR_SRCS})
target_compile_options(MuffinClient PRIVATE -DENGINE_DLL)

# file(COPY ${CMAKE_SOURCE_DIR}/Res DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)

target_include_directories(MuffinClient PUBLIC ${CMAKE_SOURCE_DIR} PRIVATE "DiligentCore")

target_link_libraries(MuffinClient PUBLIC ${CONAN_LIBS}
            PRIVATE Diligent-BuildSettings
)

if(VULKAN_SUPPORTED)
    target_link_libraries(MuffinClient PRIVATE Diligent-GraphicsEngineVk-static)
endif()