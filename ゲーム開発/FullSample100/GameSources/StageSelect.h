/*!
@file StageSelect.h
@brief ステージセレクト
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
		float m_Time;

		void CreateSelectSprite();
		//入力から選択カーソルを移動
		void StageSelectKeyInput();
		void UpdateSpriteTX();
		void ChangeStageSceneSelected();
	public:
		//構築と破棄
		StageSelect() :Stage(), m_SelectKey(SelectKey::Stage1), m_InputOnce(false), m_Time(0.0f) {}
		virtual ~StageSelect() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;
	};
}
//end basecross

