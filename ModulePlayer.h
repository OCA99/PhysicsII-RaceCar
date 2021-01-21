#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;


#define MAX_ACCELERATION 3000.0f
#define TURN_DEGREES 20.0f * DEGTORAD
#define BRAKE_POWER 1000.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	void LevelSpawn1();
	void LevelSpawn2();
	void LevelSpawn3();
	void LevelSpawn4();
public:

	PhysVehicle3D* vehicle;
	PhysVehicle3D* trolley;
	PhysVehicle3D* trolley2;

	bool canMove = false;

	float turn;
	float acceleration;
	float brake;
	bool lap = false;
	int laps = 0; 
};