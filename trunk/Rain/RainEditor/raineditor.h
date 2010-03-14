#ifndef RAINEDITOR_H
#define RAINEDITOR_H

#include <QtGui/QMainWindow>
#include <QTimer>
#include "ui_raineditor.h"
#include "EngineWidget.h"
#include "qtpropertymanager.h"
#include "qtvariantproperty.h"
#include "qttreepropertybrowser.h"
#include "../Zone.h"

class RainEditor : public QMainWindow
{
	Q_OBJECT

public:
	RainEditor(QWidget *parent = 0, Qt::WFlags flags = 0);
	~RainEditor();

	/// @brief
	/// �����������
	void CreatePropPanel();

private slots:
	/// @brief
	///	Ϊѡ�����崴���������
	void UpdateObjectProperties(Zone* zone);

	/// @brief
	/// �������ֵ�����仯
	void valueChanged(QtProperty* qProp, const QVariant& var);

	/// @brief
	/// ��ʱ���ص�����
	void TimerTick();
private:
	Ui::RainEditorClass ui;
	QTimer*			m_Timer;		///< QT��ʱ��
	EngineWidget*	m_EngineWidget;	///< ������Ⱦ�ؼ�
	QtVariantPropertyManager*	m_VariantManager;
	QtTreePropertyBrowser*		m_VariantEditor;
	bool			m_EngineToPropPanel;	///< �Ƿ����ڴ�������������崫ֵ(��ֹ�ص����������ÿ���޸�ʱ������)
	Zone*			m_SelectedZone;
};

#endif // RAINEDITOR_H
