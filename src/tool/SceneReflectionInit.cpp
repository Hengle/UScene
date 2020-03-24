#include <UScene/tool/SceneReflectionInit.h>

#include <UScene/core/core>

#include <UDP/Reflection/Reflection.h>

using namespace Ubpa;

void Ubpa::SceneReflectionInit() {
	Scene s("tmp");
	auto [sobj] = s.CreateSObj<>("tmp");

	vtable_of<SObj>::regist(sobj);

	Reflection<SObj>::Instance()
		.SetName("Ubpa::SObj")
		.Regist(&SObj::name, "name")
		.Regist(&SObj::children, "children");

	Reflection<Scene>::Instance()
		.SetName("Ubpa::Scene")
		.Regist(&Scene::root, "root")
		.RegistConstructor();

	// =================== Component ===================

	Reflection<Component>::Instance()
		.SetName("Ubpa::Component");

	Reflection<Cmpt::Camera>::Instance()
		.SetName("Ubpa::Cmpt::Camera")
		.Regist(&Cmpt::Camera::ar, "ar")
		.Regist(&Cmpt::Camera::fov, "fov")
		.RegistConstructor([](SObj* sobj) {
		auto [cmpt] = sobj->Attach<Cmpt::Camera>();
		return cmpt;
			});

	Reflection<Cmpt::Geometry>::Instance()
		.SetName("Ubpa::Cmpt::Geometry")
		.Regist(&Cmpt::Geometry::primitive, "primitive")
		.RegistConstructor([](SObj* sobj) {
		auto [cmpt] = sobj->Attach<Cmpt::Geometry>();
		return cmpt;
			});

	Reflection<Cmpt::Light>::Instance()
		.SetName("Ubpa::Cmpt::Light")
		.Regist(&Cmpt::Light::light, "light")
		.RegistConstructor([](SObj* sobj) {
		auto [cmpt] = sobj->Attach<Cmpt::Light>();
		return cmpt;
			});

	Reflection<Cmpt::Material>::Instance()
		.SetName("Ubpa::Cmpt::Material")
		.Regist(&Cmpt::Material::material, "material")
		.RegistConstructor([](SObj* sobj) {
		auto [cmpt] = sobj->Attach<Cmpt::Material>();
		return cmpt;
			});

	Reflection<Cmpt::Transform>::Instance()
		.SetName("Ubpa::Cmpt::Transform")
		.Regist(&Cmpt::Transform::pos, "pos")
		.Regist(&Cmpt::Transform::scale, "scale")
		.Regist(&Cmpt::Transform::rot, "rot")
		.RegistConstructor([](SObj* sobj) {
		auto [cmpt] = sobj->Attach<Cmpt::Transform>();
		return cmpt;
			});

	// =================== Light ===================

	Reflection<Light>::Instance()
		.SetName("Ubpa::Light")
		.RegistConstructor();

	Reflection<PointLight>::Instance()
		.SetName("Ubpa::PointLight")
		.Regist(&PointLight::intensity, "intensity")
		.Regist(&PointLight::color, "color")
		.RegistConstructor();

	// =================== Primitive ===================

	Reflection<Primitive>::Instance()
		.SetName("Ubpa::Primitive")
		.RegistConstructor();

	Reflection<Sphere>::Instance()
		.SetName("Ubpa::Sphere")
		.RegistConstructor();

	// =================== Material ===================

	Reflection<Material>::Instance()
		.SetName("Ubpa::Material");

	Reflection<Diffuse>::Instance()
		.SetName("Ubpa::Diffuse")
		.Regist(&Diffuse::albedo, "albedo")
		.RegistConstructor();
}
