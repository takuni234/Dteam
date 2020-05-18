#pragma once
#include "stdafx.h"
#include <iostream>
#include <stdio.h>

namespace basecross {
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
}