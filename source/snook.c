#include "snook.h"

#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

#define leftX -20
#define rightX 400
#define topY -20
#define bottomY 240

#define ILLITERATION_SKIP 250 // Skips a certian amount of Illiterations to create delay between movement

#define PLAYERBLOCK_WIDTH 20
#define PLAYERBLOCK_HEIGHT 20

int main(int argc, char* argv[]) {
	score = 0;
	srand((unsigned) time(&t)); // Create Random Num Gen
	currentdir.dir = right;

	notDead = true;

	blocks[0].position.pointX = 120;
	blocks[0].position.pointY = 20;
	blocks[0].direction.dir = right;

	blocks[1] = blocks[0];
	blocks[1].position.pointX = blocks[0].position.pointX - 20;

	blocks[2] = blocks[1];
	blocks[2].position.pointX = blocks[1].position.pointX - 20;

	blocks[3] = blocks[2];
	blocks[3].position.pointX = blocks[2].position.pointX - 20;

	blocks[4] = blocks[3];
	blocks[4].position.pointX = blocks[3].position.pointX - 20;

	blocks[5] = blocks[4];
	blocks[5].position.pointX = blocks[4].position.pointX - 20;


	// Init libs
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	//consoleInit(GFX_TOP, &topScreen);
	consoleInit(GFX_BOTTOM, NULL);

	// Create screens
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

	// Create colors
	u32 clrWhite = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
	u32 clrBlack = C2D_Color32(0x00, 0x00, 0x00, 0xFF);
	u32 clrGreen = C2D_Color32(0x00, 0xFF, 0x00, 0xFF);
	u32 clrRed   = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);

	// Main loop
	while (aptMainLoop())
	{
		hidScanInput();

		// Respond to user input
		u32 kDown = hidKeysDown();

		// TODO: turn this into a switch
		// Detect Key Inputs
		if (kDown & KEY_START){
			break; // Exit to the Homebrew Menu/Home menu (if installed as CIA)
		}

		/*
		if (kDown & KEY_A){
			switch (blocks[block_count-1].direction.dir){
				case up:
					blocks[block_count] = blocks[block_count-1];
					blocks[block_count].position.pointY += 20;
					block_count++;
					break;
				case down:
					blocks[block_count] = blocks[block_count-1];
					blocks[block_count].position.pointY -= 20;
					block_count++;
					break;
				case left:
					blocks[block_count] = blocks[block_count-1];
					blocks[block_count].position.pointX += 20;
					block_count++;
					break;
				case right:
					blocks[block_count] = blocks[block_count-1];
					blocks[block_count].position.pointX -= 20;
					block_count++;
					break;
			}
		}

		if (kDown & KEY_B){
			randNUM = rand() % 20;
			if (randNUM != 0){
				appleX = 20 * randNUM;
			}
			else{
				appleX = 0;
			}
			randNUM = rand() % 12;
			if (randNUM != 0){
				appleY = 20 * randNUM;
			}
			else{
				appleY = 0;
			}
			appleSpawned = true;
		}
		// Debug command to spawn more segments 
		// Or fix apple issues
		*/

		if (kDown & KEY_DDOWN){
			if (currentdir.dir != up){
				currentdir.dir = down;
				blocks[0].direction.dir = down;
			}
		}
		if (kDown & KEY_DUP){
			if (currentdir.dir != down){
				currentdir.dir = up;
				blocks[0].direction.dir = up;
			}
		}
		if (kDown & KEY_DLEFT){
			if (currentdir.dir != right){
				currentdir.dir = left;
				blocks[0].direction.dir = left;
			}
		}
		if (kDown & KEY_DRIGHT){
			if (currentdir.dir != left){
				currentdir.dir = right;
				blocks[0].direction.dir = right;
			}
		}

	
		printf("\x1b[1;1HSnook 3DS");
		printf("\x1b[2;1HCPU:     %6.2f%%\x1b[K", C3D_GetProcessingTime()*6.0f);
		printf("\x1b[3;1HGPU:     %6.2f%%\x1b[K", C3D_GetDrawingTime()*6.0f);
		printf("\x1b[4;1HCmdBuf:  %6.2f%%\x1b[K", C3D_GetCmdBufUsage()*100.0f);
		printf("\x1b[5;1HApple X: %d---", appleX); // 3 Symboles  are appended to the end as non-overwritten text will remain on screen
		printf("\x1b[6;1HApple Y: %d---", appleY); // Minus overwrites it preventing numbers such as 80 appearing as 800 from the extra
		printf("\x1b[7;1HHead X: %d---", blocks[0].position.pointX); // 0 left from 100+
		printf("\x1b[8;1HHead Y: %d---", blocks[0].position.pointY);
		printf("\x1b[15;1HMovement: DPad");
		printf("\x1b[16;1HExit: Start");
		//printf("\x1b[17;1HRespawn Apple (incase of issues): B"); // No longer needed
		printf("\x1b[30;1HScore: %d", score);
		

		// Render the scene
		// Render's the snake
		if (allowedLoop == 0 && notDead){

			switch(currentdir.dir){
			case right:
				for (int x = block_count; x>1; x--){
					blocks[x-1] = blocks[x-2];
				}
				blocks[0].position.pointX += 20;
				break;

			case left:
				for (int x = block_count; x>1; x--){
					blocks[x-1] = blocks[x-2];
				}
				blocks[0].position.pointX -= 20;
				break;

			case up:
				for (int x = block_count; x>1; x--){
					blocks[x-1] = blocks[x-2];
				}
				blocks[0].position.pointY -= 20;
				break;

			case down:
				for (int x = block_count; x>1; x--){
					blocks[x-1] = blocks[x-2];
				}
				blocks[0].position.pointY += 20;
				break;

			default:
				printf("\x1d[1;1HERROR");
				break;
			}

			//loop back
			switch (blocks[0].position.pointX){
					case leftX:
						blocks[0].position.pointX = 380;
						break;
					case rightX:
						blocks[0].position.pointX = 0;
						break;
			}
			switch (blocks[0].position.pointY){
					case topY:
						blocks[0].position.pointY = 220;
						break;
					case bottomY:
						blocks[0].position.pointY = 0;
						break;
			}
			

			//Apple Generator
			if (!appleSpawned){
				randNUM = rand() % 20;
				if (randNUM != 0){
					appleX = 20 * randNUM;
				}
				else{
					appleX = 0;
				}
				randNUM = rand() % 12;
				if (randNUM != 0){
					appleY = 20 * randNUM;
				}
				else{
					appleY = 0;
				}
				appleSpawned = true;
			}

			//Detect if you are on top of an Apple
			if (blocks[0].position.pointX == appleX && blocks[0].position.pointY == appleY){
				switch (blocks[block_count-1].direction.dir){
				case up:
					blocks[block_count] = blocks[block_count-1];
					blocks[block_count].position.pointY += 20;
					block_count++;
					break;
				case down:
					blocks[block_count] = blocks[block_count-1];
					blocks[block_count].position.pointY -= 20;
					block_count++;
					break;
				case left:
					blocks[block_count] = blocks[block_count-1];
					blocks[block_count].position.pointX += 20;
					block_count++;
					break;
				case right:
					blocks[block_count] = blocks[block_count-1];
					blocks[block_count].position.pointX -= 20;
					block_count++;
					break;
				}
				appleSpawned=false;
				score += 10 * block_count-5;
			}

			for (int x  = 1; x<block_count; x++){
				if (blocks[x].position.pointX == blocks[0].position.pointX && blocks[x].position.pointY == blocks[0].position.pointY){
					notDead = false;
				}
			}


			//Detect Dead
			//if (blocks[0].position.pointX == leftX || blocks[0].position.pointX == rightX){
			//	notDead = false;
			//}
			//if (blocks[0].position.pointY == topY || blocks[0].position.pointY == bottomY){
			//	notDead = false;
			//}

			C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
			C2D_TargetClear(top, clrBlack);
			C2D_SceneBegin(top);

			//Render Snake
			for (int x = 0; x<block_count; x++){
				if (x == 0){
					C2D_DrawRectangle(blocks[x].position.pointX, blocks[x].position.pointY, 0, PLAYERBLOCK_WIDTH, PLAYERBLOCK_HEIGHT, clrGreen, clrGreen, clrGreen, clrGreen);
				}
				else{
					C2D_DrawRectangle(blocks[x].position.pointX, blocks[x].position.pointY, 0, PLAYERBLOCK_WIDTH, PLAYERBLOCK_HEIGHT, clrWhite, clrWhite, clrWhite, clrWhite);
				}
			}
			//Render Apple
			if (appleSpawned){
					C2D_DrawRectangle(appleX+10,appleY+10,0,10,10,clrRed,clrRed,clrRed,clrRed);
			}
		
			C3D_FrameEnd(0);
			allowedLoop = ILLITERATION_SKIP;
			
	
		}
		else if (!notDead){
			printf("\x1b[21;10H You are dead.");
			printf("\x1b[22;1H Press Start to exit");
		}
		else{
			allowedLoop--;
		}
	}

	// Deinit libs
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	return 0;
}
