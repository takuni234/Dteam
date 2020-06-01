#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//コンストラクタ
	Sprite::Sprite(const shared_ptr<Stage>& stage, const wstring& key)
		:GameObject(stage),
		m_Trace(true),
		m_StartScale(Vec2(200.0f)),
		m_StartPos(Vec3(0.0f)),
		m_Key(key),
		m_Color(Col4(1.0f,1.0f,1.0f,1.0f))
	{}
	Sprite::Sprite(const shared_ptr<Stage>& stage, const wstring& key, const Col4& color)
		:GameObject(stage),
		m_Trace(true),
		m_StartScale(Vec2(200.0f)),
		m_StartPos(Vec3(0.0f)),
		m_Key(key),
		m_Color(color)
	{}
	Sprite::Sprite(const shared_ptr<Stage>& stage, const wstring& key, const bool& trace)
		:GameObject(stage),
		m_Trace(trace),
		m_StartScale(Vec2(200.0f)),
		m_StartPos(Vec3(0.0f)),
		m_Key(key),
		m_Color(Col4(1.0f, 1.0f, 1.0f, 1.0f))
	{}
	Sprite::Sprite(const shared_ptr<Stage>& stage, const wstring& key, const Vec2& startScale)
		:GameObject(stage),
		m_Trace(true),
		m_StartScale(startScale),
		m_StartPos(Vec3(0.0f)),
		m_Key(key),
		m_Color(Col4(1.0f, 1.0f, 1.0f, 1.0f))
	{}
	Sprite::Sprite(const shared_ptr<Stage>& stage, const wstring& key, const Vec2& startScale, const Vec3& startPos)
		:GameObject(stage),
		m_Trace(true),
		m_StartScale(startScale),
		m_StartPos(startPos),
		m_Key(key),
		m_Color(Col4(1.0f, 1.0f, 1.0f, 1.0f))
	{}
	Sprite::Sprite(const shared_ptr<Stage>& stage, const wstring& key, const bool& trace, const Vec2& startScale, const Vec3& startPos)
		:GameObject(stage),
		m_Trace(trace),
		m_StartScale(startScale),
		m_StartPos(startPos),
		m_Key(key),
		m_Color(Col4(1.0f, 1.0f, 1.0f, 1.0f))
	{}

	Sprite::~Sprite() {

	}

	void Sprite::OnCreate() {
		float helfSize = 0.5f;
		vector<VertexPositionColorTexture> vertex = {
			{ VertexPositionColorTexture(Vec3(-helfSize, helfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};

		vector<uint16_t> indices = { 0,1,2,1,3,2 };
		SetAlphaActive(m_Trace);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(Vec3(0.0f));
		ptrTrans->SetPosition(m_StartPos);

		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertex, indices);
		ptrDraw->SetTextureResource(m_Key);
		ptrDraw->SetDiffuse(m_Color);
	}

	void Sprite::OnUpdate() {

	}

	TransformSprite::TransformSprite(const shared_ptr<Stage>& stage, const wstring& key)
		:Sprite(stage, key)
	{}

	void TransformSprite::OnUpdate() {
		Vec2 newScale = Vec2(GetScale().x + 10.0f, GetScale().y);
		SetScale(newScale);
	}
}