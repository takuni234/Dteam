/*!
@file CopyrightInfoStage.h
@brief ���쌠���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	���쌠���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class CopyrightInfoStage : public Stage {
		float m_Alpha;
		float m_Fade;
		float m_FadeSpeed;
		bool m_FadeIn;
		float m_Time;
		//�r���[�̍쐬
		void CreateViewLight();

		void CreateSprite();
	public:
		//�\�z�Ɣj��
		CopyrightInfoStage() :Stage(), m_Alpha(1.0f), m_Fade(false), m_FadeSpeed(0.5f), m_FadeIn(false), m_Time(0.0f) {}
		virtual ~CopyrightInfoStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;
	};
}
//end basecross

