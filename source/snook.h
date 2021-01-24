#include <citro2d.h>

#include <3ds.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Struct Definition
// Struct to define direction

typedef struct rotateStruct{
	enum direction{
		up,
		down,
		left,
		right
	} dir;
} rotation;

//Basic point struct

typedef struct pointStruct{
	int pointX;
	int pointY;
} point;

//Basic block/apple struct

struct userData{
	point position;
	rotation direction;
};

//Generic Variables

// Time for Psudou Random Number Generator
time_t t;

// Array of snake's blocks
struct userData blocks[255];
//Global Direction
rotation currentdir;

//default snake length
int block_count = 6;
//Loop Counter
int allowedLoop = 3;
//Apple POS
int appleX = 0;
int appleY = 0;
int randNUM; // Used to store random numbers to make sure no divisons by 0 occur
int score; // Used to store score

bool appleSpawned = false; // Bool to determine if the apple should be rendered
bool notDead = true; // R u dead?

PrintConsole topScreen, bottomScreen; // Unnessasary, should be removed in the future