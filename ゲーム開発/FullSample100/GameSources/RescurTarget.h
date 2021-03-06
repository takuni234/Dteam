#pragma once
#pragma once
#include "stdafx.h"

namespace basecross {

	//�~�o�Ώۃx�[�X
	class RescurTarget_Base :public GameObject {
		Vec3 m_Position, m_Scale, m_Rotation;

	public:
		RescurTarget_Base(const shared_ptr<Stage>& stage, Vec3 pos, Vec3 scale, Vec3 rotate);
		~RescurTarget_Base() {}

		void OnCreate() override;
		void OnUpdate() override;
		float INGOALLENGTH();
		void INGOAL();
		float INPLAYERLANGSE();
		float INPLAYER(Vec3 target);
		bool OUTPLAYER_CALL();
		Vec3 PlayerPos();
		Vec3 GoalPos();
		void PLAYERCHASE();
		bool MoveSwitch();
		void HappyAction(float jumpforce);
		void DamegeAction(float jumpforce);
		
		bool INFlg;
		bool flg = true,SpliteFlg;
		bool LightFlg = false;
		bool Goalflg1, Goalflg2;
		bool Goal = false;
		bool HPflg = false;
		float time;
		float dathTime = 0, HappyTime = 0;
		int GoalInCount;
		int HP;

	};

	//����Z�\�������ȋ~�o�Ώ�
	//����Z�\�����̋~�o�Ώ�
	//
	class RescurTarget_1 :public RescurTarget_Base {
		Vec3 m_Position, m_Scale, m_Rotation;
		int moveChangeCost;
		float gratime;
	public:
		RescurTarget_1(const shared_ptr<Stage>& stage, Vec3 pos, Vec3 scale, Vec3 rotate)
			:RescurTarget_Base(stage, pos, scale, rotate),//help(stage, pos),
			m_Position(pos), m_Scale(scale), m_Rotation(rotate), moveChangeCost(0)
		{
		}
		~RescurTarget_1() {}

		void OnCreate() override;
		void OnUpdate() override;
		void OnCollisionEnter(shared_ptr<GameObject>& obj);
	};

	class RescurTarget_2 :public RescurTarget_Base {
		Vec3 m_Position, m_Scale, m_Rotation;
	public:
		RescurTarget_2(const shared_ptr<Stage>& stage, Vec3 pos, Vec3 scale, Vec3 rotate)
			:RescurTarget_Base(stage, pos, scale, rotate),
			m_Position(pos), m_Scale(scale), m_Rotation(rotate)
		{
		}
		~RescurTarget_2() {}

		void OnCreate() override;
		void OnUpdate() override;
		void OnCollisionEnter(shared_ptr<GameObject>& obj);

	};



	class box :public GameObject {
		Vec3 m_Position, m_Scale, m_Rotation;
	public:
		box(const shared_ptr<Stage>& stage, Vec3 pos, Vec3 scale, Vec3 rotate)
			: GameObject(stage), m_Position(pos), m_Scale(scale), m_Rotation(rotate) {

		}
		~box() {}

		void OnCreate() override;

	};

	class HelpSplite :public RescurTarget_Base {
		Vec3 Pos;
		Vec3 m_Scale;
		shared_ptr<MeshResource> mesh;
		Quat Billboard(const Vec3& Line) {
			Vec3 Temp = Line;
			Mat4x4 RotMatrix;
			Vec3 DefUp(0, 1.0f, 0);
			Vec2 TempVec2(Temp.x, Temp.z);
			if (TempVec2.length() < 0.1f) {
				DefUp = Vec3(0, 0, 1.0f);
			}
			Temp.normalize();
			RotMatrix = XMMatrixLookAtLH(Vec3(0, 0, 0), Temp, DefUp);
			RotMatrix.inverse();
			Quat Qt;
			Qt = RotMatrix.quatInMatrix();
			Qt.normalize();
			return Qt;
		}
		float time;
		float length;
	public:
		HelpSplite(const shared_ptr<Stage>& stage, Vec3 pos, Vec3 scale, Vec3 rot);
		~HelpSplite() {}

		void OnCreate() override;
		void OnUpdate() override;
	};


	class GameEndSplite :public GameObject {
		wstring Txname;
		float SceneChangeTime = 0;
		Vec2 m_Scale;
		Vec3 m_Position;
		Vec3 Pos;
		shared_ptr<MeshResource> mesh;
		Quat Billboard(const Vec3& Line) {
			Vec3 Temp = Line;
			Mat4x4 RotMatrix;
			Vec3 DefUp(0, 1.0f, 0);
			Vec2 TempVec2(Temp.x, Temp.z);
			if (TempVec2.length() < 0.1f) {
				DefUp = Vec3(0, 0, 1.0f);
			}
			Temp.normalize();
			RotMatrix = XMMatrixLookAtLH(Vec3(0, 0, 0), Temp, DefUp);
			RotMatrix.inverse();
			Quat Qt;
			Qt = RotMatrix.quatInMatrix();
			Qt.normalize();
			return Qt;
		}
		float time;
	public:
		GameEndSplite(const shared_ptr<Stage>& stage, Vec3 pos, Vec2 scale, Vec3 rot,wstring name);
		~GameEndSplite() {}

		void OnCreate() override;
		void OnUpdate() override;
	};
}