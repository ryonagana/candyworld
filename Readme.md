# Project Candy World

A Simple Platform game using C11 and SDL2 - no more details cause still indev

This project needs [SDL 2](https://www.libsdl.org) and need also:
> [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/)
> [SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer/)
> [SDL2_image](https://www.libsdl.org/projects/SDL_image/)
> [Lua 5.3+](https://lua.org)
> [Physfs](https://icculus.org/physfs/)


### Installing Packages

##### Archlinux:
```sh
$ sudo pacman -Syu SDL2 SDL2_mixer SDL2_ttf SDL2_image physfs lua5.3
```

##### Debian / Ubuntu
```sh
$ sudo apt-get install SDL2-dev SDL2_mixer-dev SDL2_ttf-dev SDL2_image-dev physfs-dev lua5.3-dev
```

##### Fedora
```sh
$ sudo dnf install SDL2-devel SDL2_mixer-devel SDL2_ttf-devel SDL2_image-devel physfs-devel lua5.3-devel
```


##### OpenSUSE
```sh
$ sudo zypper in SDL2-devel SDL2_mixer-devel SDL2_ttf-devel SDL2_image-devel physfs-devel lua5.3-devel
```

## Development:

Opening the project  file needs [Qt Creator](https://www.qt.io/product/development-tools) installed but iof you just want to build you just need  qmake-qt5 installed for generating the Makefile 

##### Installing QT Creator

###### Debian
```sh
$ sudo apt-get install qtcreator qmake-qt5 
```
###### Arch Linux
```sh
$ sudo pacman -Syu qtcreator qmake-qt5 
```

###### Fedora
```sh
$ sudo dnf install qtcreator qmake-qt5 
```

###### OpenSUSE
```sh
$ sudo zypper in qtcreator qmake-qt5 
```

##### Build with QMake
```sh
$ qmake-qt5 candy2.pro
$ make -j16
```

