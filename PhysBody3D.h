#ifndef __PhysBody3D_H__
#define __PhysBody3D_H__

#include "p2List.h"

class btRigidBody;
class Module;

// =================================================
struct PhysBody3D
{
	friend class ModulePhysics3D;
public:
	PhysBody3D(btRigidBody* body);

	~PhysBody3D();

	void Push(float x, float y, float z);
	void GetTransform(float* matrix) const;
	void SetTransform(const float* matrix) const;
	void SetPos(float x, float y, float z);
	bool IsSensor() { return is_sensor; };
	void isDraw();

protected:
	btRigidBody* body = nullptr;

public:
	p2List<Module*> collision_listeners;
	bool is_sensor;
	bool isRender = true;
};

struct PhysSensor3D : public PhysBody3D
{

public:
	enum class Type
	{
		FINISH,
		LAP,
		DEAD,
		RESTART
	};

	PhysSensor3D(btRigidBody* body, Type _type);
	~PhysSensor3D();

	void SetAsSensor();

public:
	Type type;
};

#endif // __PhysBody3D_H__