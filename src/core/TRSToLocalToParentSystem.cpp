#include <UScene/Systems/TRSToLocalToParentSystem.h>

#include <UScene/Components/LocalToParent.h>
#include <UScene/Components/Rotation.h>
#include <UScene/Components/Scale.h>
#include <UScene/Components/Translation.h>

using namespace Ubpa::UScene;

void TRSToLocalToParentSystem::OnUpdate(UECS::Schedule& schedule) {
	UECS::EntityFilter filter{
		TypeList<LocalToParent>{},
		TypeList<UECS::Latest<Translation>, UECS::Latest<Rotation>, UECS::Latest<Scale>>{},
		TypeList<>{},
	};

	schedule.Register([](UECS::ChunkView chunk) {
		auto chunkL2P = chunk.GetCmptArray<LocalToParent>();
		auto chunkT = chunk.GetCmptArray<Translation>();
		auto chunkR = chunk.GetCmptArray<Rotation>();
		auto chunkS = chunk.GetCmptArray<Scale>();

		bool containsT = chunkT != nullptr;
		bool containsR = chunkR != nullptr;
		bool containsS = chunkS != nullptr;

		for (size_t i = 0; i < chunk.EntityNum(); i++) {
			// 000
			if (!containsT && !containsR && !containsS) {
				assert(false);
			}
			// 001
			else if (!containsT && !containsR && containsS) {
				chunkL2P[i].value = transformf{ chunkS[i].value };
			}
			// 010
			else if (!containsT && containsR && !containsS) {
				chunkL2P[i].value = transformf{ chunkR[i].value };
			}
			// 011
			else if (!containsT && containsR && containsS) {
				chunkL2P[i].value = transformf{ chunkR[i].value, chunkS[i].value };
			}
			// 100
			else if (containsT && !containsR && !containsS) {
				chunkL2P[i].value = transformf{ chunkT[i].value };
			}
			// 101
			else if (containsT && !containsR && containsS) {
				chunkL2P[i].value = transformf{ chunkT[i].value, scalef3{chunkS[i].value} };
			}
			// 110
			else if (containsT && containsR && !containsS) {
				chunkL2P[i].value = transformf{ chunkT[i].value, chunkR[i].value };
			}
			// 111
			else/* if (containsT && containsR && containsS)*/ {
				chunkL2P[i].value = transformf{ chunkT[i].value, chunkR[i].value, scalef3{chunkS[i].value} };
			}
		}
		}, SystemFuncName, filter);
}
