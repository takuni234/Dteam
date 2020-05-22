#include "stdafx.h"
#include "Project.h"
namespace basecross {
	AttackArea::AttackArea(const shared_ptr<Stage>& Stage, const Vec3& scale, const Vec3& rotation, const Vec3& position)
		:GameObject(Stage),
		m_Scale(scale),
		m_Rotation(rotation),
		m_Position(position),
		m_SEflg(false)
	{}

	void AttackArea::OnCreate() {
		auto transComp = GetComponent<Transform>();
		transComp->SetScale(m_Scale);
		transComp->SetRotation(m_Rotation);
		transComp->SetPosition(m_Position);

		AddTag(L"PlayerAttackArea");

		auto drawComp = AddComponent<BcPNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetDrawActive(true);

		auto collComp = AddComponent<CollisionObb>();
		collComp->SetFixed(true);
		collComp->SetUpdateActive(false);
	}

	void AttackArea::OnUpdate() {
		auto collComp = GetComponent<CollisionObb>();
		auto drawComp = GetComponent<BcPNTStaticDraw>();
		if (collComp->IsUpdateActive()) {
			drawComp->SetDrawActive(true);
			if (!m_SEflg) {
				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(L"ICEAX_ATTACK_WAV", 0, 0.1f);
				m_SEflg = true;
			}
		}
		else {
			drawComp->SetDrawActive(false);
		}
	}

	void AttackArea::OnCollisionEnter(shared_ptr<GameObject>& Other) {

	}
}