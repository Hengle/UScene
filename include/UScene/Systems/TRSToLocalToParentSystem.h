#pragma once

#include <UECS/World.h>

namespace Ubpa::UScene {
	class TRSToLocalToParentSystem : public UECS::System {
	public:
		using System::System;

		static constexpr char SystemFuncName[] = "TRSToLocalToParentSystem";

		virtual void OnUpdate(UECS::Schedule& schedule) override;
	};
}
