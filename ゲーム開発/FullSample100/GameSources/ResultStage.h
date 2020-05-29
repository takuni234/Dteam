/*!
@file ResultStage.h
@brief ���U���g�X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	���U���g�X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class ResultStage : public Stage {
		float m_Time;
		int m_SelectNum;
		ResultStageMenuKey m_MenuKey;
		//���͔���t���O
		bool m_InputOnce;
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
		ResultStage() :Stage(), m_Time(0.0f) {}
		virtual ~ResultStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;
	};
}
//end basecross

