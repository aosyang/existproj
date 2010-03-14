#ifndef _RAINGAME_H
#define _RAINGAME_H

#include <Existence.h>
using namespace Gen;

#ifdef RAIN_EDITOR
#include <QtGui/QMainWindow>
#endif

class Zone;

class RainGame : public IGame
{
public:
	RainGame();

	// 游戏开始/结束
	void StartGame();
	void Shutdown();

	// 退出程序通知回调
	bool OnNotifyQuitting() { return true; }

	// 按键实现
	void OnKeyPressed(unsigned int key);
	void OnKeyReleased(unsigned int key) {}

	// 缩放窗体
	void OnResizeWindow(unsigned int width, unsigned int height);

	// 更新
	void Update(unsigned long deltaTime);

	// 更新旋转摄像机
	void UpdateCamera(float heading, float pitch, float range);

	// 渲染过程
	void RenderScene();

	/// @brief
	/// 通过鼠标点击屏幕选择区域
	///	@param mx
	///		鼠标位置x坐标
	///	@param my
	///		鼠标位置y坐标
	///	@returns
	///		返回鼠标点中的区域
	Zone* SelectZoneByClick(int mx, int my);

#ifdef RAIN_EDITOR
private slots:
	void SlotTest();
#endif

private:
	SceneGraph*		m_Scene;

	Camera*			m_Camera;		///< 观看场景的摄像机
	Vector3f		m_LookAtPos;	///< 摄像机观察点
	bool			m_DebugRender;
	Zone*			m_SelectedZone;
};

#endif
