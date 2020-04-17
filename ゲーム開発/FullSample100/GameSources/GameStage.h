/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//CSV
		CsvFile csvfile_1;
		CsvFile csvfile_2;
		CsvFile ObjCsvfile;
		void CreateObjectACSV();
		void CreateObjectB_CSV();

		shared_ptr<SoundItem> m_BGM;
		//ビューの作成

		void CreateViewLight();
		bool m_IsUpdate;

		InputHandler<GameStage> m_InputHandler;
	public:
		//構築と破棄
		GameStage() :Stage(), m_IsUpdate(true) {}
		virtual ~GameStage() {}
		//初期化
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

