/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
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
		//���͂���ړ��������擾
		Vec3 GetMoveVector() const;
		void MovePlayer();

		void DrawStrings();
	public:
		Player(const shared_ptr<Stage>& stage, const Vec3& scale, const Vec3& rot, const Vec3& pos);
		virtual ~Player();

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnUpdate2() override;
		//�Փ˔���
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

		//���̓C�x���g
		void OnPushStart(){}
		void OnPushA(){}
		void OnPushB(){}
		void OnPushX();
		void OnPushY(){}
	};

}
//end basecross

