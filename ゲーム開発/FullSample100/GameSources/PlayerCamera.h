/*!
@file PlayerCamera.h
@vrief カメラ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class PlayerCamera : public Camera {
		weak_ptr<GameObject> m_TargetObject;
		Vec3 m_TargetToAt;
		float m_Rad;
		//プレイヤーまでの距離
		float m_ArmLen;
	public:
		PlayerCamera();
		~PlayerCamera();

		virtual void OnUpdate() override;

		shared_ptr<GameObject> GetTargetObject() const;
		void SetTargetObject(const shared_ptr<GameObject>& Obj);
		void SetTargetToAt(const bsm::Vec3& v);
		virtual void SetAt(const bsm::Vec3& At)override;
		virtual void SetAt(float x, float y, float z)override;
	};
}
