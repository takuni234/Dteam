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
		//�g�[�^������
		float m_TotalTime;
		float m_MAXTIME;

		bool m_IsUpdate;

		//CSV
		CsvFile csvfile_1;
		CsvFile csvfile_2;
		CsvFile ObjCsvfile;

		//BGM
		shared_ptr<SoundItem> m_BGM;
		shared_ptr<SoundItem> m_RescueBGM;
		//�J�����p
		//OpeningCamera�p�̃r���[
		shared_ptr<SingleView> m_OpeningCameraView;
		//PlayerCamera�p�̃r���[
		shared_ptr<SingleView> m_PlayerCameraView;
		CameraSelect m_CameraSelect;

		Vec3 PlayerPos;
		Vec3 GoalPos;
		Vec3 GoalRot;
		Vec3 magumaPos;
		Vec3 StagePos, StageScale;
		Vec2 StageWallScale;
		
		//�C���v�b�g�n���h���[
		InputHandler<GameStage> m_InputHandler;

		//��F
		Col4 m_Color = Col4(144.0f / 255.0f, 215.0f / 255.0f, 236.0f / 255.0f, 1.0f);
		//���Ύ��̋�F
		Col4 m_Color1 = Col4(87.0f / 255.0f, 56.0f / 255.0f, 38.0f / 255.0f, 1.0f);
		
		//�|�[�Y���j���[�̃X�v���C�g�����낦�邩
		bool m_SpriteAlign;
		vector<Vec3> m_PauseMenuSpriteDefultScale;
		vector<Vec3> m_PauseMenuSpritePos;
		bool m_InputOnce;
		int m_SelectNum;
		float m_MenuKeyInputTime;
		GameStageMenuKey m_MenuKey;

		//�r���[�̍쐬
		void CreateViewLight();
		//CSV�Ǎ�
		void CreateObjectB_CSV();
		//�X�R�A�X�v���C�g�쐬
		void CreateScoreSprite();
		//�|�[�Y���j���[�쐬
		void CreatePauseSprite();
		//�؂̍쐬
		void CreateTreeObjects(const Vec2& mapSize, const Vec3& stageSize);
		//HP�o�[�̍쐬
		void CreateHPSprite();
		//�w�i�F��ύX����
		void SetBackGroundColor(Col4 color);
		//�ݒ肵�����x�ɍ��킹�Ĕw�i�F��ύX����
		void SetBackGroundPlayerPosColor(Col4 posZero, Col4 posMax, float posSizeMax);
		//�J�����}���̍쐬
		void CreateCameraman();
		//���̍쐬
		void CreateSmoke();
		//�|�[�Y���j���[�̃L�[����
		void GameStageMenuKeyInput();
		void UpdateCursor();
		void ChangeStageSceneSelected();
	public:

		//�\�z�Ɣj��
		GameStage() :Stage(), m_IsUpdate(true),m_TotalTime(App::GetApp()->GetScene<Scene>()->GetLimitTime()), m_MAXTIME(m_TotalTime) {}
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
		void LowCountTarget() { GoalCount -= 1; }
		void SetGoalCount(int goal) { GoalCount = goal; }
		int GetGoalCount() { return GoalCount; }
		void StageChange();

		void OnPushStart();
		void OnPushA();
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

