#pragma once

#include "../Component.h"

#include "../Light/Light.h"

#include <UDP/Basic/Read.h>

namespace Ubpa::Cmpt {
	class Light : public Component {
	public:
		Read<Light, Ubpa::Light*> light{ nullptr };

		void SetLight(Ubpa::Light* light) {
			delete this->light;
			this->light = light;
		}

		Light() = default;
		virtual ~Light() { delete light; }

		Light(Light&& light) noexcept : Component(light) {
			this->light = light.light;
			light.light = nullptr;
		}
	};
}
