#pragma oncem 
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Rock::OnCreate() {
		auto Draw = AddComponent<PNTStaticDraw>();
		Draw->SetMeshResource(L"DEFAULT_CUBE");
		Draw->SetTextureResource(L"GROUND2_TX");

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
		Trans->SetScale(m_Scale.x + 0.2f, m_Scale.y - 0.1f, m_Scale.z + 0.2f);
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
	void ObjRock::OnUpdate2() {
		//位置の修正
		if (m_Arrangement) {
			auto transComp = GetComponent<Transform>();
			transComp->SetRotation(m_SaveRot);
			transComp->SetPosition(m_SavePos);
		}
	}
	void ObjRock::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (!m_Arrangement) {
			auto transComp = GetComponent<Transform>();
			m_SaveRot = transComp->GetRotation();
			m_SavePos = transComp->GetPosition();
			m_Arrangement = true;
		}
		if (Other->FindTag(L"PlayerAttackArea")) {
			SetDrawActive(false);
			SetUpdateActive(false);
		}
	}
	void ObjRock::OnCollisionExcute(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"PlayerGrabArea")) {
			auto transComp = GetComponent<Transform>();
			m_SaveRot = transComp->GetRotation();
			m_SavePos = transComp->GetPosition();
		}
	}
	void CollisionBox::OnCreate() {
		auto Trans = GetComponent<Transform>();
		Trans->SetPosition(m_Position);
		Trans->SetScale(m_Scale);
		Trans->SetRotation(m_Rotation);

		auto Collision = AddComponent<CollisionObb>();
		Collision->SetFixed(true);
		Collision->SetDrawActive(true);

		AddTag(L"StageObjColl");
	}
}