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

		bool flg;
		int count;
	public:
		//ç\ízÇ∆îjä¸
		GoalObject(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~GoalObject();
		//èâä˙âª
		virtual void OnCreate() override;
		//ëÄçÏ
		virtual void OnUpdate() override;
		void TargetCount() {
			count++;
		}
	};
}