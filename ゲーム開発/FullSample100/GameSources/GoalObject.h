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
		bool swithFlg = false;
		int GoalCount=0;
		int count=0;
		int EndCount=0;
		int TargetEndCount = 0;
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
		void BadTargetCount() {
			count--;
		}
		void GameEndCount() {
			EndCount++;
		}
		void BadGoalCount() {
			if(GoalCount >1)
			GoalCount--;
		}
		bool GetGoalflg() { return Goalflg; }
		bool GetEndflg() { return GameEndflg; }
		void SetEndflg(const bool flg) { GameEndflg = flg; }
	};
}