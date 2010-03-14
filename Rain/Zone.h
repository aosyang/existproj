#ifndef _ZONE_H
#define _ZONE_H

#include <Existence.h>

using namespace Gen;

#include <set>

// ��������
// ����һ��������������ԣ�������������������
class Zone : public Actor
{
	DECLARE_FACTORY_OBJECT(Zone, Actor);
public:
	void DebugRender();

	void Update(unsigned long deltaTime);

	// ����������������������
	void OnCollide(Zone* other, unsigned long deltaTime);

	void OnSelected();
	void OnDeselected();

	// ָ������뾶������Obb
	void SetRadius(float radius);
	float GetRadius() const { return m_Radius; }

	void SetAltitude(float altitude);
	float GetAltitude() const { return m_Altitude; }

protected:

	// General Properties
	float		m_Radius;				///< ����뾶(��λ:m)
	float		m_Altitude;				///< ���θ߶�(��λ:m)
	Vector3f	m_Movement;				///< ������ƶ��ٶ�(��λ:m/s)

	// Gameplay stats

	float		m_Temperature;			///< �¶�
	float		m_Humidity;				///< ʪ��
	float		m_AtmosphericPressure;	///< ����ѹ

	bool		m_Selected;				///< ������ǰ�Ƿ�ѡ��
	bool		m_NeedUpdateOBB;		///< OBB�Ƿ���Ҫ����
};

// ���������
class ZoneManager : public Singleton<ZoneManager>
{
	friend class Singleton<ZoneManager>;
public:
	// �������
	void AddZone(Zone* zone);

	// ɾ������
	void RemoveZone(Zone* zone);

	void Update(unsigned long deltaTime);
private:
	ZoneManager();

	typedef set<Zone*>		ZoneList;
	ZoneList				m_ZoneList;
};

#endif
