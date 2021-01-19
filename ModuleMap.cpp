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
	p2List_item<Primitive*>* item = objects.getFirst();
	while (item)
	{
		item->data->Render();
		item = item->next;
	}
	return UPDATE_CONTINUE;
}

void ModuleMap::NextLevel()
{
	level++;
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
	CreateRectangle({ 6,1,132.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Black);
	CreateRectangle({ 4,1,139.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ 0,1,140.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Black);
	CreateRectangle({ -2,1,140.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -5,1,140.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Black);
	CreateRectangle({ -7,1,140.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -9,1,140.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Black);
	CreateRectangle({ -13,1,140.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -16,1,140.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Black);
	CreateRectangle({ -19,1,140.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -23,1,140.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Black);
	CreateRectangle({ -25,1,140.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -27,1,138.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Black);
	CreateRectangle({ -30,1,135.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -35,1,133.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Black);
	CreateRectangle({ -38,1,130.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -38,1,125.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Black);
	CreateRectangle({ 7,1, -3.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ 6,1,-8.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Black);
	CreateRectangle({ 4,1,-10.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -2,1,-13.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Black);
	CreateRectangle({ -5,1,-16.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -9,1,-20.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Black);
	CreateRectangle({ -14,1,-20.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -17,1,-20.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Black);
	CreateRectangle({ -19,1,-20.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -22,1,-20.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Black);
	CreateRectangle({ -25,1,-20.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -28,1,-18.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Black);
	CreateRectangle({ -35,1,-16.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -37,1,-8.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Black);
	CreateRectangle({ -38,1,-2.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);

	//Right
	//Walls
	CreateRectangle({ -7,1,60.0f }, { 0,0,0,1 }, { 1,3.f,120.0f }, Red);
	CreateRectangle({ -24,1,60.0f }, { 0,0,0,1 }, { 1,3.f,120.0f }, Red);
	//Posts
	CreateRectangle({ -7,1,122.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Black);
	CreateRectangle({ -12,1,125.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -16,1,125.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Black);
	CreateRectangle({ -20,1,125.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -24,1,123.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Black);
	CreateRectangle({ -7,1, -3.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -12,1,-6.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Black);
	CreateRectangle({ -20,1,-6.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Black);
	CreateRectangle({ -24,1, -2.0f }, { 0,0,0,1 }, { 1,3.f,1 }, Red);

	//Ramps
	CreateRectangle({ 0,0,60.0f }, { 75,1, 0, 0 }, { 14,10,0.5f }, Red);
	CreateRectangle({ -31,0,80.0f }, { 285,1, 0, 0 }, { 14,10,0.5f }, Red);

	CreateSensor({ -30,0,80.0f }, { 0,1, 0, 0 }, { 14,10,0.5f }, PhysSensor3D::Type::LAP);
	CreateSensor({ 0,0,60.0f }, { 0,1, 0, 0 }, { 14,10,0.5f }, PhysSensor3D::Type::FINISH);

	//DEAD SENSOR
	CreateSensor({ 15,2,50.0f }, { 0,0, 0, 1 }, { 15,1,200 }, PhysSensor3D::Type::DEAD);/*LEFT*/
	CreateSensor({ -15,2,60.0f }, { 0,0, 0, 1 }, { 15,1,128 }, PhysSensor3D::Type::DEAD);/*MIDDLE*/
	CreateSensor({ -46,2,50.0f }, { 0,0, 0, 1 }, { 15,1,200 }, PhysSensor3D::Type::DEAD);/*RIGHT*/
	CreateSensor({ 0,2,144.0f }, { 0,0, 0, 1 }, { 80,1,10 }, PhysSensor3D::Type::DEAD);/*TOP*/
	CreateSensor({ 0,2,-23.0f }, { 0,0, 0, 1 }, { 80,1,10 }, PhysSensor3D::Type::DEAD);/*BOTTOM*/



	//------------------------END OF STAGE 1----------------------

	//---------------------STAGE 2------------------------------0,0,0= 100,0, 0
	CreateRectangle({ 100,0,10 }, { 60,1, 0, 0 }, { 14,17,0.5f }, Red);
	CreateRectangle({ 100,4.3f,20 }, { 0,0, 0, 1 }, { 14,0.3f,5 }, Red);
	CreateRectangle({ 100,4.3f,32 }, { 0,0, 0, 1 }, { 3,0.3f,20 }, Red);
	CreateRectangle({ 100,4.3f,46 }, { 0,0, 0, 1 }, { 14,0.3f,9 }, Red);
	CreateRectangle({ 117,4.3f,46 }, { 0,0, 1, 1 }, { 20,0.3f,3 }, Red);
	CreateRectangle({ 127,4.3f,46 }, { 0,0, 1, 1 }, { 5,0.3f,14 }, Red);
	CreateRectangle({ 127,10.3f,62}, { 60,1, 0, 0 }, { 3,25,0.3f }, Red);

	CreateSensor({ 110,0,80.0f }, { 0,0, 0, 1 }, { 60,1,128 }, PhysSensor3D::Type::DEAD);/*MIDDLE*/


	//------------------------END OF STAGE 2----------------------

}

int ModuleMap::GetLevel()
{
	return level;
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

PhysSensor3D* ModuleMap::CreateSensor(vec3 position, vec4 rotation, vec3 size, PhysSensor3D::Type type, float mass)
{
	Cube* object = new Cube();

	object->SetPos(position.x, position.y, position.z);
	object->size = size;
	object->SetRotation(rotation.x, { rotation.y, rotation.z, rotation.w });
	//objects.add(object);
	return App->physics->AddSensor(*object, type);
}
