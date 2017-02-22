#if !defined RENDER_MANAGER
#define RENDER_MANAGER

#include "Scene.h"
#include <Ogre.h>
#include <OgreWindowEventUtilities.h>
#include <tinyxml.h>
#include "InputManager.h"

class GameManager;

class RenderManager : public Ogre::FrameListener, public Ogre::WindowEventListener
{
   private:
      Ogre::Root* root;
      Ogre::RenderWindow* window;
      InputManager* mInputManager;

      GameManager* game_manager;

      Scene* scene;

      void init();
      bool frameRenderingQueued(const Ogre::FrameEvent&);
      size_t window_handle;
      Ogre::Real time_since_last_frame;
      void windowResized(Ogre::RenderWindow* rw);
      void windowClosed(Ogre::RenderWindow* rw);

   public:
      RenderManager(GameManager* game_manager);
      virtual ~RenderManager();

      size_t getRenderWindowHandle();

      Ogre::RenderWindow* getRenderWindow();

      void startRendering();
      void stopRendering();
};

#endif
