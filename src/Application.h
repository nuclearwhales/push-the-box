#ifndef PushTheBox_Application_h
#define PushTheBox_Application_h

#include "PushTheBox.h"

#ifndef MAGNUM_TARGET_NACL
#include <Platform/Sdl2Application.h>
#else
#include <Platform/NaClApplication.h>
#endif

#include <ResourceManager.h>
#include <SceneGraph/Drawable.h>
#include <SceneGraph/MatrixTransformation3D.h>
#include <SceneGraph/Scene.h>

namespace PushTheBox {

class Application: public ApplicationBase {
    public:
        #ifndef MAGNUM_TARGET_NACL
        Application(int argc, char** argv);
        #else
        Application(PP_Instance instance);
        #endif

        ~Application();

    protected:
        void viewportEvent(const Math::Vector2<GLsizei>& size) override;
        void drawEvent() override;
        void keyPressEvent(KeyEvent& event) override;

    private:
        SceneResourceManager sceneResourceManager;

        Scene3D scene;
        SceneGraph::DrawableGroup<3> drawables;

        Object3D* cameraObject;
        SceneGraph::Camera3D<>* camera;
};

}

#endif
