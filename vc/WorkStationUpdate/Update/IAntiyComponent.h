#ifndef _ANTIY_COMPONENT_H
#define _ANTIY_COMPONENT_H

////////////////////////////////////////////////////////////////////////// �����ؽӿ�
// ����ӿ�
class IComponent
{
public:
	// ȡ������ƣ�ʧ�ܷ���NULL, ���򷵻������
	virtual LPCTSTR GetComponentName(LPTSTR lpName, int nSize)			= 0;

	// ȡָ���ӿ��������ָ�룬δ�ҵ�����NULL�����򷵻�ָ��
	virtual VOID *QueryInterface(LPCTSTR lpName, IComponent *pQuerist)	= 0;
};

//��������ӿ�
class IAntiyComponentFactory
{
public:
	virtual int CreateComponent(LPCTSTR lpComponentName, LPVOID *pObject)	= 0;
};

static LPCTSTR ComponentName_IAntiyComponentManager = _T("IAntiyComponentManager");//L"IAntiyComponentManager" 

class IAntiyComponentManager: public IComponent
{
public:
	// ע�����, ʧ�ܷ���false�����򷵻�true
	virtual BOOL RegisterComponent(LPCTSTR lpName, IComponent *pComponent)	= 0;

	// �������, ʧ�ܷ���false�����򷵻�true
	virtual BOOL CreateComponent(LPCTSTR lpName, IComponent **pComponent)	= 0;

	// ע�����, ʧ�ܷ���false�����򷵻�true
	virtual BOOL UnregisterComponent(IComponent *pComponent)				= 0;

	// ȡ��ע���������
	virtual int GetComponentCount()											= 0;	

	// �����ȡ��ע�����ָ��, ʧ�ܷ���false�����򷵻�true
	virtual BOOL GetComponentPtr(int nIdx, IComponent **pComponent)			= 0;
};


// DLL �����������ƶ���
#define ANTIY_DLL_EXPORT "GetAntiyComponentPtr"
// DLL ��������ԭ�Ͷ���
typedef BOOL (*PGetComponentPtr) (IComponent **pComponent, IComponent *pQuerist);

#endif//_ANTIY_COMPONENT_H
