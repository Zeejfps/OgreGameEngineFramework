#include "RenderManager.h"
#include "GameManager.h"
#include "SimpleScene.h"
//#include "SceneParser.h"
#include <OgreWindowEventUtilities.h>
#include <iostream>
using namespace std;

void RenderManager::init()
{
	root = NULL;
	window = NULL;
	scene = NULL;

	root = OGRE_NEW Ogre::Root("","");  //resource/config files go here
	root->loadPlugin("RenderSystem_GL");  //prepares external dlls for later use

	Ogre::RenderSystem* render_system = root->getRenderSystemByName("OpenGL Rendering Subsystem"); //just returns a pointer to an uninialized render system
	if (!render_system)
	{
		//ASSERT_CRITICAL(false);
	}

	render_system->setWaitForVerticalBlank(true);
	root->setRenderSystem(render_system);
	//manually set configuration options
	render_system->setConfigOption("Full Screen", "Yes");
	render_system->setConfigOption("Video Mode", "1280 x 720 @ 32-bit colour");

	//initialize render system
	//automatically create the window and give it a title
	window = root->initialise(true, "Z's Awesome Game 9000");
	window->setVSyncEnabled(true);
	window->setVSyncInterval(1);
	window->getCustomAttribute("WINDOW", &window_handle);
	root->addFrameListener(this);

	mInputManager = new InputManager(window);

	windowResized(window);
 	Ogre::WindowEventUtilities::addWindowEventListener(window, this);

	scene = new SimpleScene(root, window, mInputManager);
	if (!scene->load()) {
		// ERROR
	}
}

RenderManager::RenderManager(GameManager* gm)
{
	game_manager = gm;
	init();
}

RenderManager::~RenderManager()
{
	Ogre::WindowEventUtilities::removeWindowEventListener(window, this);
	windowClosed(window);

	game_manager = NULL;

	window->removeAllViewports();
	window->destroy();
	window = NULL;

	delete scene;
	scene = NULL;

	delete root;
	root = NULL;
}

size_t RenderManager::getRenderWindowHandle()
{
	return window_handle;
}


void RenderManager::startRendering()
{
	root->startRendering();
}

Ogre::RenderWindow* RenderManager::getRenderWindow()
{
	return window;
}

bool RenderManager::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	if(window->isClosed())
		return false;

	mInputManager->poll();
	if(mInputManager->Keyboard()->isKeyDown(OIS::KC_ESCAPE))
		return false;

	return scene->update(evt.timeSinceLastFrame);
}

void RenderManager::windowResized(Ogre::RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = mInputManager->Mouse()->getMouseState();
    ms.width = width;
    ms.height = height;
}

void RenderManager::windowClosed(Ogre::RenderWindow* rw)
{
    if(rw == window)
    {
        delete mInputManager;
    }
}
