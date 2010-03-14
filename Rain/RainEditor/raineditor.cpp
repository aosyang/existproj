#include "raineditor.h"

#define PROP_POS_X tr("Position X")
#define PROP_POS_Z tr("Position Z")
#define PROP_ALTITUDE tr("Altitude(m)")
#define PROP_RADIUS tr("Radius(m)")

RainEditor::RainEditor(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags),
	  m_EngineToPropPanel(false),
	  m_SelectedZone(NULL)
{
	ui.setupUi(this);

	m_EngineWidget = new EngineWidget();
	ui.engineLayout->insertWidget(0, m_EngineWidget);

	// ��ʼ������
	m_EngineWidget->InitEngine();

	m_Timer = new QTimer();
	connect(m_Timer, SIGNAL(timeout()), this, SLOT(TimerTick()));

	// ����ʱ��Ϊ1���룬����cpuռ��
	m_Timer->setInterval(1);
	m_Timer->start();

	// �����������
	CreatePropPanel();

	// ����ѡ�ж����ź�������������Ĳ�֮�������
	connect(m_EngineWidget, SIGNAL(ZoneSelected(Zone*)), this, SLOT(UpdateObjectProperties(Zone*)));

	// ��������еĶ�������
	UpdateObjectProperties(NULL);
}

RainEditor::~RainEditor()
{

}

void RainEditor::CreatePropPanel()
{
	m_VariantManager = new QtVariantPropertyManager();

	QtVariantEditorFactory *variantFactory = new QtVariantEditorFactory();

	m_VariantEditor = new QtTreePropertyBrowser();
	m_VariantEditor->setFactoryForManager(m_VariantManager, variantFactory);

	m_VariantEditor->setPropertiesWithoutValueMarked(true);
	m_VariantEditor->setRootIsDecorated(false);

	m_VariantEditor->show();

	ui.propLayout->addWidget(m_VariantEditor);

	connect(m_VariantManager, SIGNAL(valueChanged(QtProperty*, const QVariant&)), this, SLOT(valueChanged(QtProperty*, const QVariant&)));

}

void RainEditor::UpdateObjectProperties(Zone* zone)
{
	// ��������б������
	m_VariantEditor->clear();
	m_SelectedZone = zone;

	if (!zone) return;

	m_EngineToPropPanel = true;

	// ������Ŀ(����������Ŀ����)
	QtProperty *topItem;
	QtVariantProperty* item;
	topItem = m_VariantManager->addProperty(QtVariantPropertyManager::groupTypeId(), tr("Zone Properties"));

	Vector3f zonePos = zone->WorldTransform().GetPosition();
	

	// ��Ŀ��Ŀ
	item = m_VariantManager->addProperty(QVariant::Double, PROP_POS_X);
	item->setValue(QVariant(zonePos.x));
	topItem->addSubProperty(item);

	item = m_VariantManager->addProperty(QVariant::Double, PROP_POS_Z);
	item->setValue(QVariant(zonePos.z));
	topItem->addSubProperty(item);

	item = m_VariantManager->addProperty(QVariant::Double, PROP_RADIUS);
	item->setValue(QVariant(zone->GetRadius()));
	topItem->addSubProperty(item);

	item = m_VariantManager->addProperty(QVariant::Double, PROP_ALTITUDE);
	item->setValue(QVariant(zone->GetAltitude()));
	topItem->addSubProperty(item);

	// ��ӵ����Դ�����
	m_VariantEditor->addProperty(topItem);

	m_EngineToPropPanel = false;

}

void RainEditor::valueChanged(QtProperty* qProp, const QVariant& var)
{
	// �����洫������ֵ���������ʱ�������������
	if (m_EngineToPropPanel) return;

	if (qProp->propertyName()==PROP_POS_X)
	{
		Vector3f pos = m_SelectedZone->GetWorldPosition();
		pos.x = var.toFloat();
		m_SelectedZone->SetPosition(pos);
	}
	else if (qProp->propertyName()==PROP_POS_Z)
	{
		Vector3f pos = m_SelectedZone->GetWorldPosition();
		pos.z = var.toFloat();
		m_SelectedZone->SetPosition(pos);
	}
	else if (qProp->propertyName()==PROP_RADIUS)
	{
		m_SelectedZone->SetRadius(var.toFloat());
	}
	else if (qProp->propertyName()==PROP_ALTITUDE)
	{
		m_SelectedZone->SetAltitude(var.toFloat());
	}
}

void RainEditor::TimerTick()
{
	m_EngineWidget->UpdateEngine();
}
