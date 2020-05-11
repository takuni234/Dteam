#pragma oncem 
#include "stdafx.h"
#include "Project.h"

namespace basecross {
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
		Draw->SetTextureResource(L"SKY_TX");

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
	void ObjRock::OnCreate() {
		
		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.65f, 0.75f, 0.65f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XM_PI, 0.0f),
			Vec3(0.0f, -0.5f, 0.0f)
		);
		auto Draw = AddComponent<PNTStaticModelDraw>();
		Draw->SetMeshResource(L"HOTROCK_MESH");
		Draw->SetMeshToTransformMatrix(spanMat);
		Draw->SetTextureResource(L"HOTROCK_TX");

		auto Trans = GetComponent<Transform>();
		Trans->SetPosition(m_Position.x, m_Position.y, m_Position.z);
		Trans->SetScale(m_Scale.x+0.2f, m_Scale.y-0.1f, m_Scale.z+0.2f);
		Trans->SetRotation(m_Rotation);
		//Trans->SetPivot(m_Position.x, m_Position.y, m_Position.z);

		auto Collision = AddComponent<CollisionObb>();
		Collision->SetDrawActive(true);

		AddComponent<Gravity>();

	}
	void ObjRock::OnUpdate() {
		/*auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto plyTrans = player->GetComponent<Transform>();
		auto plyPos = plyTrans->GetPosition();
		auto Trans = GetComponent<Transform>();
		auto Pos = Trans->GetPosition();
		Vec3 langthPos = Pos - plyPos;
		float langth = langthPos.length();
		if (langth < 2) {
			if (App::GetApp()->GetInputDevice().GetControlerVec()[0].wPressedButtons & 
				XINPUT_GAMEPAD_Y) {
				GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
			}
		}*/
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
