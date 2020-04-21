#include <UScene/core.h>

#include <UDP/Visitor/MultiVisitor.h>
#include <UDP/Reflection/MemVarVisitor.h>
#include <UDP/Reflection/Reflection.h>
#include <UDP/Reflection/VarPtrVisitor.h>

#include <iostream>

using namespace std;
using namespace Ubpa;

class VarSerializer : public VarPtrVisitor<VarSerializer>, public ReflTraitsVisitor {
public:
	VarSerializer() {
		VarPtrVisitor<VarSerializer>::RegistC<
			float,
			string,
			set<SObj*>,
			SObj*,
			vecf3,
			rgbf,
			pointf3,
			quatf,
			scalef3,
			Primitive*,
			Light*,
			Material*,
			Texture2D*>();
	}

	using VarPtrVisitor<VarSerializer>::Regist;
	using ReflTraitsVisitor::Visit;

	void Visit(SObj* sobj) {
		enter();
		prefix(); cout << "\"type\": \"" << Reflection<SObj>::Instance().Name() << "\"," << endl;
		for (auto [n, v] : Reflection<SObj>::Instance().VarPtrs(*sobj)) {
			if (Reflection<SObj>::Instance().FieldMeta(n, ReflAttr::is_not_serialize) == ReflAttr::null)
				continue;
			prefix(); cout << "\"" << n << "\"" << ": ";
			VarPtrVisitor<VarSerializer>::Visit(v);
			cout << ", " << endl;
		}
		prefix(); cout << "\"components\": [";
		auto cmpts = sobj->Components();
		size_t num = cmpts.size();
		size_t i = 0;
		for (auto [cmpt, size] : cmpts) {
			Visit(cmpt);
			if (++i < num)
				cout << ",";
		}
		cout << "]" << endl;
		exist();
	}

protected:
	template<typename T>
	void ImplVisit(const T& p) { cout << p; }
	template<typename T>
	void ImplVisit(T* const& p) {
		if (p == nullptr)
			cout << "null";
		else
			ReflTraitsVisitor::Visit(p);
	}

	template<typename T>
	void ImplVisit(T& p) { cout << p; }
	template<typename T>
	void ImplVisit(T*& p) {
		if (p == nullptr)
			cout << "null";
		else
			ReflTraitsVisitor::Visit(p);
	}

	template<typename T>
	void ImplVisit(const set<T*>& p) {
		cout << "[";
		size_t num = p.size();
		size_t i = 0;
		for (auto var : p) {
			ReflTraitsVisitor::Visit(var);
			if (++i < num)
				cout << ",";
		}
		cout << "]";
	}

	void ImplVisit(const string& p) {
		cout << "\"" << p << "\"";
	}

	void ImplVisit(SObj* const& sobj) {
		Visit(sobj);
	}

	template<typename T, size_t N>
	void ImplVisit(const point<T, N>& p) {
		cout << "[";
		for (size_t i = 0; i < N - 1; i++)
			cout << p[i] << ", ";
		cout << p[N-1];
		cout << "]";
	}

	template<typename T>
	void ImplVisit(const quat<T>& q) {
		cout << "[" << q[0] << ", " << q[1] << ", " << q[2] << ", " << q[3] << "]";
	}

	template<typename T, size_t N>
	void ImplVisit(const vec<T, N>& v) {
		cout << "[";
		for (size_t i = 0; i < N-1; i++)
			cout << v[i] << ", ";
		cout << v[N-1];
		cout << "]";
	}

	template<typename T, size_t N>
	void ImplVisit(const scale<T, N>& v) {
		cout << "[";
		for (size_t i = 0; i < N - 1; i++)
			cout << v[i] << ", ";
		cout << v[N - 1];
		cout << "]";
	}

	template<typename T>
	void ImplVisit(const rgb<T>& c) {
		cout << "[" << c[0] << ", " << c[1] << ", " << c[2] << "]";
	}

private:
	virtual void Receive(const void* obj, std::string_view name, const xMap<std::string, std::shared_ptr<const VarPtrBase>>& nv) override {
		enter();
		prefix(); cout << "\"type\": \"" << name << "\"";
		size_t num = nv.size();
		if (num != 0) {
			cout << "," << endl;
			size_t i = 0;
			for (auto [n, v] : nv) {
				if (ReflectionMngr::Instance().GetReflction(obj)->FieldMeta(n, ReflAttr::is_not_serialize) == ReflAttr::null)
					continue;
				prefix(); cout << "\"" << n << "\"" << ": ";
				VarPtrVisitor<VarSerializer>::Visit(v);
				if (++i < num)
					cout << ",";
				cout << endl;
			}
		}
		else
			cout << endl;

		exist();
	}

private:
	void enter() {
		cout << "{" << endl;
		depth++;
	}
	void exist() {
		depth--;
		prefix(); cout << "}";
	}
	void prefix() {
		for (size_t i = 0; i < depth; i++)
			cout << "  ";
	}

	size_t depth{ 0 };
};

int main() {
	Scene::OnRegist();

	Scene scene("scene");

	auto [sobj0, camera] = scene.CreateSObj<Cmpt::Camera>("sobj0");
	auto [sobj1, geo, mat] = scene.CreateSObj<Cmpt::Geometry, Cmpt::Material>("sobj1");
	auto [sobj2, light] = scene.CreateSObj<Cmpt::Light>("sobj2");

	geo->SetPrimitive(new Sphere);
	mat->SetMaterial(new stdBRDF{ 1.f });
	light->SetLight(new PointLight{ 1.f, 1.f });

	VarSerializer vs;
	ReflTraitsIniter::Instance().InitC(vs);

	vs.Visit(&scene);
	cout << endl;

	cout << "--------------------------" << endl;
	cout << "test online: https://www.json.cn/" << endl;
	return 0;
}
