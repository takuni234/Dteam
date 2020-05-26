#pragma once
#include "stdafx.h"
#include <iostream>
#include <stdio.h>

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class IncreaseBox2 : public GameObject; マグマオブジェクト(見た目のみ)
	//--------------------------------------------------------------------------------------
	class IncreaseBox2 : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		//構築と破棄
		IncreaseBox2(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);
		virtual ~IncreaseBox2();
		//初期化
		virtual void OnCreate() override;
	};

	//--------------------------------------------------------------------------------------
	//	class IncreaseBox2Collision : public GameObject; マグマオブジェクト(見た目のみ)
	//--------------------------------------------------------------------------------------
	class IncreaseBox2Collision : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		int m_SaveIncreaseBoxNum;
		int m_SaveDirFlgNum;
		//判定を生成するかどうか
		bool m_Generateflg;

		shared_ptr<BcPNTStaticDraw> m_DrawObj;
	public:
		//構築と破棄
		IncreaseBox2Collision(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);
		IncreaseBox2Collision(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position, bool& Generate);
		IncreaseBox2Collision(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position, const int& num, const int& dirNum);
		IncreaseBox2Collision(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position, const int& num, const int& dirNum, bool& Generate);
		virtual ~IncreaseBox2Collision();
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate2() override;

		void SetGenerateflg(bool flg) {
			m_Generateflg = flg;
		}
	};

	//--------------------------------------------------------------------------------------
	//	class ObjectForFlowDecision : public GameObject; 流れ判定用オブジェクト
	//--------------------------------------------------------------------------------------
	class ObjectForFlowDecision2 : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		//判定する時間
		float m_Time;
		//判定を生成した元のオブジェクト
		shared_ptr<IncreaseBox2Collision> m_ParentObj;
	public:
		//構築と破棄
		ObjectForFlowDecision2(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);
		virtual ~ObjectForFlowDecision2();
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
		virtual void OnCollisionExcute(shared_ptr<GameObject>& Other) override;
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void SetParentObj(const shared_ptr<GameObject>& Obj) {
			m_ParentObj = dynamic_pointer_cast<IncreaseBox2Collision>(Obj);
		}
	};

	//--------------------------------------------------------------------------------------
	//	class IncreaseObject2: public GameObject; マグマの配置用
	//--------------------------------------------------------------------------------------

	class IncreaseObject2 : public GameObject {
		Vec3 m_Position;
		//時間処理用
		float m_Time;
		float m_Interval;
		//範囲処理用
		int m_Count;
		int m_LimitRange;
		int m_Range;
		//生成制限処理用
		bool m_GeneratableFlg[XZDIRECTION];
		int m_SaveIncreaseObjectNum;
		//流す方向
		int m_UseStartDir;
		int m_UseEndDir;
		bool m_GenerateFlg;
	public:
		IncreaseObject2(const shared_ptr<Stage>& StagePtr, const Vec3& Position);
		IncreaseObject2(const shared_ptr<Stage>& StagePtr, const Vec3& Position, bool& generate);
		IncreaseObject2(const shared_ptr<Stage>& StagePtr, const Vec3& Position, const int& limitRange, const int& useDir);
		IncreaseObject2(const shared_ptr<Stage>& StagePtr, const Vec3& Position, const int& limitRange, const int& useStartDir, const int& useEndDir);
		IncreaseObject2(const shared_ptr<Stage>& StagePtr, const Vec3& Position, const int& limitRange, const int& useStartDir, const int& useEndDir, bool& generate);
		virtual ~IncreaseObject2() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		int GetLimitRange() const {
			return m_Range;
		}
		int GetSaveIncreaseObjectNum() const {
			return m_SaveIncreaseObjectNum;
		}
		void SetGeneratableFlg(int index, bool flg) {
			m_GeneratableFlg[index] = flg;
		}
	};
}