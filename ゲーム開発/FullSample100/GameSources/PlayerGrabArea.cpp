#include "stdafx.h"
#include "Project.h"
namespace basecross {
	GrabArea::GrabArea(const shared_ptr<Stage>& Stage, const Vec3& scale, const Vec3& rotation, const Vec3& position)
		:GameObject(Stage),
		m_Scale(scale),
		m_Rotation(rotation),
		m_Position(position)
	{}

	void GrabArea::OnCreate() {
		auto transComp = GetComponent<Transform>();
		transComp->SetScale(m_Scale);
		transComp->SetRotation(m_Rotation);
		transComp->SetPosition(m_Position);

		AddTag(L"PlayerGrabArea");

		auto drawComp = AddComponent<BcPNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetDrawActive(false);

		auto collComp = AddComponent<CollisionObb>();
		collComp->SetFixed(true);
		collComp->SetUpdateActive(false);
	}

	void GrabArea::OnUpdate() {
		//デバッグ用
		//auto collComp = GetComponent<CollisionObb>();
		//auto drawComp = GetComponent<BcPNTStaticDraw>();
		//if (collComp->IsUpdateActive()) {
		//	drawComp->SetDrawActive(false);
		//}
		//else {
		//	drawComp->SetDrawActive(false);
		//}
	}

	void GrabArea::OnCollisionEnter(shared_ptr<GameObject>& Other) {

	}
}