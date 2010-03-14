#ifndef _ENGINEWIDGET_H
#define _ENGINEWIDGET_H

#include <QWidget>
#include <Existence.h>
#include "../RainGame.h"

using namespace Gen;

/// @brief
/// ����ؼ�
///	@par
///		һ�����������3Dͼ����Ⱦ�Ŀؼ����û�����ʹ������ؼ��鿴����Ч����������������н���
class EngineWidget : public QWidget
{
	Q_OBJECT
public:
	EngineWidget(QWidget* parent=0, Qt::WindowFlags f=0);
	~EngineWidget();

	/// @brief
	///	�ؼ����Żص�����
	///	@par
	///		���ؼ��ߴ緢���仯ʱ����������ᱻ���á�
	void resizeEvent(QResizeEvent* event);

	/// @brief
	///	��ʼ������
	void InitEngine();

	/// @brief
	///	��ʱ��������
	void UpdateEngine();

	/// @brief
	/// ��ȡ�������е���Ϸ
	RainGame* GetGame() const { return m_Game; }

signals:
	/// @brief
	///	qt�źţ�����ѡ����һ���������
	/// @param zone
	///		��ѡ�е�����
	void ZoneSelected(Zone* zone);

protected:
	void mousePressEvent(QMouseEvent* event);

private:
	Timer*			m_ExistTimer;		///< �����ʱ��
	unsigned long	m_LastUpdateTime;	///< �������һ�θ���ʱ��
	RainGame*		m_Game;				///< ���������е���Ϸ
};

#endif
