#include <UScene/core/Cmpt/Material.h>

#include <UScene/core/SObj.h>

#include "detail/dynamic_reflection/Material.inl"

using namespace Ubpa;
using namespace std;

void Cmpt::Material::OnRegist() {
	detail::dynamic_reflection::ReflRegist_Material();
}

Cmpt::Material::Material() = default;
Cmpt::Material::~Material() {
	delete material;
}

Cmpt::Material::Material(Material&& material) noexcept
	: material{ material.material }
{
	material.material.val = nullptr;
}

void Cmpt::Material::SetMaterial(Ubpa::Material* material) {
	delete this->material;
	this->material.val = material;
}