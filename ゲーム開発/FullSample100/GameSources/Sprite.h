#pragma once
#include "stdafx.h"

namespace basecross {
	class Sprite : public GameObject {
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		bool m_Trace;
		wstring m_Key;
		Col4 m_Color;
	public:
		Sprite(const shared_ptr<Stage>& stage, const wstring& key);
		Sprite(const shared_ptr<Stage>& stage, const wstring& key, const Col4& color);
		Sprite(const shared_ptr<Stage>& stage, const wstring& key, const bool& trace);
		Sprite(const shared_ptr<Stage>& stage, const wstring& key, const Vec2& startScale);
		Sprite(const shared_ptr<Stage>& stage, const wstring& key, const Vec2& startScale, const Vec3& startPos);
		Sprite(const shared_ptr<Stage>& stage, const wstring& key, const bool& trace, const Vec2& startScale, const Vec3& startPos);
		virtual ~Sprite();

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void SetTextureKey(const wstring& key) {
			auto ptrDraw = GetComponent<PCTSpriteDraw>();
			ptrDraw->SetTextureResource(key);
		}
		Vec2 GetScale()const {
			return m_StartScale;
		}
		void SetPosition(const Vec3& pos) {
			GetComponent<Transform>()->SetPosition(m_StartPos);
		}
	};
}