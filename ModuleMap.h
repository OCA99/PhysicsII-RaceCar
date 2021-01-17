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

	PhysBody3D* CreateRectangle(vec3 position, vec4 rotation, vec3 size, Color s_color, float mass);


private:
	p2List<Primitive*> objects;
};
