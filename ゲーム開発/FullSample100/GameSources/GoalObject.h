#pragma once
#include "stdafx.h"
#include <iostream>
#include <stdio.h>

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class GoalObject : public GameObject;
	//--------------------------------------------------------------------------------------
	class GoalObject : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		bool flg = false;
		int GoalCount;
		int count;
	public:
		//�\�z�Ɣj��
		GoalObject(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			int Count
		);
		virtual ~GoalObject();
		//������
		virtual void OnCreate() override;
		//����
		virtual void OnUpdate() override;
		void TargetCount() {
			count++;
		}
		bool Getflg() { return flg; }
	};
}