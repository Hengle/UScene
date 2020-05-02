#pragma once

#include "Light.h"

#include <UGM/rgb.h>
#include <UGM/point.h>

namespace Ubpa {
	class Texture2D;

	// lambertian
	// AreaLight's radiance = intensity * color * texture(u, v)
	struct AreaLight : Light {
		[[range("0,")]]
		float intensity;
		rgbf color;
		Texture2D* texture;

		rgbf RadianceFactor() const noexcept { return intensity * color; }
		rgbf Radiance(const pointf2& uv) const noexcept;

		AreaLight(float intensity = 1.f, const rgbf& color = rgbf{ 1.f }, Texture2D* texture = nullptr)
			: intensity{ intensity }, color{ color }, texture{ texture }{}

		static void OnRegister();
	};
}
