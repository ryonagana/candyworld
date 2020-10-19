TEMPLATE = app
CONFIG += console c11 use_c_linker
CONFIG -= app_bundle
CONFIG -= qt
TARGET = mapconv

#fedora claims NULL is undefined just cand find stddef.h (it might be a bug?)
#so i hardcorded my gcc include path just to shut up compiler
INCLUDEPATH += /usr/lib/gcc/x86_64-redhat-linux/10/include
#will be removed later


    LIBS += -L/usr/local/lib #-lallegro -lallegro_main
    INCLUDEPATH += /usr/local/include /usr/include
SOURCES += \
        csv_parser.c \
        ini_parser.c \
        main.c \
        ini.c \
        map.c

HEADERS += ini.h \
    csv_parser.h \
    ini_parser.h \
    map.h
