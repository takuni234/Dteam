/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	enum class CameraSelect {
		openingCamera,
		playerCamera
	};

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		bool GameEndFlg = false;
		bool TimeUpFlg = false;
		int GoalCount = 0;
		//CSV
		CsvFile csvfile_1;
		CsvFile csvfile_2;
		CsvFile ObjCsvfile;
		void CreateObjectB_CSV();
		//�X�R�A�X�v���C�g�쐬
		void CreateScoreSprite();
		//HP�o�[�̍쐬
		void CreateHPSprite();
		//�g�[�^������
		float m_TotalTime;


		shared_ptr<SoundItem> m_BGM;
		//�r���[�̍쐬

		void CreateViewLight();
		bool m_IsUpdate;

		Vec3 PlayerPos;
		Vec3 GoalPos;
		Vec3 magumaPos;
		Vec3 StagePos, StageScale;
		//��F
		Col4 m_Color = Col4(144.0f / 255.0f, 215.0f / 255.0f, 236.0f / 255.0f, 1.0f);
		//���Ύ��̋�F
		Col4 m_Color1 = Col4(87.0f/255.0f,56.0f/255.0f, 38.0f/255.0f, 1.0f);

		//�w�i�F��ύX����
		void SetBackGroundColor(Col4 color);
		//�ݒ肵�����x�ɍ��킹�Ĕw�i�F��ύX����
		void SetBackGroundPlayerPosColor(Col4 posZero, Col4 posMax, float posSizeMax);

		//�J�����p
		//OpeningCamera�p�̃r���[
		shared_ptr<SingleView> m_OpeningCameraView;
		//PlayerCamera�p�̃r���[
		shared_ptr<SingleView> m_PlayerCameraView;
		CameraSelect m_CameraSelect;
		//�J�����}���̍쐬
		void CreateCameraman();

		InputHandler<GameStage> m_InputHandler;
	public:

		//�\�z�Ɣj��
		GameStage() :Stage(), m_IsUpdate(true),m_TotalTime(App::GetApp()->GetScene<Scene>()->GetLimitTime()) {}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		virtual void UpdateStage() override;
		virtual void OnDestroy() override;

		void ToPlayerCamera();
		CameraSelect GetCameraSelect() const {
			return m_CameraSelect;
		}
		bool GetEndFlg() { return TimeUpFlg; }
		void StageChange();

		void OnPushStart();
		void OnPushA(){}
		void OnUpA(){}
		void OnPushB(){}
		void OnUpB(){}
		void OnPushX(){}
		void OnUpX(){}
		void OnPushY(){}
		void OnUpY() {}
	};
}
//end basecross

