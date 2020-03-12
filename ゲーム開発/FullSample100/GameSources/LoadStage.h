/*!
@file LoadStage.h
@brief ���[�h�X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	���[�h�X�e�[�W�N���X�i���[�h��ʁj
	//--------------------------------------------------------------------------------------
	class LoadStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		//�X�v���C�g�̍쐬
		void CreateTitleSprite();
		//���\�[�X���[�h�p�̃X���b�h�i�X�^�e�B�b�N�֐��j
		static void LoadResourceFunc();
		//���\�[�X��ǂݍ��񂾂��Ƃ�m�点��t���O�i�X�^�e�B�b�N�ϐ��j
		static bool m_Loaded;
		//�~���[�e�b�N�X
		static std::mutex mtx;
	public:
		//�\�z�Ɣj��
		LoadStage() :Stage() {}
		virtual ~LoadStage() {}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;
	};

}