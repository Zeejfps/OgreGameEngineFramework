#ifndef SCENE_H
#define SCENE_H

#include <OgreRoot.h>
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>

class Scene {

public:
     Scene(Ogre::Root* pRoot, Ogre::RenderWindow* pWindow) {
     	mSceneManager = pRoot->createSceneManager(Ogre::ST_GENERIC);
     	mWindow = pWindow;
     }
     virtual ~Scene() {
     	mSceneManager->clearScene();
     	mSceneManager->destroyAllCameras();
     }
     virtual bool load() = 0;
     virtual bool update(float) = 0;

protected:
     Ogre::SceneManager* mSceneManager;
     Ogre::RenderWindow* mWindow;
};

#endif /* SCENE_H */
