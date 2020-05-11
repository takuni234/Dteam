#pragma oncem 
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//救出対象のベース
	RescurTarget_Base::RescurTarget_Base(const shared_ptr<Stage>& stage, Vec3 pos, Vec3 scale, Vec3 rotate)
		:GameObject(stage), m_Position(pos), m_Scale(scale), m_Rotation(rotate) {
	}
	void RescurTarget_Base::OnCreate() {

	}
	void RescurTarget_Base::OnUpdate() {

	}
	float RescurTarget_Base::INPLAYERLANGSE() {
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto plyTrans = player->GetComponent<Transform>();
		auto plyPos = plyTrans->GetPosition();
		auto Trans = GetComponent<Transform>();
		auto Pos = Trans->GetPosition();
		Vec3 langthPos = Pos - plyPos;
		float langth = langthPos.length();
		return langth;

	}
	Vec3 RescurTarget_Base::PlayerPos() {
		return GetStage()->GetSharedGameObject<Player>(L"Player")->
			GetComponent<Transform>()->GetPosition();
	}
	void RescurTarget_Base::PLAYERCHASE() {
		auto Trans = GetComponent<Transform>();
		m_Position = Trans->GetPosition();
		auto deltatime = App::GetApp()->GetElapsedTime();
		Vec3 plyPos = PlayerPos();
		Vec3 movePos = Vec3(0);
		float length = INPLAYERLANGSE();
		if (length < 2) {
			INFlg = true;
			plyPos = plyPos - Trans->GetPosition();
		}
		else {
			INFlg = false;
			plyPos = Vec3(0);
		}
		m_Position += plyPos * deltatime*0.5f;
		Trans->SetPosition(m_Position);

		auto UB = GetBehavior<UtilBehavior>();
		UB->RotToHead(1.0f);

	}
	bool RescurTarget_Base::MoveSwitch() {
		if (INFlg&&App::GetApp()->GetInputDevice().GetControlerVec()[0].wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
			INFlg = false;
			return true;
		}

		if (INFlg == false && App::GetApp()->GetInputDevice().GetControlerVec()[0].wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
			INFlg = true;
			return true;
		}
	}
	bool RescurTarget_Base::OUTPLAYER_CALL() {
		float Length = INPLAYERLANGSE();
		if (Length < 3) {

		}
		return false;
	}



	RescurNomalTarget::RescurNomalTarget(const shared_ptr<Stage>& stage, Vec3 pos, Vec3 scale, Vec3 rotate)
		:GameObject(stage), m_Position(pos), m_Scale(scale), m_Rotation(rotate) {

	}

	void RescurNomalTarget::OnCreate() {
		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XM_PI, 0.0f),
			Vec3(0.0f, -0.5f, 0.0f)
		);

		auto Draw = AddComponent<BcPNTBoneModelDraw>();
		Draw->SetMeshResource(L"SURVIVOR_1");
		Draw->SetMeshToTransformMatrix(spanMat);
		Draw->SetTextureResource(L"SURVIVOR_TX");
		Draw->AddAnimation(L"woak", 0, 30, true, 25);
		Draw->AddAnimation(L"stop", 0, 30, true, 25);


		auto Trans = GetComponent<Transform>();
		Trans->SetScale(Vec3(0.25f, 0.25f, 0.25f));
		Trans->SetRotation(m_Rotation);
		Trans->SetPosition(m_Position.x, m_Position.y, m_Position.z);

		auto collision = AddComponent<CollisionObb>();
		collision->SetDrawActive(true);


		auto gravity = AddComponent<Gravity>();
		gravity->GetGravityVelocity();

		auto shadow = AddComponent<Shadowmap>();
		shadow->SetMeshResource(L"DEFAULT_CAPSULE");
		shadow->SetDrawActive(true);

		INFlg = false;
	}

	void RescurNomalTarget::OnUpdate() {
		auto time = App::GetApp()->GetElapsedTime();
		auto draw = GetComponent<BcPNTBoneModelDraw>();
		draw->SetFogEnabled(true);
		//draw->SetMeshResource(L"SURVIVOR_TX");
		draw->UpdateAnimation(time);


		if (MoveSwitch()) {
			draw->GetCurrentAnimation() + L"woak";
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

		auto UB = GetBehavior<UtilBehavior>();
		UB->RotToHead(1.0f);

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
		RescurTarget_Base::OnCreate();
		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XM_PI, 0.0f),
			Vec3(0.0f, -0.5f, 0.0f)
		);

		auto Draw = AddComponent<BcPNTBoneModelDraw>();
		Draw->SetMeshResource(L"SURVIVOR_1");
		Draw->SetMeshToTransformMatrix(spanMat);
		Draw->SetTextureResource(L"SURVIVOR_TX");
		Draw->AddAnimation(L"woak", 0, 30, true, 25);
		Draw->AddAnimation(L"stop", 30, 60, true, 25);


		auto Trans = GetComponent<Transform>();
		Trans->SetScale(Vec3(0.25f, 0.25f, 0.25f));
		Trans->SetRotation(m_Rotation);
		Trans->SetPosition(m_Position.x, m_Position.y, m_Position.z);

		auto collision = AddComponent<CollisionObb>();
		collision->SetDrawActive(true);


		auto gravity = AddComponent<Gravity>();
		gravity->GetGravityVelocity();

		auto shadow = AddComponent<Shadowmap>();
		shadow->SetMeshResource(L"DEFAULT_CAPSULE");
		shadow->SetDrawActive(true);

		INFlg = false;

	}

	void RescurTarget_1::OnUpdate() {
		auto time = App::GetApp()->GetElapsedTime();
		auto draw = GetComponent<BcPNTBoneModelDraw>();
		draw->SetFogEnabled(true);
		draw->SetTextureResource(L"SURVIVOR_TX");
		draw->UpdateAnimation(time);
        draw->GetCurrentAnimation() + L"stop";

		PLAYERCHASE();
		if (INFlg==false) {
			draw->ChangeCurrentAnimation(L"woak");
		}
		else {	
			draw->GetCurrentAnimation()+L"stop";
		}

	}

	//
	void RescurTarget_2::OnCreate() {
		RescurTarget_Base::OnCreate();
		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XM_PI, 0.0f),
			Vec3(0.0f, -0.5f, 0.0f)
		);

		auto Draw = AddComponent<BcPNTBoneModelDraw>();
		Draw->SetMeshResource(L"SURVIVOR_2");
		Draw->SetMeshToTransformMatrix(spanMat);
		Draw->SetTextureResource(L"SURVIVOR_TX");
		Draw->AddAnimation(L"woak", 0, 30, true, 25);
		Draw->AddAnimation(L"stop", 0, 30, true, 25);


		auto Trans = GetComponent<Transform>();
		Trans->SetScale(Vec3(0.25f, 0.25f, 0.25f));
		Trans->SetRotation(m_Rotation);
		Trans->SetPosition(m_Position.x, m_Position.y, m_Position.z);

		auto collision = AddComponent<CollisionObb>();
		collision->SetDrawActive(true);


		auto gravity = AddComponent<Gravity>();
		gravity->GetGravityVelocity();

		auto shadow = AddComponent<Shadowmap>();
		shadow->SetMeshResource(L"DEFAULT_CAPSULE");
		shadow->SetDrawActive(true);

		INFlg = false;
	}

	void RescurTarget_2::OnUpdate() {
		RescurTarget_Base::OnUpdate();
		auto time = App::GetApp()->GetElapsedTime();
		auto draw = GetComponent<BcPNTBoneModelDraw>();
		draw->SetFogEnabled(true);
		draw->SetTextureResource(L"SURVIVOR_TX");
		draw->UpdateAnimation(time);


		PLAYERCHASE();
		if (INFlg == false) {
			draw->UpdateAnimation(time);
			draw->ChangeCurrentAnimation(L"woak");
		}
		else {
			draw->UpdateAnimation(time);
			draw->GetCurrentAnimation() + L"stop";
		}


	}
}
