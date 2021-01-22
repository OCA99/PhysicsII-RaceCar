#pragma once
#include "Module.h"
#include "Globals.h"
#include "ModulePhysics3D.h"

struct PhysBody3D;

#define OBJECTS 20


class ModuleMap : public Module
{
public:

	ModuleMap(Application* app, bool start_enabled = true);
	~ModuleMap();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void CreateRectangles();
	void CountDownSetPos(vec3 pos, float dt);
	void CreateCountDown();
	void ResetCountDown();
	void NextLevel();
	int GetLevel();
	void Reset(float dt);

	Primitive* CreateRectangle(vec3 position, vec4 rotation, vec3 size, Color s_color, float mass = 0.0f,bool render = true, bool countDown = false);
	PhysSensor3D* CreateSensor(vec3 position, vec4 rotation, vec3 size,PhysSensor3D::Type type, float mass = 0.0f);

	Primitive* oneObj[OBJECTS] = { nullptr };
	Primitive* twoObj[OBJECTS] = { nullptr };
	Primitive* threeObj[OBJECTS] = { nullptr };
	vec3* origin = new vec3(0, 1.5, 10);

private:

	//Countdown Checkers
	float counter = 0;
	bool one = false;
	bool two = false;
	bool three = false;


	p2List<Primitive*> objects;
	int level = 0;
};
