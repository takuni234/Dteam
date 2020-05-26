#include "stdafx.h"
#include "Project.h"
namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class GoalObject : public GameObject;
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	GoalObject::GoalObject(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{
	}
	GoalObject::~GoalObject() {}

	//������
	void GoalObject::OnCreate() {
		Mat4x4 spanMat; 
		spanMat.affineTransformation(
			Vec3(0.15f, 0.15f, 0.15f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XM_PI, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//OBB�Փ�j�����t����
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		//�^�O������
		AddTag(L"GoalObj");
		//�e������i�V���h�E�}�b�v��`�悷��j
		auto shadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		shadowPtr->SetMeshResource(L"GOAL_MESH");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->SetMeshResource(L"GOAL_MESH");
		ptrDraw->SetTextureResource(L"GOAL_TX");
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);

	}
	void GoalObject::OnUpdate() {
		shared_ptr<RescurTarget_Base> target = nullptr;
		auto gameobjects = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetGameObjectVec();
		for (auto obj : gameobjects) {
			target = dynamic_pointer_cast<RescurTarget_Base>(obj);
			if (target) {
				
				auto Tpos = target->GetComponent<Transform>()->GetPosition();
				auto pos = GetComponent<Transform>()->GetPosition();
				Vec3 length = Tpos - pos;
				if (length.length() < 1 && target->GetFlg(L"1")==true || target->GetFlg(L"2") == true){					
				}		

			}
		}
		if (count == 2) {
			App::GetApp()->GetScene<Scene>()->
				ChangeScene(SceneKey::Title);
		}
	}
}