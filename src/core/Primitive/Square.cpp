#pragma once

#include <UScene/core/Primitive/Square.h>

#include "detail/dynamic_reflection/Square.inl"

using namespace Ubpa;

void Square::OnRegist() {
	detail::dynamic_reflection::ReflRegist_Square();
}
