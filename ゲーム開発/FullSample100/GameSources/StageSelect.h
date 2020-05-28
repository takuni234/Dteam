/*!
@file StageSelect.h
@brief �X�e�[�W�Z���N�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	enum SelectKey {
		Stage1,
		Stage2,
		Max
	};
	//--------------------------------------------------------------------------------------
	//	�X�e�[�W�Z���N�g�N���X
	//--------------------------------------------------------------------------------------
	class StageSelect : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		shared_ptr<SoundItem> m_BGM;
		int m_SelectNum;
		SelectKey m_SelectKey;
		//���͔���t���O
		bool m_InputOnce;
		float m_Time;

		void CreateSelectSprite();
		//���͂���I���J�[�\�����ړ�
		void StageSelectKeyInput();
		void UpdateSpriteTX();
		void ChangeStageSceneSelected();
	public:
		//�\�z�Ɣj��
		StageSelect() :Stage(), m_SelectKey(SelectKey::Stage1), m_InputOnce(false), m_Time(0.0f) {}
		virtual ~StageSelect() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;
	};
}
//end basecross

