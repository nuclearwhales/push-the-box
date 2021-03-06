#include "Player.h"

#include <Magnum/Mesh.h>
#include <Magnum/Shaders/Phong.h>

namespace PushTheBox { namespace Game {

Player::Player(Object3D* parent, SceneGraph::DrawableGroup3D* drawables): Object3D(parent), SceneGraph::Drawable3D(*this, drawables) {
    /* Get shader and mesh buffer */
    shader = SceneResourceManager::instance().get<AbstractShaderProgram, Shaders::Phong>("phong");
    mesh = SceneResourceManager::instance().get<Mesh>("player-mesh");
    bodyMesh = SceneResourceManager::instance().get<Mesh>("player-body-mesh");
}

void Player::draw(const Matrix4& transformationMatrix, SceneGraph::Camera3D&) {
    shader->setTransformationMatrix(transformationMatrix)
          /** @todo rotationNormalized() when precision problems are fixed */
          .setNormalMatrix(transformationMatrix.rotationScaling());

    shader->setDiffuseColor(Color3::fromHsv(Deg(210.0f), 0.85f, 0.8f));
    mesh->draw(*shader);
    shader->setDiffuseColor(Color3::fromHsv(Deg(50.0f), 0.85f, 0.8f));
    bodyMesh->draw(*shader);
}

}}

