#include "stdafx.h"
#include "Project.h"

namespace basecross {
	PlayerCamera::PlayerCamera()
		:m_Rad(0.0f),
		m_TargetToAt(0,0,0),
		m_ArmLen(5.0f)
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
		}
		else if (!(keyState.m_bPushKeyTbl[VK_LEFT] && keyState.m_bPushKeyTbl[VK_RIGHT])) {
			if (keyState.m_bPushKeyTbl[VK_RIGHT]) {
				m_Rad += 3.0f * elapsedTime;
			}
			if (keyState.m_bPushKeyTbl[VK_LEFT]) {
				m_Rad -= 3.0f * elapsedTime;
			}
		}

		Quat qtXZ;
		qtXZ.rotation(m_Rad, bsm::Vec3(0.0f, 1.0f, 0.0f));
		qtXZ.normalize();

		Mat4x4 Mat;
		Mat.strTransformation(
			bsm::Vec3(1.0f, 1.0f, 1.0f),
			bsm::Vec3(0.0f, 0.0f, -1.0f),
			qtXZ
		);

		Vec3 posXZ = Mat.transInMatrix();
		//XZ‚Ì’l‚ª‚í‚©‚Á‚½‚Ì‚Å˜rŠp“x‚É‘ã“ü
		armVec.x = posXZ.x;
		armVec.z = posXZ.z;
		//˜rŠp“x‚ð³‹K‰»
		armVec.normalize();

		auto ptrTarget = GetTargetObject();
		if (ptrTarget) {
			//–ÚŽw‚µ‚½‚¢êŠ
			Vec3 toAt = ptrTarget->GetComponent<Transform>()->GetWorldMatrix().transInMatrix();
			toAt += m_TargetToAt;
			newAt = Lerp::CalculateLerp(GetAt(), toAt, 0, 1.0f, 1.0, Lerp::Linear);
		}

		Vec3 toEye = newAt + armVec;
		newEye = Lerp::CalculateLerp(GetEye(), toEye, 0.0f, 1.0f, 1.0f, Lerp::Linear);

		SetEye(newEye);
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
}