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

}

update_status ModuleMap::Update(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModuleMap::CleanUp()
{

}