cmake_minimum_required(VERSION 3.5...3.25)


if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(asteroids)
include("${VITASDK}/share/vita.cmake" REQUIRED)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(Freetype REQUIRED)

find_package(PNG REQUIRED)



set(VITA_APP_NAME "Asteroids Vita")
set(VITA_TITLEID  "VSDK00017")
set(VITA_VERSION  "01.00")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")



add_executable(${PROJECT_NAME}
src/main.cpp
src/Renderer.cpp
src/Renderer.h
        src/Model.cpp
        src/Model.h
        src/Player.cpp
        src/Player.h
        src/App.cpp
        src/App.h
        src/Button.cpp
        src/Button.h
        src/TextRenderer.cpp
        src/TextRenderer.h
        src/Asteroid.cpp
        src/Asteroid.h
        src/Projectile.cpp
        src/Projectile.h

        src/Managers/SceneManager.cpp
        src/Managers/SceneManager.h
        
        src/Scenes/Scene.cpp
        src/Scenes/Scene.h
        src/Scenes/GameScene.cpp
        src/Scenes/GameScene.h
        src/Scenes/GameOverScene.cpp
        src/Scenes/GameOverScene.h
        src/Scenes/GameMenuScene.cpp
        src/Scenes/GameMenuScene.h

        src/Scenes/ControlsScene.cpp
        src/Scenes/ControlsScene.h

        src/Systems/SystemRender.cpp
        src/Systems/SystemRender.h

        src/Systems/ISystem.cpp
        src/Systems/ISystem.h

        src/Managers/AudioManager.h
        src/Managers/AudioManager.cpp
)

target_link_libraries(${PROJECT_NAME}
pthread
jsoncpp
box2d

${CURL_LIBRARIES}
${OPENSSL_LIBRARIES}

SDL2_image
SDL2_mixer
SDL2_ttf
SDL2_gfx
SDL2

vorbisfile
vorbis
ogg
mikmod
modplug
mpg123
FLAC
webp
jpeg
png
z
freetype
            opus
            opusfile
            modplug
            bz2
            xmp


SceAudio_stub
SceAudioIn_stub
SceCommonDialog_stub
SceCtrl_stub
SceDisplay_stub
SceGxm_stub
SceHid_stub
SceSysmodule_stub
SceTouch_stub
SceMotion_stub


            m
            stdc++
            c
)

# target_link_libraries(asteroids PRIVATE /usr/local/vitasdk/arm-vita-eabi/lib/libpng.a /usr/local/vitasdk/arm-vita-eabi/lib/libz.a)


vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME})
vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
  FILE sce_sys/icon0.png sce_sys/icon0.png
  FILE sce_sys/livearea/contents/bg.png sce_sys/livearea/contents/bg.png
  FILE sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
  FILE sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml
  FILE res/Orbitron-Regular.ttf res/Orbitron-Regular.ttf  # Include font in VPK
  FILE res/Explosion.wav res/Explosion.wav
)
