#include "stdafx.h"
#include "Project.h"
namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class IncreaseBox2 : public GameObject;
	//--------------------------------------------------------------------------------------
	//構築と破棄
	IncreaseBox2::IncreaseBox2(const shared_ptr<Stage>& StagePtr,
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

	IncreaseBox2::~IncreaseBox2() {}

	//初期化
	void IncreaseBox2::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetDiffuse(Col4(1, 0, 0, 1));
	}

	//--------------------------------------------------------------------------------------
	//	class IncreaseBox2Collision : public GameObject; (Collisionのみ)
	//--------------------------------------------------------------------------------------
	//構築と破棄
	IncreaseBox2Collision::IncreaseBox2Collision(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_SaveIncreaseBoxNum(-1),
		m_SaveDirFlgNum(-1),
		m_Generateflg(true)
	{
	}

	IncreaseBox2Collision::IncreaseBox2Collision(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position,
		bool& Generate
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_SaveIncreaseBoxNum(-1),
		m_SaveDirFlgNum(-1),
		m_Generateflg(false)
	{
	}

	IncreaseBox2Collision::IncreaseBox2Collision(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position,
		const int& num,
		const int& dirNum
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_SaveIncreaseBoxNum(num),
		m_SaveDirFlgNum(dirNum),
		m_Generateflg(true)
	{
	}	
	
	IncreaseBox2Collision::IncreaseBox2Collision(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position,
		const int& num,
		const int& dirNum,
		bool &Generate
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_SaveIncreaseBoxNum(num),
		m_SaveDirFlgNum(dirNum),
		m_Generateflg(Generate)
	{
	}

	IncreaseBox2Collision::~IncreaseBox2Collision() {}

	//初期化
	void IncreaseBox2Collision::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);

		m_DrawObj = GetStage()->AddGameObject<IncreaseBox2>(m_Scale, m_Rotation, m_Position)->GetComponent<BcPNTStaticDraw>();

		//OBB衝突j判定を付ける
		auto ptrColl = AddComponent<CollisionSphere>();
		ptrColl->SetSleepActive(true);
		AddTag(L"IncBox");

		//判定用
		if (m_Generateflg) {
			Vec3 objPos = Vec3(ptrTransform->GetPosition().x, ptrTransform->GetPosition().y - ptrTransform->GetScale().y, ptrTransform->GetPosition().z);
			auto ptrObj = GetStage()->AddGameObject<ObjectForFlowDecision2>(m_Scale, ptrTransform->GetRotation(), objPos);
			ptrObj->SetParentObj(GetThis<IncreaseBox2Collision>());
		}
	}

	void IncreaseBox2Collision::OnUpdate2() {
		//判定は取りたいが移動はさせないために物が触れた時に位置を戻す
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
	}

	void IncreaseBox2Collision::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Bullet")) {
			SetDrawActive(false);
			SetUpdateActive(false);
			m_DrawObj->SetDrawActive(false);
			m_DrawObj->SetUpdateActive(false);
			GetStage()->AddGameObject<ColdBox>(m_Scale * 0.999f, m_Rotation, m_Position);
		}
	}


	ObjectForFlowDecision2::ObjectForFlowDecision2(const shared_ptr<Stage>& Stage, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position)
		:GameObject(Stage),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{}

	ObjectForFlowDecision2::~ObjectForFlowDecision2() {}

	void ObjectForFlowDecision2::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale - 0.1f);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);
		auto ptrColl = AddComponent<CollisionObb>();
	}

	void ObjectForFlowDecision2::OnUpdate() {
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		m_Time += elapsedTime;
		if (m_Time >= 5.0f) {
			auto ptrTrans = GetComponent<Transform>();
			auto AdjustmentScale = Vec3(m_Scale.x - 0.0001f, m_Scale.y - 0.0001f, m_Scale.z - 0.0001f);
			GetStage()->AddGameObject<IncreaseBox2Collision>(AdjustmentScale, ptrTrans->GetRotation(), ptrTrans->GetPosition());
			SetDrawActive(false);
			SetUpdateActive(false);
		}
	}

	void ObjectForFlowDecision2::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		//衝突していたら消滅する
		if (Other->FindTag(L"StageObjColl") || Other->FindTag(L"Ground") || Other->FindTag(L"IncBox") || Other->FindTag(L"FixedBox")) {
			m_ParentObj->SetGenerateflg(false);
			SetDrawActive(false);
			SetUpdateActive(false);
		}
	}

	void ObjectForFlowDecision2::OnCollisionExcute(shared_ptr<GameObject>& Other) {
		//判定は取りたいが移動はさせないために物が触れた時に位置を戻す
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
	}

	//--------------------------------------------------------------------------------------
	//	class IncreaseObject2: public GameObject;
	//--------------------------------------------------------------------------------------
	IncreaseObject2::IncreaseObject2(const shared_ptr<Stage>& StagePtr, const Vec3& Position)
		:GameObject(StagePtr), m_Position(Position), m_Time(0.0f), m_Interval(5.0f), m_Count(0), m_Range(0), m_LimitRange(3), m_SaveIncreaseObjectNum(IncreaseObjectNum), m_GenerateFlg(true)
	{
		for (int i = 0; i < XZDIRECTION; i++) {
			m_GeneratableFlg[i] = true;
		}
	}

	IncreaseObject2::IncreaseObject2(const shared_ptr<Stage>& StagePtr, const Vec3& Position, bool& generate)
		:GameObject(StagePtr), m_Position(Position), m_Time(0.0f), m_Interval(5.0f), m_Count(0), m_Range(0), m_LimitRange(3), m_SaveIncreaseObjectNum(IncreaseObjectNum), m_GenerateFlg(generate)
	{
		for (int i = 0; i < XZDIRECTION; i++) {
			m_GeneratableFlg[i] = true;
		}
	}

	IncreaseObject2::IncreaseObject2(const shared_ptr<Stage>& StagePtr, const Vec3& Position, const int& limitRange, const int& useDir)
		:GameObject(StagePtr), m_Position(Position), m_Time(0.0f), m_Interval(5.0f), m_Count(0), m_Range(0), m_LimitRange(limitRange), m_UseStartDir(useDir), m_UseEndDir(useDir), m_GenerateFlg(true)
	{
		for (int i = 0; i < XZDIRECTION; i++) {
			if (i == m_UseStartDir) {
				m_GeneratableFlg[i] = true;
			}
			else {
				m_GeneratableFlg[i] = false;
			}
		}
	}

	IncreaseObject2::IncreaseObject2(const shared_ptr<Stage>& StagePtr, const Vec3& Position, const int& limitRange, const int& useStartDir, const int& useEndDir)
		:GameObject(StagePtr), m_Position(Position), m_Time(0.0f), m_Interval(5.0f), m_Count(0), m_Range(0), m_LimitRange(limitRange), m_UseStartDir(useStartDir), m_UseEndDir(useEndDir), m_GenerateFlg(true)
	{
		for (int i = 0; i < XZDIRECTION; i++) {
			if (i == m_UseStartDir || i == m_UseEndDir) {
				m_GeneratableFlg[i] = true;
			}
			else {
				m_GeneratableFlg[i] = false;
			}
		}
	}

	IncreaseObject2::IncreaseObject2(const shared_ptr<Stage>& StagePtr, const Vec3& Position, const int& limitRange, const int& useStartDir, const int& useEndDir, bool& generate)
		:GameObject(StagePtr), m_Position(Position), m_Time(0.0f), m_Interval(5.0f), m_Count(0), m_Range(0), m_LimitRange(limitRange), m_UseStartDir(useStartDir), m_UseEndDir(useEndDir), m_GenerateFlg(generate)
	{
		for (int i = 0; i < XZDIRECTION; i++) {
			if (i == m_UseStartDir || i == m_UseEndDir) {
				m_GeneratableFlg[i] = true;
			}
			else {
				m_GeneratableFlg[i] = false;
			}
		}
	}

	void IncreaseObject2::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_Position);
		AddNumTag(m_SaveIncreaseObjectNum);
	}

	void IncreaseObject2::OnUpdate() {
		//生成するマグマのサイズ
		if (m_LimitRange > m_Range) {
			auto transPtr = this->GetComponent<Transform>();
			auto increaseBoxScale = Vec3(0.5f, 0.5f, 0.5f);
			auto AdjustmentScale = Vec3(increaseBoxScale.x - 0.0001f, increaseBoxScale.y - 0.0001f, increaseBoxScale.z - 0.0001f);
			auto elapsedTime = App::GetApp()->GetElapsedTime();
			m_Time += elapsedTime;
			if (m_Time > m_Interval) {
				shared_ptr<IncreaseBox2Collision> incObjPtr;
				//四方マスの状態を見る
				for (int i = 0; i < XZDIRECTION; i++) {
					//アクティブなら生成
					if (m_GeneratableFlg[i]) {
						switch (i)
						{
							//中央マス
						case 0:
							incObjPtr = GetStage()->AddGameObject<IncreaseBox2Collision>(AdjustmentScale, Vec3(0.0f), Vec3(transPtr->GetPosition().x, transPtr->GetPosition().y + increaseBoxScale.y * 0.5f, transPtr->GetPosition().z), m_SaveIncreaseObjectNum, i, m_GenerateFlg);
							break;
							//Z軸のプラス方向
						case 1:
							incObjPtr = GetStage()->AddGameObject<IncreaseBox2Collision>(AdjustmentScale, Vec3(0.0f), Vec3(transPtr->GetPosition().x, transPtr->GetPosition().y + increaseBoxScale.y * 0.5f, transPtr->GetPosition().z + float(m_Count * increaseBoxScale.z)), m_SaveIncreaseObjectNum, i, m_GenerateFlg);
							break;
							//X軸のプラス方向
						case 2:
							incObjPtr = GetStage()->AddGameObject<IncreaseBox2Collision>(AdjustmentScale, Vec3(0.0f), Vec3(transPtr->GetPosition().x + float(m_Count * increaseBoxScale.x), transPtr->GetPosition().y + increaseBoxScale.y * 0.5f, transPtr->GetPosition().z), m_SaveIncreaseObjectNum, i, m_GenerateFlg);
							break;
							//Z軸のマイナス方向
						case 3:
							incObjPtr = GetStage()->AddGameObject<IncreaseBox2Collision>(AdjustmentScale, Vec3(0.0f), Vec3(transPtr->GetPosition().x, transPtr->GetPosition().y + increaseBoxScale.y * 0.5f, transPtr->GetPosition().z + float(-m_Count * increaseBoxScale.z)), m_SaveIncreaseObjectNum, i, m_GenerateFlg);
							break;
							//X軸のマイナス方向
						case 4:
							incObjPtr = GetStage()->AddGameObject<IncreaseBox2Collision>(AdjustmentScale, Vec3(0.0f), Vec3(transPtr->GetPosition().x + float(-m_Count * increaseBoxScale.x), transPtr->GetPosition().y + increaseBoxScale.y * 0.5f, transPtr->GetPosition().z), m_SaveIncreaseObjectNum, i, m_GenerateFlg);
							break;
						default:
							//エラー
							break;
						}
						//group->IntoGroup(incObjPtr);
					}
				}
				//中央以外
				if (m_Count % 2 == 1 && m_Count < m_LimitRange * 0.5f) {
					for (int i = 1; i < XZDIRECTION; i++) {
						int UseStartNum = i % 4 + 1;
						int UseEndNum = (i + 1) % 4 + 1;
						if (m_GeneratableFlg[UseStartNum] && m_GeneratableFlg[UseEndNum]) {
							switch (i)
							{
								//X+Z-
							case 1:
								GetStage()->AddGameObject<IncreaseObject2>(Vec3(transPtr->GetPosition().x + float(m_Count * increaseBoxScale.x), transPtr->GetPosition().y, transPtr->GetPosition().z + float(-m_Count * increaseBoxScale.z)), m_LimitRange - 1, UseStartNum, UseEndNum, m_GenerateFlg);
								break;
								//X-Z-
							case 2:
								GetStage()->AddGameObject<IncreaseObject2>(Vec3(transPtr->GetPosition().x + float(-m_Count * increaseBoxScale.x), transPtr->GetPosition().y, transPtr->GetPosition().z + float(-m_Count * increaseBoxScale.z)), m_LimitRange - 1, UseStartNum, UseEndNum, m_GenerateFlg);
								break;
								//X-Z+
							case 3:
								GetStage()->AddGameObject<IncreaseObject2>(Vec3(transPtr->GetPosition().x + float(-m_Count * increaseBoxScale.x), transPtr->GetPosition().y, transPtr->GetPosition().z + float(+m_Count * increaseBoxScale.z)), m_LimitRange - 1, UseStartNum, UseEndNum, m_GenerateFlg);
								break;
								//X+Z+
							case 4:
								GetStage()->AddGameObject<IncreaseObject2>(Vec3(transPtr->GetPosition().x + float(m_Count * increaseBoxScale.x), transPtr->GetPosition().y, transPtr->GetPosition().z + float(+m_Count * increaseBoxScale.z)), m_LimitRange - 1, UseStartNum, UseEndNum, m_GenerateFlg);
								break;
							default:
								//エラー
								break;
							}
						}
					}
				}
				m_Count++;
				m_Range++;
				m_Time = 0.0f;
			}
		}
	}
}