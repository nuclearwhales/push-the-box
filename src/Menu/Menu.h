#ifndef PushTheBox_Menu_Menu_h
#define PushTheBox_Menu_Menu_h

/** @file
 * @brief Class PushTheBox::Menu::Menu
 */

#include <DebugTools/ResourceManager.h>
#include <Physics/ObjectShapeGroup.h>
#include <SceneGraph/Drawable.h>
#include <SceneGraph/EuclideanMatrixTransformation2D.h>
#include <SceneGraph/Scene.h>

#include "AbstractScreen.h"

namespace PushTheBox { namespace Menu {

/** @brief %Menu screen */
class Menu: public AbstractScreen {
    public:
        Menu(Text::FontRenderer& renderer);

    protected:
        void focusEvent() override;
        void blurEvent() override;
        void viewportEvent(const Vector2i& size) override;
        void drawEvent() override;
        void mousePressEvent(MouseEvent& event) override;

    private:
        /** @todo remove when done properly */
        DebugTools::ResourceManager debugDrawResourceManager;

        Scene2D scene;
        SceneGraph::DrawableGroup<2> drawables;
        Physics::ObjectShapeGroup2D shapes;

        Object2D* cameraObject;
        SceneGraph::Camera2D<>* camera;
};

}}

#endif
