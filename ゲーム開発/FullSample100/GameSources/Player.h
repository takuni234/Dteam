/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Player : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		Vec3 m_MoveDir;
		//�ړ��X�s�[�h
		float m_Speed;
		//�����̊Ԋu����
		float m_IntervalTime;
		//�C���v�b�g�n���h���[
		InputHandler<Player> m_InputHandler;

		//���͂��擾
		Vec2 GetInputState() const;

		void DrawStrings();

		//�X�e�[�g�}�V�[��
		unique_ptr<StateMachine<Player>> m_StateMachine;

		//����p
		shared_ptr<AttackArea> m_PlayerAttackArea;
		float m_AttackInterval;
		shared_ptr<GrabArea> m_PlayerGrabArea;

		//���֌W
		shared_ptr<SoundItem> m_BGM;
		float m_BGMInterval;
		bool m_BGMflg; //�����p
		float m_Stride;
	public:
		Player(const shared_ptr<Stage>& stage, const Vec3& scale, const Vec3& rot, const Vec3& pos);
		virtual ~Player();

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnUpdate2() override;
		//�Փ˔���
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

		//���͂���ړ��������擾
		Vec3 GetMoveVector() const;

		void PlayerMove();
		void PlayerSneak();
		void PlayerShot();
		void PlayerWalk();
		void PlayerAttack();
		void PlayerGrab();
		
		//��
		void PlayerSound(bool active, const wstring& key);
		void PlayerSound(bool active, const wstring& key, float volume);
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

		//���̓C�x���g
		void OnPushStart() {}
		void OnPushA();
		void OnPushB();
		void OnUpB();
		void OnPushX();
		void OnUpX();
		void OnPushY();
		void OnUpY();
		//�A�N�Z�T
		const unique_ptr<StateMachine<Player>>& GetStateMachine() {
			return m_StateMachine;
		}
		float GetSpeed() const {
			return m_Speed;
		}
		void SetSpeed(float speed) {
			m_Speed = speed;
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
}
//end basecross

