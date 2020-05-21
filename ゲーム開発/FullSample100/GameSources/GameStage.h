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
		//CSV
		CsvFile csvfile_1;
		CsvFile csvfile_2;
		CsvFile ObjCsvfile;
		void CreateObjectACSV();
		void CreateObjectB_CSV();
		//�X�R�A�X�v���C�g�쐬
		void CreateScoreSprite();
		//�ǖ͗l�̃X�v���C�g�쐬
		void CreatePushSprite();

		//�g�[�^������
		float m_TotalTime;


		shared_ptr<SoundItem> m_BGM;
		//�r���[�̍쐬

		void CreateViewLight();
		bool m_IsUpdate;

		Vec3 PlayerPos;

		InputHandler<GameStage> m_InputHandler;
	public:

		//�\�z�Ɣj��
		GameStage() :Stage(), m_IsUpdate(true),m_TotalTime(0) {}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		virtual void UpdateStage() override;
		virtual void OnDestroy() override;

		void OnPushStart();
		void OnPushA(){}
		void OnPushB(){}
		void OnUpB(){}
		void OnPushX(){}
		void OnUpX(){}
		void OnPushY(){}
		void OnUpY() {}
	};
}
//end basecross

