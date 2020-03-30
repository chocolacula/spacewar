#pragma once

struct Transform;

class ProjectileSubSystem
{
protected:
	static void LaunchProjectile(const Transform& transform, int tag);
};