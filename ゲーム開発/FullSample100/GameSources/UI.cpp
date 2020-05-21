#include "stdafx.h"
#include "Project.h"

namespace basecross {
	TraceSprite::TraceSprite(const shared_ptr<Stage>& StagePtr, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_TotalTime(0),
		m_Gauge(-0.5f)
	{}
	TraceSprite::~TraceSprite() {}
	void TraceSprite::OnCreate() {
		float helfSize = 0.5f;
		//���_�z��
		m_BackupVertices = {
			{ VertexPositionColor(Vec3(-helfSize, helfSize, 0),Col4(1.0f,0.0f,0.0f,0.0f)) },
			{ VertexPositionColor(Vec3(helfSize, helfSize, 0), Col4(0.0f, 1.0f, 0.0f, 0.0f)) },
			{ VertexPositionColor(Vec3(-helfSize, -helfSize, 0), Col4(0.0f, 0.0f, 1.0f, 0.0f)) },
			{ VertexPositionColor(Vec3(helfSize, -helfSize, 0), Col4(0.0f, 0.0f, 0, 0.0f)) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_StartPos);
		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		AddComponent<PCSpriteDraw>(m_BackupVertices, indices);
	}
	void TraceSprite::OnUpdate() {
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += elapsedTime;
		if (m_TotalTime >= XM_PI) {
			m_TotalTime = 0;
		}

		vector<VertexPositionColor> newVertices;
		for (size_t i = 0; i < m_BackupVertices.size(); i++) {
			Col4 col = m_BackupVertices[i].color;
			col.w = sin(m_TotalTime);
			VertexPositionColor v;
			if (i==0)
			{
				v = VertexPositionColor(Vec3(-0.5f, 0.5f, 0.0f), Col4(1.0f, 0.0f, 0.0f, 1.0f));
			}
			if (i==1)
			{
				v = VertexPositionColor(Vec3(m_Gauge, 0.5f, 0.0f), Col4(1.0f, 0.0f, 0.0f, 1.0f));
			}
			if (i==2)
			{
				v = VertexPositionColor(Vec3(-0.5f, -0.5f, 0.0f), Col4(1.0f, 0.0f, 0.0f, 1.0f));
			}
			if (i==3)
			{
				v = VertexPositionColor(Vec3(m_Gauge, -0.5f, 0.0f), Col4(1.0f, 0.0f, 0.0f, 1.0f));
			}
			
			newVertices.push_back(v);
		}
		auto ptrDraw = GetComponent<PCSpriteDraw>();
		ptrDraw->UpdateVertices(newVertices);

	}
	//--------------------------------------------------------------------------------------
///	�ǖ͗l�̃X�v���C�g
//--------------------------------------------------------------------------------------
	PushSprite::PushSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_TotalTime(0.0f)

	{}

	PushSprite::~PushSprite() {}
	void PushSprite::OnCreate() {
		float helfSize = 0.5f;
		//���_�z��(�c��5���\��)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize, helfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0, 1.0f), Vec2(1.0f, 1.0f)) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_StartPos);
		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(m_TextureKey);
	}
	void PushSprite::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += ElapsedTime * 5.0f;
		if (m_TotalTime >= XM_2PI) {
			m_TotalTime = 0;
		}
		auto PtrDraw = GetComponent<PCTSpriteDraw>();
		Col4 col(1.0, 1.0, 1.0, 1.0);
		col.w = sin(m_TotalTime) * 0.5f + 0.5f;
		PtrDraw->SetDiffuse(col);
	}


}