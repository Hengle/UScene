#include <UScene/core/core>
#include <UScene/tool/Intersector/IntersectorVisibility.h>
#include <UScene/tool/Accel/BVH.h>

#include <fstream>
#include <iostream>

using namespace std;
using namespace Ubpa;

int main() {
	constexpr size_t width = 400;
	constexpr size_t height = 200;

	Scene scene("scene");

	auto [sobj0, camera] = scene.CreateSObj<Cmpt::Camera>("sobj0");
	auto [sobj1, geo1] = scene.CreateSObj<Cmpt::Geometry>("sobj1");
	auto [sobj2, geo2] = scene.CreateSObj<Cmpt::Geometry>("sobj2");
	auto [sobj3, geo3] = scene.CreateSObj<Cmpt::Geometry>("sobj3");

	geo1->SetPrimitive(new Sphere);
	geo2->SetPrimitive(new Square);
	geo3->SetPrimitive(new TriMesh(TriMesh::Type::Cube));
	sobj0->Get<Cmpt::Position>()->value = pointf3{ 0,0,8 };
	sobj1->Get<Cmpt::Position>()->value = pointf3{ -4,0,0 };
	sobj2->Get<Cmpt::Rotation>()->value = quatf{ vecf3{1,0,0}, to_radian(45.f) };
	sobj3->Get<Cmpt::Position>()->value = pointf3{ 4,0,0 };
	sobj3->Get<Cmpt::Scale>()->value = scalef3{ 1,2,1 };
	sobj3->Get<Cmpt::Rotation>()->value = quatf{ vecf3{1,2,1}.normalize(), to_radian(45.f) };
	camera->ar = width / static_cast<float>(height);
	camera->fov = to_radian(60.f);

	// ===========

	scene.Update(true); // update Cmpt::Transform, Cmpt::L2W

	auto l2w = sobj0->Get<Cmpt::L2W>()->value;
	auto cameraCoordSystem = camera->GenCoordinateSystem(l2w);
	
	BVH bvh(&scene);
	IntersectorVisibility intersector;

	Image img(width, height, 1);
	for (size_t j = 0; j < height; j++) {
		float v = j / static_cast<float>(height);
		for (size_t i = 0; i < width; i++) {
			float u = i / static_cast<float>(width);
			rayf3 r = camera->GenRay(u, v, cameraCoordSystem);
			bool visibility = intersector.Visit(&bvh, r);
			img.At(i, j, 0) = static_cast<float>(visibility);
		}
	}
	
	img.Save("../data/test_05_visibility_out.png");

	return 0;
}
