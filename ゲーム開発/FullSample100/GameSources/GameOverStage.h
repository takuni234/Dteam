/*!
@file GameOverStage.h
@brief �Q�[���I�[�o�[�X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�Q�[���I�[�o�[�X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameOverStage : public Stage {
		float m_Time;
		int m_SelectNum;
		GameOverStageMenuKey m_MenuKey;
		//���͔���t���O
		bool m_InputOnce;
		//�X�v���C�g�����낦�邩
		bool m_SpriteAlign;
		vector<Vec3> m_ResultSpriteDefultScale;
		vector<Vec3> m_ResultSpritePos;
		void CreateViewLight();
		//�X�v���C�g�쐬
		void CreatePushSprite();

		void CreateSprite();
		shared_ptr<SoundItem> m_BGM;
		//���͂���I���J�[�\�����ړ�
		void StageSelectKeyInput();
		void UpdateCursor();
		void ChangeStageSceneSelected();
	public:
		//�\�z�Ɣj��
		GameOverStage() :Stage(), m_Time(0.0f), m_SpriteAlign(true) {}
		virtual ~GameOverStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;
	};
}
//end basecross

