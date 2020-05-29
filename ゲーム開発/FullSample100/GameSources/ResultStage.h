/*!
@file ResultStage.h
@brief リザルトステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	リザルトステージクラス
	//--------------------------------------------------------------------------------------
	class ResultStage : public Stage {
		float m_Time;
		int m_SelectNum;
		ResultStageMenuKey m_MenuKey;
		//入力判定フラグ
		bool m_InputOnce;
		vector<Vec3> m_ResultSpriteDefultScale;
		vector<Vec3> m_ResultSpritePos;
		void CreateViewLight();
		//スプライト作成
		void CreatePushSprite();

		void CreateSprite();
		shared_ptr<SoundItem> m_BGM;
		//入力から選択カーソルを移動
		void StageSelectKeyInput();
		void UpdateCursor();
		void ChangeStageSceneSelected();
	public:
		//構築と破棄
		ResultStage() :Stage(), m_Time(0.0f) {}
		virtual ~ResultStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;
	};
}
//end basecross

