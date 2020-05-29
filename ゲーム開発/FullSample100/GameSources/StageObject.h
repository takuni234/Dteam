#pragma once
#pragma once
#include "stdafx.h"

namespace basecross {
	//////////////////////////////
	class Rock :public GameObject {
		bool flg;
		Vec3 m_Position, m_Scale, m_Rotation;
	public:
		Rock(const shared_ptr<Stage>& stage, Vec3 pos, Vec3 scale, Vec3 rotate)
			: GameObject(stage), m_Position(pos), m_Scale(scale), m_Rotation(rotate), flg(false) {

		}
		~Rock() {}

		void OnCreate() override;
		void OnUpdate() override;
		void OnCollisionEnter(shared_ptr<GameObject>& obj);
	};
	class ObjRock :public GameObject {
		Vec3 m_Position, m_Scale, m_Rotation;
		//à íuÇ∏ÇÍëŒçÙóp
		Vec3 m_SaveRot;
		Vec3 m_SavePos;
		bool m_Arrangement;

		wstring Tx_name;
		bool FallFlg;
	public:
		ObjRock(const shared_ptr<Stage>& stage, Vec3 pos, Vec3 scale, Vec3 rotate, wstring name,bool fallFlg)
			: GameObject(stage),
			m_Position(pos), m_Scale(scale), m_Rotation(rotate),
			m_SaveRot(rotate), m_SavePos(pos),
			m_Arrangement(false), 
			Tx_name(name), FallFlg(fallFlg){

		}
		~ObjRock() {}

		void OnCreate() override;
		void OnUpdate() override;
		virtual void OnUpdate2() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other)override;
		virtual void OnCollisionExcute(shared_ptr<GameObject>& Other)override;
	};
	class CollisionBox :public GameObject {
		Vec3 m_Position, m_Scale, m_Rotation;
	public:
		CollisionBox(const shared_ptr<Stage>& stage, Vec3 pos, Vec3 scale, Vec3 rotate)
			: GameObject(stage), m_Position(pos), m_Scale(scale), m_Rotation(rotate) {

		}
		~CollisionBox() {}

		void OnCreate() override;

	};

	class Obj_Cinder :public GameObject {
		Vec3 m_Position;
		float time = 0;
		bool AddFlg = false;
		int UpNO;
	public:
		Obj_Cinder(const shared_ptr<Stage>& stage,Vec3 Pos,int UpRNo)
			:GameObject(stage),m_Position(Pos),UpNO(UpRNo){}
		~Obj_Cinder(){}
		 
		void OnCreate() override;
		void OnUpdate() override;
	};
	
}