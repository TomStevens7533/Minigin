#pragma once
struct point {
	float x;
	float y;
};
	
enum class EnemyType {
	Begin = 0,
	WORST,
	EGG,
	SPIKE,
	END = 4 
};
struct EnemySpawnInfo {
	int MaxInStage;
	int Score;
	int CurrentInStage = 0;
};
enum class Direction {
	NONE,
	LEFT,
	RIGHT,
	UP,
	DOWN
};