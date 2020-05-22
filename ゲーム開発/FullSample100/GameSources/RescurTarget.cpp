#pragma oncem 
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//救出対象のベース
	RescurTarget_Base::RescurTarget_Base(const shared_ptr<Stage>& stage, Vec3 pos, Vec3 scale, Vec3 rotate)
		:GameObject(stage), m_Position(pos), m_Scale(scale), m_Rotation(rotate), INFlg(false) ,SpliteFlg(true){
	}
	void RescurTarget_Base::OnCreate() {
		//ナンバースクエアを作成して関連させる		
		GetStage()->AddGameObject<HelpSplite>(m_Position,Vec3(0),Vec3(0));

	}
	void RescurTarget_Base::OnUpdate() {
		PLAYERCHASE();

	}
	float RescurTarget_Base::INPLAYERLANGSE() {
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto plyTrans = player->GetComponent<Transform>();
		auto plyPos = plyTrans->GetPosition();
		auto Trans = GetComponent<Transform>();
		auto Pos = Trans->GetPosition();
		Vec3 langthPos = Pos - plyPos;
		return  langthPos.length();

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
			SpliteFlg = false;
			LightFlg = true;
			plyPos = plyPos - Trans->GetPosition();
		}
		else {		
			if (SpliteFlg==false&&LightFlg) {
				GetStage()->AddGameObject<HelpSplite>(m_Position, Vec3(0), Vec3(0));
			
				LightFlg = false;

			}
			SpliteFlg = true;
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
		if (Length > 3) {

		}
		return false;
	}
	void RescurTarget_Base::HappyAction() {
		Vec3 jumpPos;
		auto Trans = GetComponent<Transform>();
		auto Pos = Trans->GetPosition();
		m_Position = Pos;
		jumpPos = Vec3(0, 1, 0);

		m_Position += jumpPos * App::GetApp()->GetElapsedTime()*2.0f;

		Trans->SetPosition(m_Position);
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
		Draw->AddAnimation(L"Default", 200, 100, true, 20.0f);
		Draw->AddAnimation(L"Walk", 0, 30, true, 60);
		Draw->AddAnimation(L"jump", 34, 65, true, 30);
		


		auto Trans = GetComponent<Transform>();
		Trans->SetScale(Vec3(0.25f, 0.25f, 0.25f));
		Trans->SetRotation(m_Rotation);
		Trans->SetPosition(m_Position.x, m_Position.y, m_Position.z);

		auto collision = AddComponent<CollisionObb>();
		collision->SetDrawActive(true);

		GetStage()->SetSharedGameObject(L"s", GetThis<GameObject>());
		AddTag(L"RescurTarget1");

		auto gravity = AddComponent<Gravity>();

		auto shadow = AddComponent<Shadowmap>();
		shadow->SetMeshResource(L"DEFAULT_CAPSULE");
		shadow->SetDrawActive(true);
		

		//ナンバースクエアを作成して関連させる		
		//GetStage()->AddGameObject<HelpSplite>(m_Position);
		INFlg = false;
		flg = false;
		//help = dynamic_pointer_cast<HelpSplite>(hs);
	}

	void RescurTarget_1::OnUpdate() {
		auto Pos = GetComponent<Transform>()->GetPosition();
		time = App::GetApp()->GetElapsedTime();
		auto draw2 = GetComponent<BcPNTBoneModelDraw>();
		draw2->SetTextureResource(L"SURVIVOR_TX");
		draw2->SetFogEnabled(true);

		PLAYERCHASE();

		if (INFlg==false&&draw2->GetCurrentAnimation()!=L"jump") {		
			draw2->ChangeCurrentAnimation(L"jump");
			flg = true;
			//GetStage()->AddGameObject<HelpSplite>(Pos,Vec3(0),Vec3(0));

		}

		if (INFlg && draw2->GetCurrentAnimation() != L"Walk") {
			draw2->ChangeCurrentAnimation(L"Walk");
			flg = false;
		}
		if (flg) {
			HappyAction();
		}
		draw2->UpdateAnimation(time);

	}
	void RescurTarget_1::OnCollisionEnter(shared_ptr<GameObject>& obj) {
		if (obj->FindTag(L"Player")) {
			HappyAction();
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
		Draw->AddAnimation(L"Default", 200, 100, true, 20.0f);
		Draw->AddAnimation(L"Walk", 0, 30, true, 60);
		Draw->AddAnimation(L"jump", 34, 65, true, 30);

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
		Vec3 pos = m_Position;
	}

	void RescurTarget_2::OnUpdate() {
		auto Pos = GetComponent<Transform>()->GetPosition();
		time = App::GetApp()->GetElapsedTime();
		auto draw2 = GetComponent<BcPNTBoneModelDraw>();
		draw2->SetTextureResource(L"SURVIVOR_TX");
		draw2->SetFogEnabled(true);

		PLAYERCHASE();

		if (INFlg == false && draw2->GetCurrentAnimation() != L"jump") {
			draw2->ChangeCurrentAnimation(L"jump");
			flg = true;
			//GetStage()->AddGameObject<HelpSplite>(Pos,Vec3(0),Vec3(0));
		}

		if (INFlg && draw2->GetCurrentAnimation() != L"Walk") {
			draw2->ChangeCurrentAnimation(L"Walk");
			flg = false;
		}
		if (flg) {
			HappyAction();
		}
		draw2->UpdateAnimation(time);


	}

	void box::OnCreate() {
		auto Draw = AddComponent<PNTStaticDraw>();
		Draw->SetMeshResource(L"DEFAULT_CUBE");
		Draw->SetTextureResource(L"HELPTEXT_TX");
		Draw->SetDrawActive(true);

		auto Trans = GetComponent<Transform>();
		Trans->SetPosition(m_Position);
		Trans->SetScale(m_Scale);
		Trans->SetRotation(m_Rotation);

	}

	HelpSplite::HelpSplite(const shared_ptr<Stage>& stage, Vec3 pos, Vec3 scale, Vec3 rot)
		:RescurTarget_Base(stage,pos,scale,rot) ,Pos(pos){

	}
	void HelpSplite::OnCreate() {
		float HelfSize = 0.75f;
		float HelfSizey = 0.5f;

		//頂点配列(縦横5個ずつ表示)

		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize-0.0f, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize-0.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize-0.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize-0.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};

		auto PtrTransform = GetComponent<Transform>();

		//if (!m_SeekObject.expired()) {
		Pos.y += 1.0f;// 0.75f;
			PtrTransform->SetPosition(Vec3(Pos.x,Pos.y,Pos.z));
			PtrTransform->SetScale(1.0f, 1.0f, 1.0f);
			//PtrTransform->SetQuaternion(SeekTransPtr->GetQuaternion());
			///変更できるスクエアリソースを作成
			vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };

			//新しい頂点を使ってメッシュリソースの作成
			mesh = MeshResource::CreateMeshResource<VertexPositionColorTexture>(vertices, indices, true);


			SetAlphaActive(true);
			//auto PtrTransform = GetComponent<Transform>();
			PtrTransform->SetScale(Vec3(1));
			PtrTransform->SetRotation(0, 0, 0);
			PtrTransform->SetPosition(Pos);

			auto DrawComp = AddComponent<PCTStaticDraw>();
			DrawComp->SetMeshResource(mesh);
			DrawComp->SetTextureResource(L"HELPTEXT_TX");
			SetAlphaActive(true);
			SetDrawLayer(1);

	}
	void HelpSplite::OnUpdate() {
		auto PtrCamera = GetStage()->GetView()->GetTargetCamera();
		auto PtrTransform = GetComponent<Transform>();

		Quat Qt;
		//向きをビルボードにする
		Qt = Billboard(PtrCamera->GetAt() - PtrCamera->GetEye());

		PtrTransform->SetQuaternion(Qt);

		time += App::GetApp()->GetElapsedTime();
		if (INPLAYERLANGSE()<2) {
			GetStage()->RemoveGameObject<HelpSplite>(GetThis<HelpSplite>());
		}
	}
}
