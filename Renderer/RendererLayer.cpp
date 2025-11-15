#include <RendererLayer.h>

RendererLayer::RendererLayer()
{
    
}

void RendererLayer::onAttach() 
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
        exit(-1);
    }

	//OpenGL state initialization
    glEnable(GL_DEPTH_TEST);
}

void RendererLayer::onUpdate(float deltaTime) 
{

}

void RendererLayer::onRender() 
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto& func : renderQueue)
        func();

    renderQueue.clear();
}

void RendererLayer::onDetach() {
    renderQueue.clear();
}

void RendererLayer::submit(const std::function<void()>& renderFunc) {
    renderQueue.push_back(renderFunc);
}

