#include "stdafx.h"
#include "Project.h"
namespace basecross {
	AttackArea::AttackArea(const shared_ptr<Stage>& Stage, const Vec3& scale, const Vec3& rotation, const Vec3& position)
		:GameObject(Stage),
		m_Scale(scale),
		m_Rotation(rotation),
		m_Position(position)
	{}

	void AttackArea::OnCreate() {
		auto transComp = GetComponent<Transform>();
		transComp->SetScale(m_Scale);
		transComp->SetRotation(m_Rotation);
		transComp->SetPosition(m_Position);

		AddTag(L"PlayerAttackArea");

		auto drawComp = AddComponent<BcPNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");

		auto collComp = AddComponent<CollisionObb>();
		collComp->SetFixed(true);
		collComp->SetUpdateActive(false);
	}

	void AttackArea::OnUpdate() {
		auto collComp = GetComponent<CollisionObb>();
		auto drawComp = GetComponent<BcPNTStaticDraw>();
		if (collComp->IsUpdateActive()) {
			drawComp->SetDrawActive(false);
		}
		else {
			drawComp->SetDrawActive(false);
		}
	}

	void AttackArea::OnCollisionEnter(shared_ptr<GameObject>& Other) {

	}
}