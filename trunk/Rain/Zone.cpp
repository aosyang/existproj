#include "Zone.h"

Zone::Zone(SceneGraph* scene)
: BaseClass(scene),
  m_Altitude(3000.0f),
  m_Movement(0.0f, 0.0f, 0.0f),
  m_Selected(false),
  m_NeedUpdateOBB(false)
{
	// 设置区域的默认半径
	SetRadius(100.0f);

	ZoneManager::Instance().AddZone(this);

	// 使区域可以被射线选中
	m_CollisionGroupMask = 1;
}

Zone::~Zone()
{
}

void Zone::DebugRender()
{
	GameObjectBase::DebugRender();

	// 绘制区域圆环
	static unsigned int segment = 18;
	Vector3f p = m_WorldTransform.GetPosition();
	int i=0;

	// 渲染时的高度折合为实际的1/100
	float draw_altitude = m_Altitude / 100.0f;

	// 渲染半径折合为实际的1/10
	float draw_radius = m_Radius / 10.0f;

	Vector3f start, end(p.x + draw_radius * sinf(float(i)/segment * Math::k2Pi), draw_altitude, p.z + draw_radius * cosf(float(i)/segment * Math::k2Pi));

	// 使用红色显示选中的区域
	Color4f color;
	if (m_Selected)
		color = Color4f(1.0f, 0.0f, 0.0f);
	else
		color = Color4f(1.0f, 1.0f, 1.0f);

	for (i=1; i<segment+1; i++)
	{
		start = end;
		end = Vector3f(p.x + draw_radius * sinf(float(i)/segment * Math::k2Pi), draw_altitude, p.z + draw_radius * cosf(float(i)/segment * Math::k2Pi));
		Renderer::Instance().RenderLine(start, end, color);
	}

	// 绘制海拔
	Renderer::Instance().RenderLine(p, p + Vector3f(0.0f, draw_altitude, 0.0f));

	// 绘制移动方向
	Renderer::Instance().RenderLine(p, p + m_Movement, Color4f(0.5f, 1.0f, 1.0f));
}

void Zone::Update(unsigned long deltaTime)
{
	//Vector3f p = Transform().GetPosition();
	//SetPosition(p + m_Wind * deltaTime * 0.01f);

	if (m_NeedUpdateOBB)
	{
		float draw_radius = m_Radius / 10.0f;

		float ymax = Math::Max(0.0f, m_Altitude / 100.0f);
		float ymin = Math::Min(0.0f, m_Altitude / 100.0f);
		m_OBB.localMin = Vector3f(-draw_radius, ymin, -draw_radius);
		m_OBB.localMax = Vector3f(draw_radius, ymax, draw_radius);

		m_NeedUpdateOBB = false;
	}

	GameObjectBase::Update(deltaTime);

	Vector3f pos = GetWorldPosition();
	pos += m_Movement * deltaTime * 0.001f;
	SetPosition(pos);

	// 消亡判定
	if (m_Radius<=0.0f)
	{
		ZoneManager::Instance().RemoveZone(this);
		m_Scene->RemoveObject(this);
	}
}

void Zone::OnCollide(Zone* other, unsigned long deltaTime)
{
	Vector3f p = m_WorldTransform.GetPosition();
	Vector3f p2 = other->WorldTransform().GetPosition();
	float r = other->m_Radius + this->m_Radius;

	// 两球相交
	if (r*r > (p - p2).SquaredLength())
	{
		if (FLOAT_EQUAL(other->m_Radius, this->m_Radius)) return;

		if (other->m_Radius > this->m_Radius)
		{
			SetRadius(this->m_Radius - 0.001f * deltaTime);
			other->SetRadius(other->m_Radius + 0.001f * deltaTime);
		}
		else
		{
			other->SetRadius(other->m_Radius - 0.001f * deltaTime);
			SetRadius(this->m_Radius + 0.001f * deltaTime);
		}
	}
}

void Zone::OnSelected()
{
	m_Selected = true;
}

void Zone::OnDeselected()
{
	m_Selected = false;
}

void Zone::SetRadius(float radius)
{
	m_Radius = radius;

	m_NeedUpdateOBB = true;
}

void Zone::SetAltitude(float altitude)
{
	m_Altitude = altitude;
	m_NeedUpdateOBB = true;
}

// -------------------------- ZoneManager

ZoneManager::ZoneManager()
{
}

void ZoneManager::AddZone(Zone* zone)
{
	m_ZoneList.insert(zone);
}

void ZoneManager::RemoveZone(Zone* zone)
{
	ZoneList::iterator iter = m_ZoneList.find(zone);
	if (iter==m_ZoneList.end()) return;
	m_ZoneList.erase(iter);
}

void ZoneManager::Update(unsigned long deltaTime)
{
	ZoneList::iterator iter1, iter2;

	// 对所有的区域进行两两碰撞检测
	for (iter1=m_ZoneList.begin(); iter1!=m_ZoneList.end(); iter1++)
	{
		iter2 = iter1;
		iter2++;
		for (; iter2!=m_ZoneList.end(); iter2++)
		{
			(*iter1)->OnCollide(*iter2, deltaTime);
		}
	}
}
