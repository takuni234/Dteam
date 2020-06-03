/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	enum class CameraSelect {
		openingCamera,
		playerCamera
	};

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		bool GameEndFlg = false;
		bool TimeUpFlg = false;
		int GoalCount = 0;
		//CSV
		CsvFile csvfile_1;
		CsvFile csvfile_2;
		CsvFile ObjCsvfile;
		void CreateObjectB_CSV();
		//スコアスプライト作成
		void CreateScoreSprite();
		//HPバーの作成
		void CreateHPSprite();
		//トータル時間
		float m_TotalTime;


		shared_ptr<SoundItem> m_BGM;
		//ビューの作成

		void CreateViewLight();
		bool m_IsUpdate;

		Vec3 PlayerPos;
		Vec3 GoalPos;
		Vec3 magumaPos;
		Vec3 StagePos, StageScale;
		//空色
		Col4 m_Color = Col4(144.0f / 255.0f, 215.0f / 255.0f, 236.0f / 255.0f, 1.0f);
		//噴火時の空色
		Col4 m_Color1 = Col4(87.0f/255.0f,56.0f/255.0f, 38.0f/255.0f, 1.0f);

		//背景色を変更する
		void SetBackGroundColor(Col4 color);
		//設定した高度に合わせて背景色を変更する
		void SetBackGroundPlayerPosColor(Col4 posZero, Col4 posMax, float posSizeMax);

		//カメラ用
		//OpeningCamera用のビュー
		shared_ptr<SingleView> m_OpeningCameraView;
		//PlayerCamera用のビュー
		shared_ptr<SingleView> m_PlayerCameraView;
		CameraSelect m_CameraSelect;
		//カメラマンの作成
		void CreateCameraman();

		InputHandler<GameStage> m_InputHandler;
	public:

		//構築と破棄
		GameStage() :Stage(), m_IsUpdate(true),m_TotalTime(App::GetApp()->GetScene<Scene>()->GetLimitTime()) {}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		virtual void UpdateStage() override;
		virtual void OnDestroy() override;

		void ToPlayerCamera();
		CameraSelect GetCameraSelect() const {
			return m_CameraSelect;
		}
		bool GetEndFlg() { return TimeUpFlg; }
		void StageChange();

		void OnPushStart();
		void OnPushA(){}
		void OnUpA(){}
		void OnPushB(){}
		void OnUpB(){}
		void OnPushX(){}
		void OnUpX(){}
		void OnPushY(){}
		void OnUpY() {}
	};
}
//end basecross

