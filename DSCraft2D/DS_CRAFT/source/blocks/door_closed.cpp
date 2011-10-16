#include <nds.h> //BLAH
#include "../ndsvideo.h"
#include "block.h" //Include the block graphics
#include "../blockID.h"
u16* DOOR_CLOSEDgfx;
void DOOR_CLOSED_render(int x,int y){
	createsprite32x64(x,y,DOOR_CLOSEDgfx,false,0);	
}
void DOOR_CLOSED_setup(){
	DOOR_CLOSEDgfx=oamAllocateGfx(&oamMain,SpriteSize_32x64,SpriteColorFormat_256Color);
	char* blocktiles;
	blocktiles=(char*)&blockTiles;
	blocktiles+=(32*32)*DOOR_CLOSED;
	dmaCopy(blocktiles,DOOR_CLOSEDgfx,32*64);
}