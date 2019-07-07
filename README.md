# SDL2-Game
A small 2D, SDL2 Game written in C++ featuring destructive terrain, raycasts, tailphysics and more!

![bsp_img](https://i.imgur.com/bT7p3lS.jpg)

This is what it looks like: https://www.youtube.com/watch?v=upb3DJJbQIM

Only dependencies are the SDL2 and SDL2-image libraries. See [here](https://krother.gitbooks.io/objektorientierte-programmierung-mit-c/content/gitbook/SDL_unter_eclipse.html).

All code was written by me and is public domain.

# Controls
- WASD to move the player
- LMB to fire a projectile that destroys terrain
- RMB to create terrain

Healthbars and AI are missing, so you will have to control the boss/enemy yourself:
- 1 for the Boss to shoot his laser
- 2 for the Boss to shoot his rockets
- 3 to toggle a continous rain of rockets

# Sources for Artwork:
- Projectiles: 	http://millionthvector.blogspot.de/p/free-sprites.html
- Fire animation: 			https://opengameart.org/content/wgstudio-fire-animation-loop
- Explosion animation: 		https://opengameart.org/content/explosion
- Metal Structure: https://opengameart.org/content/metal-grate-texture
- Metal Supports: 	https://opengameart.org/content/brown-metal-trim (And similar from the same author)
- Laser Flare: 	http://www.photos-public-domain.com/2011/11/19/bright-sun/
- Destructible Rock texture: textures.com
- Everything Else: Myself

# Documentation:

### Root directory

The root directory contains what you might consider to be the 'game engine':
- *defs.h*: All constant values used across other files, including file directories, window size etc.
- *random.h*: Inline header file to generate random numbers.
- *main.cpp*: Runs the start-method in gamemaster.cpp. That's all.
- *gamemaster.cpp/.h*: Contains the base 'game-loop'. Continously clears, draws and updates all relevant objects.
- *base.cpp/.h*: Fundamental classes/functions used and inherited throughout the project. This includes: Timer, Vector2, Camera, GameWindow, Object, Image, AdvImage. Object being the base class for all Objects drawn on screen.


### Assets directory

Includes more specialized files. All of these inherit from either the Object or Image class.
- *animation*: Class for a spritesheet-animation. Used by explosion or fire aniamtions, aswells as the player sprite.
- *background*: Parallax background image that scrolls relative to player position and level size.
- *terrain*: Actual level. Pixel collision and destructible terrain are handled here.
- *missile*: The missiles that the boss spawns on his second attack.
- *physicsObj*: Base class for all physics-based Objects.
- *player*: The player.
- *projectile*: Base class for physics-based projectiles.


### assets/NAV directory

Point- and Path-classes used for the Navigation of the Boss.
Paths can have ease-in/-out aswell as linear, bezier or sine-curve interpolations.
nav_graph creates and includes preset paths for the boss to navigate along.


### assets/BOSS directory

All classes concerning the boss.
- *boss_AI*: Main wrapper for the entire thing. Looks at what attack the boss is doing and executes it by calling boss_Controller methods.
- *boss_Controller*: Handles boss idle animations, laser animations etc. Second layer of complexity wrapping.
- *boss_Head*: The main bulk of the boss' head.
- *boss_TailSegment*: The small segments that constitute the boss' tail. Each segment has an angular and positional velocity aswell as an angular and positional acceleration. At a certain self-positonal-velocity the segments will accelerate towards the vector of said velocity. If this velocity is smaller than the given threshhold, the segments will accelerate towards their default position.
- *boss_TailSegmentConnector*: The red connectors between segments.


Certain elements are heavily inspired by the Supreme Jeh'Oul bossfight from Wings of Vi ([this one](https://www.youtube.com/watch?v=VD-y3-hH1do)).
