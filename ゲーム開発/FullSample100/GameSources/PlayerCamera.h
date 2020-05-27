/*!
@file PlayerCamera.h
@vrief �J����
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class PlayerCamera : public Camera {
		weak_ptr<GameObject> m_TargetObject;
		Vec3 m_TargetToAt;
		float m_Rad;
		//�v���C���[�܂ł̋���
		float m_ArmLen;

		Vec3 m_Eye;
	public:
		PlayerCamera();
		~PlayerCamera();

		virtual void OnUpdate() override;

		shared_ptr<GameObject> GetTargetObject() const;
		void SetTargetObject(const shared_ptr<GameObject>& Obj);
		void SetTargetToAt(const bsm::Vec3& v);
		virtual void SetAt(const bsm::Vec3& At)override;
		virtual void SetAt(float x, float y, float z)override;
	};

	//--------------------------------------------------------------------------------------
	//	�I�[�v�j���O�J�����i�R���|�[�l���g�ł͂Ȃ��j
	//--------------------------------------------------------------------------------------
	class OpeningCamera : public Camera {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		OpeningCamera();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~OpeningCamera();
		//--------------------------------------------------------------------------------------
		/*!
		@brief �X�V����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;
	};

	//--------------------------------------------------------------------------------------
	//�@���̂̃J�����}��
	//--------------------------------------------------------------------------------------
	class Cameraman : public GameObject {
		float m_ToPlayerLen;
	public:
		//�\�z�Ɣj��
		Cameraman(const shared_ptr<Stage>& StagePtr,
			float ToPlayerLen
		);
		virtual ~Cameraman();
		//������
		virtual void OnCreate() override;
		//����
		virtual void OnUpdate() override;
	};

	//--------------------------------------------------------------------------------------
	//�@�I�[�v�j���O�J�����}��
	//--------------------------------------------------------------------------------------
	class OpeningCameraman : public GameObject {
		Vec3 m_StartPos;
		Vec3 m_EndPos;
		Vec3 m_AtStartPos;
		Vec3 m_AtEndPos;
		Vec3 m_AtPos;
		float m_TotalTime;
		//�X�e�[�g�}�V�[��
		unique_ptr< StateMachine<OpeningCameraman> >  m_StateMachine;
		//�T�o�C�o�[�J�E���g
		int m_ObjCount;
		Vec3 m_ObjSPosVecBuff;
		Vec3 m_ObjEPosVecBuff;
		Vec3 m_ObjAtVecBuff;
		Vec3 m_ObjEAtVecBuff;
		vector<shared_ptr<GameObject>> m_Vec;
		bool m_Once;
	public:
		//�\�z�Ɣj��
		OpeningCameraman(const shared_ptr<Stage>& StagePtr);
		virtual ~OpeningCameraman();
		//������
		virtual void OnCreate() override;
		//����
		virtual void OnUpdate() override;
		//�A�N�Z�T
		const unique_ptr<StateMachine<OpeningCameraman>>& GetStateMachine() {
			return m_StateMachine;
		}

		Vec3 GetAtPos() const {
			return m_AtPos;
		}
		void ToGoalEnterBehavior();
		void ToStartEnterBehavior();
		void ToSurvivorEnterBehavior(shared_ptr<GameObject>& obj, Vec3& startPos);
		void ToSurvivorRoundBehavior(shared_ptr<GameObject>& obj, Vec3& startPos, Vec3& startAt);
		//void ToRoundEnterBehavior(shared_ptr<GameObject>& obj, Vec3& startPos, Vec3& startAt);
		void ToRoundEnterBehavior(Vec3& startPos, Vec3& endPos, Vec3& startAt, Vec3& endAt);
		bool ExcuteBehavior(float totaltime);
		void EndStateEnterBehavior();

		int GetObjCount() const {
			return m_ObjCount;
		}
		void SetObjCount(int count) {
			m_ObjCount = count;
		}		
		Vec3 GetObjSPosVecBuff() const {
			return m_ObjSPosVecBuff;
		}
		void SetObjSPosVecBuff(Vec3& vec) {
			m_ObjSPosVecBuff = vec;
		}
		Vec3 GetObjEPosVecBuff() const {
			return m_ObjEPosVecBuff;
		}
		void SetObjEPosVecBuff(Vec3& vec) {
			m_ObjEPosVecBuff = vec;
		}
		Vec3 GetObjAtVecBuff() const {
			return m_ObjAtVecBuff;
		}
		void SetObjAtVecBuff(Vec3& vec) {
			m_ObjAtVecBuff = vec;
		}
		Vec3 GetObjEAtVecBuff() const {
			return m_ObjEAtVecBuff;
		}
		void SetObjEAtVecBuff(Vec3& vec) {
			m_ObjEAtVecBuff = vec;
		}
		vector<shared_ptr<GameObject>> GetObjVec() const {
			return m_Vec;
		}
		void AddObj(shared_ptr<GameObject>& obj) {
			m_Vec.push_back(obj);
		}
		void ResetObj() {
			m_Once = false;
			m_Vec.clear();
		}
		bool GetOnce() const {
			return m_Once;
		}
		void SetOnce(bool flg) {
			m_Once = flg;
		}
	};

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToGoalState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	class OpeningCameramanToGoalState : public ObjState<OpeningCameraman>
	{
		OpeningCameramanToGoalState() {}
	public:
		static shared_ptr<OpeningCameramanToGoalState> Instance();
		virtual void Enter(const shared_ptr<OpeningCameraman>& Obj)override;
		virtual void Execute(const shared_ptr<OpeningCameraman>& Obj)override;
		virtual void Exit(const shared_ptr<OpeningCameraman>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToStartState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	class OpeningCameramanToStartState : public ObjState<OpeningCameraman>
	{
		OpeningCameramanToStartState() {}
	public:
		static shared_ptr<OpeningCameramanToStartState> Instance();
		virtual void Enter(const shared_ptr<OpeningCameraman>& Obj)override;
		virtual void Execute(const shared_ptr<OpeningCameraman>& Obj)override;
		virtual void Exit(const shared_ptr<OpeningCameraman>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanEndState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	class OpeningCameramanEndState : public ObjState<OpeningCameraman>
	{
		OpeningCameramanEndState() {}
	public:
		static shared_ptr<OpeningCameramanEndState> Instance();
		virtual void Enter(const shared_ptr<OpeningCameraman>& Obj)override;
		virtual void Execute(const shared_ptr<OpeningCameraman>& Obj)override;
		virtual void Exit(const shared_ptr<OpeningCameraman>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToSurvivorState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	class OpeningCameramanToSurvivorState : public ObjState<OpeningCameraman>
	{
		OpeningCameramanToSurvivorState() {}
	public:
		static shared_ptr<OpeningCameramanToSurvivorState> Instance();
		virtual void Enter(const shared_ptr<OpeningCameraman>& Obj)override;
		virtual void Execute(const shared_ptr<OpeningCameraman>& Obj)override;
		virtual void Exit(const shared_ptr<OpeningCameraman>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToRoundState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	class OpeningCameramanToRoundState : public ObjState<OpeningCameraman>
	{
		float m_CameraLength;
		float m_CameraHeight;
		OpeningCameramanToRoundState() :m_CameraLength(20.0f), m_CameraHeight(5.0f){}
	public:
		static shared_ptr<OpeningCameramanToRoundState> Instance();
		virtual void Enter(const shared_ptr<OpeningCameraman>& Obj)override;
		virtual void Execute(const shared_ptr<OpeningCameraman>& Obj)override;
		virtual void Exit(const shared_ptr<OpeningCameraman>& Obj)override;
		
		void SetCameraLength(float len) {
			m_CameraLength = len;
		}
		void SetCameraHeight(float height) {
			m_CameraHeight = height;
		}
	};
}
