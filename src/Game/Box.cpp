#include "Box.h"

#include <Buffer.h>
#include <Mesh.h>
#include <SceneGraph/AbstractCamera.h>
#include <Shaders/PhongShader.h>

namespace PushTheBox { namespace Game {

Box::Box(const Math::Vector2<int>& position, Object3D* parent, SceneGraph::DrawableGroup<3>* group): Object3D(parent), SceneGraph::Drawable<3>(this, group) {
    shader = SceneResourceManager::instance()->get<AbstractShaderProgram, Shaders::PhongShader>("phong");
    mesh = SceneResourceManager::instance()->get<Mesh>("box-mesh");
    levelPosition = position;
}

void Box::draw(const Matrix4& transformationMatrix, SceneGraph::AbstractCamera<3>* camera) {
    shader->setTransformationMatrix(transformationMatrix)
          ->setProjectionMatrix(camera->projectionMatrix())
          ->setDiffuseColor(Color3<>::fromHSV(0.0f, 1.0f, 0.6f))
          ->use();

    mesh->draw();
}

void Box::setLevelPosition(Math::Vector2<int>& position){
    levelPosition = position;
}

Math::Vector2<int> Box::getPosition(){
    return levelPosition;
}

}}
