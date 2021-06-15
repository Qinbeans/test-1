# Instructions
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

# Credits
All the repositories I used are not mine and I do not take credit for them.<br>
Nathan Chan<br>
Ryan Fong<br>
