/*
 * defs.h
 *
 *  Created on: 19.05.2017
 *      Author: sahel08_bk7
 */

/*
 * ART SOURCES:
 * Projectiles: 	http://millionthvector.blogspot.de/p/free-sprites.html
 * Fire: 			https://opengameart.org/content/wgstudio-fire-animation-loop
 * Explosion: 		https://opengameart.org/content/explosion
 * Metal Structure: https://opengameart.org/content/metal-grate-texture
 * Metal Supports: 	https://opengameart.org/content/brown-metal-trim (And similar from the same author)
 * Laser Flare: 	http://www.photos-public-domain.com/2011/11/19/bright-sun/
 * Destructible Rock: textures.com
 * Everything Else: Myself
 */

#ifndef DEFS_H_
#define DEFS_H_

#define LEVELWIDTH 2000
#define LEVELHEIGHT 1500
#define SWIDTH 1280
#define SHEIGHT 800
#define BGWIDTH 1600
#define BGHEIGHT 1155
#define WINDOWNAME "Game"
#define DEFAULTTAG '&'
#define MIN_FRAMETIME 10

//CONSTANTS
#define GRAVITY 0.4
#define FRICTION 0.95
#define PLAYER_ACCEL_X 0.6
#define PLAYER_ACCEL_Y 0.8
#define BOSS_TAILSEGMENT_ACEL_MULTIPLIER 0.7f
#define BOSS_TAILSEGMENT_AACEL_MULTIPLIER 0.06f
#define BOSS_TAILSEGMENT_VEL_MULTIPLIER 0.1f
#define BOSS_TAILSEGMENT_AVEL_MULTIPLIER 0.4f
#define BOSS_TAILSEGMENT_BLEND_VELOCITY 4.0f
#define BOSS_TAILSEGMENT_DISTANCE 50
#define BOSS_TAILSEGMENT_CONNECTOR_HIDE_DISTANCE_UP 10
#define BOSS_TAILSEGMENT_CONNECTOR_HIDE_DISTANCE_DOWN 15
#define BOSS_IDLEANIMATION_SPEED 3
#define BOSS_IDLEANIMATION_RADIUS 10
#define BOSS_DEFAULT_TAIL_ROTATION 200
#define BOSS_TAILWIGGLE_AMPLITUDE 30
#define BOSS_TAILWIGGLE_SPEED 0.005f
#define CAMERASMOOTHING 0.03f
#define EASE_OUT_PERC 0.2f
#define EASE_IN_PERC 0.1f
#define MOVE_ANIM_VEL 3
#define ROCKET_SPEED 3.0f
#define BOSS_LASER_DURATION 1500.0f

//PATHS
#define HITMARKER "resource/hitmarker.png"
#define FIRESPRITE "resource/fire.png"
#define POINT "resource/point.png"
#define PLAYERSPRITE "resource/player.png"
#define PROJECTILESPRITE "resource/projectile.png"
#define MISSILESPRITE "resource/missile.png"
#define MISSILEDROPSPRITE "resource/missile_drop.png"
#define EXPLOSIONSPRITE "resource/exp.png"
#define LARGEEXPLOSIONSPRITE "resource/exp_large.png"
#define TERRAIN1 "resource/terrain1.png"
#define TERRAIN1_MASK "resource/terrain1_msk.png"
#define BACKGROUND1 "resource/bg_volcano.png"
#define BOSS_TAILSEGMENT_SPRITE "resource/boss_tailsegment.png"
#define BOSS_TAILSEGMENT_SPRITE_END "resource/boss_tailsegment_end.png"
#define BOSS_TAILSEGMENTCONNECTOR_SPRITE "resource/boss_tailsegmentconnector.png"
#define BOSS_HEAD_SPRITE "resource/boss_head.png"
#define BOSS_HEAD_SPRITE_ALTERNATIVE "resource/boss_head_alt.png"
#define LASER_SPRITE "resource/laser_sprite.png"
#define LASER_IMPACT_SPRITE "resource/flare_01_0.png"

//COLORS
#define TRANSPARENT 16777215
#define EARTH -12816337

//MATH
#define PI 3.14159265


#endif /* DEFS_H_ */
