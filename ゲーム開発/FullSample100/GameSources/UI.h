#pragma once
#include "Project.h"

namespace basecross {
	class TraceSprite : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		float m_TotalTime;

		float m_Gauge;
		//�o�b�N�A�b�v���_�f�[�^
		vector<VertexPositionColor> m_BackupVertices;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		@param[in]	Trace	�����������邩�ǂ���
		@param[in]	StartScale	�����X�P�[��
		@param[in]	StartPos	�����ʒu
		*/
		//--------------------------------------------------------------------------------------
		TraceSprite(const shared_ptr<Stage>& StagePtr, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~TraceSprite();
		//--------------------------------------------------------------------------------------
		/*!
		@brief ������
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �X�V
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;
		float GetGauge() {
			return m_Gauge;
		}
		void SetGauge(float gauge) {
			m_Gauge = gauge;
		}

	};
}