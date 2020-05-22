#pragma once
#include "stdafx.h"

namespace basecross {
	class Enemy :public GameObject {
		Vec3 m_Position, m_Scale, m_Rotation;
		float Speed, MaxSpeed = 5;
		bool InFlg;
		float time, changetime;
		float posX,posZ;
		Vec3 position;
	public:
		Enemy(const shared_ptr<Stage>& stage, Vec3 pos, Vec3 scale, Vec3 rot);
		~Enemy(){}
		int atime;

		void OnCreate() override;
		void OnUpdate() override;
		void RayEye();
		Vec3 RandomPos();
		void FREEMOVE();
		void E_PLAYERCHACE();
		Vec3 PlayerPos();
		float Acceleration();
		void Attack();
		float Time(){
			return time += App::GetApp()->GetElapsedTime();
		}
		void OnCollisionEnter(const shared_ptr<GameObject> obj);
			
	};
}