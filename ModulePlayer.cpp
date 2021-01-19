#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	VehicleInfo car;

	// Car properties ----------------------------------------
	car.chassis_size.Set(2, 1, 4);
	car.chassis_offset.Set(0, 1.5, 0);
	car.mass = 300.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.6f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x * 0.5f;
	float half_length = car.chassis_size.z * 0.5f;

	vec3 direction(0, -1, 0);
	vec3 axis(-1, 0, 0);

	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(0, 1.5, 10);

	VehicleInfo tro;
	tro.chassis_size.Set(2, 1, 2);
	tro.chassis_offset.Set(0, 1.5, 0);
	tro.mass = 200.0f;
	tro.suspensionStiffness = 15.88f;
	tro.suspensionCompression = 0.83f;
	tro.suspensionDamping = 0.88f;
	tro.maxSuspensionTravelCm = 1000.0f;
	tro.frictionSlip = 50.5;
	tro.maxSuspensionForce = 6000.0f;

	connection_height = 1.8f;

	half_width = tro.chassis_size.x * 0.5f;
	half_length = tro.chassis_size.z * 0.5f;

	tro.num_wheels = 2;
	tro.wheels = new Wheel[2];

	tro.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, 0.0f);
	tro.wheels[0].direction = direction;
	tro.wheels[0].axis = axis;
	tro.wheels[0].suspensionRestLength = suspensionRestLength;
	tro.wheels[0].radius = wheel_radius;
	tro.wheels[0].width = wheel_width;
	tro.wheels[0].front = true;
	tro.wheels[0].drive = true;
	tro.wheels[0].brake = false;
	tro.wheels[0].steering = true;

	tro.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, 0.0f);
	tro.wheels[1].direction = direction;
	tro.wheels[1].axis = axis;
	tro.wheels[1].suspensionRestLength = suspensionRestLength;
	tro.wheels[1].radius = wheel_radius;
	tro.wheels[1].width = wheel_width;
	tro.wheels[1].front = true;
	tro.wheels[1].drive = true;
	tro.wheels[1].brake = false;
	tro.wheels[1].steering = true;

	trolley = App->physics->AddVehicle(tro);
	trolley->SetPos(0, 1, 8);

	App->physics->AddConstraintP2P(*vehicle, *trolley, vec3(0, -0.6f, -1.6f), vec3(0, 0, 2));

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

void ModulePlayer::LevelSpawn1()
{
	mat4x4 carMatrix;
	vehicle->GetTransform(&carMatrix);

	carMatrix.rotate(0, { 0, 1, 0 });
	carMatrix.translate(0, 2, 10);

	vehicle->SetTransform(&carMatrix.M[0]);

	vehicle->vehicle->getRigidBody()->setLinearVelocity({ 0, 0, 0 });
	vehicle->vehicle->getRigidBody()->setAngularVelocity({ 0, 0, 0 });

	trolley->GetTransform(&carMatrix);

	carMatrix.rotate(0, { 0, 1, 0 });
	carMatrix.translate(0, 1, 8);

	trolley->SetTransform(&carMatrix.M[0]);

	trolley->vehicle->getRigidBody()->setLinearVelocity({ 0, 0, 0 });
	trolley->vehicle->getRigidBody()->setAngularVelocity({ 0, 0, 0 });

	//trolley2->GetTransform(&carMatrix);

	//carMatrix.rotate(0, { 0, 1, 0 });
	//carMatrix.translate(0, 1, 6);

	//trolley2->SetTransform(&carMatrix.M[0]);

	//trolley2->vehicle->getRigidBody()->setLinearVelocity({ 0, 0, 0 });
	//trolley2->vehicle->getRigidBody()->setAngularVelocity({ 0, 0, 0 });
}

void ModulePlayer::LevelSpawn2()
{
	mat4x4 carMatrix;
	vehicle->GetTransform(&carMatrix);

	carMatrix.rotate(0, { 0, 1, 0 });
	carMatrix.translate(100, 2, -10);

	vehicle->SetTransform(&carMatrix.M[0]);

	vehicle->vehicle->getRigidBody()->setLinearVelocity({ 0, 0, 0 });
	vehicle->vehicle->getRigidBody()->setAngularVelocity({ 0, 0, 0 });

	trolley->GetTransform(&carMatrix);

	carMatrix.rotate(0, { 0, 1, 0 });
	carMatrix.translate(100, 1, -8);

	trolley->SetTransform(&carMatrix.M[0]);

	trolley->vehicle->getRigidBody()->setLinearVelocity({ 0, 0, 0 });
	trolley->vehicle->getRigidBody()->setAngularVelocity({ 0, 0, 0 });

	//trolley2->GetTransform(&carMatrix);

	//carMatrix.rotate(0, { 0, 1, 0 });
	//carMatrix.translate(0, 1, 6);

	//trolley2->SetTransform(&carMatrix.M[0]);

	//trolley2->vehicle->getRigidBody()->setLinearVelocity({ 0, 0, 0 });
	//trolley2->vehicle->getRigidBody()->setAngularVelocity({ 0, 0, 0 });
}
// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN)
	{
		LevelSpawn2();
	}
	turn = acceleration = brake = 0.0f;
	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		laps++;
	}
	if (canMove > 0)
	{
		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		{
			if (vehicle->GetKmh() < -1.0f)
			{
				brake = BRAKE_POWER;
			}
			else
			{
				acceleration = MAX_ACCELERATION;
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		{
			if (turn < TURN_DEGREES)
				turn += TURN_DEGREES;
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			if (turn > -TURN_DEGREES)
				turn -= TURN_DEGREES;
		}

		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		{
			if (vehicle->GetKmh() > 1.0f)
			{
				brake = BRAKE_POWER;
			}
			else
			{
				acceleration = -MAX_ACCELERATION;
			}
		}
	}


	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		LevelSpawn1();
	}

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->Render();
	trolley->Render();

	//trolley2->Render();

	char title[80];
	sprintf_s(title, "%.1f Km/h  Laps: %i Level: %d", vehicle->GetKmh(), this->laps,App->map->GetLevel());
	App->window->SetTitle(title);
	if ((int)counter == 3 && !one)
	{
		//Text ONE
		App->map->CreateRectangle({ 0,10,170.0f }, { 0,0,0,1 }, { 1,8.0f,1 }, White);
		App->map->CreateRectangle({ 0.8f,12,170.0f }, { 30,0,0,1 }, { 1,3.0f,1 }, White);
		if (boost)
		{
			for (int i = 0; i < 5000; ++i)
			{
				acceleration = MAX_ACCELERATION * 100000;
				vehicle->ApplyEngineForce(acceleration);
			}
		}
		canMove *= -1;
		one = true;

	}
	else if ((int)counter == 2 && !one && !two)
	{
		//Text TWO
		App->map->CreateRectangle({ -8,13,170.0f }, { 0,0,0,1 }, { 5,1,1 }, Green);
		App->map->CreateRectangle({ -10,12,170.0f }, { 90,0,0,1 }, { 3,1,1 }, Green);
		App->map->CreateRectangle({ -8,10,170.0f }, { 0,0,0,1 }, { 5,1,1 }, Green);
		App->map->CreateRectangle({ -6,9,170.0f }, { 90,0,0,1 }, { 3,1,1 }, Green);
		App->map->CreateRectangle({ -8,7,170.0f }, { 0,0,0,1 }, { 5,1,1 }, Green);
		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		{
			boost = true;
		}
		two = true;
	}
	else if ((int)counter == 1 && !one && !three)
	{
		//Text THREE
		App->map->CreateRectangle({ -18,13,170.0f }, { 0,0,0,1 }, { 5,1,1 }, Red);
		App->map->CreateRectangle({ -20,12,170.0f }, { 90,0,0,1 }, { 3,1,1 }, Red);
		App->map->CreateRectangle({ -18,10,170.0f }, { 0,0,0,1 }, { 5,1,1 }, Red);
		App->map->CreateRectangle({ -20,9,170.0f }, { 90,0,0,1 }, { 3,1,1 }, Red);
		App->map->CreateRectangle({ -18,7,170.0f }, { 0,0,0,1 }, { 5,1,1 }, Red);
		three = true;
	}
	else if (!one) counter += dt;

	switch (laps)
	{
	case 1:
	{


		break;
	}
	case 2:
	{


		break;
	}
	case 3:
	{

		switch (App->map->GetLevel())
		{
		case 1:
		{
			LevelSpawn2();

			break;
		}
		case 2:
		{
			LevelSpawn1();
			break;
		}
		default:
			break;
		}
		App->map->NextLevel();
		laps = 0;
		break;
	}
	default:
		break;
	}
	return UPDATE_CONTINUE;
}



