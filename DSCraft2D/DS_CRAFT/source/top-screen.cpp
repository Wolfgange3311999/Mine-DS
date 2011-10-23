#include <nds.h>
#include <stdio.h>
#include "ndsvideo.h" // Include the video functions (for setupVideo();)
#include "blockID.h" //Want to use it to display the current block
#include "world.h"
#include "top-screen.h"
#include "block.h"
#include <stdio.h>
#include "h1.h" //Include Heart graphics 
#include "subscreen2.h" //image file
int oldblock=0;
u16* gfx;
u16* heartgfx;
void subBGSetup(){ //Its a setup function, not a update function :P
	oamInit(&oamSub, SpriteMapping_1D_32, true);
	vramSetBankD(VRAM_D_SUB_SPRITE);
	vramSetBankI(VRAM_I_LCD);
	gfx = oamAllocateGfx(&oamSub, SpriteSize_32x32, SpriteColorFormat_256Color);
	heartgfx = oamAllocateGfx(&oamSub, SpriteSize_8x8, SpriteColorFormat_256Color);
   	int bg = bgInitSub(3, BgType_Bmp16, BgSize_B16_256x256, 0,0);
    	dmaCopy(subscreen2Bitmap, bgGetGfxPtr(bg), subscreen2BitmapLen);
	dmaCopy(blockPal,VRAM_I_EXT_SPR_PALETTE[0],blockPalLen);
	dmaCopy(h1Pal,VRAM_I_EXT_SPR_PALETTE[1],h1PalLen);
	char* h1gfx;//Copy the graphics into memory
  	h1gfx=(char*)h1Tiles;
	dmaCopy(h1gfx,heartgfx,8*8);
	vramSetBankI(VRAM_I_SUB_SPRITE_EXT_PALETTE);
}
void subLifes(int count){
    oamClear(&oamSub,3,11); //clear the 10 lives sprites
    int i=1;
	if (count>=1){

	oamSet(&oamSub,3, //Then draw the sprite on the screen
	1, 
	176, 
	0, 
	1,
	SpriteSize_8x8, 
	SpriteColorFormat_256Color, 
	heartgfx, 
	-1, 
	false, 
	false,			
	false, false, 
	false	
	);   
	if (count>=2){
	oamSet(&oamSub,4, //Then draw the sprite on the screen
	9, 
	176, 
	0, 
	1,
	SpriteSize_8x8, 
	SpriteColorFormat_256Color, 
	heartgfx, 
	-1, 
	false, 
	false,			
	false, false, 
	false	
	); 
	if (count>=3){
	oamSet(&oamSub,5, //Then draw the sprite on the screen
	18, 
	176, 
	0, 
	1,
	SpriteSize_8x8, 
	SpriteColorFormat_256Color, 
	heartgfx, 
	-1, 
	false, 
	false,			
	false, false, 
	false	
	);  
	if (count>=4){
	oamSet(&oamSub,6, //Then draw the sprite on the screen
	27, 
	176, 
	0, 
	1,
	SpriteSize_8x8, 
	SpriteColorFormat_256Color, 
	heartgfx, 
	-1, 
	false, 
	false,			
	false, false, 
	false	
	); 
	if (count>=5){
	oamSet(&oamSub,7, //Then draw the sprite on the screen
	36, 
	176, 
	0, 
	1,
	SpriteSize_8x8, 
	SpriteColorFormat_256Color, 
	heartgfx, 
	-1, 
	false, 
	false,			
	false, false, 
	false	
	);  
	if (count>=6){
	oamSet(&oamSub,8, //Then draw the sprite on the screen
	45, 
	176, 
	0, 
	1,
	SpriteSize_8x8, 
	SpriteColorFormat_256Color, 
	heartgfx, 
	-1, 
	false, 
	false,			
	false, false, 
	false	
	);  
	if (count>=7){
	oamSet(&oamSub,9, //Then draw the sprite on the screen
	54, 
	176, 
	0, 
	1,
	SpriteSize_8x8, 
	SpriteColorFormat_256Color, 
	heartgfx, 
	-1, 
	false, 
	false,			
	false, false, 
	false	
	);
	if (count>=8){
	oamSet(&oamSub,10, //Then draw the sprite on the screen
	63, 
	176, 
	0, 
	1,
	SpriteSize_8x8, 
	SpriteColorFormat_256Color, 
	heartgfx, 
	-1, 
	false, 
	false,			
	false, false, 
	false	
	);  
	}   
	} 
	} 
	} 
	}
	} 
	}
	}

}

void subShowBlock(int block){
	if (block==AIR) oamClear(&oamSub,0,3); //If the block is air, remove all of the sprite's with oam Clear
	if (block==PLACED_LOG) block=LOG; //If the block is a PLACED_LOG pretend it is a normal LOG
	if (block==PLACED_LOG_W) block=WHITE_WOOD; //Look up
	if (block==PLACED_LOG_D) block=DARK_WOOD;//^
	if (block==PLACED_LEAF) block=LEAVES;//^
	if (block<128){//If the block is actually in the block.png file
		char* blockgfx;//Copy the graphics into memory
		blockgfx=(char*)blockTiles;
		blockgfx+=(32*32)*block;//this is in the block/*.cpp
		dmaCopy(blockgfx,gfx,32*32);//^
		oamSet(&oamSub,0, //Then draw the sprite on the screen
			38, 
			32, 
			0, 
			0,
			SpriteSize_32x32, 
			SpriteColorFormat_256Color, 
			gfx, 
			-1, 
			false, 
			false,			
			false, false, 
			false	
			);    	
	}

}
	