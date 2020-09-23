TEMPLATE = app
CONFIG += console
CONFIG += c11
CONFIG -= app_bundle
CONFIG -= qt
TEMPLATE += app


QMAKE_CFLAGS += -Wall -Wextra -pedantic
QMAKE_CC=gcc

unix : {
    debug: {
        DEFINES += DEBUG
        DEFINES += ALLEGRO_LOG
    }




    #allegro
    LIBS += -L/usr/local/lib -lallegro -lallegro_main -lallegro_audio -lallegro_acodec -lallegro_image -lallegro_font -lallegro_ttf -lallegro_primitives -lallegro_dialog -lallegro_physfs
    LIBS += -L/usr/lib64 -llua
    LIBS += -lm
    LIBS += -L/usr/lib64 -lphysfs
    INCLUDEPATH += /usr/local/include /usr/include
    INCLUDEPATH += $$PWD
    INCLUDEPATH += $$PWD/include
}

win32: {

    debug: {
        DEFINES += DEBUG
        DEFINES += ALLEGRO_LOG
    }

    #ALLEGRO
    INCLUDEPATH += $$PWD/../../../libs/mingw32/include
    DEPENDPATH += $$PWD/../../../libs/mingw32/include
    LIBS += -L$$PWD/../../../libs/allegro_winpkg-1.11.0/universal/allegro/build-mingw/lib/  -lallegro.dll -lallegro_audio.dll -lallegro_acodec.dll -lallegro_font.dll -lallegro_ttf.dll -lallegro_image.dll -lallegro_main.dll -lallegro_physfs.dll -lallegro_primitives.dll -lallegro_dialog.dll

    #LUA
    win32: LIBS += -L$$PWD/../../../libs/lua-5.4.0/ -llua54
    INCLUDEPATH += $$PWD/../../../libs/lua-5.4.0/include
    DEPENDPATH += $$PWD/../../../libs/lua-5.4.0/include
    win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../../libs/lua-5.4.0/lua54.lib
    else:win32-g++: PRE_TARGETDEPS += $$PWD/../../../libs/lua-5.4.0/liblua54.a

    #PHYSFS
    win32: LIBS += -L$$PWD/../../../libs/physfs-3.0.2/windows_build/ -lphysfs

    INCLUDEPATH += $$PWD/../../../libs/physfs-3.0.2/windows_build
    DEPENDPATH += $$PWD/../../../libs/physfs-3.0.2/windows_build

    #PROJECT
    INCLUDEPATH += $$PWD
    INCLUDEPATH += $$PWD/include
}



HEADERS += \
        $$PWD/include/main.h \
        include/log.h \
        include/lua_shared.h \
        include/resources.h \
        include/window.h\
        include/sound.h \
        include/shared.h \
        include/game.h \
        include/lua_vm.h \
        include/lua_hud.h \
        include/hud.h

SOURCES += \
        $$PWD/src/main.c \
        src/log.c \
        src/lua_shared.c \
        src/resources.c \
        src/window.c \
        src/sound.c \
        src/shared.c \
        src/game.c \
        src/lua_vm.c \
        src/lua_hud.c \
        src/hud.c
