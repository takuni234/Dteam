/*!
@file Scene.h
@brief シーン
*/
#pragma once

#include "stdafx.h"

namespace basecross{
	//シーン遷移用
	enum class SceneKey : int {
		Title,
		Select,
		Game,
		Result,
		GameOver,
		Load,
		Max
	};

	//リザルトステージのメニュー用
	enum class ResultStageMenuKey : int{
		NextStage,
		Select,
		Retry,
		Title,
		Max
	};

	//ゲームオーバーステージのメニュー用
	enum class GameOverStageMenuKey : int{
		Select,
		Retry,
		Title,
		Max
	};	
	
	//ゲームステージのメニュー用
	enum class GameStageMenuKey : int{
		Retry,
		Select,
		Title,
		Max
	};

	//ステージ数
	enum class SelectKey : int{
		Stage1,
		Stage2,
		Stage3,
		Max
	};

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase{
		float m_LimitTime;
		int m_AllMember;
		int m_RescueCount;
		wstring m_StageCSVKey;
		SelectKey m_CurrentScene;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		Scene() :SceneBase(), m_LimitTime(0.0f){}
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Scene();
		//--------------------------------------------------------------------------------------
		/*!
		@brief 初期化
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief イベント取得
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnEvent(const shared_ptr<Event>& event) override;
		void ChangeScene(SceneKey key);

		//ゲッターセッター群
		float GetLimitTime() const {
			return m_LimitTime;
		}
		void SetLimitTime(float time) {
			m_LimitTime = time;
		}
		wstring GetStageCSVKey() const {
			return m_StageCSVKey;
		}
		void SetStageCSVKey(const wstring& key) {
			m_StageCSVKey = key;
		}
		void SetAllMember(const int& value) {
			m_AllMember = value;
		}
		int GetAllMember() const {
			return m_AllMember;
		}
		void SetRescueCount(const int& rescueCount) {
			m_RescueCount = rescueCount;
		}
		void AddRescueCount(const int& rescueCount) {
			m_RescueCount += rescueCount;
		}
		int GetRescueCount() const {
			return m_RescueCount;
		}
		SelectKey GetCurrentSceneKey() const {
			return m_CurrentScene;
		}
		void SetCurrentSceneKey(const SelectKey& key) {
			m_CurrentScene = key;
		}
	};

}

//end basecross
