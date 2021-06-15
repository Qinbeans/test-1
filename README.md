# Instructions
This will initialize the folders required for making the game and only needs to be ran once.<br>
 ```make init```<br>
 Always needs to be run everytime you want to make a new build.<br>
 ```make```<br>
## Windows
### Requirements
-[MSYS2](https://www.msys2.org/)<br>
-[Clang](https://packages.msys2.org/package/mingw-w64-x86_64-clang): [Website](https://clang.llvm.org/)<br>
-[Enet](https://packages.msys2.org/package/mingw-w64-x86_64-enet?repo=mingw64): [Website](http://enet.bespin.org/)<br>
-[Raylib](https://www.raylib.com/) *This is already installed for most devices*<br>
### Installation
-Follow MSYS installation guide (click/launch and choose configuration you want)<br>
-Launch MSYS2 and copy the following commands<br>
```pacman -Syu```<br>
```pacman -S mingw-w64-x86_64-clang```<br>
```pacman -S mingw-w64-x86_64-enet```<br>
-add the following directory replacing MSYSdir with your MSYS directory to environment path (HINT: search for environment and click environment variables)<br>
```<MSYSdir>/mingw64/bin```<br>
```<MSYSdir>/bin```<br>
## Mac
### Requirements
-Clang<br>
-Brew<br>
-Enet<br>
-Raylib<br>
### Installation
-Type the following command into the terminal<br>
```brew install enet```
## Linux(WSL insiders does work)
-Clang<br>
-Brew<br>
-Enet<br>
-Raylib<br>
Installation may vary, but most mainstream package managers have all these available

# Premise
This is just a fun little project to get to know code better.  A bonus is that we can play with friends.

# Some Hints
## Makefile
I tried to make a more fluid way of making commits by adding date, time, and user to the commit changes<br>
```make updategit COMMENTS=<some text>```

# Credits
All the repositories I used are not mine and I do not take credit for them.<br>
Nathan Chan<br>
Ryan Fong<br>
