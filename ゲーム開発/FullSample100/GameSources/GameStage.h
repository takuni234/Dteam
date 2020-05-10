/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		shared_ptr<SoundItem> m_BGM;
		//�r���[�̍쐬
		void CreateViewLight();
		bool m_IsUpdate;

		//�Z���}�b�v�̍쐬
		void CreateStageCellMap();
		//�R�X�g���Z���}�b�v�ɔ��f
		void SetCellMapCost();

		InputHandler<GameStage> m_InputHandler;
	public:
		//�\�z�Ɣj��
		GameStage() :Stage(), m_IsUpdate(true) {}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate()override;
		virtual void UpdateStage() override;
		virtual void OnDestroy() override;

		void OnPushStart();
		void OnPushA(){}
		void OnPushB(){}
		void OnPushX(){}
		void OnPushY(){}
	};
}
//end basecross

