#include "stdafx.h"
#include "Project.h"
namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class IncreaseBox : public GameObject;
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	IncreaseBox::IncreaseBox(const shared_ptr<Stage>& StagePtr,
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

	IncreaseBox::IncreaseBox(const shared_ptr<Stage>& StagePtr,
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

	IncreaseBox::~IncreaseBox() {}

	//������
	void IncreaseBox::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//OBB�Փ�j�����t����
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::Auto);
		ptrColl->SetSleepActive(true);
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//ptrDraw->SetTextureResource(L"SKY_TX");
		ptrDraw->SetDiffuse(Col4(1, 0, 0, 1));
		AddTag(L"IncBox");

		//����p
		if (m_Generateflg) {
			Vec3 objPos = Vec3(ptrTransform->GetPosition().x, ptrTransform->GetPosition().y - ptrTransform->GetScale().y, ptrTransform->GetPosition().z);
			auto ptrObj = GetStage()->AddGameObject<ObjectForFlowDecision>(m_Scale, ptrTransform->GetRotation(), objPos);
			ptrObj->SetParentObj(GetThis<IncreaseBox>());
		}
	}

	void IncreaseBox::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);

		if (Other->FindTag(L"Bullet")) {
			shared_ptr<GameObject> IncObj = nullptr;
			auto objVec = GetStage()->GetGameObjectVec();
			for (auto& obj : objVec) {
				auto IncObj = dynamic_pointer_cast<IncreaseObject>(obj);
				if (IncObj) {
					if (IncObj->FindNumTag(m_SaveIncreaseBoxNum)) {
						IncObj->SetGeneratableFlg(m_SaveDirFlgNum, false);
						break;
					}
				}
			}
			SetDrawActive(false);
			SetUpdateActive(false);
			auto transPtr = GetComponent<Transform>();
			GetStage()->AddGameObject<ColdBox>(Vec3(transPtr->GetScale()), Vec3(0.0f), Vec3(transPtr->GetPosition()));
		}
	}

	void IncreaseBox::OnCollisionExcute(shared_ptr<GameObject>& Other) {
		//����͎�肽�����ړ��͂����Ȃ����߂ɕ����G�ꂽ���Ɉʒu��߂�
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
	}

	ObjectForFlowDecision::ObjectForFlowDecision(const shared_ptr<Stage>& Stage, const Vec3& Scale,	const Vec3& Rotation, const Vec3& Position)
		:GameObject(Stage),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{}

	ObjectForFlowDecision::~ObjectForFlowDecision(){}

	void ObjectForFlowDecision::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale - 0.1f);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);
		auto ptrColl = AddComponent<CollisionObb>();
	}

	void ObjectForFlowDecision::OnUpdate() {
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		m_Time += elapsedTime;
		if (m_Time >= 5.0f) {
			auto ptrTrans = GetComponent<Transform>();
			auto AdjustmentScale = Vec3(m_Scale.x - 0.0001f, m_Scale.y - 0.0001f, m_Scale.z - 0.0001f);
			GetStage()->AddGameObject<IncreaseBox>(AdjustmentScale, ptrTrans->GetRotation(), ptrTrans->GetPosition());
			SetDrawActive(false);
			SetUpdateActive(false);
		}
	}

	void ObjectForFlowDecision::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		//�Փ˂��Ă�������ł���
		if (Other->FindTag(L"StageObjColl") || Other->FindTag(L"Ground") || Other->FindTag(L"IncBox")) {
			m_ParentObj->SetGenerateflg(false);
			SetDrawActive(false);
			SetUpdateActive(false);
		}
	}

	void ObjectForFlowDecision::OnCollisionExcute(shared_ptr<GameObject>& Other) {
		//����͎�肽�����ړ��͂����Ȃ����߂ɕ����G�ꂽ���Ɉʒu��߂�
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
	}

	//--------------------------------------------------------------------------------------
	//	class IncreaseObject: public GameObject;
	//--------------------------------------------------------------------------------------
	IncreaseObject::IncreaseObject(const shared_ptr<Stage>& StagePtr, const Vec3& Position)
		:GameObject(StagePtr), m_Position(Position), m_Time(0.0f), m_Interval(5.0f), m_Count(0), m_Range(0), m_LimitRange(3), m_SaveIncreaseObjectNum(IncreaseObjectNum)
	{
		for (int i = 0; i < XZDIRECTION; i++) {
			m_GeneratableFlg[i] = true;
		}
	}

	IncreaseObject::IncreaseObject(const shared_ptr<Stage>& StagePtr, const Vec3& Position, const int& limitRange, const int& useDir)
		:GameObject(StagePtr), m_Position(Position), m_Time(0.0f), m_Interval(5.0f), m_Count(0), m_Range(0), m_LimitRange(limitRange), m_UseStartDir(useDir), m_UseEndDir(useDir)
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

	IncreaseObject::IncreaseObject(const shared_ptr<Stage>& StagePtr, const Vec3& Position, const int& limitRange, const int& useStartDir, const int& useEndDir)
		:GameObject(StagePtr), m_Position(Position), m_Time(0.0f), m_Interval(5.0f), m_Count(0), m_Range(0), m_LimitRange(limitRange), m_UseStartDir(useStartDir), m_UseEndDir(useEndDir)
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

	void IncreaseObject::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_Position);
		AddNumTag(m_SaveIncreaseObjectNum);
	}

	void IncreaseObject::OnUpdate() {
		auto transPtr = this->GetComponent<Transform>();
		//��������}�O�}�̃T�C�Y
		auto increaseBoxScale = Vec3(0.5f, 0.5f,0.5f);
		auto AdjustmentScale = Vec3(increaseBoxScale.x - 0.0001f, increaseBoxScale.y - 0.0001f, increaseBoxScale.z - 0.0001f);
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		m_Time += elapsedTime;
		if (m_Time > m_Interval) {
			if (m_LimitRange > m_Range) {
				shared_ptr<IncreaseBox> incObjPtr;
				//�l���}�X�̏�Ԃ�����
				for (int i = 0; i < XZDIRECTION; i++) {
					//�A�N�e�B�u�Ȃ琶��
					if (m_GeneratableFlg[i]) {
						switch (i)
						{
							//�����}�X
						case 0:
							incObjPtr = GetStage()->AddGameObject<IncreaseBox>(AdjustmentScale, Vec3(0.0f), Vec3(transPtr->GetPosition().x, transPtr->GetPosition().y + increaseBoxScale.y * 0.5f, transPtr->GetPosition().z), m_SaveIncreaseObjectNum, i);
							break;
							//Z���̃v���X����
						case 1:
							incObjPtr = GetStage()->AddGameObject<IncreaseBox>(AdjustmentScale, Vec3(0.0f), Vec3(transPtr->GetPosition().x, transPtr->GetPosition().y + increaseBoxScale.y * 0.5f, transPtr->GetPosition().z + float(m_Count * increaseBoxScale.z)), m_SaveIncreaseObjectNum, i);
							break;
							//X���̃v���X����
						case 2:
							incObjPtr = GetStage()->AddGameObject<IncreaseBox>(AdjustmentScale, Vec3(0.0f), Vec3(transPtr->GetPosition().x + float(m_Count * increaseBoxScale.x), transPtr->GetPosition().y + increaseBoxScale.y * 0.5f, transPtr->GetPosition().z), m_SaveIncreaseObjectNum, i);
							break;
							//Z���̃}�C�i�X����
						case 3:
							incObjPtr = GetStage()->AddGameObject<IncreaseBox>(AdjustmentScale, Vec3(0.0f), Vec3(transPtr->GetPosition().x, transPtr->GetPosition().y + increaseBoxScale.y * 0.5f, transPtr->GetPosition().z + float(-m_Count * increaseBoxScale.z)), m_SaveIncreaseObjectNum, i);
							break;
							//X���̃}�C�i�X����
						case 4:
							incObjPtr = GetStage()->AddGameObject<IncreaseBox>(AdjustmentScale, Vec3(0.0f), Vec3(transPtr->GetPosition().x + float(-m_Count * increaseBoxScale.x), transPtr->GetPosition().y + increaseBoxScale.y * 0.5f, transPtr->GetPosition().z), m_SaveIncreaseObjectNum, i);
							break;
						default:
							//�G���[
							break;
						}
						//group->IntoGroup(incObjPtr);
					}
				}
				//�����ȊO
				if (m_Count % 2 == 1 && m_Count < m_LimitRange * 0.5f) {
					for (int i = 1; i < XZDIRECTION; i++) {
						int UseStartNum = i % 4 + 1;
						int UseEndNum = (i + 1) % 4 + 1;
						if (m_GeneratableFlg[UseStartNum] && m_GeneratableFlg[UseEndNum]) {
							switch (i)
							{
								//X+Z-
							case 1:
								GetStage()->AddGameObject<IncreaseObject>(Vec3(transPtr->GetPosition().x + float(m_Count * increaseBoxScale.x), transPtr->GetPosition().y, transPtr->GetPosition().z + float(-m_Count * increaseBoxScale.z)), m_LimitRange - 1, UseStartNum, UseEndNum);
								break;
								//X-Z-
							case 2:
								GetStage()->AddGameObject<IncreaseObject>(Vec3(transPtr->GetPosition().x + float(-m_Count * increaseBoxScale.x), transPtr->GetPosition().y, transPtr->GetPosition().z + float(-m_Count * increaseBoxScale.z)), m_LimitRange - 1, UseStartNum, UseEndNum);
								break;
								//X-Z+
							case 3:
								GetStage()->AddGameObject<IncreaseObject>(Vec3(transPtr->GetPosition().x + float(-m_Count * increaseBoxScale.x), transPtr->GetPosition().y, transPtr->GetPosition().z + float(+m_Count * increaseBoxScale.z)), m_LimitRange - 1, UseStartNum, UseEndNum);
								break;
								//X+Z+
							case 4:
								GetStage()->AddGameObject<IncreaseObject>(Vec3(transPtr->GetPosition().x + float(m_Count * increaseBoxScale.x), transPtr->GetPosition().y, transPtr->GetPosition().z + float(+m_Count * increaseBoxScale.z)), m_LimitRange - 1, UseStartNum, UseEndNum);
								break;
							default:
								//�G���[
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

	//--------------------------------------------------------------------------------------
	//	class ColdBox : public GameObject;
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	ColdBox::ColdBox(const shared_ptr<Stage>& StagePtr,
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

	ColdBox::~ColdBox() {}

	//������
	void ColdBox::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//OBB�Փ�j�����t����
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		//�^�O������
		AddTag(L"FixedBox");
		//�e������i�V���h�E�}�b�v��`�悷��j
		auto shadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		shadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//ptrDraw->SetTextureResource(L"SKY_TX");
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetDiffuse(Col4(0.5, 0.5, 0.5, 1));



	}
}