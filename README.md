# 1. Introduction
###### This section was last checked in the 2.0.2. version of the engine
**Note:** The 2.0.2. version of the engine now runs on Linux too! This port is thanks to the work of [SuperFola](https://github.com/SuperFola) who also did a few quality of life changes as well, go and check him out!

## 1.1. The structure of this documentation
###### This section was last checked in the 2.0.2. version of the engine
This documentation will have three main parts and a [table of contents](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/documentation/online/4.%20Table%20of%20contents.md/#4-table-of-contents):
* [The first](#1-introduction) is the introduction (the part you are reading right now)
* [The second](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/documentation/online/2.%20How%20to%20use%20the%20engine%20and%202.1.%20How%20the%20engine%20works.md/#2-how-to-use-the-engine) is an overview of [how the engine works](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/documentation/online/2.%20How%20to%20use%20the%20engine%20and%202.1.%20How%20the%20engine%20works.md/#21-how-the-engine-works-a-breakdown-of-the-main-cpp-file) and [how you can operate it and it's different editors](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/documentation/online/2.2.%20How%20to%20use%20the%20editors%2C%20and%20other%20further%20details.md/#22-how-to-use-the-editors-and-other-further-details)
* [The third](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/documentation/online/3.%20Description%20of%20EVERYTHING%20and%203.1.%20Defines.md/#3-detailed-description-of-everything) will go over every last detail about the [defines](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/documentation/online/3.%20Description%20of%20EVERYTHING%20and%203.1.%20Defines.md/#31-defines), [structures](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/documentation/online/3.2.%20Structures.md/#32-structures), [variables](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/documentation/online/3.3.%20Variables%20in%20the%20main%20.cpp%20file.md/#33-variables-in-the-main-cpp-file) and [functions](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/documentation/online/3.4.%20Functions%20and%203.4.1.%20input.h.md/#34-functions) the engine uses

In the [introduction](#1-introduction) I will cover [my motivation](#12-who-the-hell-am-i-and-what-the-hecky-heck-is-this) for this engine, [the idea, the end product and plans about the future of the project](#13-so-what-is-the-project).

[The second part](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/documentation/online/2.%20How%20to%20use%20the%20engine%20and%202.1.%20How%20the%20engine%20works.md/#2-how-to-use-the-engine) will have two segments. [The first](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/documentation/online/2.%20How%20to%20use%20the%20engine%20and%202.1.%20How%20the%20engine%20works.md/#21-how-the-engine-works-a-breakdown-of-the-main-cpp-file) detailing the architecture of the system, what it does. [The second](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/documentation/online/2.2.%20How%20to%20use%20the%20editors%2C%20and%20other%20further%20details.md/#22-how-to-use-the-editors-and-other-further-details) will be the guide to operate it. Hopefully these two segments will provide you with sufficient information to make a game with this engine.

[The last part](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/documentation/online/3.%20Description%20of%20EVERYTHING%20and%203.1.%20Defines.md/#3-detailed-description-of-everything) will (as mentioned above) go over the hows of the systems in place. It will be broken down into different subsections, each dealing with a header or cpp file and it's [defines](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/documentation/online/3.%20Description%20of%20EVERYTHING%20and%203.1.%20Defines.md/#31-defines), [structures](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/documentation/online/3.2.%20Structures.md/#32-structures), [variables](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/documentation/online/3.3.%20Variables%20in%20the%20main%20.cpp%20file.md/#33-variables-in-the-main-cpp-file), or [functions](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/documentation/online/3.4.%20Functions%20and%203.4.1.%20input.h.md/#34-functions). [This part](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/documentation/online/3.%20Description%20of%20EVERYTHING%20and%203.1.%20Defines.md/#3-detailed-description-of-everything) will act more like a cheat sheet than anything, if you wish to conserve your sanity do not read it from start to finish in one sitting.

## 1.2. Who the hell am I and what the hecky heck is this?
###### This section was last checked in the 2.0.2. version of the engine
I am a high school student, who is interested in computer science and more specifically, creating video games. This project was a challenge I gave myself. The aim was to find out if I am able to create something rather complex with my basic understanding of programming, whilst not looking up solutions to my problems. I have already tried my hands at [a project similar to this](https://github.com/mmmuscus/Snake), but this was way more ambitious so it was also a test in planning and creating coexisting systems.

## 1.3. So what is the project?
###### This section was last checked in the 2.0.2. version of the engine
The bare minimum I wanted to accomplish was a real time 2D top down game, with a "realistic" binary shading system (this was all planned to be running in the windows console). The concept of the shading system is the following: There is a player (represented by the '@' character); who has a field of view in which he can see things; anything that would block his view (e.g.: an 'x' character) casts a shadow, meaning that he can't see the things behind the "wall", even if those things would be in his field of view.

Here is an example for the shading system in action:

![example](https://github.com/mmmuscus/Shadow-Functions-Engine/blob/master/documentation/screenShots/example.png)

Besides the minimum goal I created basic text file based level and field of view editors. I also created the option to make new characters that could block light, or player movement. In the latest version (2.0.0.) I added an animation pipeline, with this you can create .txt files that will be parsed into animation arrays and can be played in the console window.

Features as of now:
* Real time 8 directional player movement
* Binary shading
* Map and field of view editors
* Character attribute editors (can this character block light? can it block player movement?)
* Animation pipeline

The next big update of the project (3.0.0.) will be the entity update. In this version I plan to add different entities with different attributes, for example: torches that emit light, NPCs that can be interacted with, posts that have text on them etc.
