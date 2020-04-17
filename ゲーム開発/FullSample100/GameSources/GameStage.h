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

		shared_ptr<SoundItem> m_BGM;
		//�r���[�̍쐬

		void CreateViewLight();
		bool m_IsUpdate;

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

