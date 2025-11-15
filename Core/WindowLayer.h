#pragma once
#include <Layer.h>
#include <GLFW/glfw3.h>
#include <string>

class WindowLayer : public Layer {
public:
    WindowLayer(int width, int height, const std::string& title);
    ~WindowLayer();

    void onAttach() override;
    void onUpdate(float deltaTime) override;
    void onRender() override;
    void onDetach() override;

    GLFWwindow* getWindow() const { return window; }
    bool shouldClose() const;

	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }

    void close();


private:
    void swapBuffersAndPollEvents();

    int width, height;
    std::string title;
    GLFWwindow* window;
};
