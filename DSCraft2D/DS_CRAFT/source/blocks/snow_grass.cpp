#include <nds.h> //BLAH
#include "../ndsvideo.h"
#include "block.h" //Include the block graphics
#include "../blockID.h"
#include "../world.h"
#include "../player.h"
#include "../sounds.h"
#include "../inventory.h"
u16* SNOW_GRASSgfx;
int SNOW_GRASSls=0;
void SNOW_GRASS_render(int x,int y){
	createsprite32x32(x,y,SNOW_GRASSgfx,false,0);	
}
void SNOW_GRASS_setup(){
	SNOW_GRASSgfx=oamAllocateGfx(&oamMain,SpriteSize_32x32,SpriteColorFormat_256Color);
	char* blocktiles;
	blocktiles=(char*)&blockTiles;
	blocktiles+=(32*32)*SNOW_GRASS;
	dmaCopy(blocktiles,SNOW_GRASSgfx,32*32);
}
void SNOW_GRASS_colision(playerActor* player,worldObject* world,int bx,int by,int result){
	if (result==0 || result==2){
		player->y=by*32-63; //64 == playerheight
		player->vy=0;
		player->onblock=true;
		if (!(bx==player->sx && by==player->sy)){
			player->sx=bx,player->sy=by;
			if (SNOW_GRASSls==0){
				playSound(GRASS_A);		
				SNOW_GRASSls++;
			}
			else if (SNOW_GRASSls==1){
				playSound(GRASS_B);
				SNOW_GRASSls++;
			}	
			else if (SNOW_GRASSls==2){
				playSound(GRASS_C);
				SNOW_GRASSls++;
			}			
			else if (SNOW_GRASSls==3){
				playSound(GRASS_D);
				SNOW_GRASSls=0;
			}
		}
	}
	if (result==3){//player colides on right
		player->x-=2; //Move him back one so he is not coliding anymore :)
	}
	if (result==1){//colides on left
		player->x+=2;
	}
	if (result==4){
		//colision upwards
		player->vy=0;
		player->y=by*32+33;
	}
}
void SNOW_GRASS_update(int bx,int by,worldObject* world,playerActor* player){
	if (!(bx<player->sx-32 && bx>player->sx+32)){
		//Check for change to dirt
		int i;
		for (i=0;i<=by;i++){
			if (i<by && world->blocks[bx][i]!=AIR) world->blocks[bx][by]=DIRT;	
		}	
	}
}
void SNOW_GRASS_mine(worldObject* world,int* mine_time,int x,int y){
	if (*mine_time>54){
		world->blocks[x][y]=AIR;
		inventoryAdd(DIRT);
		*mine_time=0;
	}
}