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

	void CreateRectangle(vec3 position, vec4 rotation, vec3 size, Color s_color, float mass = 0.0f);
	void CreateSensor(vec3 position, vec4 rotation, vec3 size, Color c);

private:
	p2List<Primitive*> objects;
	float i = 0;

};
