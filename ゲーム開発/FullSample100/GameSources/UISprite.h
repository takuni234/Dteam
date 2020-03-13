
/*!
@file UISprite.h
@brief UI用のスプライトなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	連番アニメスプライト
	//--------------------------------------------------------------------------------------
	class SerialAnimeSprite : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
		uint32_t m_PieceXCount;
		uint32_t m_PieceYCount;
		uint32_t m_PieceIndex;
		float m_AnimeTime;
		wstring m_TextureKey;
		//トータル時間
		float m_TotalTime;
		//バックアップ頂点データ
		vector<VertexPositionColorTexture> m_BackupVertices;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		@param[in]	StagePtr	ステージ
		@param[in]	TextureKey	テクスチャキー
		@param[in]	Trace	透明処理するかどうか
		@param[in]	StartScale	初期スケール
		@param[in]	StartPos	初期位置
		@param[in]	PieceXCount	X方向の片数
		@param[in]	PieceYCount	Y方向の片数
		@param[in]	AnimeTime	1つの片の表示時間
		*/
		//--------------------------------------------------------------------------------------
		SerialAnimeSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos, uint32_t PieceXCount, uint32_t PieceYCount,
			float AnimeTime);
		//破棄
		virtual ~SerialAnimeSprite();
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate()override;
	};
}