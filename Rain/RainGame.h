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

	// ��Ϸ��ʼ/����
	void StartGame();
	void Shutdown();

	// �˳�����֪ͨ�ص�
	bool OnNotifyQuitting() { return true; }

	// ����ʵ��
	void OnKeyPressed(unsigned int key);
	void OnKeyReleased(unsigned int key) {}

	// ���Ŵ���
	void OnResizeWindow(unsigned int width, unsigned int height);

	// ����
	void Update(unsigned long deltaTime);

	// ������ת�����
	void UpdateCamera(float heading, float pitch, float range);

	// ��Ⱦ����
	void RenderScene();

	/// @brief
	/// ͨ���������Ļѡ������
	///	@param mx
	///		���λ��x����
	///	@param my
	///		���λ��y����
	///	@returns
	///		���������е�����
	Zone* SelectZoneByClick(int mx, int my);

#ifdef RAIN_EDITOR
private slots:
	void SlotTest();
#endif

private:
	SceneGraph*		m_Scene;

	Camera*			m_Camera;		///< �ۿ������������
	Vector3f		m_LookAtPos;	///< ������۲��
	bool			m_DebugRender;
	Zone*			m_SelectedZone;
};

#endif
