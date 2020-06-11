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
		//トータル時間
		float m_TotalTime;
		float m_MAXTIME;

		bool m_IsUpdate;

		//CSV
		CsvFile csvfile_1;
		CsvFile csvfile_2;
		CsvFile ObjCsvfile;

		//BGM
		shared_ptr<SoundItem> m_BGM;
		shared_ptr<SoundItem> m_RescueBGM;
		//カメラ用
		//OpeningCamera用のビュー
		shared_ptr<SingleView> m_OpeningCameraView;
		//PlayerCamera用のビュー
		shared_ptr<SingleView> m_PlayerCameraView;
		CameraSelect m_CameraSelect;

		Vec3 PlayerPos;
		Vec3 GoalPos;
		Vec3 GoalRot;
		Vec3 magumaPos;
		Vec3 StagePos, StageScale;
		Vec2 StageWallScale;
		
		//インプットハンドラー
		InputHandler<GameStage> m_InputHandler;

		//空色
		Col4 m_Color = Col4(144.0f / 255.0f, 215.0f / 255.0f, 236.0f / 255.0f, 1.0f);
		//噴火時の空色
		Col4 m_Color1 = Col4(87.0f / 255.0f, 56.0f / 255.0f, 38.0f / 255.0f, 1.0f);
		
		//ポーズメニューのスプライトをそろえるか
		bool m_SpriteAlign;
		vector<Vec3> m_PauseMenuSpriteDefultScale;
		vector<Vec3> m_PauseMenuSpritePos;
		bool m_InputOnce;
		int m_SelectNum;
		float m_MenuKeyInputTime;
		GameStageMenuKey m_MenuKey;

		//ビューの作成
		void CreateViewLight();
		//CSV読込
		void CreateObjectB_CSV();
		//スコアスプライト作成
		void CreateScoreSprite();
		//ポーズメニュー作成
		void CreatePauseSprite();
		//木の作成
		void CreateTreeObjects(const Vec2& mapSize, const Vec3& stageSize);
		//HPバーの作成
		void CreateHPSprite();
		//背景色を変更する
		void SetBackGroundColor(Col4 color);
		//設定した高度に合わせて背景色を変更する
		void SetBackGroundPlayerPosColor(Col4 posZero, Col4 posMax, float posSizeMax);
		//カメラマンの作成
		void CreateCameraman();
		//煙の作成
		void CreateSmoke();
		//ポーズメニューのキー操作
		void GameStageMenuKeyInput();
		void UpdateCursor();
		void ChangeStageSceneSelected();
	public:

		//構築と破棄
		GameStage() :Stage(), m_IsUpdate(true),m_TotalTime(App::GetApp()->GetScene<Scene>()->GetLimitTime()), m_MAXTIME(m_TotalTime) {}
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
		void LowCountTarget() { GoalCount -= 1; }
		void SetGoalCount(int goal) { GoalCount = goal; }
		int GetGoalCount() { return GoalCount; }
		void StageChange();

		void OnPushStart();
		void OnPushA();
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

