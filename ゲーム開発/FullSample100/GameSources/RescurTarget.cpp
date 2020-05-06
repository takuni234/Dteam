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
		Trans->SetScale(Vec3(0.25f, 0.25f, 0.25f));
		Trans->SetRotation(m_Rotation);

		auto collisiton = AddComponent<CollisionCapsule>();

		auto gravity = AddComponent<Gravity>();
		gravity->GetGravityVelocity();

		auto shadow = AddComponent<Shadowmap>();
		shadow->SetMeshResource(L"DEFAULT_CAPSULE");
		shadow->SetDrawActive(true);

		INFlg = false;
	}

	void RescurNomalTarget::OnUpdate() {
		if (MoveSwitch()) {
			PLAYERCHASE();
		}
	}

	float RescurNomalTarget::INPLAYERLANGSE() {
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto plyTrans = player->GetComponent<Transform>();
		auto plyPos = plyTrans->GetPosition();
		auto Trans = GetComponent<Transform>();
		auto Pos = Trans->GetPosition();
		Vec3 langthPos = Pos - plyPos;
		float langth = langthPos.length();
		return langth;

	}
	Vec3 RescurNomalTarget::PlayerPos() {
		return GetStage()->GetSharedGameObject<Player>(L"Player")->
			GetComponent<Transform>()->GetPosition();
	}
	void RescurNomalTarget::PLAYERCHASE() {
		auto Trans = GetComponent<Transform>();
		m_Position = GetComponent<Transform>()->GetPosition();
		auto deltatime = App::GetApp()->GetElapsedTime();
		Vec3 plyPos = PlayerPos();
		Vec3 movePos = Vec3(0);
		float length = INPLAYERLANGSE();
		if (length < 2) {

			plyPos = plyPos - Trans->GetPosition();
		}
		else {
			plyPos = Vec3(0);
		}
		m_Position += plyPos * deltatime*0.5f;
		Trans->SetPosition(m_Position);


	}
	bool RescurNomalTarget::MoveSwitch() {
		if (INFlg&&App::GetApp()->GetInputDevice().GetControlerVec()[0].wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
			INFlg = false;
			return true;
		}

		if (INFlg == false && App::GetApp()->GetInputDevice().GetControlerVec()[0].wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
			INFlg = true;
			return true;
		}
	}
	bool RescurNomalTarget::OUTPLAYER_CALL() {
		float Length = INPLAYERLANGSE();
		if (Length < 3) {

		}
		return false;
	}



	//
	void RescurTarget_1::OnCreate() {
		RescurNomalTarget::OnCreate();
		auto Draw = AddComponent<PNTStaticDraw>();
		Draw->SetDiffuse(Col4(1, 1, 0, 1));
		auto Trans = GetComponent<Transform>();
		Trans->SetPosition(m_Position);


	}

	void RescurTarget_1::OnUpdate() {

		if (MoveSwitch()) {
			PLAYERCHASE();
		}

	}

	//
	void RescurTarget_2::OnCreate() {
		RescurNomalTarget::OnCreate();
		auto Draw = AddComponent<PNTStaticDraw>();
		Draw->SetDiffuse(Col4(1, 1, 0, 1));
		auto Trans = GetComponent<Transform>();
		Trans->SetPosition(m_Position);
	}

	void RescurTarget_2::OnUpdate() {
		RescurNomalTarget::OnUpdate();
	}



	//-----------------------------------------------------
	//<<<<<<<<<<<<<
	void Rock::OnCreate() {
		auto Draw = AddComponent<PNTStaticDraw>();
		Draw->SetMeshResource(L"DEFAULT_CUBE");

		auto Trans = GetComponent<Transform>();
		Trans->SetPosition(m_Position);
		Trans->SetScale(m_Scale);
		Trans->SetRotation(m_Rotation);

		//auto Collision = AddComponent<CollisionObb>();
		//Collision->SetFixed(true);
	}
	void Rock::OnUpdate() {		
		if (flg) {		
		}
	}
	void Rock::OnCollisionEnter(shared_ptr<GameObject>& obj) {
		int x = 1;
		m_Position.x += x * 2 * App::GetApp()->GetElapsedTime();
		GetComponent<Transform>()->SetPosition(m_Position);

		flg = true;
	}
	void Slope::OnCreate() {
		auto Draw = AddComponent<PNTStaticDraw>();
		Draw->SetMeshResource(L"DEFAULT_CUBE");

		auto Trans = GetComponent<Transform>();
		Trans->SetPosition(m_Position);
		Trans->SetScale(m_Scale);
		Trans->SetRotation(m_Rotation);

		auto Collision = AddComponent<CollisionObb>();
		Collision->SetFixed(true);
		Collision->SetDrawActive(true);
	}
	void CollisionBox::OnCreate() {
		auto Trans = GetComponent<Transform>();
		Trans->SetPosition(m_Position);
		Trans->SetScale(m_Scale);
		Trans->SetRotation(m_Rotation);

		auto Collision = AddComponent<CollisionObb>();
		Collision->SetFixed(true);
		Collision->SetDrawActive(true);
	}

	//>>>>>>>>>>>>>>>>
	//--------------------------------------------------------
}

