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

		void DrawStrings();
		//ステートマシーン
		unique_ptr<StateMachine<Player>> m_StateMachine;
		shared_ptr<AttackArea> m_PlayerAttackArea;
	public:
		Player(const shared_ptr<Stage>& stage, const Vec3& scale, const Vec3& rot, const Vec3& pos);
		virtual ~Player();

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnUpdate2() override;
		//衝突判定
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

		//入力から移動方向を取得
		Vec3 GetMoveVector() const;

		void PlayerMove();
		void PlayerShot();
		void PlayerWalk();
		void PlayerAttack();
		shared_ptr<GameObject> GetAttackArea() {
			return m_PlayerAttackArea;
		}

		//入力イベント
		void OnPushStart(){}
		void OnPushA();
		void OnPushB(){}
		void OnPushX();
		void OnUpX();
		void OnPushY();
		void OnUpY();
		//アクセサ
		const unique_ptr<StateMachine<Player>>& GetStateMachine() {
			return m_StateMachine;
		}
	};

	//--------------------------------------------------------------------------------------
	//	class DefaultState : public ObjState<Player>;
	//--------------------------------------------------------------------------------------
	class DefaultState : public ObjState<Player>
	{
		DefaultState() {}
	public:
		static shared_ptr<DefaultState> Instance();
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};
	
	//--------------------------------------------------------------------------------------
	//	class WalkState : public ObjState<Player>;
	//--------------------------------------------------------------------------------------
	class WalkState : public ObjState<Player>
	{
		WalkState() {}
	public:
		static shared_ptr<WalkState> Instance();
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class ShotState : public ObjState<Player>;
	//--------------------------------------------------------------------------------------
	class ShotState : public ObjState<Player>
	{
		ShotState(){}
	public:
		static shared_ptr<ShotState> Instance();
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class MovingShootingState : public ObjState<Player>;
	//--------------------------------------------------------------------------------------
	class MovingShootingState : public ObjState<Player>
	{
		MovingShootingState(){}
	public:
		static shared_ptr<MovingShootingState> Instance();
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class AttackState : public ObjState<Player>;
	//--------------------------------------------------------------------------------------
	class AttackState : public ObjState<Player>
	{
		AttackState(){}
	public:
		static shared_ptr<AttackState> Instance();
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};
}
//end basecross

