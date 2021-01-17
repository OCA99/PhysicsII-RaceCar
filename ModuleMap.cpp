#include "Globals.h"
#include "Application.h"
#include "ModuleMap.h"
#include "Primitive.h"
#include "PhysBody3D.h"


ModuleMap::ModuleMap(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleMap::~ModuleMap()
{

}

bool ModuleMap::Start()
{
	bool ret = true;
	//Create Map
	CreateRectangles();

	return ret;
}

update_status ModuleMap::Update(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModuleMap::CleanUp()
{

	return true;
}

void ModuleMap::CreateRectangles()
{
	
	CreateRectangle({ 7,1,0 }, { 0,0,0,1 }, { 1,3.f,1 }, White, 500.0f);
}

PhysBody3D* ModuleMap::CreateRectangle(vec3 position, vec4 rotation, vec3 size, Color s_color, float mass)
{
	Cube* object = new Cube();

	object->SetPos(position.x, position.y, position.z);
	object->size = size;
	object->color = s_color;
	object->SetRotation(rotation.x, { rotation.y, rotation.z, rotation.w });

	objects.add(object);
	return App->physics->AddBody(*object, mass);
}
