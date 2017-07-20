/*
 * defs.h
 *
 *  Created on: 19.05.2017
 *      Author: sahel08_bk7
 */

/*
 * SOURCES:
 * http://millionthvector.blogspot.de/p/free-sprites.html
 * https://opengameart.org/content/wgstudio-fire-animation-loop
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
#define HITMARKER "hitmarker.png"
#define FIRESPRITE "fire.png"
#define POINT "point.png"
#define PLAYERSPRITE "player.png"
#define PROJECTILESPRITE "projectile.png"
#define MISSILESPRITE "missile.png"
#define MISSILEDROPSPRITE "missile_drop.png"
#define EXPLOSIONSPRITE "exp.png"
#define LARGEEXPLOSIONSPRITE "exp_large.png"
#define TERRAIN1 "terrain1.png"
#define BACKGROUND1 "bg_volcano.png"
#define BOT_BASIC_SPRITE "6.png"
#define BOSS_TAILSEGMENT_SPRITE "boss_tailsegment.png"
#define BOSS_TAILSEGMENT_SPRITE_END "boss_tailsegment_end.png"
#define BOSS_TAILSEGMENTCONNECTOR_SPRITE "boss_tailsegmentconnector.png"
#define BOSS_HEAD_SPRITE "boss_head.png"
#define BOSS_HEAD_SPRITE_ALTERNATIVE "boss_head_alt.png"
#define LASER_SPRITE "laser_sprite.png"
#define LASER_IMPACT_SPRITE "laser_impact.png"

//COLORS
#define TRANSPARENT 16777215
#define EARTH -12816337

//MATH
#define PI 3.14159265


#endif /* DEFS_H_ */
