#include "WindowLayer.h"
#include <iostream>

WindowLayer::WindowLayer(int w, int h, const std::string& t)
    : width(w), height(h), title(t), window(nullptr) {
}

WindowLayer::~WindowLayer() {}

void WindowLayer::onAttach() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window);
}

void WindowLayer::onUpdate(float) 
{
    swapBuffersAndPollEvents();
}

void WindowLayer::onRender()
{
}

void WindowLayer::onDetach()
{
    if (window) glfwDestroyWindow(window);
    glfwTerminate();
}

bool WindowLayer::shouldClose() const { return glfwWindowShouldClose(window); }

void WindowLayer::close() { glfwSetWindowShouldClose(window, GLFW_TRUE); }

void WindowLayer::swapBuffersAndPollEvents() 
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}
