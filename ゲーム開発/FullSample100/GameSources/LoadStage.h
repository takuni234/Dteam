/*!
@file LoadStage.h
@brief ロードステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	ロードステージクラス（ロード画面）
	//--------------------------------------------------------------------------------------
	class LoadStage : public Stage {
		//ビューの作成
		void CreateViewLight();
		//スプライトの作成
		void CreateTitleSprite();
		//リソースロード用のスレッド（スタティック関数）
		static void LoadResourceFunc();
		//リソースを読み込んだことを知らせるフラグ（スタティック変数）
		static bool m_Loaded;
		//ミューテックス
		static std::mutex mtx;
	public:
		//構築と破棄
		LoadStage() :Stage() {}
		virtual ~LoadStage() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;
	};

}