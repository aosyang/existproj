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
	/// 创建属性面板
	void CreatePropPanel();

private slots:
	/// @brief
	///	为选中物体创建面板属性
	void UpdateObjectProperties(Zone* zone);

	/// @brief
	/// 属性面板值发生变化
	void valueChanged(QtProperty* qProp, const QVariant& var);

	/// @brief
	/// 计时器回调函数
	void TimerTick();
private:
	Ui::RainEditorClass ui;
	QTimer*			m_Timer;		///< QT计时器
	EngineWidget*	m_EngineWidget;	///< 引擎渲染控件
	QtVariantPropertyManager*	m_VariantManager;
	QtTreePropertyBrowser*		m_VariantEditor;
	bool			m_EngineToPropPanel;	///< 是否正在从引擎向属性面板传值(防止回调函数在面板每次修改时被调用)
	Zone*			m_SelectedZone;
};

#endif // RAINEDITOR_H
