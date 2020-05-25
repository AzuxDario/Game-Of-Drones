# Game of Drones
<p align="center">
<a href="https://github.com/AzuxDario/Game-Of-Drones/pulls?q=is%3Apr+is%3Aclosed"><img src="https://img.shields.io/github/issues-pr-closed-raw/AzuxDario/Game-Of-Drones" alt="Closed pull requests"></img></a>	
<a href="https://github.com/AzuxDario/Game-Of-Drones/blob/master/LICENSE"><img src="https://img.shields.io/github/license/AzuxDario/Game-Of-Drones" alt="License"></img></a>
</p>
Simple drone racing game in space.

# Origin
We're learning OpenGL API during laboratory classes by creating project. Project should be done as 3D racing game which simple models of drones and terrain. Template provided to us was made using WinAPI and old version of OpenGL. In template models was created using `glVertex3fv()` functions.

Since we wanted to learn something newer, we switched to OpenGL 3.3. It's not the newest version, but it has shaders, buffers and other useful stuff. To made window and UI elements we used Qt 5.7.

All models was made all by us. Textures belongs to Solar System Scope. Some textures are remixes of SSS textures.
Game has also simple collision system.

# Gameplay
![Game window](./Pictures/ScreenShot%202%2017-06-16%20003.png)

Racing takes place in space. Player races against NPC with simple AI (go to next checkpoint). The goal is to fly through all checkpoints and finish is near to Pluto.

# Control
  * W - up
  * S - down
  * A - left
  * D - right
  * space - accelerate

# Bugs
The most noticable bug is [gimbal lock](https://en.wikipedia.org/wiki/Gimbal_lock). Since we weren't aware of this problem during classes.

# Release
Now - 3 years after making this project, we release it as exetutable version after refactoring and moving to Qt 5.12. Only just for fun.

# Used stuff
  * [Qt 5.7](https://www.qt.io/)
  * [OpenGL](http://www.opengl.org/)
  * [Textures - Solar System Scope](https://www.solarsystemscope.com/textures/)
