/*!
@file TitleStage.h
@brief �^�C�g���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�^�C�g���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class TitleStage : public Stage {
		float m_Time;
		//�r���[�̍쐬
		void CreateViewLight();
		//�X�v���C�g�쐬
		void CreatePushSprite();

		void CreateSprite();
		shared_ptr<SoundItem> m_BGM;
	public:
		//�\�z�Ɣj��
		TitleStage() :Stage(), m_Time(0.0f) {}
		virtual ~TitleStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;
	};
}
//end basecross

