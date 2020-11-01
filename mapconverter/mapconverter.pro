TEMPLATE = app
CONFIG += console c11 use_c_linker
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c11


QMAKE_CFLAGS += -std=c11 -Wall -Wextra -pedantic


#fedora claims NULL is undefined just cand find stddef.h (it might be a bug?)
#so i hardcorded my gcc include path just to shut up compiler
INCLUDEPATH += /usr/lib/gcc/x86_64-redhat-linux/10/include
#will be removed later




DEFINES += MAPCONV_PROJECT

HEADERS += \
    csv_parser.h \
    ini.h \
    ini_parser.h \
    ../include/map.h

SOURCES += \
    csv_parser.c \
    ini.c \
    ini_parser.c \
    main.c \
    ../src/map.c
