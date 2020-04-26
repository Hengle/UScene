#pragma once

#include <UGM/bbox.h>

#include <vector>
#include <unordered_map>

namespace Ubpa {
	class Primitive;

	class BVHNode {
	public:
		BVHNode(const std::unordered_map<const Primitive*, bboxf3>& p2b,
			std::vector<const Primitive*>& primitives,
			size_t primitiveOffset, size_t primitiveNum);

		~BVHNode();

		bool IsLeaf() const noexcept { return l == nullptr && r == nullptr; }
		const bboxf3& GetBBox() const noexcept { return box; }
		size_t GetPrimitiveOffset() const noexcept { return primitiveOffset; }
		size_t GetPrimitiveNum() const noexcept { return primitiveNum; }
		Axis GetAxis() const noexcept { return axis; }
		BVHNode* GetL() const noexcept { return l; }
		BVHNode* GetR() const noexcept { return r; }

	private:
		// ���� primitives ��˳������ l, r, box �� axis
		void Build(const std::unordered_map<const Primitive*, bboxf3>& p2b, std::vector<const Primitive*>& primitives);

	private:
		bboxf3 box;
		size_t primitiveOffset;
		size_t primitiveNum;
		Axis axis{ Axis::INVALID };
		BVHNode* l{ nullptr };
		BVHNode* r{ nullptr };
	};
}
