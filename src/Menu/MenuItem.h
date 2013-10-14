#ifndef PushTheBox_Menu_MenuItem_h
#define PushTheBox_Menu_MenuItem_h

/** @file
 * @brief Class PushTheBox::Menu::MenuItem
 */

#include <Buffer.h>
#include <Color.h>
#include <Mesh.h>
#include <Resource.h>
#include <SceneGraph/Drawable.h>
#include <SceneGraph/TranslationTransformation.h>
#include <Shaders/Shaders.h>
#include <Shapes/AxisAlignedBox.h>
#include <Shapes/Shape.h>
#include <Interconnect/Emitter.h>

#include "PushTheBox.h"

namespace PushTheBox { namespace Menu {

/** @brief %Menu item */
class MenuItem: public Object2D, SceneGraph::Drawable2D, public Shapes::Shape<Shapes::AxisAlignedBox2D>, public Interconnect::Emitter {
    public:
        /**
         * @brief Constructor
         * @param title         Title
         * @param parent        Parent object
         * @param drawables     Drawable group
         * @param shapes        Shape group
         */
        MenuItem(const std::string& title, Object2D* parent, SceneGraph::DrawableGroup2D* drawableGroup, Shapes::ShapeGroup2D* shapes);

        void hoverChanged(bool hovered);

        inline Signal clicked() {
            return emit(&MenuItem::clicked);
        }

    protected:
        void draw(const Matrix3& transformationMatrix, SceneGraph::AbstractCamera2D& camera) override;

    private:
        Resource<AbstractShaderProgram, Shaders::DistanceFieldVector2D> shader;
        Resource<Text::GlyphCache> glyphCache;
        Buffer vertexBuffer, indexBuffer;
        Mesh mesh;
        Color3 color;
};

}}

#endif
