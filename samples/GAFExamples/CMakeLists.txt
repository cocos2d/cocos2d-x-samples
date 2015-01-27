cmake_minimum_required(VERSION 2.6)

set(APP_NAME GAFExample)
project (${APP_NAME})

set(GAME_SRC
  Example.linux/main.cpp
  Classes/AppDelegate.cpp
  Classes/GafFeatures.cpp
)

include_directories(
  Classes
  ${GAF_ROOT}
  ${GAF_ROOT}/Sources
  ${COCOS_ROOT}
  ${COCOS_ROOT}/2d
  ${COCOS_ROOT}/platform/${PLATFORM_FOLDER}
  ${COCOS_ROOT}/../external/${PLATFORM_FOLDER}-specific/zlib/include
  ${COCOS_ROOT}/../external/glfw3/include/${PLATFORM_FOLDER}
  ${COCOS_ROOT}/math
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
  gafplayer
  cocos2d
  )

set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin/${APP_NAME}")

set_target_properties(${APP_NAME} PROPERTIES
     RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")

pre_build(${APP_NAME}
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}/Resources
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${APP_BIN_DIR}/Resources
  )

