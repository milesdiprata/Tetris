Tetris in C++!
==============

The classic game of Tetris written in C++ using SDL 2.0 written on Mac.

Featuring the same tetromino colors as seen in Tetris DX for Game Boy color.

## Dependencies

Required external libraries:

+ [SDL 2.0](https://www.libsdl.org/download-2.0.php)

### Mac

#### Install Homebrew
```
ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
# Check for success
brew doctor
```

#### Instal SDL 2.0
```
brew install sdl2
```

## Build & Run Game
```
git clone https://github.com/milesdiprata/tetris
cd tetris
make
./tetris
```

## Controls

Left arrow: 	move tetromino one cell to the left

Right arrow: 	move tetromino one cell to the right

Down arrow:		move tetromino one cell down

x:				send tetromino to the bottom-most free position on the board

z: 				rotate the current tetromino

## Credits

Thanks [Javier López](https://twitter.com/javilop) for his Tetris tutorial

Gained inspiration from his game loop and tetromino dictionary method.
