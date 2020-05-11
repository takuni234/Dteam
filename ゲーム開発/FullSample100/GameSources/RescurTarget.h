#pragma once
#pragma once
#include "stdafx.h"

namespace basecross {
	//ã~èoëŒè€ÉxÅ[ÉX
	class RescurTarget_Base :public GameObject {
		Vec3 m_Position, m_Scale, m_Rotation;

	public:
		RescurTarget_Base(const shared_ptr<Stage>& stage, Vec3 pos, Vec3 scale, Vec3 rotate);
		~RescurTarget_Base() {}

		void OnCreate() override;
		void OnUpdate() override;
		float INPLAYERLANGSE();
		bool OUTPLAYER_CALL();
		Vec3 PlayerPos();
		void PLAYERCHASE();
		bool MoveSwitch();

		bool INFlg = false;
	};

	//ì¡éÍãZî\ÇéùÇΩÇ»ã~èoëŒè€
	class RescurNomalTarget :public GameObject {
		Vec3 m_Position, m_Scale, m_Rotation;
		bool INFlg = false;
	public:
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
	class RescurTarget_1 :public RescurTarget_Base {
		Vec3 m_Position, m_Scale, m_Rotation;
	public:
		RescurTarget_1(const shared_ptr<Stage>& stage, Vec3 pos, Vec3 scale, Vec3 rotate)
			:RescurTarget_Base(stage, pos, scale, rotate),
			m_Position(pos), m_Scale(scale), m_Rotation(rotate)
		{
		}
		~RescurTarget_1() {}

		void OnCreate() override;
		void OnUpdate() override;
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
	};





}