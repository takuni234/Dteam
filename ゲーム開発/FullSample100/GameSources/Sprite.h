#pragma once
#include "stdafx.h"

namespace basecross {
	class Sprite : public GameObject {
		void UpdateScale() {
			GetComponent<Transform>()->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		}
		void UpdatePosition() {
			GetComponent<Transform>()->SetPosition(m_StartPos);
		}
	protected:
		Vec2 m_StartScale;
		Vec3 m_Rotation;
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
		Sprite(const shared_ptr<Stage>& stage, const wstring& key, const Vec2& startScale, const Vec3& rot, const Vec3& startPos);
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
		void SetScale(const Vec2& scale) {
			m_StartScale = scale;
			UpdateScale();
		}
		void SetPosition(const Vec3& pos) {
			m_StartPos = pos;
			UpdatePosition();
		}
	};

	class HPSprite : public Sprite {
		float m_HPMAX;
		float m_Hp;

		void UpdateHP();
	public:
		HPSprite(const shared_ptr<Stage>& stage, const wstring& key);
		HPSprite(const shared_ptr<Stage>& stage, const wstring& key, const float& HPMAX);
		HPSprite(const shared_ptr<Stage>& stage, const wstring& key, const float& HP, const float& HPMAX);
		HPSprite(const shared_ptr<Stage>& stage, const wstring& key, const float& HPMAX, const Vec2& startScale, const Vec3& startPos);
		HPSprite(const shared_ptr<Stage>& stage, const wstring& key, const float& HP, const float& HPMAX, const Vec2& startScale, const Vec3& startPos);
		virtual ~HPSprite(){}
		virtual void OnCreate()override;
		//��������HP
		void SetHPScale(const Vec2& vec);

		float AddHp(const float& value) {
			m_Hp += value;
			if (m_Hp <= 0.0f) {
				m_Hp = 0.0f;
			}
			else if (m_Hp >= m_HPMAX) {
				m_Hp = m_HPMAX;
			}
			UpdateHP();
			return m_Hp;
		}
	};
}