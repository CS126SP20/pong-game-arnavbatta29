# Final Project

[![license](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![docs](https://img.shields.io/badge/docs-yes-brightgreen)](docs/README.md)

Read [this document](https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html) to understand the project
layout.

<img width="600" alt="csfinalprojectSS" src="https://user-images.githubusercontent.com/55147991/81247570-f8a0fb00-8fdf-11ea-9344-7e0a14c8adde.png">

Pong is a popular two-player game which is similar to air hockey, with both players using their paddles to knock the game ball to the opponent's side, and earning a point if the ball hits the opponent's home wall. The first player to 10 points wins the game. This version of Pong also contains a practice mode in which a player can play against a computer controlled pong paddle.

## Dependencies:
* Clion 
* Cinder
* CMake
* Box2d

## How to install: 
(Adaped from https://courses.grainger.illinois.edu/cs126/sp2020/assignments/snake/)

(Windows)
1) Downgrade your Microsoft Build Tools to v140 or v141. This is how:
2. Uninstall Visual Studio Build Tools 2019 if present on your machine by navigating to Control Panel > Programs > Programs and Features > Uninstall a Program, and then uninstall Visual Studio Build Tools 2019
3. Go to: https://my.visualstudio.com/Downloads?q=visual%20studio%202015&wt.mc_id=o~msft~vscom~older-downloads. You'll also be able to access this page by going to https://my.visualstudio.com/downloads and searching for 2015
4) Next, download Visual Studio Community 2015 with Update 3 for your architecture
5) Run the installer and if prompted, select Modify.
6) Now, you only need to select the Common Tools for Visual C++ 2015 option, then click Next. Note that this will take up around 8GB on your machine.
7) Continue along with the installation. The installation process can take a while (~20 minutes).
8) After the installation is complete, do not need to click the "Launch" button.
9) Go back to CLion and make the default toolchain be a Visual Studio environment, pointing to C:\Program Files (x86)\Microsoft Visual Studio 14.0. Confirm that there are no warnings.


(MacOS and Windows)
1) Download Clion (https://www.jetbrains.com/clion/)
2) Download Cinder (v0.9.2) for your platform (https://libcinder.org/download). 
3) Extract the downloaded item into a folder. Let's call this folder ~/Cinder
4) Open the ~/Cinder folder in CLion and click the green build button. This will build libcinder. You only need to do this once per machine.
5) Create a directory, say my-projects in ~/Cinder. Clone the final project into this folder. 
6) Open the final project in CLion, set the target to my-app and click the run button

## Controls: 
| Key           | Action                        |
| ------------- | ------------------------------|
| a             | bottom paddle left            |
| d             | bottom paddle right           |
| left arrow    | top paddle left               |
| right arrow   | top paddle right              |
| p             | enable/disable practice mode  |
| n             | reset scores/new game         |
| q             | quit game                     |

## Additional Notes: 
This game was developed as my final project for CS 126. I utilized both the OpenGL library as well as Box2D to simulate movement and ball physics. 

#### Author: Arnav Batta (arnavb3@illinois.edu)
