#include "stdafx.h"
#include "Project.h"
namespace basecross {
	AttackArea::AttackArea(const shared_ptr<Stage>& Stage, const Vec3& scale, const Vec3& rotation, const Vec3& position)
		:GameObject(Stage),
		m_Scale(scale),
		m_Rotation(rotation),
		m_Position(position),
		m_SEflg(false),
		m_Hit(false),
		m_Time(0.0f),
		m_Once(false)
	{}

	void AttackArea::OnCreate() {
		auto transComp = GetComponent<Transform>();
		transComp->SetScale(m_Scale);
		transComp->SetRotation(m_Rotation);
		transComp->SetPosition(m_Position);
		AddTag(L"PlayerAttackArea");

		auto drawComp = AddComponent<BcPNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SPHERE");
		drawComp->SetDrawActive(false);

		auto collComp = AddComponent<CollisionSphere>();
		collComp->SetUpdateActive(false);
	}

	void AttackArea::OnUpdate() {
		auto collComp = GetComponent<CollisionSphere>();
		auto drawComp = GetComponent<BcPNTStaticDraw>();
		if (collComp->IsUpdateActive()) {
			auto elapsedTime = App::GetApp()->GetElapsedTime();
			m_Time += elapsedTime;
			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			if (m_Time >= 0.2f && m_Time < 0.5f) { // ピッケルの振り下ろしモーション開始時間12f
				if (!m_Once) {
					if (!m_SEflg) {
						//drawComp->SetDrawActive(true);
						m_SE = ptrXA->Start(L"ICEAX_ATTACK_WAV", 0, 0.2f);
						m_SEflg = true;
					}
					if (m_Hit) {
						if (m_DestructionReservationObj != nullptr) {
							//空振り音を消す
							ptrXA->Stop(m_SE);
							//破壊時の音を出す
							ptrXA->Start(L"ROCK_DESTORY_WAV", 0, 0.2f);
							m_DestructionReservationObj->SetDrawActive(false);
							m_DestructionReservationObj->SetUpdateActive(false);
							m_DestructionReservationObj = nullptr;
						}
					}
					m_Once = true;
				}
			}
			else if (m_Time >= 0.5f) { // ピッケルの全体モーション時間15f
				ptrXA->Stop(m_SE);
				drawComp->SetDrawActive(false);
				ResetAttackFlg();
			}
		}
		else {
			//drawComp->SetDrawActive(false);
		}
	}

	void AttackArea::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"ColdBox")) {
			m_Hit = true;
			m_DestructionReservationObj = Other;
		}
	}
}