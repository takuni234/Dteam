#include "stdafx.h"
#include "Project.h"
namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class GoalObject : public GameObject;
	//--------------------------------------------------------------------------------------
	//構築と破棄
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

	//初期化
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
		//OBB衝突j判定を付ける
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		//タグをつける
		AddTag(L"GoalObj");
		//影をつける（シャドウマップを描画する）
		auto shadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		shadowPtr->SetMeshResource(L"GOAL_MESH");
		shadowPtr->SetMeshToTransformMatrix(spanMat);
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->SetMeshResource(L"GOAL_MESH");
		ptrDraw->SetTextureResource(L"GOAL_TX");
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);

	}
	void GoalObject::OnUpdate() {
		if (count == GoalCount) {
			Goalflg = true;
		}
		if (EndCount == GoalCount) {
			GameEndflg = true;
		}
	}
}