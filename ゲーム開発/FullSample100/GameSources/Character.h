/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"
#include <iostream>
#include <stdio.h>

namespace basecross{
	//--------------------------------------------------------------------------------------
	//	class FixedBox : public GameObject;
	//--------------------------------------------------------------------------------------
	class FixedBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		//�\�z�Ɣj��
		FixedBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~FixedBox();
		//������
		virtual void OnCreate() override;
		//����
	};

	//--------------------------------------------------------------------------------------
//	class IncreaseBox : public GameObject;
//--------------------------------------------------------------------------------------
	class IncreaseBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

	public:
		int check;
		//�\�z�Ɣj��
	IncreaseBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		//virtual int checkkansu();
		void OnCollisionEnter(shared_ptr<GameObject>& Other);
		

		virtual ~IncreaseBox();
		//������
		virtual void OnCreate() override;
		//����
	};
	//--------------------------------------------------------------------------------------
//	class ColdBox : public GameObject;
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
	//	class IncreaseObject: public GameObject;
	//--------------------------------------------------------------------------------------

	class IncreaseObject : public GameObject {
		Vec3 m_Vec3;
		int count;
		int time;
		int x;
		int z;
		int randomx;
		int randomz;
		Vec3 m_Position;
		//weak_ptr<StageCellMap> m_CelMap;

	public:
		IncreaseObject(const shared_ptr<Stage>& StagePtr,
			const Vec3& Position
		);
		virtual ~IncreaseObject();
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

	};


	//--------------------------------------------------------------------------------------
	//	class FixedSphere : public GameObject;
	//--------------------------------------------------------------------------------------
	class FixedSphere : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		//�\�z�Ɣj��
		FixedSphere(const shared_ptr<Stage>& StagePtr,
			const float Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~FixedSphere();
		//������
		virtual void OnCreate() override;
		//����
	};

	//--------------------------------------------------------------------------------------
	//	class FixedCapsule : public GameObject;
	//--------------------------------------------------------------------------------------
	class FixedCapsule : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		//�\�z�Ɣj��
		FixedCapsule(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~FixedCapsule();
		//������
		virtual void OnCreate() override;
		//����
	};

	class AttackArea : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		AttackArea(const shared_ptr<Stage>& Stage, const Vec3& scale, const Vec3& rotation, const Vec3& position);
		virtual ~AttackArea(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
	};
}
//end basecross
