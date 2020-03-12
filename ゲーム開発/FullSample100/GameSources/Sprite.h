#pragma once
#include "stdafx.h"

namespace basecross {
	class Sprite : public GameObject {
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		bool m_Trace;
		wstring m_Key;
	public:
		Sprite(const shared_ptr<Stage>& stage, const wstring& key);
		Sprite(const shared_ptr<Stage>& stage, const wstring& key, const bool& trace);
		Sprite(const shared_ptr<Stage>& stage, const wstring& key, const Vec2& startScale);
		Sprite(const shared_ptr<Stage>& stage, const wstring& key, const Vec2& startScale, const Vec3& startPos);
		Sprite(const shared_ptr<Stage>& stage, const wstring& key, const bool& trace, const Vec2& startScale, const Vec3& startPos);
		virtual ~Sprite();

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}