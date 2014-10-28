cmake_minimum_required(VERSION 2.8)

set(APP_NAME LiquidFun-Testbed)
project (${APP_NAME})


set(GAME_SRC
  proj.linux/main.cpp
  Classes/AppDelegate.cpp
  Classes/ParticleParameter.cpp
  Classes/VisibleRect.cpp
  Classes/TestEntries.cpp
  Classes/Test.cpp
  Classes/GLESDebugDraw.cpp
  Classes/Box2dView.cpp
)

set(COCOS2D_ROOT ${CMAKE_SOURCE_DIR}/../../libs/cocos2d-x)

include_directories(
  Classes
  /usr/local/include/GLFW
  ${COCOS2D_ROOT}
  ${COCOS2D_ROOT}/../liquidfun/liquidfun/liquidfun/Box2D
  ${COCOS2D_ROOT}/cocos
  ${COCOS2D_ROOT}/cocos/audio/include
  ${COCOS2D_ROOT}/cocos/2d
  ${COCOS2D_ROOT}/cocos/2d/renderer
  ${COCOS2D_ROOT}/cocos/2d/platform
  ${COCOS2D_ROOT}/cocos/2d/platform/desktop
  ${COCOS2D_ROOT}/cocos/2d/platform/linux
  ${COCOS2D_ROOT}/cocos/math/kazmath
  ${COCOS2D_ROOT}/external/linux-specific/fmod/include/${ARCH_DIR}
  ${COCOS2D_ROOT}/external/xxhash
)

# add the executable
add_executable(${APP_NAME}
  ${GAME_SRC}
)

if ( CMAKE_SIZEOF_VOID_P EQUAL 8 )
set(FMOD_LIB "fmodex64")
else()
set(FMOD_LIB "fmodex")
endif()

target_link_libraries(${APP_NAME}
  cocos2d
  liquidfun
  )

set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin")

set_target_properties(${APP_NAME} PROPERTIES
     RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")

pre_build(${APP_NAME}
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}/Resources
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${APP_BIN_DIR}/Resources
  )

