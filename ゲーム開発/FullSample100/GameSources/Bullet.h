#pragma once
#include "stdafx.h"

namespace basecross {
	//放水用のオブジェクト
	class Bullet : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		Vec3 m_MoveDir;
		float m_Speed;
		bool m_Hit;
		float m_ExistenceTime;
		float m_Time;
	public:
		Bullet(const shared_ptr<Stage>& StagePtr, const Vec3& ScalePtr, const Vec3& RotPtr, const Vec3& PosPtr, const Vec3& MoveDirPtr, const float& SpeedPtr);
		virtual ~Bullet();
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
		//弾のリセット
		void Reset(const Vec3& rot, const Vec3& pos, const Vec3& moveDirPtr);
	};
}