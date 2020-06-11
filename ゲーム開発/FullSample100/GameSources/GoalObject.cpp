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
		const Vec3& Position,
		int Count
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		GoalCount(Count),
		count(0)
	{
		auto ptrScene = App::GetApp()->GetScene<Scene>();
		ptrScene->SetRescueCount(count);
	}
	GoalObject::~GoalObject() {}

	//������
	void GoalObject::OnCreate() {
		Mat4x4 spanMat; 
		spanMat.affineTransformation(
			Vec3(0.2f, 0.15f, 0.1f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XM_PI, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale.x * 0.75f, m_Scale.y, m_Scale.z * 1.5f);
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
		shadowPtr->SetMeshToTransformMatrix(spanMat);
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->SetMeshResource(L"GOAL_MESH");
		ptrDraw->SetTextureResource(L"GOAL_TX");
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);

		auto obj = GetStage()->GetThis<GameStage>();
		GoalCount = obj->GetGoalCount();
		TargetEndCount = obj->GetGoalCount();
	}
	void GoalObject::OnUpdate() {
		auto obj = GetStage()->GetThis<GameStage>();
		obj->SetGoalCount(GoalCount);
		auto col = GetComponent<CollisionObb>();
		Vec3 movepos;
		if (count == GoalCount) {
			Goalflg = true;
			col->SetUpdateActive(false);
			auto trans = GetComponent<Transform>();
			auto Pos = trans->GetPosition();
			m_Position = Pos;
			movepos = trans->GetForword();
			m_Position += movepos * App::GetApp()->GetElapsedTime()*2.0f;
			trans->SetPosition(m_Position);

		}
		if (EndCount == TargetEndCount) {
			GameEndflg = true;
		}		

	}
}