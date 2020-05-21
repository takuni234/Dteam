#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Bullet::Bullet(const shared_ptr<Stage>& StagePtr, const Vec3& ScalePtr, const Vec3& RotPtr, const Vec3& PosPtr, const Vec3& MoveDirPtr, const float& SpeedPtr)
		:GameObject(StagePtr),
		m_Scale(ScalePtr),
		m_Rotation(RotPtr),
		m_Position(PosPtr),
		m_MoveDir(MoveDirPtr),
		m_Speed(SpeedPtr),
		m_Hit(false),
		m_ExistenceTime(0.5f),
		m_Time(0.0f)
	{}

	Bullet::~Bullet(){}

	void Bullet::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		auto gravPtr = AddComponent<Gravity>();

		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		ptrDraw->SetTextureResource(L"SKY_TX");

		AddComponent<CollisionSphere>();

		auto group = GetStage()->GetSharedObjectGroup(L"PlayerBullet");
		group->IntoGroup(GetThis<GameObject>());

		AddTag(L"Bullet");
	}

	void Bullet::OnUpdate() {
		auto ptrTrans = GetComponent<Transform>();
		if (ptrTrans->GetPosition().y > -10.0f) {
			auto elapsedTime = App::GetApp()->GetElapsedTime();
			if (m_Hit) {
				m_Time += elapsedTime;
				if (m_Time >= m_ExistenceTime) {
					SetDrawActive(false);
					SetUpdateActive(false);
				}
			}
			Vec3 newPos = Vec3(ptrTrans->GetPosition() + m_MoveDir * m_Speed * elapsedTime);
			ptrTrans->SetPosition(newPos);
		}
		else {
			SetDrawActive(false);
			SetUpdateActive(false);
		}
	}

	void Bullet::Reset(const Vec3& rot, const Vec3& pos, const Vec3& moveDirPtr) {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->ResetPosition(pos);
		auto ptrGrav = GetComponent<Gravity>();
		ptrGrav->SetGravityVerocityZero();
		m_Time = 0.0f;
		m_MoveDir = moveDirPtr;
		SetUpdateActive(true);
		SetDrawActive(true);
	}

	void Bullet::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		m_Hit = true;
	}
}