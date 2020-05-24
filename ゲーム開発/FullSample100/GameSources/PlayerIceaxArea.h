#pragma once
#include "stdafx.h"
#include <iostream>
#include <stdio.h>
namespace basecross {
	class AttackArea : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		shared_ptr<SoundItem> m_SE;
		bool m_SEflg;
		bool m_Hit;
		float m_Time;
		bool m_Once;
		shared_ptr<GameObject> m_DestructionReservationObj;
	public:
		AttackArea(const shared_ptr<Stage>& Stage, const Vec3& scale, const Vec3& rotation, const Vec3& position);
		virtual ~AttackArea() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

		void ResetAttackFlg() {
			m_SEflg = false;
			m_Hit = false;
			m_Time = 0.0f;
			m_Once = false;
		}
	};
}