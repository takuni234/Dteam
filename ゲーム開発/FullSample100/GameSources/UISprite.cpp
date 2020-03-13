/*!
@file UISprite.cpp
@brief UI�p�̃X�v���C�g�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	�A�ԃA�j���X�v���C�g
	//--------------------------------------------------------------------------------------
	SerialAnimeSprite::SerialAnimeSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec2& StartPos, uint32_t PieceXCount, uint32_t PieceYCount, float AnimeTime) :
		GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_TotalTime(0.0f),
		m_PieceXCount(PieceXCount),
		m_PieceYCount(PieceYCount),
		m_PieceIndex(0),
		m_AnimeTime(AnimeTime)

	{}

	SerialAnimeSprite::~SerialAnimeSprite() {}

	void SerialAnimeSprite::OnCreate() {
		float HelfSize = 0.5f;
		//���_�z��(�c��5���\��)
		m_BackupVertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);
		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto PtrDraw = AddComponent<PCTSpriteDraw>(m_BackupVertices, indices);
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);
		PtrDraw->SetTextureResource(m_TextureKey);
	}

	void SerialAnimeSprite::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += ElapsedTime;
		if (m_TotalTime >= m_AnimeTime) {
			m_PieceIndex++;
			if (m_PieceIndex >= m_PieceXCount * m_PieceYCount) {
				m_PieceIndex = 0;
			}
			m_TotalTime = 0;
		}
		vector<VertexPositionColorTexture> newVertices;
		uint32_t pieceX = m_PieceIndex % m_PieceXCount;
		uint32_t pieceY = m_PieceIndex / m_PieceXCount;
		float pieceWidth = 1.0f / (float)m_PieceXCount;
		float pieceHeight = 1.0f / (float)m_PieceYCount;

		float pieceStartX = (float)pieceX * pieceWidth;
		float pieceEndX = pieceStartX + pieceWidth;

		float pieceStartY = (float)pieceY * pieceHeight;
		float pieceEndY = pieceStartY + pieceHeight;

		for (size_t i = 0; i < m_BackupVertices.size(); i++) {
			Vec2 uv = m_BackupVertices[i].textureCoordinate;
			switch (i) {
			case 0:
				uv.x = pieceStartX;
				uv.y = pieceStartY;
				break;
			case 1:
				uv.x = pieceEndX;
				uv.y = pieceStartY;
				break;
			case 2:
				uv.x = pieceStartX;
				uv.y = pieceEndY;
				break;
			case 3:
				uv.x = pieceEndX;
				uv.y = pieceEndY;
				break;
			}
			auto v = VertexPositionColorTexture(
				m_BackupVertices[i].position,
				m_BackupVertices[i].color,
				uv
			);
			newVertices.push_back(v);
		}
		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		ptrDraw->UpdateVertices(newVertices);
	}
}