#pragma once
#include "stdafx.h"
#include <iostream>
#include <stdio.h>

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class IncreaseBox : public GameObject; マグマオブジェクト
	//--------------------------------------------------------------------------------------
	class IncreaseBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		int m_SaveIncreaseBoxNum;
		int m_SaveDirFlgNum;
		//判定を生成するかどうか
		bool m_Generateflg;
	public:
		//構築と破棄
		IncreaseBox(const shared_ptr<Stage>& StagePtr,const Vec3& Scale,const Vec3& Rotation,const Vec3& Position);
		IncreaseBox(const shared_ptr<Stage>& StagePtr,const Vec3& Scale,const Vec3& Rotation,const Vec3& Position, const int& num, const int& dirNum);
		virtual ~IncreaseBox();
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
		virtual void OnCollisionExcute(shared_ptr<GameObject>& Other) override;
		//初期化
		virtual void OnCreate() override;

		void SetGenerateflg(bool flg) {
			m_Generateflg = flg;
		}
	};
	
	//--------------------------------------------------------------------------------------
	//	class ObjectForFlowDecision : public GameObject; 流れ判定用オブジェクト
	//--------------------------------------------------------------------------------------
	class ObjectForFlowDecision : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		//判定する時間
		float m_Time;
		//判定を生成した元のオブジェクト
		shared_ptr<IncreaseBox> m_ParentObj;
	public:
		//構築と破棄
		ObjectForFlowDecision(const shared_ptr<Stage>& StagePtr,const Vec3& Scale,const Vec3& Rotation,const Vec3& Position);
		virtual ~ObjectForFlowDecision();
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
		virtual void OnCollisionExcute(shared_ptr<GameObject>& Other) override;
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void SetParentObj(const shared_ptr<GameObject>& Obj) {
			m_ParentObj = dynamic_pointer_cast<IncreaseBox>(Obj); 
		}
	};

	//--------------------------------------------------------------------------------------
	//	class ColdBox : public GameObject; 冷えたマグマオブジェクト
	//--------------------------------------------------------------------------------------
	class ColdBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

	public:

		//構築と破棄
		ColdBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);


		virtual ~ColdBox();
		//初期化
		virtual void OnCreate() override;
		//操作
	};

	//--------------------------------------------------------------------------------------
	//	class IncreaseObject: public GameObject; マグマの配置用
	//--------------------------------------------------------------------------------------
	const int XZDIRECTION = 5; //中央も含めた四方
	static int IncreaseObjectNum = 0;

	class IncreaseObject : public GameObject {
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
	public:
		IncreaseObject(const shared_ptr<Stage>& StagePtr, const Vec3& Position);
		IncreaseObject(const shared_ptr<Stage>& StagePtr, const Vec3& Position, const int& limitRange, const int& useDir);
		IncreaseObject(const shared_ptr<Stage>& StagePtr, const Vec3& Position, const int& limitRange, const int& useStartDir, const int& useEndDir);
		virtual ~IncreaseObject() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		int GetLimitRange() const {
			return m_Range;
		}
		int GetSaveIncreaseObjectNum() const {
			return m_SaveIncreaseObjectNum;
		}
		void SetGeneratableFlg(int index,bool flg) {
			m_GeneratableFlg[index] = flg;
		}
	};
}