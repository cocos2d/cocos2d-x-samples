//
//  consts.h
//  Moon3d
//
//  Created by Hao Wu on 3/5/14.
//
//

#ifndef Moon3d_consts_h
#define Moon3d_consts_h

#define PLAYER_LIMIT_LEFT -240
#define PLAYER_LIMIT_RIGHT 240
#define PLAYER_LIMIT_TOP 737
#define PLAYER_LIMIT_BOT -376

const static Rect BOUND_RECT = Rect(-380,PLAYER_LIMIT_BOT-60,760,PLAYER_LIMIT_TOP-PLAYER_LIMIT_BOT+180 );
const static Rect ENEMY_BOUND_RECT = Rect(-480,PLAYER_LIMIT_BOT-60,960,PLAYER_LIMIT_TOP-PLAYER_LIMIT_BOT+380 );
#endif

enum entityTypes
{
    kPlayerBullet,
    kPlayerMissiles,
    kEnemyBullet,
    
    kPlayer,
    kEnemy,
    
    kEnemyFodder,
    kEnemyFodderL,
    kEnemyBigDude,
    kEnemyBoss,
    
    kRewardPotion,
    kRewardCoin
};