/*!
@file Scene.h
@brief �V�[��
*/
#pragma once

#include "stdafx.h"

namespace basecross{
	enum SceneKey {
		Title,
		Select,
		Game,
		Result,
		Load
	};
	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase{
		float m_LimitTime;
		wstring m_StageCSVKey;
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
	};

}

//end basecross
