#pragma once
#include "Module.h"
#include "Globals.h"

struct PhysBody3D;

class ModuleMap : public Module
{
public:

	ModuleMap(Application* app, bool start_enabled = true);
	~ModuleMap();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void CreateRectangles();
	void CreateCountDown(vec3 pos, float dt);
	void NextLevel();
	int GetLevel();

	PhysBody3D* CreateRectangle(vec3 position, vec4 rotation, vec3 size, Color s_color, float mass = 0.0f);
	PhysSensor3D* CreateSensor(vec3 position, vec4 rotation, vec3 size,PhysSensor3D::Type type, float mass = 0.0f);


private:
	//Countdown Checkers
	float counter = 0;
	bool one = false;
	bool two = false;
	bool three = false;


	p2List<Primitive*> objects;
	int level = 1;
};
