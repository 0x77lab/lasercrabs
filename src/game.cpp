#include "types.h"
#include "vi_assert.h"

#include "render/view.h"
#include "render/armature.h"
#include "render/render.h"
#include "data/array.h"
#include "data/entity.h"
#include "data/components.h"
#include "game/awk.h"
#include "game/player.h"
#include "data/mesh.h"
#include "physics.h"
#include "game/entities.h"
#include "game/player.h"
#include "game/walker.h"

void game_loop(RenderSync::Swapper* swapper)
{
	Physics::btWorld->setGravity(btVector3(0, -9.8f, 0));

	Loader::swapper = swapper;

	StaticGeom* a = World::create<StaticGeom>(Asset::Model::city3);

	Sentinel* sentinel = World::create<Sentinel>(Vec3(0, -1.5f, -9), Quat::identity);

	Player* player = World::create<Player>();
	player->get<Transform>()->pos = Vec3(2, -1.5f, -7);

	//Noclip* noclip = World::create<Noclip>();
	//noclip->get<Transform>()->pos = Vec3(2, -1.5f, -7);

	RenderParams render_params;

	SyncData* sync = swapper->get();

	Update u;

	while (!sync->quit)
	{
		u.input = &sync->input;
		u.time = sync->time;

		// Update
		{
			Physics::update(u);
			for (auto i = World::components<Walker>().iterator(); !i.is_last(); i.next())
				i.item()->update(u);
			for (auto i = World::components<Awk>().iterator(); !i.is_last(); i.next())
				i.item()->update(u);
			for (auto i = World::components<PlayerControl>().iterator(); !i.is_last(); i.next())
				i.item()->update(u);
			for (auto i = World::components<NoclipControl>().iterator(); !i.is_last(); i.next())
				i.item()->update(u);
			for (auto i = World::components<Armature>().iterator(); !i.is_last(); i.next())
				i.item()->update(u);
		}

		render_params.sync = sync;

		render_params.projection = Camera::main.projection;
		render_params.view = Camera::main.view;

		sync->write(RenderOp_Clear);
		
		sync->write<GLbitfield>(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw
		{
			for (auto i = World::components<View>().iterator(); !i.is_last(); i.next())
				i.item()->draw(&render_params);
			for (auto i = World::components<Armature>().iterator(); !i.is_last(); i.next())
				i.item()->draw(&render_params);
		}

		sync = swapper->swap<SwapType_Write>();
		sync->queue.length = 0;
	}
}