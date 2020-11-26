TEMPLATE = app
CONFIG += console c11 use_c_linker
QT_CONFIG -= no-pkg-config
CONFIG += link_pkgconfig
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c11
@CONFIG += debug_and_release@

#PKGCONFIG += sdl2 SDL2_image SDL2_image SDL2_mixer SDL2_ttf
QMAKE_CFLAGS += -std=c11



#fedora claims NULL is undefined just cand find stddef.h (it might be a bug?)
#so i hardcorded my gcc include path just to shut up compiler
#INCLUDEPATH += /usr/lib/gcc/x86_64-redhat-linux/10/include
#will be removed later


unix : {
    QMAKE_CFLAGS += -D_REENTRANT

    debug: {
        DEFINES += DEBUG
        QMAKE_CFLAGS_DEBUG += -O0
        QMAKE_CFLAGS_DEBUG += -Wall -Wextra -pedantic

    }


    #SDL
    INCLUDEPATH += /usr/local/include
    LIBS += -L/usr/local/lib -Wl,-rpath,/usr/local/lib -Wl,--enable-new-dtags -lSDL2  -lSDL2_image -lSDL2_mixer -lSDL2_ttf

    INCLUDEPATH += /usr/include
    INCLUDEPATH += /usr/include/lua5.3
    DEPENDPATH  += /usr/include

    #allegro

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
        QMAKE_CFLAGS += -O0
        QMAKE_CXXFLAGS += -O0
    }

    LIBS += -L$$PWD/../../../libs/SDL2-2.0.12/i686-w64-mingw32/lib/ -lmingw32 -lSDL2main -lSDL2.dll -lSDL2_ttf.dll -lSDL2_image.dll -lSDL2_mixer.dll

    INCLUDEPATH += $$PWD/../../../libs/SDL2-2.0.12/i686-w64-mingw32/include
    DEPENDPATH += $$PWD/../../../libs/SDL2-2.0.12/i686-w64-mingw32/include

    #win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../../libs/SDL2-2.0.12/x86_64-w64-mingw32/lib/SDL2.lib
    #else:win32-g++: PRE_TARGETDEPS += $$PWD/../../../libs/SDL2-2.0.12/x86_64-w64-mingw32/lib/libSDL2.a

    #ALLEGRO

    #INCLUDEPATH += $$PWD/../../../libs/mingw32/include
    #DEPENDPATH += $$PWD/../../../libs/mingw32/include
    #LIBS += -L$$PWD/../../../libs/allegro_winpkg-1.11.0/universal/allegro/build-mingw/lib/  -lallegro.dll -lallegro_audio.dll -lallegro_acodec.dll -lallegro_font.dll -lallegro_ttf.dll -lallegro_image.dll -lallegro_main.dll -lallegro_physfs.dll -lallegro_primitives.dll -lallegro_dialog.dll

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
    include/camera.h \
        include/debug.h \
    include/gameplay.h \
        include/keyboard.h \
        include/log.h \
        include/lua_shared.h \
        include/map_render.h \
        include/player.h \
        include/render.h \
        include/resources.h \
        #include/thread.h \
        include/sprite.h \
    include/sprite_animation.h \
        include/text.h \
        include/timer.h \
        include/window.h\
        include/sound.h \
        include/shared.h \
        include/game.h \
        include/lua_vm.h \
        include/lua_hud.h \
        include/hud.h \
        include/map.h \
        include/std.h \
        $$PWD/mapconverter/ini_parser.h \
        $$PWD/mapconverter/csv_parser.h \
        $$PWD/mapconverter/ini.h \


SOURCES += \
        $$PWD/src/main.c \
        src/camera.c \
        src/gameplay.c \
        src/map_render.c \
        src/debug.c \
        src/keyboard.c \
        src/log.c \
        src/lua_shared.c \
        src/player.c \
        src/render.c \
        src/resources.c \
        #src/thread.c \
        src/sprite.c \
        src/sprite_animation.c \
        src/timer.c \
        src/window.c \
        src/sound.c \
        src/shared.c \
        src/game.c \
        src/lua_vm.c \
        src/lua_hud.c \
        src/hud.c \
        src/map.c \
        src/std.c \
        $$PWD/mapconverter/ini_parser.c \
        $$PWD/mapconverter/csv_parser.c \
        $$PWD/mapconverter/ini.c \
        src/text.c


