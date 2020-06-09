/*!
@file StageSelect.h
@brief ステージセレクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	ステージセレクトクラス
	//--------------------------------------------------------------------------------------
	class StageSelect : public Stage {
		//ビューの作成
		void CreateViewLight();
		shared_ptr<SoundItem> m_BGM;
		int m_SelectNum;
		SelectKey m_SelectKey;
		//入力判定フラグ
		bool m_InputOnce;
		float m_InputTime;
		//カーソルのサイズ
		Vec2 m_ArrowCursorScale;
		float m_RCursorTime;
		float m_LCursorTime;
		//CSV読み込み用
		CsvFile m_CsvFile;

		void CreateSelectSprite();
		//入力から選択カーソルを移動
		void StageSelectKeyInput();
		void UpdateSpriteTX();
		void ChangeStageSceneSelected();
		void SetCSVKey();
		int GetObjCountInCSV(const wstring& key);
	public:
		//構築と破棄
		StageSelect() :Stage(), m_SelectKey(SelectKey(0)), m_InputOnce(false), m_InputTime(0.0f), m_ArrowCursorScale(100.0f), m_RCursorTime(0.0f) {}
		virtual ~StageSelect() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;
	};
}
//end basecross

