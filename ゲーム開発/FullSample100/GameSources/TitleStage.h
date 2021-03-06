/*!
@file TitleStage.h
@brief タイトルステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	タイトルステージクラス
	//--------------------------------------------------------------------------------------
	class TitleStage : public Stage {
		float m_Time;
		//ビューの作成
		void CreateViewLight();
		//スプライト作成
		void CreatePushSprite();

		void CreateSprite();
		shared_ptr<SoundItem> m_BGM;
	public:
		//構築と破棄
		TitleStage() :Stage(), m_Time(0.0f) {}
		virtual ~TitleStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;
	};
}
//end basecross

