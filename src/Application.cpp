#include "Application.h"

#include <Corrade/Containers/ArrayView.h>
#include <Corrade/Utility/Resource.h>
#include <Magnum/AbstractShaderProgram.h>
#include <Magnum/DefaultFramebuffer.h>
#include <Magnum/Renderer.h>
#include <Magnum/Buffer.h>
#include <Magnum/Mesh.h>
#include <Magnum/MeshTools/FullScreenTriangle.h>
#include <Magnum/Shaders/DistanceFieldVector.h>
#include <Magnum/Text/DistanceFieldGlyphCache.h>
#include <Magnum/Text/AbstractFont.h>
#include <Magnum/Trade/AbstractImporter.h>

#include "Game/Game.h"
#include "Menu/Menu.h"
#include "Splash/Splash.h"
#include "configure.h"

#if defined(CORRADE_TARGET_NACL_NEWLIB) || defined(CORRADE_TARGET_EMSCRIPTEN)
static int importStaticPlugins() {
    CORRADE_PLUGIN_IMPORT(MagnumFont)
    CORRADE_PLUGIN_IMPORT(TgaImporter)
    return 0;
} CORRADE_AUTOMATIC_INITIALIZER(importStaticPlugins)
#endif

namespace PushTheBox {

Application* Application::_instance = nullptr;

Application* Application::instance() {
    CORRADE_INTERNAL_ASSERT(_instance);
    return _instance;
}

Application::Application(const Arguments& arguments): Platform::ScreenedApplication(arguments, NoCreate), importerPluginManager(MAGNUM_PLUGINS_IMPORTER_DIR), fontPluginManager(MAGNUM_PLUGINS_FONT_DIR)
{
    CORRADE_INTERNAL_ASSERT(!_instance);
    _instance = this;

    /* Try to create MSAA context, fall back to no-AA */
    Configuration conf;
    conf.setSampleCount(16);
    #ifndef CORRADE_TARGET_NACL
    conf.setTitle("Push The Box");
    #endif
    if(!tryCreateContext(conf)) {
        Debug() << "Cannot create 16x MSAA context, fallback to no antialiasing";
        createContext(conf.setSampleCount(0));
    }

    Renderer::enable(Renderer::Feature::FaceCulling);
    Renderer::enable(Renderer::Feature::DepthTest);
    Renderer::setClearColor(Color3(0.0f));

    /* Add resource loader and fallback meshes */
    sceneResourceManager.setLoader(&meshResourceLoader);
    sceneResourceManager.setFallback<Mesh>(new Mesh);

    /* Load TGA importer plugin */
    if(!(importerPluginManager.load("TgaImporter") & PluginManager::LoadState::Loaded))
        std::exit(1);
    std::unique_ptr<Trade::AbstractImporter> tgaImporter = importerPluginManager.instance("TgaImporter");

    /* Save full screen triangle and TGA importer to resource manager */
    std::pair<std::unique_ptr<Buffer>, Mesh> triangle = MeshTools::fullScreenTriangle();
    if(triangle.first) SceneResourceManager::instance().set("fullscreentriangle", std::move(triangle.first.release()));
    SceneResourceManager::instance()
        .set("fullscreentriangle", std::move(triangle.second))
        .set("tga-importer", tgaImporter.release());

    /* Font plugin */
    if(!(fontPluginManager.load("MagnumFont") & PluginManager::LoadState::Loaded))
        std::exit(1);
    std::unique_ptr<Text::AbstractFont> font = fontPluginManager.instance("MagnumFont");

    /* Load font and create glyph cache */
    Utility::Resource rs("PushTheBoxResources");
    font->openData(std::vector<std::pair<std::string, Containers::ArrayView<const char>>>{
        {"luckiest-guy.conf", rs.getRaw("luckiest-guy.conf")},
        {"luckiest-guy.tga",  rs.getRaw("luckiest-guy.tga")}}, 0.0f);
    std::unique_ptr<Text::GlyphCache> cache = font->createGlyphCache();

    /* Save font resources to resource manager */
    SceneResourceManager::instance().set<AbstractShaderProgram>("text2d", new Shaders::DistanceFieldVector2D)
        .set("font", font.release()).set("cache", cache.release());

    /* Add the screens */
    _gameScreen = new Game::Game;
    _menuScreen = new Menu::Menu;
    _splashScreen = new Splash::Splash;
    addScreen(*_splashScreen);
    addScreen(*_gameScreen);
    addScreen(*_menuScreen);

    _timeline.start();

    /* Set some sane speed */
    setSwapInterval(1);
    #ifndef CORRADE_TARGET_EMSCRIPTEN
    setMinimalLoopPeriod(16);
    #endif
}

Application::~Application() {
    CORRADE_INTERNAL_ASSERT(_instance == this);

    /* Remove all screens before deleting the resource manager, so the
       resources can be properly freed */
    while(screens().last()) removeScreen(*screens().last());
}

void Application::globalViewportEvent(const Vector2i& size) {
    defaultFramebuffer.setViewport({{}, size});
}

void Application::globalDrawEvent() {
    swapBuffers();
    _timeline.nextFrame();
}

}

MAGNUM_APPLICATION_MAIN(PushTheBox::Application)
