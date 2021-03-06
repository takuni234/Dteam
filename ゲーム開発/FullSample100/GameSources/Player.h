/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Player : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		Vec3 m_MoveDir;
		//岩の貫通バグ防止用
		Vec3 m_CollisionPos;
		//移動スピード
		float m_Speed;
		//向いている方向
		Vec3 m_HeadRot;
		//放水の間隔時間
		float m_IntervalTime;
		//ノックバック中の操作不能時間
		float m_KnockBackTime;
		//インプットハンドラー
		InputHandler<Player> m_InputHandler;

		//入力を取得
		Vec2 GetInputState() const;

		void DrawStrings();

		//ステートマシーン
		unique_ptr<StateMachine<Player>> m_StateMachine;

		//判定用
		shared_ptr<AttackArea> m_PlayerAttackArea;
		float m_AttackInterval;
		shared_ptr<GrabArea> m_PlayerGrabArea;

		//音関係
		shared_ptr<SoundItem> m_BGM;
		shared_ptr<SoundItem> m_BGM2;
		float m_BGMInterval;
		bool m_BGMflg; //足音用
		float m_Stride;
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
		void PlayerSneak();
		void PlayerShot();
		void PlayerWalk();
		void PlayerAttack();
		void PlayerGrab();
		
		//音
		void PlayerSound(bool active, const wstring& key);
		void PlayerSound(bool active, const wstring& key, float volume);
		void PlayerSound(bool active, const wstring& key, shared_ptr<SoundItem> bgm);
		void PlayerSound(bool active, const wstring& key, float volume, bool loop, shared_ptr<SoundItem> bgm);
		void ResetBGMInterval() {
			m_BGMflg = false;
			m_BGMInterval = 0.2f;
		}

		shared_ptr<GameObject> GetAttackArea() {
			return m_PlayerAttackArea;
		}
		shared_ptr<AttackArea> GetAttackAreaObj() {
			return m_PlayerAttackArea;
		}
		shared_ptr<GameObject> GetGrabArea() {
			return m_PlayerGrabArea;
		}

		//入力イベント
		void OnPushStart() {}
		void OnPushA();
		void OnUpA();
		void OnPushB();
		void OnUpB();
		void OnPushX();
		void OnUpX();
		void OnPushY();
		void OnUpY();
		//アクセサ
		const unique_ptr<StateMachine<Player>>& GetStateMachine() {
			return m_StateMachine;
		}
		float GetSpeed() const {
			return m_Speed;
		}
		void SetSpeed(float speed) {
			m_Speed = speed;
		}
		Vec3 GetHeadRot() const {
			return m_HeadRot;
		}
		float GetKnockBackTime()const {
			return m_KnockBackTime;
		}
		shared_ptr<SoundItem> GetSoundItem2() const {
			return m_BGM2;
		}
		void SetSoundItem2(const shared_ptr<SoundItem>& bgm) {
			m_BGM2 = bgm;
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
		ShotState() {}
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
		MovingShootingState() {}
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
		AttackState() {}
	public:
		static shared_ptr<AttackState> Instance();
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};
	
	//--------------------------------------------------------------------------------------
	//	class GrabState : public ObjState<Player>;
	//--------------------------------------------------------------------------------------
	class GrabState : public ObjState<Player>
	{
		GrabState() {}
	public:
		static shared_ptr<GrabState> Instance();
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};
	
	//--------------------------------------------------------------------------------------
	//	class PushState : public ObjState<Player>;
	//--------------------------------------------------------------------------------------
	class PushState : public ObjState<Player>
	{
		PushState() {}
	public:
		static shared_ptr<PushState> Instance();
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};
	
	//--------------------------------------------------------------------------------------
	//	class PullState : public ObjState<Player>;
	//--------------------------------------------------------------------------------------
	class PullState : public ObjState<Player>
	{
		PullState() {}
	public:
		static shared_ptr<PullState> Instance();
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class DamageState : public ObjState<Player>;
	//--------------------------------------------------------------------------------------
	class DamageState : public ObjState<Player>
	{
		float m_Time;
		DamageState() {}
	public:
		static shared_ptr<DamageState> Instance();
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};
}
//end basecross

