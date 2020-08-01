#pragma once

#include <UECS/World.h>

namespace Ubpa {
	namespace UScene {
		class WorldToLocalSystem : public UECS::System {
		public:
			using System::System;

			static constexpr char SystemFuncName[] = "WorldToLocalSystem";

			virtual void OnUpdate(UECS::Schedule& schedule) override;
		};
	}
}
