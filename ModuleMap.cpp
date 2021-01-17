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
	objects.clear();
	return true;
}

void ModuleMap::CreateRectangles()
{
	//Left
	//---------------------STAGE 1------------------------------
	// Walls
	CreateRectangle({ 7,1,60.0f }, { 0,0,0,1 }, { 1,3.0f,120.0f }, Red);
	CreateRectangle({ -38,1,60.0f }, { 0,0,0,1 }, { 1,3.0f,120.0f }, Red);

	//Posts
	CreateRectangle({ 7,1,125.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ 6,1,132.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ 4,1,139.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ 0,1,140.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -2,1,140.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -5,1,140.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -7,1,140.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -9,1,140.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -13,1,140.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -16,1,140.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -19,1,140.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -23,1,140.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -25,1,140.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -27,1,138.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -30,1,135.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -35,1,133.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -38,1,130.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -38,1,125.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ 7,1, -3.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ 6,1,-8.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ 4,1,-10.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -2,1,-13.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -5,1,-16.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -9,1,-20.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -14,1,-20.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -17,1,-20.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -19,1,-20.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -22,1,-20.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -25,1,-20.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -28,1,-18.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -35,1,-16.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -37,1,-8.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -38,1,-2.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);

	//Right
	//Walls
	CreateRectangle({ -7,1,60.0f }, { 0,0,0,1 }, { 1,3.f,120.0f }, Red);
	CreateRectangle({ -24,1,60.0f }, { 0,0,0,1 }, { 1,3.f,120.0f }, Red);
	//Posts
	CreateRectangle({ -7,1,122.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -12,1,125.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -16,1,125.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -20,1,125.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -24,1,123.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -7,1, -3.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -12,1,-6.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -20,1,-6.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -24,1, -2.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);

	//Ramps
	CreateRectangle({ 0,0,60.0f }, { 60,1, 0, 0 }, { 14,10,0.5f }, Red);
	CreateRectangle({ -30,0,80.0f }, { 120,1, 0, 0}, { 14,10,0.5f }, Red);

	//------------------------END OF STAGE 1----------------------

}

PhysBody3D* ModuleMap::CreateRectangle(vec3 position, vec4 rotation, vec3 size, Color c, float mass)
{
	Cube* object = new Cube();

	object->SetPos(position.x, position.y, position.z);
	object->size = size;
	object->color = c;
	object->SetRotation(rotation.x, { rotation.y, rotation.z, rotation.w });

	objects.add(object);
	return App->physics->AddBody(*object, mass);
}
