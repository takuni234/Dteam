#pragma oncem 
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	RescurNomalTarget::RescurNomalTarget(const shared_ptr<Stage>& stage, Vec3 pos, Vec3 scale, Vec3 rotate)
		:GameObject(stage), m_Position(pos), m_Scale(scale), m_Rotation(rotate) {

	}

	void RescurNomalTarget::OnCreate() {
		auto Drow = AddComponent<PNTStaticDraw>();
		Drow->SetMeshResource(L"DEFAULT_CAPSULE");
		Drow->SetDiffuse(Col4(1, 0, 0, 1));

		auto Trans = GetComponent<Transform>();
		Trans->SetPosition(m_Position);
		Trans->SetScale(Vec3(0.25f,0.25f,0.25f));
		Trans->SetRotation(m_Rotation);

		auto collisiton = AddComponent<CollisionCapsule>();
		
		auto gravity = AddComponent<Gravity>();
		gravity->GetGravityVelocity();

		auto shadow = AddComponent<Shadowmap>();
		shadow->SetMeshResource(L"DEFAULT_CAPSULE");
		shadow->SetDrawActive(true);
	}

	void RescurNomalTarget::OnUpdate() {
		auto Trans = GetComponent<Transform>();
		m_Position = GetComponent<Transform>()->GetPosition();
		auto deltatime = App::GetApp()->GetElapsedTime();
		Vec3 plyPos = PlayerPos();
		Vec3 movePos = Vec3(0);
		float length = INPLAYERLANGSE();
		if (length < 1) {
			plyPos = plyPos - Trans->GetPosition();
		}
		else {
			plyPos = Vec3(0);
		}	
		m_Position += plyPos * deltatime/2;
		Trans->SetPosition(m_Position);

	}

	float RescurNomalTarget::INPLAYERLANGSE() {
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto plyTrans = player->GetComponent<Transform>();
		auto plyPos = plyTrans->GetPosition();
		auto Trans = GetComponent<Transform>();
		auto Pos = Trans->GetPosition();
		Vec3 langthPos = plyPos - Pos;
		return langthPos.length();

	}

	Vec3 RescurNomalTarget::PlayerPos() {
		return GetStage()->GetSharedGameObject<Player>(L"Player")->
			GetComponent<Transform>()->GetPosition();
	}
}