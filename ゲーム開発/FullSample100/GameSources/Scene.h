/*!
@file Scene.h
@brief �V�[��
*/
#pragma once

#include "stdafx.h"

namespace basecross{
	//�V�[���J�ڗp
	enum class SceneKey : int {
		Title,
		Select,
		Game,
		Result,
		GameOver,
		Load,
		Max
	};

	//���U���g�X�e�[�W�̃��j���[�p
	enum class ResultStageMenuKey : int{
		NextStage,
		Select,
		Retry,
		Title,
		Max
	};

	//�Q�[���I�[�o�[�X�e�[�W�̃��j���[�p
	enum class GameOverStageMenuKey : int{
		Select,
		Retry,
		Title,
		Max
	};	
	
	//�Q�[���X�e�[�W�̃��j���[�p
	enum class GameStageMenuKey : int{
		Retry,
		Select,
		Title,
		Max
	};

	//�X�e�[�W��
	enum class SelectKey : int{
		Stage1,
		Stage2,
		Stage3,
		Max
	};

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase{
		float m_LimitTime;
		int m_AllMember;
		int m_RescueCount;
		wstring m_StageCSVKey;
		SelectKey m_CurrentScene;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		Scene() :SceneBase(), m_LimitTime(0.0f){}
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Scene();
		//--------------------------------------------------------------------------------------
		/*!
		@brief ������
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �C�x���g�擾
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnEvent(const shared_ptr<Event>& event) override;
		void ChangeScene(SceneKey key);

		//�Q�b�^�[�Z�b�^�[�Q
		float GetLimitTime() const {
			return m_LimitTime;
		}
		void SetLimitTime(float time) {
			m_LimitTime = time;
		}
		wstring GetStageCSVKey() const {
			return m_StageCSVKey;
		}
		void SetStageCSVKey(const wstring& key) {
			m_StageCSVKey = key;
		}
		void SetAllMember(const int& value) {
			m_AllMember = value;
		}
		int GetAllMember() const {
			return m_AllMember;
		}
		void SetRescueCount(const int& rescueCount) {
			m_RescueCount = rescueCount;
		}
		void AddRescueCount(const int& rescueCount) {
			m_RescueCount += rescueCount;
		}
		int GetRescueCount() const {
			return m_RescueCount;
		}
		SelectKey GetCurrentSceneKey() const {
			return m_CurrentScene;
		}
		void SetCurrentSceneKey(const SelectKey& key) {
			m_CurrentScene = key;
		}
	};

}

//end basecross
