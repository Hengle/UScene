#include <UScene/core/Scene.h>

#include <UScene/core/Cmpt/Transform.h>
#include <UScene/core/Cmpt/Geometry.h>
#include <UScene/core/Cmpt/Light.h>
#include <UScene/core/Cmpt/Material.h>
#include <UScene/core/Cmpt/Camera.h>

#include <UScene/core/Primitive/Sphere.h>
#include <UScene/core/Light/PointLight.h>
#include <UScene/core/Material/stdBRDF.h>

#include <iostream>

using namespace std;
using namespace Ubpa;

int main() {
	Scene scene("scene");

	auto [sobj0, camera] = scene.CreateSObj<Cmpt::Camera>("sobj0");
	auto [sobj1, geo, mat] = scene.CreateSObj<Cmpt::Geometry, Cmpt::Material>("sobj1");
	auto [sobj2, light] = scene.CreateSObj<Cmpt::Light>("sobj2");

	geo->SetPrimitive(new Sphere);
	mat->SetMaterial(new stdBRDF);
	light->SetLight(new PointLight{ 1.f, 1.f });

	return 0;
}
