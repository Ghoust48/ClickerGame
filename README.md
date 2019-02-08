# Bubble clck-clck-clck

My game is create on C++ and were used GLUT and GLAUX. 
To play in game you need install libraries GLUT and GLAUX. To do this you need:
1. Install libraries;
2. Project Setup Visual Studio.

# Install libraries

1. Download folder "GL Files".
2. Copy glut.dll and glut32.dll to the Winodws: system folder (the folder may be named differently, depending on the version of Windows you have installed).
   Important! On a 64-bit system (for example, Windows 7), place the 32-bit .dll in the "C: / Windows / SysWOW64" folder where the 32-bit dynamic libraries are stored. The System32 folder, on the other hand, is designed to store 64-bit .dlls, which sometimes causes confusion.
4. Copy glut.h to the "\ include \ GL folder" (- the folder where VC ++ is installed).
5. Copy glut.lib and glut32.lib to the "\ lib folder".

# Project Setup Visual Studio

1. Launch VS and create a new project like "Console Win32 Application".
2. Specify in the additional parameters of the project "Empty Project".
3. In the project properties (menu "Project / Properties") select the tab "Linker" and then "Input".
4. In the "Additional dependencies" field (Linker -> Input -> Additional Dependencies) add: opengl32.lib glut32.lib glu32.lib.
