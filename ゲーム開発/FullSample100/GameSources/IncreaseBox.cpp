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
		auto ptrColl = AddComponent<CollisionSphere>();
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
		if (Other->FindTag(L"StageObjColl") || Other->FindTag(L"Ground") || Other->FindTag(L"IncBox") || Other->FindTag(L"FixedBox")) {
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
		//��������}�O�}�̃T�C�Y
		if (m_LimitRange > m_Range) {
			auto transPtr = this->GetComponent<Transform>();
			auto increaseBoxScale = Vec3(0.5f, 0.5f,0.5f);
			auto AdjustmentScale = Vec3(increaseBoxScale.x - 0.0001f, increaseBoxScale.y - 0.0001f, increaseBoxScale.z - 0.0001f);
			auto elapsedTime = App::GetApp()->GetElapsedTime();
			m_Time += elapsedTime;
			if (m_Time > m_Interval) {
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

	CellIncreaseObject::CellIncreaseObject(const shared_ptr<Stage>& StagePtr, const float& CellScale, const Vec3& Position, const int& limitRange)
		:GameObject(StagePtr),
		m_CellScale(CellScale),
		m_Position(Position),
		m_LimitRange(limitRange)
	{}

	//�Œ�̃{�b�N�X�̃R�X�g���Z���}�b�v�ɔ��f
	void CellIncreaseObject::SetCellMapCost() {
		//�Z���}�b�v����FixedBox�̏����Z�b�g
		auto PtrCellmap = GetStage()->GetSharedGameObject<StageCellMap>(L"StageCellMap");
		auto BoxGroup = GetStage()->GetSharedObjectGroup(L"FixedBoxes");
		//�Z���}�b�v����Z���̔z����擾
		auto& CellVec = PtrCellmap->GetCellVec();
		//�{�b�N�X�O���[�v����{�b�N�X�̔z����擾
		auto& BoxVec = BoxGroup->GetGroupVector();
		vector<AABB> ObjectsAABBVec;
		for (auto& v : BoxVec) {
			auto FixedBoxPtr = dynamic_pointer_cast<TilingFixedBox>(v.lock());
			if (FixedBoxPtr) {
				auto ColPtr = FixedBoxPtr->GetComponent<CollisionObb>();
				//�{�b�N�X�̏Փ˔��肩���b�s���O����AABB���擾���ĕۑ�
				ObjectsAABBVec.push_back(ColPtr->GetObb().GetWrappedAABB());
			}
		}
		//�Z���z�񂩂�Z�����X�L����
		for (auto& v : CellVec) {
			for (auto& v2 : v) {
				for (auto& vObj : ObjectsAABBVec) {
					if (HitTest::AABB_AABB_NOT_EQUAL(v2.m_PieceRange, vObj)) {
						//�{�b�N�X��ABB��NOT_EQUAL�ŏՓ˔���
						v2.m_Cost = -1;
						break;
					}
				}
			}
		}
	}

	void CellIncreaseObject::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_Position);
		auto Ptr = GetStage()->AddGameObject<StageCellMap>(Vec3(ptrTrans->GetPosition().x + -m_LimitRange * 0.5f * m_CellScale, ptrTrans->GetPosition().y, ptrTrans->GetPosition().z + -m_LimitRange * 0.5f * m_CellScale), m_CellScale, m_LimitRange, m_LimitRange);
		//�Z���}�b�v�̋���\������ꍇ�͈ȉ��̐ݒ�
		Ptr->SetDrawActive(true);
		//����ɃZ���̃C���f�b�N�X�ƃR�X�g��\������ꍇ�͈ȉ��̐ݒ�
		//Ptr->SetCellStringActive(true);
		GetStage()->SetSharedGameObject(L"IncreaseBoxCellMap", Ptr);
		//�Z���}�b�v�ւ̃{�b�N�X�̃R�X�g�ݒ�
		SetCellMapCost();
	}

	void CellIncreaseObject::OnUpdate() {

	}

	//--------------------------------------------------------------------------------------
	//�@�^�C�����O����Œ�̃{�b�N�X
	//--------------------------------------------------------------------------------------
	TilingFixedBox::TilingFixedBox(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position,
		float UPic,
		float VPic
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_UPic(UPic),
		m_VPic(VPic)
	{}
	TilingFixedBox::~TilingFixedBox() {}
	//������
	void TilingFixedBox::OnCreate() {
		auto PtrTrans = GetComponent<Transform>();
		PtrTrans->SetScale(m_Scale);
		PtrTrans->SetRotation(m_Rotation);
		PtrTrans->SetPosition(m_Position);
		auto Coll = AddComponent<CollisionObb>();
		Coll->SetFixed(true);
		vector<VertexPositionNormalTexture> vertices;
		vector<uint16_t> indices;
		MeshUtill::CreateCube(1.0f, vertices, indices);
		float UCount = m_Scale.x / m_UPic;
		float VCount = m_Scale.z / m_VPic;
		for (size_t i = 0; i < vertices.size(); i++) {
			if (vertices[i].textureCoordinate.x >= 1.0f) {
				vertices[i].textureCoordinate.x = UCount;
			}
			if (vertices[i].textureCoordinate.y >= 1.0f) {
				float FrontBetween = bsm::angleBetweenNormals(vertices[i].normal, Vec3(0, 1, 0));
				float BackBetween = bsm::angleBetweenNormals(vertices[i].normal, Vec3(0, -1, 0));
				if (FrontBetween < 0.01f || BackBetween < 0.01f) {
					vertices[i].textureCoordinate.y = VCount;
				}
			}
		}
		//�`��R���|�[�l���g�̒ǉ�
		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		//�`��R���|�[�l���g�Ɍ`��i���b�V���j��ݒ�
		PtrDraw->CreateOriginalMesh(vertices, indices);
		PtrDraw->SetOriginalMeshUse(true);
		PtrDraw->SetFogEnabled(true);
		//�����ɉe���f�肱�ނ悤�ɂ���
		PtrDraw->SetOwnShadowActive(true);
		//�`��R���|�[�l���g�e�N�X�`���̐ݒ�
		PtrDraw->SetTextureResource(L"SKY_TX");
		//�^�C�����O�ݒ�
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);
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
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetDiffuse(Col4(0.5, 0.5, 0.5, 1));
	}
	//--------------------------------------------------------------------------------------
	//	class ColdBoxCollision : public GameObject;
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	ColdBoxCollision::ColdBoxCollision(const shared_ptr<Stage>& StagePtr,
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

	ColdBoxCollision::~ColdBoxCollision() {}

	//������
	void ColdBoxCollision::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		AddTag(L"ColdBox");
	}
}