#include "SimpleScene.h"
#include "SceneParser.h"

SimpleScene::SimpleScene(
     Ogre::Root          *pRoot,
     Ogre::RenderWindow  *pWindow,
     InputManager        *pInputManager
) : Scene(pRoot, pWindow) {
     mInputManager = pInputManager;
     mSceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
     //mSceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
}

SimpleScene::~SimpleScene() {

}

bool SimpleScene::load() {
     Ogre::ResourceGroupManager& rgm = Ogre::ResourceGroupManager::getSingleton();
     Ogre::Log* logger = Ogre::LogManager::getSingleton().getDefaultLog();
     parseScene("./assets/scenes/Simple.scene", mSceneManager, rgm, logger);

     Ogre::Camera* camera = mSceneManager->getCamera("MainCamera");
     Ogre::Viewport* viewport = mWindow->addViewport(camera, 0, 0.0, 0.0, 1.0, 1.0);
     viewport->setBackgroundColour(Ogre::ColourValue(0,0,0));

     float actual_width = Ogre::Real(viewport->getActualWidth());
     float actual_height = Ogre::Real(viewport->getActualHeight());
     float aspect_ratio = actual_width/actual_height;
     camera->setAspectRatio(aspect_ratio);

     mSceneManager->setSkyBox(true, "Skybox-Material");
     mPlayerNode = mSceneManager->getSceneNode("Player");

     mPlatformNode = mSceneManager->getSceneNode("PlatformNode");

     mWheelFL = mSceneManager->getSceneNode("WheelNodeFL");
     mWheelFR = mSceneManager->getSceneNode("WheelNodeFR");

     mAnimations = new Ogre::AnimationState*[5];

     Ogre::SceneNode* node;
     Ogre::Entity* entity;

     node = mSceneManager->getSceneNode("Squirrel01");
     entity = (Ogre::Entity*)node->getAttachedObject("Squirrel01");
     mAnimations[0] = entity->getAnimationState("my_animation");
     mAnimations[0]->setLoop(true);
     mAnimations[0]->setEnabled(true);

     node = mSceneManager->getSceneNode("Squirrel02");
     entity = (Ogre::Entity*)node->getAttachedObject("Squirrel02");
     mAnimations[1] = entity->getAnimationState("my_animation");
     mAnimations[1]->setLoop(true);
     mAnimations[1]->setEnabled(true);

     mAnimations[2] = mSceneManager->getAnimationState("rotate");
     mAnimations[2]->setLoop(true);
     mAnimations[2]->setEnabled(true);

     mAnimations[3] = mSceneManager->getAnimationState("hood_open_anim");
     mAnimations[3]->setLoop(true);
     mAnimations[3]->setEnabled(true);

     node = mSceneManager->getSceneNode("Spring");
     entity = (Ogre::Entity*)node->getAttachedObject("Spring");
     mAnimations[4] = entity->getAnimationState("spring");
     mAnimations[4]->setLoop(true);
     mAnimations[4]->setEnabled(true);

     return true;
}

bool SimpleScene::update(float dt) {

     OIS::MouseState state = mInputManager->Mouse()->getMouseState();

     mPlayerNode->yaw(Ogre::Degree(-0.07 * state.X.rel), Ogre::Node::TS_WORLD);
     mPlayerNode->pitch(Ogre::Degree(-0.07 * state.Y.rel));

     if (mInputManager->Keyboard()->isKeyDown(OIS::KC_W)) {
          mPlayerNode->translate(0, 0, -15*dt, Ogre::Node::TS_LOCAL);
     }
     else if (mInputManager->Keyboard()->isKeyDown(OIS::KC_S)) {
          mPlayerNode->translate(0, 0, 15*dt, Ogre::Node::TS_LOCAL);
     }

     if (mInputManager->Keyboard()->isKeyDown(OIS::KC_A)) {
          mPlayerNode->translate(-15*dt, 0, 0, Ogre::Node::TS_LOCAL);
     }
     else if (mInputManager->Keyboard()->isKeyDown(OIS::KC_D)) {
          mPlayerNode->translate(15*dt, 0, 0, Ogre::Node::TS_LOCAL);
     }

     if (mInputManager->Keyboard()->isKeyDown(OIS::KC_A)) {
          mWheelFR->rotate(Ogre::Quaternion(Ogre::Degree(45*dt), Ogre::Vector3(0, 1, 0)));
     }

     mPlatformNode->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(25 * dt));
     for (int i = 0; i < 5; i++) {
          mAnimations[i]->addTime(dt);
     }
     return true;
}
