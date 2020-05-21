#pragma once
#include "Project.h"

namespace basecross {
	class TraceSprite : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		float m_TotalTime;

		float m_Gauge;
		//バックアップ頂点データ
		vector<VertexPositionColor> m_BackupVertices;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		@param[in]	StagePtr	ステージ
		@param[in]	Trace	透明処理するかどうか
		@param[in]	StartScale	初期スケール
		@param[in]	StartPos	初期位置
		*/
		//--------------------------------------------------------------------------------------
		TraceSprite(const shared_ptr<Stage>& StagePtr, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~TraceSprite();
		//--------------------------------------------------------------------------------------
		/*!
		@brief 初期化
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief 更新
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;
		float GetGauge() {
			return m_Gauge;
		}
		void SetGauge(float gauge) {
			m_Gauge = gauge;
		}

	};

	//--------------------------------------------------------------------------------------
///	プッシュのスクリプト
//--------------------------------------------------------------------------------------
	class PushSprite : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;
		//トータル時間
		float m_TotalTime;

	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		@param[in]	StagePtr	ステージ
		@param[in]	TextureKey	テクスチャキー
		@param[in]	Trace	透明処理するかどうか
		@param[in]	StartScale	初期スケール
		@param[in]	StartPos	初期位置
		*/
		//--------------------------------------------------------------------------------------
		PushSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~PushSprite();
		//--------------------------------------------------------------------------------------
		/*!
		@brief 初期化
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief 更新
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;
	};

}