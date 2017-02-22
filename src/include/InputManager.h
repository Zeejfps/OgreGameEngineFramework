#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OgreRenderWindow.h>

class InputManager {
public:
     InputManager(Ogre::RenderWindow*);
     ~InputManager();
     void poll();
     OIS::Mouse* Mouse();
     OIS::Keyboard* Keyboard();
private:
     OIS::InputManager* mInputManager;
     OIS::Mouse* mMouse;
     OIS::Keyboard* mKeyboard;
};

#endif /* INPUT_MANAGER_H */
