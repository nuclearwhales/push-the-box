#ifndef PushTheBox_Application_h
#define PushTheBox_Application_h

/** @file
 * @brief Class PushTheBox::Application
 */

#include <Corrade/Interconnect/Receiver.h>
#include <Corrade/PluginManager/Manager.h>
#include <Magnum/ResourceManager.h>
#include <Magnum/Timeline.h>
#include <Magnum/Trade/Trade.h>
#include <Magnum/Platform/ScreenedApplication.h>
#include <Magnum/Platform/Sdl2Application.h>

#include "PushTheBox.h"
#include "ResourceManagement/MeshResourceLoader.h"

namespace PushTheBox {

namespace Game {
    class Game;
}

namespace Menu {
    class Menu;
}

namespace Splash {
    class Splash;
}

/** @brief Main application class */
class Application: public Platform::ScreenedApplication, public Interconnect::Receiver {
    public:
        static Application* instance();

        /** @brief Constructor */
        Application(const Arguments& arguments);

        ~Application();

        /** @brief Game screen */
        inline Game::Game* gameScreen() { return _gameScreen; }

        /** @brief Menu screen */
        inline Menu::Menu* menuScreen() { return _menuScreen; }

        /** @brief Timeline */
        inline Timeline& timeline() { return _timeline; }

    private:
        void globalDrawEvent() override;
        void globalViewportEvent(const Vector2i& size) override;

        static Application* _instance;

        PluginManager::Manager<Trade::AbstractImporter> importerPluginManager;
        PluginManager::Manager<Text::AbstractFont> fontPluginManager;
        SceneResourceManager sceneResourceManager;
        ResourceManagement::MeshResourceLoader meshResourceLoader;
        Timeline _timeline;

        Game::Game* _gameScreen;
        Menu::Menu* _menuScreen;
        Splash::Splash* _splashScreen;
};

}

#endif
