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

void ModulePlayer::SetPos(vec3 pos)
{
	vehicle->SetPos(pos.x,pos.y,pos.z);
	trolley->SetPos(pos.x, pos.y-0.5f, pos.z-2.0f);

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

	//SetPos({ 0,2,10 });

	vehicle->SetTransform(&carMatrix.M[0]);

	vehicle->vehicle->getRigidBody()->setLinearVelocity({ 0, 0, 0 });
	vehicle->vehicle->getRigidBody()->setAngularVelocity({ 0, 0, 0 });

	trolley->GetTransform(&carMatrix);

	carMatrix.rotate(0, { 0, 1, 0 });
	carMatrix.translate(0, 2, 6);

	trolley->SetTransform(&carMatrix.M[0]);

	trolley->vehicle->getRigidBody()->setLinearVelocity({ 0, 0, 0 });
	trolley->vehicle->getRigidBody()->setAngularVelocity({ 0, 0, 0 });
	
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
	carMatrix.translate(100, 2, -14);

	trolley->SetTransform(&carMatrix.M[0]);

	trolley->vehicle->getRigidBody()->setLinearVelocity({ 0, 0, 0 });
	trolley->vehicle->getRigidBody()->setAngularVelocity({ 0, 0, 0 });


	
}

void ModulePlayer::LevelSpawn3()
{
	mat4x4 carMatrix;
	vehicle->GetTransform(&carMatrix);

	carMatrix.rotate(0, { 0, 1, 0 });
	carMatrix.translate(-100, 2, -10);

	vehicle->SetTransform(&carMatrix.M[0]);

	vehicle->vehicle->getRigidBody()->setLinearVelocity({ 0, 0, 0 });
	vehicle->vehicle->getRigidBody()->setAngularVelocity({ 0, 0, 0 });

	trolley->GetTransform(&carMatrix);

	carMatrix.rotate(0, { 0, 1, 0 });
	carMatrix.translate(-100, 2, -14);

	trolley->SetTransform(&carMatrix.M[0]);

	trolley->vehicle->getRigidBody()->setLinearVelocity({ 0, 0, 0 });
	trolley->vehicle->getRigidBody()->setAngularVelocity({ 0, 0, 0 });


	
}

void ModulePlayer::LevelSpawn4()
{
	mat4x4 carMatrix;
	vehicle->GetTransform(&carMatrix);

	carMatrix.rotate(0, { 0, 1, 0 });
	carMatrix.translate(-3, 2, -110);

	vehicle->SetTransform(&carMatrix.M[0]);

	vehicle->vehicle->getRigidBody()->setLinearVelocity({ 0, 0, 0 });
	vehicle->vehicle->getRigidBody()->setAngularVelocity({ 0, 0, 0 });

	trolley->GetTransform(&carMatrix);

	carMatrix.rotate(0, { 0, 1, 0 });
	carMatrix.translate(-3, 2, -114);

	trolley->SetTransform(&carMatrix.M[0]);

	trolley->vehicle->getRigidBody()->setLinearVelocity({ 0, 0, 0 });
	trolley->vehicle->getRigidBody()->setAngularVelocity({ 0, 0, 0 });
}

void ModulePlayer::LevelSpawn5()
{
	mat4x4 carMatrix;
	vehicle->GetTransform(&carMatrix);

	carMatrix.rotate(0, { 0, 1, 0 });
	carMatrix.translate(100, 2, -110);

	vehicle->SetTransform(&carMatrix.M[0]);

	vehicle->vehicle->getRigidBody()->setLinearVelocity({ 0, 0, 0 });
	vehicle->vehicle->getRigidBody()->setAngularVelocity({ 0, 0, 0 });

	trolley->GetTransform(&carMatrix);

	carMatrix.rotate(0, { 0, 1, 0 });
	carMatrix.translate(100, 2, -114);

	trolley->SetTransform(&carMatrix.M[0]);

	trolley->vehicle->getRigidBody()->setLinearVelocity({ 0, 0, 0 });
	trolley->vehicle->getRigidBody()->setAngularVelocity({ 0, 0, 0 });
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	turn = acceleration = brake = 0.0f;
	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		laps = 3;
	}
	if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
	{
		App->audio->PlayFx(1, 0);
	}
	if (canMove)
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
		switch (App->map->GetLevel())
		{
		case 1:
		{
			LevelSpawn1();
			break;
		}
		case 2:
		{
			LevelSpawn2();
			break;
		}
		case 3:
		{
			LevelSpawn3();
			break;
		}
		case 4:
		{
			LevelSpawn4();
			break;
		}
		case 5:
		{
			LevelSpawn5();
			break;
		}
		
		default:
			break;
		}
	}

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->Render();
	trolley->Render();

	//trolley2->Render();

	char title[80];
	if (App->map->GetLevel() != 4 && App->map->GetLevel() != 5)
		sprintf_s(title, "%.1f Km/h  Laps: %i Level: %d Lifes: %d", vehicle->GetKmh(), this->laps, App->map->GetLevel(), lifes);
	else if (App->map->GetLevel() == 4)
		sprintf_s(title, "%.1f Km/h  Laps: %i Level: %d Lifes: %d HIT THE BOX OR PRESS P TO RESTART", vehicle->GetKmh(), this->laps, App->map->GetLevel(), lifes);
	else if (App->map->GetLevel() == 5)
		sprintf_s(title, "%.1f Km/h  Laps: %i Level: %d Lifes: %d HIT THE BOX OR PRESS P TO RESTART", vehicle->GetKmh(), this->laps, App->map->GetLevel(), lifes);
	App->window->SetTitle(title);
	//CHECKPOINTS
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
		App->map->NextLevel();
		App->map->ResetCountDown();
		App->audio->PlayFx(2, 0);
		switch (App->map->GetLevel())
		{
		case 1:
		{
			App->map->CountDownSetPos(vec3(0, 0, 110), dt);
			lifes = 3;
			break;
		}
		case 2:
		{
			LevelSpawn2();
			App->map->CountDownSetPos(vec3(100, 0, 110), dt);
			lifes = 3;
			break;
		}
		case 3:
		{
			LevelSpawn3();
			App->map->CountDownSetPos(vec3(-150, 0, 110), dt);
			lifes = 3;
			break;
		}
		case 4:
		{
			LevelSpawn4();
			canMove = true;
			lifes = 100;
			break;
		}
		case 5:
		{
			LevelSpawn5();
			canMove = true;
			lifes = 100;
			break;
		}
		default:
			break;
		}
		laps = 0;
		break;
	}
	default:
		break;
	}

	return UPDATE_CONTINUE;
}



