#pragma once
#pragma once
#include "stdafx.h"

namespace basecross {
	//ì¡éÍãZî\ÇéùÇΩÇ»ã~èoëŒè€
	class RescurNomalTarget :public GameObject {
		Vec3 m_Position, m_Scale, m_Rotation;
		bool INFlg = false;
	public :
		RescurNomalTarget(const shared_ptr<Stage>& stage, Vec3 pos, Vec3 scale, Vec3 rotate);
		~RescurNomalTarget() {}

		void OnCreate() override;
		void OnUpdate() override;
		float INPLAYERLANGSE();
		bool OUTPLAYER_CALL();
		Vec3 PlayerPos();
		void PLAYERCHASE();
		bool MoveSwitch();
	};

	//ì¡éÍãZî\éùÇøÇÃã~èoëŒè€
	//
	class RescurTarget_1 :public RescurNomalTarget {
		Vec3 m_Position, m_Scale, m_Rotation;
	public:
		RescurTarget_1(const shared_ptr<Stage>& stage, Vec3 pos, Vec3 scale, Vec3 rotate)
			:RescurNomalTarget(stage, pos, scale, rotate),
			m_Position(pos), m_Scale(scale), m_Rotation(rotate)
		{

		}
		void OnCreate() override;
		void OnUpdate() override;
		void BreakRock();
	};
	//
	class RescurTarget_2 :public RescurNomalTarget {
		Vec3 m_Position, m_Scale, m_Rotation;
	public:
		RescurTarget_2(const shared_ptr<Stage>& stage, Vec3 pos, Vec3 scale, Vec3 rotate)
			:RescurNomalTarget(stage, pos, scale, rotate),
			m_Position(pos), m_Scale(scale), m_Rotation(rotate)
		{

		}
		void OnCreate() override;
		void OnUpdate() override;
	};



//////////////////////////////
	class Rock :public GameObject {
		bool flg;
		Vec3 m_Position, m_Scale, m_Rotation;
	public :
		Rock(const shared_ptr<Stage>& stage, Vec3 pos, Vec3 scale, Vec3 rotate)
			: GameObject(stage), m_Position(pos), m_Scale(scale), m_Rotation(rotate),flg(false) {

		}
		~Rock(){}

		void OnCreate() override;
		void OnUpdate() override;
		void OnCollisionEnter(shared_ptr<GameObject>& obj);
	};
	class ObjRock :public GameObject {
		Vec3 m_Position, m_Scale, m_Rotation;
	public:
		ObjRock(const shared_ptr<Stage>& stage, Vec3 pos, Vec3 scale, Vec3 rotate)
			: GameObject(stage), m_Position(pos), m_Scale(scale), m_Rotation(rotate) {

		}
		~ObjRock() {}

		void OnCreate() override;
		void OnUpdate() override;
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

}
