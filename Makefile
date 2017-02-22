############################### README ###############################
# 1. Uncoment the OGRE_PATH, BOOST_PATH, and TINYXML_PATH variables
# 2. Commend my OGRE_PATH and BOOST_PATH
# 3. Uncoment LDFLAGS
# 4. Uncoment the -I include for tiny xml and -L
# 5. ...
# 6. Profit!
######################################################################

CXX := g++
CXXFLAGS := -Wall -c
LDFLAGS := -lboost_system -lOgreMain -ltinyxml -lOIS
#LDFLAGS := -lboost_system-mgw51-mt-1_63 -lOgreMain -ltinyxml

############## PATHS FOR WINDOWS ###############
################################################
#OGRE_PATH := J:/Game_Engine/Ogre-1.8.1
#BOOST_PATH := J:/Game_Engine/boost_1_63_0
#TINYXML_PATH := J:/Game_Engine/tinyxml_2.6.2
################################################

OGRE_PATH := /home/zeejfps/Programming/Game-Engine/libs/ogre_src_v1-8-1
BOOST_PATH := /home/zeejfps/Programming/Game-Engine/libs/boost_1_63_0
OIS_PATH := /usr/include/OIS

EXECUTABLE := ZsAwesomeGame9000
OBJ_DIR := out
SRC_DIR := src
INC_DIR := -I$(SRC_DIR)/include -I$(OIS_PATH) -I$(OGRE_PATH)/OgreMain/include -I$(BOOST_PATH) -I$(OGRE_PATH)/build/include #-I$(TINYXML_PATH)/include
LIB_DIR := -L$(OBJ_DIR) -L$(OGRE_PATH)/build/lib -L$(BOOST_PATH)/stage/lib #-L$(TINYXML_PATH)/lib

SOURCES := GameDriver.cpp GameManager.cpp RenderManager.cpp SimpleScene.cpp InputManager.cpp
OBJECTS := $(SOURCES:%.cpp=$(OBJ_DIR)/%.o)


$(EXECUTABLE) : $(OBJ_DIR) $(OBJECTS)
	$(CXX) $(LIB_DIR) -o $(EXECUTABLE) $(OBJECTS) $(LDFLAGS)


run: $(EXECUTABLE)
	export LD_LIBRARY_PATH=/home/zeejfps/Programming/Game-Engine/libs/ogre_src_v1-8-1/build/lib/ && ./$(EXECUTABLE)


$(OBJ_DIR):
	@mkdir $(OBJ_DIR)


$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CXX) -MMD $(CXXFLAGS) $(INC_DIR) $< -o $@


ifneq ($(MAKECMDGOALS),clean)
-include $(SOURCES:%.cpp=$(OBJ_DIR)/%.d)
endif


.PHONY: clean
clean:
	@rm -f $(OBJ_DIR)/*.o $(EXECUTABLE) Ogre.log *$(OBJ_DIR)/*.d
