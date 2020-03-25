#pragma once
#pragma once
#include "stdafx.h"

namespace basecross {
	//“Áê‹Z”\‚ğ‚½‚È‚¢‹~o‘ÎÛ
	class RescurNomalTarget :public GameObject {
		Vec3 m_Position, m_Scale, m_Rotation;
	public :
		RescurNomalTarget(const shared_ptr<Stage>& stage, Vec3 pos, Vec3 scale, Vec3 rotate);
		~RescurNomalTarget() {}

		void OnCreate() override;
		void OnUpdate() override;
	};
}
