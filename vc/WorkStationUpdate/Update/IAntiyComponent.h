#ifndef _ANTIY_COMPONENT_H
#define _ANTIY_COMPONENT_H

////////////////////////////////////////////////////////////////////////// 组件相关接口
// 组件接口
class IComponent
{
public:
	// 取组件名称，失败返回NULL, 否则返回组件名
	virtual LPCTSTR GetComponentName(LPTSTR lpName, int nSize)			= 0;

	// 取指定接口名的组件指针，未找到返回NULL，否则返回指针
	virtual VOID *QueryInterface(LPCTSTR lpName, IComponent *pQuerist)	= 0;
};

//组件工厂接口
class IAntiyComponentFactory
{
public:
	virtual int CreateComponent(LPCTSTR lpComponentName, LPVOID *pObject)	= 0;
};

static LPCTSTR ComponentName_IAntiyComponentManager = _T("IAntiyComponentManager");//L"IAntiyComponentManager" 

class IAntiyComponentManager: public IComponent
{
public:
	// 注册组件, 失败返回false，否则返回true
	virtual BOOL RegisterComponent(LPCTSTR lpName, IComponent *pComponent)	= 0;

	// 创建组件, 失败返回false，否则返回true
	virtual BOOL CreateComponent(LPCTSTR lpName, IComponent **pComponent)	= 0;

	// 注销组件, 失败返回false，否则返回true
	virtual BOOL UnregisterComponent(IComponent *pComponent)				= 0;

	// 取已注册组件数量
	virtual int GetComponentCount()											= 0;	

	// 按序号取已注册组件指针, 失败返回false，否则返回true
	virtual BOOL GetComponentPtr(int nIdx, IComponent **pComponent)			= 0;
};


// DLL 导出函数名称定义
#define ANTIY_DLL_EXPORT "GetAntiyComponentPtr"
// DLL 导出函数原型定义
typedef BOOL (*PGetComponentPtr) (IComponent **pComponent, IComponent *pQuerist);

#endif//_ANTIY_COMPONENT_H
