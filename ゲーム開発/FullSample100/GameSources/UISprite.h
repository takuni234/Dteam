
/*!
@file UISprite.h
@brief UI�p�̃X�v���C�g�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	�A�ԃA�j���X�v���C�g
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
		//�g�[�^������
		float m_TotalTime;
		//�o�b�N�A�b�v���_�f�[�^
		vector<VertexPositionColorTexture> m_BackupVertices;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		@param[in]	TextureKey	�e�N�X�`���L�[
		@param[in]	Trace	�����������邩�ǂ���
		@param[in]	StartScale	�����X�P�[��
		@param[in]	StartPos	�����ʒu
		@param[in]	PieceXCount	X�����̕А�
		@param[in]	PieceYCount	Y�����̕А�
		@param[in]	AnimeTime	1�̕Ђ̕\������
		*/
		//--------------------------------------------------------------------------------------
		SerialAnimeSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos, uint32_t PieceXCount, uint32_t PieceYCount,
			float AnimeTime);
		//�j��
		virtual ~SerialAnimeSprite();
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate()override;
	};
}