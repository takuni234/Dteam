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

		bool Goalflg = false;
		bool GameEndflg = false;
		int GoalCount;
		int count;
		int EndCount;
	public:
		//ç\ízÇ∆îjä¸
		GoalObject(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			int Count
		);
		virtual ~GoalObject();
		//èâä˙âª
		virtual void OnCreate() override;
		//ëÄçÏ
		virtual void OnUpdate() override;
		void TargetCount() {
			auto ptrScene = App::GetApp()->GetScene<Scene>();
			ptrScene->AddRescueCount(1);
			count++;
		}
		void GameEndCount() {
			EndCount++ ;
		}
		bool GetGoalflg() { return Goalflg; }
		bool GetEndflg() { return GameEndflg; }
	};
}