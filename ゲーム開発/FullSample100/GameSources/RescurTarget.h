#pragma once
#pragma once
#include "stdafx.h"

namespace basecross {
	//����Z�\�������Ȃ��~�o�Ώ�
	class RescurNomalTarget :public GameObject {
		Vec3 m_Position, m_Scale, m_Rotation;
	public :
		RescurNomalTarget(const shared_ptr<Stage>& stage, Vec3 pos, Vec3 scale, Vec3 rotate);
		~RescurNomalTarget() {}

		void OnCreate() override;
		void OnUpdate() override;
	};
}
