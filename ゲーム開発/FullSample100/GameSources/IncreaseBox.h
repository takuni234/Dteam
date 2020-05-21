#pragma once
#include "stdafx.h"
#include <iostream>
#include <stdio.h>

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class IncreaseBox : public GameObject; �}�O�}�I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	class IncreaseBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		int m_SaveIncreaseBoxNum;
		int m_SaveDirFlgNum;
		//����𐶐����邩�ǂ���
		bool m_Generateflg;
	public:
		//�\�z�Ɣj��
		IncreaseBox(const shared_ptr<Stage>& StagePtr,const Vec3& Scale,const Vec3& Rotation,const Vec3& Position);
		IncreaseBox(const shared_ptr<Stage>& StagePtr,const Vec3& Scale,const Vec3& Rotation,const Vec3& Position, const int& num, const int& dirNum);
		virtual ~IncreaseBox();
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
		virtual void OnCollisionExcute(shared_ptr<GameObject>& Other) override;
		//������
		virtual void OnCreate() override;

		void SetGenerateflg(bool flg) {
			m_Generateflg = flg;
		}
	};
	
	//--------------------------------------------------------------------------------------
	//	class ObjectForFlowDecision : public GameObject; ���ꔻ��p�I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	class ObjectForFlowDecision : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		//���肷�鎞��
		float m_Time;
		//����𐶐��������̃I�u�W�F�N�g
		shared_ptr<IncreaseBox> m_ParentObj;
	public:
		//�\�z�Ɣj��
		ObjectForFlowDecision(const shared_ptr<Stage>& StagePtr,const Vec3& Scale,const Vec3& Rotation,const Vec3& Position);
		virtual ~ObjectForFlowDecision();
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
		virtual void OnCollisionExcute(shared_ptr<GameObject>& Other) override;
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void SetParentObj(const shared_ptr<GameObject>& Obj) {
			m_ParentObj = dynamic_pointer_cast<IncreaseBox>(Obj); 
		}
	};

	//--------------------------------------------------------------------------------------
	//	class ColdBox : public GameObject; �₦���}�O�}�I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	class ColdBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

	public:

		//�\�z�Ɣj��
		ColdBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);


		virtual ~ColdBox();
		//������
		virtual void OnCreate() override;
		//����
	};

	//--------------------------------------------------------------------------------------
	//	class IncreaseObject: public GameObject; �}�O�}�̔z�u�p
	//--------------------------------------------------------------------------------------
	const int XZDIRECTION = 5; //�������܂߂��l��
	static int IncreaseObjectNum = 0;

	class IncreaseObject : public GameObject {
		Vec3 m_Position;
		//���ԏ����p
		float m_Time;
		float m_Interval;
		//�͈͏����p
		int m_Count;
		int m_LimitRange;
		int m_Range;
		//�������������p
		bool m_GeneratableFlg[XZDIRECTION];
		int m_SaveIncreaseObjectNum;
		//��������
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