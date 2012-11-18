#include "Application.h"

#include <Math/Constants.h>
#include <AbstractShaderProgram.h>
#include <Framebuffer.h>
#include <Mesh.h>
#include <SceneGraph/Camera3D.h>
#include <Shaders/PhongShader.h>

#include "Floor.h"

namespace PushTheBox {

#ifndef MAGNUM_TARGET_NACL
Application::Application(int argc, char** argv): ApplicationBase(argc, argv, "Push The Box") {
#else
Application::Application(PP_Instance instance): ApplicationBase(instance) {
#endif

    Framebuffer::setFeature(Framebuffer::Feature::FaceCulling, true);
    Framebuffer::setFeature(Framebuffer::Feature::DepthTest, true);
    Framebuffer::setClearColor(Color3<GLfloat>::fromHSV(15.0f, 0.95f, 0.2f));

    /* Add shader to resource manager */
    sceneResourceManager.set<AbstractShaderProgram>("phong",
        new Shaders::PhongShader, ResourceDataState::Final, ResourcePolicy::Resident);

    /* Configure camera */
    (cameraObject = new Object3D(&scene))
        ->translate(Vector3::zAxis(5.5f))
        ->rotateX(deg(-35.0f));
    (camera = new SceneGraph::Camera3D<>(cameraObject))
        ->setPerspective(deg(35.0f), 0.001f, 100.0f)
        ->setAspectRatioPolicy(SceneGraph::AspectRatioPolicy::Extend);

    /* Add some default crap to the scene */
    new Floor(Color3<GLfloat>::fromHSV(15.0f, 0.55f, 0.6f), &scene, &drawables);
    (new Floor(Color3<GLfloat>::fromHSV(75.0f, 0.55f, 0.6f), &scene, &drawables))
        ->translate({1, 0, 0});
    (new Floor(Color3<GLfloat>::fromHSV(210.0f, 0.55f, 0.6f), &scene, &drawables))
        ->translate({0, 0, -1});
    (new Floor(Color3<GLfloat>::fromHSV(150.0f, 0.55f, 0.6f), &scene, &drawables))
        ->translate({-1, 0, 1});
}

Application::~Application() {}

void Application::viewportEvent(const Math::Vector2<GLsizei>& size) {
    Framebuffer::setViewport({}, size);
    camera->setViewport(size);
}

void Application::drawEvent() {
    Framebuffer::clear(Framebuffer::Clear::Color|Framebuffer::Clear::Depth);
    camera->draw(drawables);
    swapBuffers();
}

void Application::keyPressEvent(KeyEvent& event) {
    if(event.key() == KeyEvent::Key::Up)
        cameraObject->rotateX(deg(-5.0f));
    else if(event.key() == KeyEvent::Key::Down)
        cameraObject->rotateX(deg(5.0f));
    else return;

    event.setAccepted();
    redraw();
}

}

MAGNUM_APPLICATION_MAIN(PushTheBox::Application)
