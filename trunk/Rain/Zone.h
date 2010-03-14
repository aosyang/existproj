#ifndef _ZONE_H
#define _ZONE_H

#include <Existence.h>

using namespace Gen;

#include <set>

// 气候区域
// 描述一个区域的气候属性，会与其他区域发生互动
class Zone : public Actor
{
	DECLARE_FACTORY_OBJECT(Zone, Actor);
public:
	void DebugRender();

	void Update(unsigned long deltaTime);

	// 当区域与其他区域发生互动
	void OnCollide(Zone* other, unsigned long deltaTime);

	void OnSelected();
	void OnDeselected();

	// 指定区域半径，更新Obb
	void SetRadius(float radius);
	float GetRadius() const { return m_Radius; }

	void SetAltitude(float altitude);
	float GetAltitude() const { return m_Altitude; }

protected:

	// General Properties
	float		m_Radius;				///< 区域半径(单位:m)
	float		m_Altitude;				///< 海拔高度(单位:m)
	Vector3f	m_Movement;				///< 区域的移动速度(单位:m/s)

	// Gameplay stats

	float		m_Temperature;			///< 温度
	float		m_Humidity;				///< 湿度
	float		m_AtmosphericPressure;	///< 大气压

	bool		m_Selected;				///< 该区域当前是否被选中
	bool		m_NeedUpdateOBB;		///< OBB是否需要更新
};

// 区域管理器
class ZoneManager : public Singleton<ZoneManager>
{
	friend class Singleton<ZoneManager>;
public:
	// 添加区域
	void AddZone(Zone* zone);

	// 删除区域
	void RemoveZone(Zone* zone);

	void Update(unsigned long deltaTime);
private:
	ZoneManager();

	typedef set<Zone*>		ZoneList;
	ZoneList				m_ZoneList;
};

#endif
