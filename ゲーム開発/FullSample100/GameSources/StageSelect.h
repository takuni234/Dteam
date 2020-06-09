/*!
@file StageSelect.h
@brief �X�e�[�W�Z���N�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�X�e�[�W�Z���N�g�N���X
	//--------------------------------------------------------------------------------------
	class StageSelect : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		shared_ptr<SoundItem> m_BGM;
		int m_SelectNum;
		SelectKey m_SelectKey;
		//���͔���t���O
		bool m_InputOnce;
		float m_InputTime;
		//�J�[�\���̃T�C�Y
		Vec2 m_ArrowCursorScale;
		float m_RCursorTime;
		float m_LCursorTime;
		//CSV�ǂݍ��ݗp
		CsvFile m_CsvFile;

		void CreateSelectSprite();
		//���͂���I���J�[�\�����ړ�
		void StageSelectKeyInput();
		void UpdateSpriteTX();
		void ChangeStageSceneSelected();
		void SetCSVKey();
		int GetObjCountInCSV(const wstring& key);
	public:
		//�\�z�Ɣj��
		StageSelect() :Stage(), m_SelectKey(SelectKey(0)), m_InputOnce(false), m_InputTime(0.0f), m_ArrowCursorScale(100.0f), m_RCursorTime(0.0f) {}
		virtual ~StageSelect() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;
	};
}
//end basecross

