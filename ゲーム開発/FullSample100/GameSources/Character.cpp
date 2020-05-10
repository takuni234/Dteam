/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"
namespace basecross{
	//--------------------------------------------------------------------------------------
	//	class FixedBox : public GameObject;
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	FixedBox::FixedBox(const shared_ptr<Stage>& StagePtr,
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
	FixedBox::~FixedBox() {}

	//������
	void FixedBox::OnCreate() {
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
		ptrDraw->SetTextureResource(L"SKY_TX");
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);

	}
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
		m_Position(Position)
	{
	}

	IncreaseBox::~IncreaseBox() {}

	//������
	void IncreaseBox::OnCreate() {
		check = 0;
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//OBB�Փ�j�����t����
		auto ptrColl = AddComponent<CollisionObb>();
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
		ptrDraw->SetDiffuse(Col4(1, 0, 0, 1));



	}
	//int IncreaseBox::checkkansu() {
	//	return check;
	//}
	void IncreaseBox::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Bullet")) {
				SetDrawActive(false);
				SetUpdateActive(false);
				auto posTarget = GetComponent<Transform>()->GetPosition();
				GetStage()->AddGameObject<ColdBox>(Vec3(0.2), Vec3(0), Vec3(posTarget));

		}

		check = 1;
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

	//--------------------------------------------------------------------------------------
	//	class FixedSphere : public GameObject;
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	FixedSphere::FixedSphere(const shared_ptr<Stage>& StagePtr,
		const float Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{
	}
	FixedSphere::~FixedSphere() {}

	//������
	void FixedSphere::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//CollisionSphere�Փ�j�����t����
		auto ptrColl = AddComponent<CollisionSphere>();
		ptrColl->SetFixed(true);
		//�^�O������
		AddTag(L"FixedSphere");
		//�e������i�V���h�E�}�b�v��`�悷��j
		auto shadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		shadowPtr->SetMeshResource(L"DEFAULT_SPHERE");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		ptrDraw->SetTextureResource(L"SKY_TX");
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);

	}

	//--------------------------------------------------------------------------------------
	//	class FixedCapsule : public GameObject;
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	FixedCapsule::FixedCapsule(const shared_ptr<Stage>& StagePtr,
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
	FixedCapsule::~FixedCapsule() {}

	//������
	void FixedCapsule::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//CAPSULE�Փ�j�����t����
		auto ptrColl = AddComponent<CollisionCapsule>();
		ptrColl->SetFixed(true);
		//�^�O������
		AddTag(L"FixedCapsule");
		//�e������i�V���h�E�}�b�v��`�悷��j
		auto shadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		shadowPtr->SetMeshResource(L"DEFAULT_CAPSULE");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CAPSULE");
		ptrDraw->SetTextureResource(L"SKY_TX");
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);
	}

	//--------------------------------------------------------------------------------------
	//	class IncreaseObject: public GameObject;
	//--------------------------------------------------------------------------------------
	IncreaseObject::IncreaseObject(const shared_ptr<Stage>& StagePtr ,const Vec3& Position):GameObject(StagePtr),m_Position(Position) ,count(0),x(0),z(0){}
	IncreaseObject::~IncreaseObject(){}
	void IncreaseObject::OnCreate(){

	}
	void IncreaseObject::OnUpdate() {
		if (count != 4) {
			//for (int i = 0; i < 5; i++) {
			if (time == 60) {	
				//randomx = rand() % 3-1;
				//randomz = rand() % 3-1;
				//if (!(randomx == 0 && randomz == 0)) {
				//	x = x + randomx;
					//z = z + randomz;
				//}
				
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x+0)*0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 0)*0.2));
				z ++;

				count++;
				//time = 0;
			}	

			if (time == 120) {

				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -1) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 0)*0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 1) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 0)*0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -1) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 1)*0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 0) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 1)*0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 1) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 1)*0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -1) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -1)*0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 0) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -1)*0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 1) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -1)*0.2));

				z++;

				count++;
				//time = 0;
			}
			if (time == 180) {

				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 2) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 0) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -2) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 0) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 2) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 1) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -2)* 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 1) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 2) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -1) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -2) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -1) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 2) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 2) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -2) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 2) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 2) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -2) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -2) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -2) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 0) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 2) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 0) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -2) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 1) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 2) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 1) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -2) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -1) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 2) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -1) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -2) * 0.2));
				z++;

				count++;
				//time = 0;
			}
			if (time == 240) {

				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 3) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 0) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -3) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 0) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 3) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 1) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -3) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 1) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 3) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -1) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -3) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -1) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 3) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 2) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -3) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 2) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 3) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -2) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -3) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -2) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 3) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 3) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -3) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 3) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 3) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -3) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -3)* 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -3) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 0) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 3) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 0) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -3) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 1) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 3) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 1) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -3) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -1) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 3) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -1) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -3) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 2) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 3) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 2) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -3) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -2) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 3) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -2) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -3) * 0.2));
				z++;

				count++;
				//time = 0;
			}

			time++;

			//}
		}

	}

}
//end basecross
