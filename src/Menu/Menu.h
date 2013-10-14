#ifndef PushTheBox_Menu_Menu_h
#define PushTheBox_Menu_Menu_h

/** @file
 * @brief Class PushTheBox::Menu::Menu
 */

#include <Interconnect/Receiver.h>
#include <Shapes/ShapeGroup.h>
#include <SceneGraph/Drawable.h>
#include <SceneGraph/TranslationTransformation.h>
#include <SceneGraph/Scene.h>

#include "AbstractScreen.h"

namespace PushTheBox { namespace Menu {

class Cursor;

/** @brief %Menu screen */
class Menu: public AbstractScreen, public Interconnect::Receiver {
    public:
        Menu();

    protected:
        void focusEvent() override;
        void blurEvent() override;
        void viewportEvent(const Vector2i& size) override;
        void drawEvent() override;
        void mousePressEvent(MouseEvent& event) override;
        void mouseMoveEvent(MouseMoveEvent& event) override;

    private:
        Scene2D scene;
        SceneGraph::DrawableGroup2D drawables;
        Shapes::ShapeGroup2D shapes;

        SceneGraph::Camera2D* camera;
        Cursor* cursor;
};

}}

#endif
