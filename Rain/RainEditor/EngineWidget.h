#ifndef _ENGINEWIDGET_H
#define _ENGINEWIDGET_H

#include <QWidget>
#include <Existence.h>
#include "../RainGame.h"

using namespace Gen;

/// @brief
/// 引擎控件
///	@par
///		一个承载引擎的3D图形渲染的控件，用户可以使用这个控件查看引擎效果，或者与引擎进行交互
class EngineWidget : public QWidget
{
	Q_OBJECT
public:
	EngineWidget(QWidget* parent=0, Qt::WindowFlags f=0);
	~EngineWidget();

	/// @brief
	///	控件缩放回调函数
	///	@par
	///		当控件尺寸发生变化时，这个函数会被调用。
	void resizeEvent(QResizeEvent* event);

	/// @brief
	///	初始化引擎
	void InitEngine();

	/// @brief
	///	定时更新引擎
	void UpdateEngine();

	/// @brief
	/// 获取引擎运行的游戏
	RainGame* GetGame() const { return m_Game; }

signals:
	/// @brief
	///	qt信号，表明选中了一个区域对象
	/// @param zone
	///		所选中的区域
	void ZoneSelected(Zone* zone);

protected:
	void mousePressEvent(QMouseEvent* event);

private:
	Timer*			m_ExistTimer;		///< 引擎计时器
	unsigned long	m_LastUpdateTime;	///< 引擎最后一次更新时间
	RainGame*		m_Game;				///< 引擎所运行的游戏
};

#endif
