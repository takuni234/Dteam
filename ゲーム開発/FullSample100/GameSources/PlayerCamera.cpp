#include "stdafx.h"
#include "Project.h"

namespace basecross {
	PlayerCamera::PlayerCamera()
		:m_Rad(0.0f),
		m_RadY(0.0f),
		m_TargetToAt(0,0,0),
		m_ArmLen(2.0f)
	{}

	PlayerCamera::~PlayerCamera(){}

	void PlayerCamera::OnUpdate() {
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto keyState = App::GetApp()->GetInputDevice().GetKeyState();

		Vec3 newEye = GetEye();
		Vec3 newAt = GetAt();

		bsm::Vec3 armVec = newEye - newAt;
		armVec.normalize();

		if (cntlVec[0].bConnected) {
			m_Rad += cntlVec[0].fThumbRX * 3.0f * elapsedTime;
			m_RadY -= cntlVec[0].fThumbRY * 3.0f * elapsedTime;
		}
		else if (!(keyState.m_bPushKeyTbl[VK_LEFT] && keyState.m_bPushKeyTbl[VK_RIGHT])) {
			if (keyState.m_bPushKeyTbl[VK_RIGHT]) {
				m_Rad += 3.0f * elapsedTime;
				m_RadY -= 3.0f * elapsedTime;
			}
			if (keyState.m_bPushKeyTbl[VK_LEFT]) {
				m_Rad -= 3.0f * elapsedTime;
				m_RadY += 3.0f * elapsedTime;
			}
		}

		if (m_RadY >= XM_PIDIV4) {
			m_RadY = XM_PIDIV4;
		}
		else if (m_RadY <= -XM_PIDIV4) {
			m_RadY = -XM_PIDIV4;
		}
		Quat qtXZ;
		qtXZ.rotation(m_Rad, bsm::Vec3(0.0f, 1.0f, 0.0f));
		qtXZ.normalize();

		Mat4x4 Mat;
		Mat.strTransformation(
			bsm::Vec3(1.0f, 1.0f, 1.0f),
			bsm::Vec3(0.0f, 0.0f, -4.0f),
			qtXZ
		);

		Vec3 posXZ = Mat.transInMatrix();
		//XZの値がわかったので腕角度に代入
		armVec.x = posXZ.x;
		armVec.z = posXZ.z;
		//腕角度を正規化
		armVec.normalize();

		auto ptrTarget = GetTargetObject();
		if (ptrTarget) {
			//目指したい場所
			Vec3 toAt = ptrTarget->GetComponent<Transform>()->GetWorldMatrix().transInMatrix();
			toAt += m_TargetToAt + Vec3(0.0f,0.5f,0.0f);
			newAt = Lerp::CalculateLerp(GetAt(), toAt, 0, 1.0f, 1.0, Lerp::Linear);
		}

		Vec3 toEye = newAt + armVec;
		newEye = Lerp::CalculateLerp(GetEye(), toEye, 0.0f, 1.0f, 1.0f, Lerp::Linear);
		m_Eye = Vec3(newEye.x, newEye.y + sinf(m_RadY), newEye.z);
		SetEye(m_Eye);
		SetAt(newAt);
		Camera::OnUpdate();
	}

	shared_ptr<GameObject> PlayerCamera::GetTargetObject() const {
		if (!m_TargetObject.expired()) {
			return m_TargetObject.lock();
		}
		return nullptr;
	}

	void PlayerCamera::SetTargetObject(const shared_ptr<GameObject>& Obj) {
		m_TargetObject = Obj;
	}

	void PlayerCamera::SetTargetToAt(const bsm::Vec3& v) {
		m_TargetToAt = v;
	}

	void PlayerCamera::SetAt(const bsm::Vec3& At) {
		Camera::SetAt(At);
		Vec3 armVec = GetEye() - GetAt();
		armVec.normalize();
		armVec *= m_ArmLen;
		Vec3 newEye = GetAt() + armVec;
		Camera::SetEye(newEye);
	}

	void PlayerCamera::SetAt(float x, float y, float z) {
		Camera::SetAt(x, y, z);
		Vec3 armVec = GetEye() - GetAt();
		armVec.normalize();
		armVec *= m_ArmLen;
		Vec3 newEye = GetAt() + armVec;
		Camera::SetEye(newEye);
	}

	//--------------------------------------------------------------------------------------
	//	オープニングカメラ（コンポーネントではない）
	//--------------------------------------------------------------------------------------
	OpeningCamera::OpeningCamera() :
		Camera()
	{}
	OpeningCamera::~OpeningCamera() {}

	void OpeningCamera::OnUpdate() {
		auto ptrOpeningCameraman = dynamic_pointer_cast<OpeningCameraman>(GetCameraObject());
		if (ptrOpeningCameraman) {
			auto pos = ptrOpeningCameraman->GetAtPos();
			SetAt(pos);
		}
		Camera::OnUpdate();
	}

	//--------------------------------------------------------------------------------------
	//　球体のカメラマン
	//--------------------------------------------------------------------------------------
	//構築と破棄
	Cameraman::Cameraman(const shared_ptr<Stage>& StagePtr,
		float ToPlayerLen
	) :
		GameObject(StagePtr),
		m_ToPlayerLen(ToPlayerLen)
	{}
	Cameraman::~Cameraman() {}

	//初期化
	void Cameraman::OnCreate() {
		//初期位置などの設定
		auto ptr = GetComponent<Transform>();
		ptr->SetScale(0.25f, 0.25f, 0.25f);	//直径25センチの球体
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetPosition(0, -m_ToPlayerLen, 1.0f);
		//描画コンポーネントの設定
		auto ptrDraw = AddComponent<PNTStaticDraw>();
		//描画するメッシュを設定
		ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");
	}
	//操作
	void Cameraman::OnUpdate() {
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto playerPos = ptrPlayer->GetComponent<Transform>()->GetPosition();
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		Vec3 span = pos - playerPos;
		float nowLen = length(span);
		span.normalize();
		span *= m_ToPlayerLen;
		Vec3 target = playerPos + span;
		target.y = playerPos.y + 1.0f;
		Easing<Vec3> easig;
		Vec3 v;
		if (nowLen < 1.5f) {
			v = easig.EaseIn(EasingType::Cubic, pos, target, 0.7, 1.0f);
		}
		else {
			v = easig.EaseIn(EasingType::Cubic, pos, target, 0.3f, 1.0f);
		}
		ptrTrans->SetPosition(v);
	}

	//--------------------------------------------------------------------------------------
	//　オープニングカメラマン
	//--------------------------------------------------------------------------------------
	//構築と破棄
	OpeningCameraman::OpeningCameraman(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_StartPos(-20.0f, 5.0f, -20.0f),
		m_EndPos(18.0f, 2.0f, 10.0f),
		m_AtStartPos(0.0f, 0.0f, 0.0f),
		m_AtEndPos(18.0f, 0.0f, 18.0f),
		m_AtPos(m_AtStartPos),
		m_TotalTime(0.0f),
		m_ObjCount(0),
		m_ObjSPosVecBuff(Vec3(-20.0f, 10.0f, -20.0f)),
		m_ObjEPosVecBuff(Vec3(-20.0f, 10.0f, -20.0f)),
		m_ObjAtVecBuff(Vec3(-10.0f, 0.0f, 0.0f)),
		m_Once(false)
	{}
	OpeningCameraman::~OpeningCameraman() {}
	//初期化
	void OpeningCameraman::OnCreate() {
		//初期位置などの設定
		auto ptr = GetComponent<Transform>();
		ptr->SetScale(0.25f, 0.25f, 0.25f);	//直径25センチの球体
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetPosition(m_StartPos);
		//ステートマシンの構築
		m_StateMachine.reset(new StateMachine<OpeningCameraman>(GetThis<OpeningCameraman>()));
		//最初のステートをOpeningCameramanToGoalStateに設定
		m_StateMachine->ChangeState(OpeningCameramanToRoundState::Instance());
	}
	//操作
	void OpeningCameraman::OnUpdate() {
		//ステートマシンのUpdateを行う
		//この中でステートの切り替えが行われる
		m_StateMachine->Update();
	}

	void OpeningCameraman::ToGoalEnterBehavior() {
		m_StartPos = Vec3(-20.0f, 10.0f, -20.0f);
		m_EndPos = Vec3(18.0f, 2.0f, 10.0f);
		m_AtStartPos = Vec3(-10.0f, 0.0f, 0.0f);
		m_AtEndPos = Vec3(18.0f, 0.0f, 18.0f);
		m_AtPos = m_AtStartPos;
		m_TotalTime = 0.0f;
	}

	void OpeningCameraman::ToStartEnterBehavior() {
		m_StartPos = Vec3(18.0f, 2.0f, 10.0f);
		m_EndPos = Vec3(0.0f, 3.0f, -5.0f);
		m_AtStartPos = Vec3(18.0f, 0.0f, 18.0f);
		m_AtEndPos = Vec3(0.0f, 0.0f, 0.0f);
		m_AtPos = m_AtStartPos;
		m_TotalTime = 0.0f;
	}

	void OpeningCameraman::ToSurvivorEnterBehavior(shared_ptr<GameObject>& obj, Vec3& startPos) {
		auto ptrTrans = obj->GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();

		m_StartPos = startPos;
		m_EndPos = pos + Vec3(0.0f,1.5f,4.0f);
		m_AtStartPos = Vec3(-10.0f, 0.0f, 0.0f);
		m_AtEndPos = pos;
		m_AtPos = m_AtStartPos;
		m_TotalTime = 0.0f;
	}

	void OpeningCameraman::ToSurvivorRoundBehavior(shared_ptr<GameObject>& obj, Vec3& startPos, Vec3& startAt) {
		auto ptrTrans = obj->GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();

		m_StartPos = startPos;
		m_EndPos = pos + Vec3(0.0f,1.5f,4.0f);
		m_AtStartPos = startAt;
		m_AtEndPos = pos;
		m_AtPos = m_AtStartPos;
		m_TotalTime = 0.0f;

		SetObjSPosVecBuff(m_EndPos);
		SetObjAtVecBuff(m_AtEndPos);
	}

	//void OpeningCameraman::ToRoundEnterBehavior(shared_ptr<GameObject>& obj, Vec3& startPos, Vec3& startAt) {
	//	auto ptrTrans = obj->GetComponent<Transform>();
	//	auto pos = ptrTrans->GetPosition();

	//	m_StartPos = startPos;
	//	m_EndPos = pos + Vec3(0.0f, 1.5f, 4.0f);
	//	m_AtStartPos = startAt;
	//	m_AtEndPos = Vec3(0.0f,0.0f,0.0f);
	//	m_AtPos = m_AtStartPos;
	//	m_TotalTime = 0.0f;

	//	SetObjPosVecBuff(m_EndPos);
	//	SetObjAtVecBuff(m_AtEndPos);
	//}

	void OpeningCameraman::ToRoundEnterBehavior(Vec3& startPos, Vec3& endPos, Vec3& startAt, Vec3& endAt) {
		m_StartPos = startPos;
		m_EndPos = endPos;
		m_AtStartPos = startAt;
		m_AtEndPos = endAt;
		m_AtPos = m_AtStartPos;
		m_TotalTime = 0.0f;

		SetObjSPosVecBuff(m_EndPos);
		SetObjAtVecBuff(m_AtEndPos);
	}

	bool OpeningCameraman::ExcuteBehavior(float totaltime) {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += ElapsedTime;
		if (m_TotalTime > totaltime) {
			return true;
		}
		Easing<Vec3> easing;
		auto TgtPos = easing.EaseInOut(EasingType::Cubic, m_StartPos, m_EndPos, m_TotalTime, totaltime);
		m_AtPos = easing.EaseInOut(EasingType::Cubic, m_AtStartPos, m_AtEndPos, m_TotalTime, totaltime);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(TgtPos);
		return false;
	}

	void OpeningCameraman::EndStateEnterBehavior() {
		auto ptrGameGtage = GetTypeStage<GameStage>();
		ptrGameGtage->ToPlayerCamera();
	}

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToGoalState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	shared_ptr<OpeningCameramanToGoalState> OpeningCameramanToGoalState::Instance() {
		static shared_ptr<OpeningCameramanToGoalState> instance(new OpeningCameramanToGoalState);
		return instance;
	}
	void OpeningCameramanToGoalState::Enter(const shared_ptr<OpeningCameraman>& Obj) {
		Obj->ToGoalEnterBehavior();
	}
	void OpeningCameramanToGoalState::Execute(const shared_ptr<OpeningCameraman>& Obj) {
		if (Obj->ExcuteBehavior(5.0f)) {
			Obj->GetStateMachine()->ChangeState(OpeningCameramanToStartState::Instance());
		}
	}
	void OpeningCameramanToGoalState::Exit(const shared_ptr<OpeningCameraman>& Obj) {
	}
	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToStartState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	shared_ptr<OpeningCameramanToStartState> OpeningCameramanToStartState::Instance() {
		static shared_ptr<OpeningCameramanToStartState> instance(new OpeningCameramanToStartState);
		return instance;
	}
	void OpeningCameramanToStartState::Enter(const shared_ptr<OpeningCameraman>& Obj) {
		Obj->ToStartEnterBehavior();
	}
	void OpeningCameramanToStartState::Execute(const shared_ptr<OpeningCameraman>& Obj) {
		if (Obj->ExcuteBehavior(3.0f)) {
			Obj->GetStateMachine()->ChangeState(OpeningCameramanEndState::Instance());
		}
	}
	void OpeningCameramanToStartState::Exit(const shared_ptr<OpeningCameraman>& Obj) {
	}

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanEndState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	shared_ptr<OpeningCameramanEndState> OpeningCameramanEndState::Instance() {
		static shared_ptr<OpeningCameramanEndState> instance(new OpeningCameramanEndState);
		return instance;
	}
	void OpeningCameramanEndState::Enter(const shared_ptr<OpeningCameraman>& Obj) {
		Obj->EndStateEnterBehavior();
	}
	void OpeningCameramanEndState::Execute(const shared_ptr<OpeningCameraman>& Obj) {
	}
	void OpeningCameramanEndState::Exit(const shared_ptr<OpeningCameraman>& Obj) {
	}

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToSurvivorState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	shared_ptr<OpeningCameramanToSurvivorState> OpeningCameramanToSurvivorState::Instance() {
		static shared_ptr<OpeningCameramanToSurvivorState> instance(new OpeningCameramanToSurvivorState);
		return instance;
	}
	void OpeningCameramanToSurvivorState::Enter(const shared_ptr<OpeningCameraman>& Obj) {
		//ステージにいるサバイバーを取得
		shared_ptr<GameObject> shResObj = nullptr;
		auto vec = Obj->GetStage()->GetSharedObjectGroup(L"RescurTargetGroup")->GetGroupVector();
		for (auto& v : vec) {
			auto shObj = v.lock();
			if (shObj) {
				shResObj = dynamic_pointer_cast<GameObject>(shObj);
				Obj->AddObj(shResObj);
			}
		}
		//サバイバーの人数の初期化
		Obj->SetObjCount(int(vec.size()));
	}
	void OpeningCameramanToSurvivorState::Execute(const shared_ptr<OpeningCameraman>& Obj) {
		int i = Obj->GetObjCount();
		auto vec = Obj->GetObjVec();
		//救出対象全員分
		if (i > 0) {
			if (!Obj->GetOnce()) {
				Obj->ToSurvivorRoundBehavior(vec[i - 1], Obj->GetObjSPosVecBuff(), Obj->GetObjAtVecBuff());
				Obj->SetOnce(true);
			}
			if (Obj->ExcuteBehavior(3.0f)) {
				Obj->SetOnce(false);
				Obj->SetObjCount(--i);
			}
		}
		else {
			Obj->GetStateMachine()->ChangeState(OpeningCameramanEndState::Instance());
		}
	}
	void OpeningCameramanToSurvivorState::Exit(const shared_ptr<OpeningCameraman>& Obj) {
		Obj->ResetObj();
	}

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToRoundState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	shared_ptr<OpeningCameramanToRoundState> OpeningCameramanToRoundState::Instance() {
		static shared_ptr<OpeningCameramanToRoundState> instance(new OpeningCameramanToRoundState);
		return instance;
	}
	void OpeningCameramanToRoundState::Enter(const shared_ptr<OpeningCameraman>& Obj) {
		//shared_ptr<GameObject> minimumXBuff = nullptr; // ステージの端のPositionを一時保持する
		//shared_ptr<GameObject> maximumXBuff = nullptr;
		//shared_ptr<GameObject> minimumZBuff = nullptr;
		//shared_ptr<GameObject> maximumZBuff = nullptr;
		////ステージ内にあるすべてのオブジェクトを取得
		//shared_ptr<GameObject> shResObj = nullptr;
		//auto vec = Obj->GetStage()->GetGameObjectVec();
		//for (auto& v : vec) {
		//	if (v) {
		//		shResObj = dynamic_pointer_cast<GameObject>(v);
		//		if (shResObj) {
		//			if (minimumXBuff == nullptr || maximumXBuff == nullptr || minimumZBuff == nullptr || maximumZBuff == nullptr) {
		//				minimumXBuff = shResObj;
		//				maximumXBuff = shResObj;
		//				minimumZBuff = shResObj;
		//				maximumZBuff = shResObj;
		//			}
		//			auto ptrPosVec = shResObj->GetComponent<Transform>()->GetPosition();
		//			if (minimumXBuff->GetComponent<Transform>()->GetPosition().x > ptrPosVec.x) {
		//				minimumXBuff = shResObj;
		//			}
		//			if (maximumZBuff->GetComponent<Transform>()->GetPosition().z < ptrPosVec.z) {
		//				maximumZBuff = shResObj;
		//			}
		//			if (maximumXBuff->GetComponent<Transform>()->GetPosition().x < ptrPosVec.x) {
		//				maximumXBuff = shResObj;
		//			}
		//			if (minimumZBuff->GetComponent<Transform>()->GetPosition().z > ptrPosVec.z) {
		//				minimumZBuff = shResObj;
		//			}
		//		}
		//	}
		//}
		//Obj->AddObj(minimumXBuff);
		//Obj->AddObj(maximumZBuff);
		//Obj->AddObj(maximumXBuff);
		//Obj->AddObj(minimumZBuff);
		////初期化
		//Obj->SetObjCount(4);
		Obj->SetObjCount(4);
	}
	void OpeningCameramanToRoundState::Execute(const shared_ptr<OpeningCameraman>& Obj) {
		int i = Obj->GetObjCount();
		//救出対象全員分
		if (i > 0) {
			if (!Obj->GetOnce()) {
				auto player = Obj->GetStage()->GetSharedGameObject<Player>(L"Player");
				auto ptrTrans = player->GetComponent<Transform>();
				auto ptrCamera = dynamic_pointer_cast<PlayerCamera>(Obj->OnGetDrawCamera());
				Vec3 pos;
				Vec3 newPos;
				if (ptrCamera) {
					pos = ptrCamera->GetEye();
					newPos = ptrCamera->GetAt();
				}
				else {
					pos = ptrTrans->GetPosition() + Vec3(0.0f,0.6f,-2.0f);
					newPos = pos + Vec3(0.0f,0.0f,1.0f);
				}
				switch (i - 1)
				{
				case 0:
					Obj->SetObjSPosVecBuff(Vec3(-m_CameraLength, m_CameraHeight, 0.0f));
					Obj->SetObjEPosVecBuff(pos);
					Obj->SetObjEAtVecBuff(newPos);
					break;
				case 1:
					Obj->SetObjSPosVecBuff(Vec3(0.0f, m_CameraHeight, m_CameraLength));
					Obj->SetObjEPosVecBuff(Vec3(-m_CameraLength, m_CameraHeight, 0.0f));
					break;
				case 2:
					Obj->SetObjSPosVecBuff(Vec3(m_CameraLength, m_CameraHeight, 0.0f));
					Obj->SetObjEPosVecBuff(Vec3(0.0f, m_CameraHeight, m_CameraLength));
					break;
				case 3:
					Obj->SetObjSPosVecBuff(Vec3(0.0f, m_CameraHeight, -m_CameraLength));
					Obj->SetObjEPosVecBuff(Vec3(m_CameraLength, m_CameraHeight, 0.0f));
					Obj->SetObjAtVecBuff(Vec3(0.0f));
					Obj->SetObjEAtVecBuff(Vec3(0.0f));
					break;
				default:
					break;
				}
				Obj->ToRoundEnterBehavior(Obj->GetObjSPosVecBuff(), Obj->GetObjEPosVecBuff(), Obj->GetObjAtVecBuff(), Obj->GetObjEAtVecBuff());
				Obj->SetOnce(true);
			}
			if (Obj->ExcuteBehavior(2.5f)) {
				Obj->SetOnce(false);
				Obj->SetObjCount(--i);
			}
		}
		else {
			Obj->GetStateMachine()->ChangeState(OpeningCameramanEndState::Instance());
		}
	}
	void OpeningCameramanToRoundState::Exit(const shared_ptr<OpeningCameraman>& Obj) {
	}

}