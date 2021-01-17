#pragma once
#include "Module.h"
#include "Globals.h"

struct PhysBody3D;
struct PhysMotor3D;
struct PhysSensor3D;

class ModuleMap : public Module
{
public:

	ModuleMap(Application* app, bool start_enabled = true);
	~ModuleMap();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

private:

};
