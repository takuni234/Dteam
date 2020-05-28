/*!
@file Scene.h
@brief シーン
*/
#pragma once

#include "stdafx.h"

namespace basecross{
	enum SceneKey {
		Title,
		Select,
		Game,
		Result,
		Load
	};
	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase{
		float m_LimitTime;
		wstring m_StageCSVKey;
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
	};

}

//end basecross
