#pragma once

// �汾��Ϣ
#define GINKGO_VERSION	"0.1.0"

#define EXPORT
#ifdef EXPORT
// ����Ҫ�����ĺ������඼��ǰ����ϴ�ǰ׺
#define DLL		__declspec(dllexport)
#else
#define DLL		__declspec(dllimport)
#endif // EXPORT

/*�������ǵ������������������STL�е�ģ��ģ����յ�����һ�����棺
Warning	C4251 xxx needs to have dll-interface to be used by clients of class 'xxx'
���ڵ��÷������������ӣ��������������ε��������*/
#pragma warning(disable:4251)