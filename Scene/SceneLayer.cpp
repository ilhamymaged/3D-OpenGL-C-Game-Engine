#include <SceneLayer.h>
#include <Components.h>
#include <Mesh.h>

SceneLayer::SceneLayer(RendererLayer* renderer, InputLayer* inputLayer,
    CameraLayer* cameraLayer, WindowLayer* windowLayer)
	:renderLayer{renderer}, inputLayer(inputLayer), cameraLayer(cameraLayer),
    windowLayer(windowLayer), shader(nullptr)
{}

void SceneLayer::onAttach()
{
	shader = new Shader("cube");

	auto cube = registry.create();
	registry.emplace<Transform>(cube);
	registry.emplace<Renderable>(cube, Mesh::generateBlock());
}

void SceneLayer::onDetach()
{
	delete shader;
}

void SceneLayer::onUpdate(float deltaTime)
{
}

void SceneLayer::onRender()
{
    glm::mat4 viewMat = cameraLayer->getViewMatrix();
    glm::mat4 projection = glm::perspective(
        glm::radians(cameraLayer->getFOV()),
        (float)windowLayer->getWidth()/windowLayer->getHeight(), 
        0.1f, 100.0f
    );

    renderLayer->submit([this, viewMat, projection]() {
        shader->use();
        shader->setMat4(viewMat, "view");
        shader->setMat4(projection, "projection");

        auto view = registry.view<Transform, Renderable>();
        for (auto entity : view) 
        {
            auto& transform = view.get<Transform>(entity);
            auto& renderable = view.get<Renderable>(entity);

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, transform.position);
            model = glm::rotate(model, transform.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, transform.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::rotate(model, transform.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, transform.scale);

            shader->setMat4(model, "model");
            renderable.mesh->render();
        }
    });
}
	