#pragma once

#include "data/entity.h"
#include "lmath.h"
#include "bullet/src/BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h"

namespace VI
{

struct RigidBody;

struct Walker : public ComponentType<Walker>
{
	Vec2 dir;
	r32 height,
		support_height,
		radius,
		mass,
		speed,
		max_speed,
		rotation,
		target_rotation,
		rotation_speed,
		air_control_accel,
		last_supported_speed,
		fall_damage_threshold,
		accel1,
		accel2,
		accel_threshold,
		deceleration,
		net_speed;
	Ref<RigidBody> support;
	b8 auto_rotate;
	b8 enabled;
	Walker(r32 = 0.0f);
	void awake();
	b8 slide(Vec2*, const Vec3&);

	Vec3 base_pos();

	void update(const Update&);
};

}