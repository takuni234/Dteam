/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Player : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		Vec3 m_MoveDir;
		//移動スピード
		float m_Speed;
		//放水の間隔時間
		float m_IntervalTime;
		//インプットハンドラー
		InputHandler<Player> m_InputHandler;

		//入力を取得
		Vec2 GetInputState() const;
		//入力から移動方向を取得
		Vec3 GetMoveVector() const;
		void MovePlayer();

		void DrawStrings();
	public:
		Player(const shared_ptr<Stage>& stage, const Vec3& scale, const Vec3& rot, const Vec3& pos);
		virtual ~Player();

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnUpdate2() override;
		//衝突判定
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

		//入力イベント
		void OnPushStart(){}
		void OnPushA(){}
		void OnPushB(){}
		void OnPushX();
		void OnPushY(){}
	};

}
//end basecross

