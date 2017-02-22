#include "InputManager.h"

InputManager::InputManager(Ogre::RenderWindow* pWindow) {
     OIS::ParamList pl;
     size_t windowHnd = 0;
     std::ostringstream windowHndStr;

     pWindow->getCustomAttribute("WINDOW", &windowHnd);
     windowHndStr << windowHnd;
     pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

     mInputManager = OIS::InputManager::createInputSystem(pl);
     mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, false));
     mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, false));
}

InputManager::~InputManager() {
     if(mInputManager) {
          mInputManager->destroyInputObject( mMouse );
          mInputManager->destroyInputObject( mKeyboard );

          OIS::InputManager::destroyInputSystem(mInputManager);
          mInputManager = 0;
     }
}

void InputManager::poll() {
     mKeyboard->capture();
     mMouse->capture();
}

OIS::Mouse* InputManager::Mouse() {
     return mMouse;
}

OIS::Keyboard* InputManager::Keyboard() {
     return mKeyboard;
}
