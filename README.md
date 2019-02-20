# Introduction
**Note:** I was using Dev C++ as the IDE with TMD-GCC 4.9.2. as the compiler, I have seen the project not functioning as intended with other IDEs and compilers.
## The structure of this documentation
###### This section was last checked in the 1.0.0. version of the engine
This documentation will have three main parts and a table of contents:
* [The first](#introduction) is the introduction (the part you are reading right now)
* [The second](#how-to-use-the-engine) is an overview of [how the engine works](#how-the-engine-works-a-breakdown-of-the-main-cpp-file) and how can you operate it and it's different editors
* The third will go over every last detail about the structures variables and functions the engine uses

In the [introduction](#introduction) I will cover [my motivation](#who-the-hell-am-i-and-what-the-hecky-heck-is-this) for this engine, [the idea, the end product and plans about the future of the project](#so-what-is-the-project).

[The second part](#how-to-use-the-engine) will have two segments. [The first](#how-the-engine-works-a-breakdown-of-the-main-cpp-file) detailing the architecture of the system, what it does. The second will be the guide to operate it. Hopefully theese two segments will provide you with sufficent information to make a game with this engine.

The last part will (as mentioned above) go over the hows of the systems in place. It will be broken down into different subsections, each dealing with a header or cpp file and it's structres, variables, or functions.

## Who the hell am I and what the hecky heck is this?
###### This section was last checked in the 1.0.0. version of the engine
I am a highschool student, who is interested in computer science and more specifically, creating video games. This project was a challange I gave myself. The aim was to find out if I am able to create something rather complex with my basic understanding of programming, whilst not looking up solutions to my problems. I have already tried my hands at [a project similar to this](https://github.com/mmmuscus/Snake), but this was way more abitious so it was also a test in planning and creating coexsiting systems.

## So what is the project?
###### This section was last checked in the 1.0.0. version of the engine
The bare minimum I wanted to accomplish was a real time 2D top down game, with a "realistic" binary shading system (this was all planned to be running in the windows console). The concept of the shading system is the following: There is a player (represented by the '@' character); who has a field of view in which he can see things; anything that would block his view (e.g.: an 'x' character) casts a shadow, meaning that he can't see the things behind the "wall", even if those things would be in his field of view.

Right now this shading system has a small bug, which I will discuss in a later section of the documentation. Besides the minimum goal I created basic text file based level and field of view editors. I also created the option to make new characters that could block light, or player movement.

Features as of now:
* Real time 8 directional player movement
* Binary shading
* Map and field of view editors
* Character attribute editors (can this character block light? can it block player movement?)

The next main goal of the project is to make an animation pipeline. The plan for it is to have every frame drawn in a textfile under each other, with a general function that can read any animation text file into a 3 dimensional array, and another general function that could play said animation in a set position on the screen. Beside this main goal I plan to make several quality of life changes to the different text based editors.

# How to use the engine
## How the engine works: a breakdown of the main .cpp file
###### This section was last checked in the 1.0.0. version of the engine
First things first. The system adds all variables, most of theese are vital for the engine and should not be altered. All of theese will be explained in bigger detail in the next big segement of the documentation, but here are some examples:
```cpp
bool isWPressed;
```
This variable is true on any frame on which the W button is pressed.
```cpp
koordinate playerPov;
```
The koordinate structure has two sub variables: one for the x and another for the y axis. This koordinate variable stores the coordinate from which the player "sees" things. Algorythmically speaking it stores the coordinate from which lines are cast that will determine whether something is in the shadows or not.
```cpp
bool isNotExit = true;
```
While this variable is true the game loop keeps being called every x miliseconds.

The next category of variables are ones that are hardcoded, but can be freely altered to anyone's desire. Again I will provide some examples but every variable will be explained in detail in the next segment of the documentation:
```cpp
player.row = 31;
player.col = 45;
```
This is the starting position of the player. The row runs along the x axis and the col runs along the y axis. It should be noted that theese are different from the coordinates that are mentioned above. Theese refer to a set cell's row and column on the map. Each cell's four points have different coordinates. The cell that is defined by row = a and col = b has the following four coordinates associated with it's points: (a; b), (a + 1; b), (a; b + 1) and (a + 1; b + 1). It should also be noted that the coordinate system is only dealing with positive coordinates, and it's flipped, meaning that the (0; 0) point is in the top left, and the (infinity; infinity) point would be in the bottom right.
```cpp
int sleepTime = 30;
```
This variable is the number of miliseconds that pass between every iteration of the game loop. 
