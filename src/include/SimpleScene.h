#ifndef SIMPLE_SCENE_H
#define SIMPLE_SCENE_H

#include "InputManager.h"
#include "Scene.h"
#include <tinyxml.h>
#include <OgreSceneNode.h>
#include <OgreAnimationState.h>

class SimpleScene : public Scene {

public:
     SimpleScene(Ogre::Root*, Ogre::RenderWindow*, InputManager*);
     ~SimpleScene();
     bool load();
     bool update(float);
     void unload();

private:
     Ogre::SceneNode *mPlayerNode;
     Ogre::SceneNode *mWheelFL;
     Ogre::SceneNode *mWheelFR;
     Ogre::SceneNode *mPlatformNode;
     Ogre::AnimationState **mAnimations;
     InputManager *mInputManager;
};

#endif //SIMPLE_SCENE_H
