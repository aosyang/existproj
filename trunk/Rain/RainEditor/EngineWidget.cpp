#include "EngineWidget.h"
#include <QResizeEvent>

EngineWidget::EngineWidget(QWidget* parent, Qt::WindowFlags f)
: QWidget(parent, f),
  m_ExistTimer(NULL),
  m_Game(NULL)
{

}

EngineWidget::~EngineWidget()
{
	m_Game->Shutdown();
	Engine::Instance().Shutdown();

	SAFE_DELETE(m_ExistTimer);
	SAFE_DELETE(m_Game);
}

void EngineWidget::resizeEvent(QResizeEvent* event)
{
	int w = event->size().width();
	int h = event->size().height();
	Engine::Instance().ResizeWindow(w, h);
}


void EngineWidget::InitEngine()
{

	// 这个方法将获取窗体的HWND(Win32)
	WId hwnd = winId();

	m_ExistTimer = new Timer();

	m_ExistTimer->Reset();
	m_LastUpdateTime = m_ExistTimer->GetMilliseconds();

	m_Game = new RainGame();
	Engine::Instance().SetGame(m_Game);

	System::Instance().SetRenderWindowHandle(static_cast<RenderWindowHandle>(hwnd));
	Engine::Instance().Initialize(false);

	System::Instance().LoadResources("resources.cfg");

	m_Game->StartGame();
}

void EngineWidget::UpdateEngine()
{
	if (!m_ExistTimer) return;

	unsigned long deltaTime = m_ExistTimer->GetMilliseconds() - m_LastUpdateTime;
	m_LastUpdateTime = m_ExistTimer->GetMilliseconds();
	Engine::Instance().ManualUpdate(deltaTime);
}

void EngineWidget::mousePressEvent(QMouseEvent* event)
{
	// 点击渲染空间，在游戏中选择对象
	Zone* zone = m_Game->SelectZoneByClick(event->x(), event->y());
	emit ZoneSelected(zone);
}
