/*!
@file CopyrightInfoStage.h
@brief 著作権情報ステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	著作権情報ステージクラス
	//--------------------------------------------------------------------------------------
	class CopyrightInfoStage : public Stage {
		float m_Alpha;
		float m_Fade;
		float m_FadeSpeed;
		bool m_FadeIn;
		float m_Time;
		//ビューの作成
		void CreateViewLight();

		void CreateSprite();
	public:
		//構築と破棄
		CopyrightInfoStage() :Stage(), m_Alpha(1.0f), m_Fade(false), m_FadeSpeed(0.5f), m_FadeIn(false), m_Time(0.0f) {}
		virtual ~CopyrightInfoStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;
	};
}
//end basecross

