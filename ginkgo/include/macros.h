#pragma once

// �汾��Ϣ
#define GINKGO_VERSION	"0.1.0"

// ѡ��ڵ�����ʽ������2D��Ϸ���붨��ú�ʹ�ð�zֵ���򣻶���3D��Ϸ����ע�͵������ʹ��
// ���������������Ҫ��Ϊ��һ���̶����Ż�͸����ͼ����Ȼ���֮��ĳ�ͻ����Ϊ��û��ʹ�ø�
// ����Ч�Ĵ���ʽ����ֻ�Ǽ򵥵ĸ�����ڵ�λ����������Ⱦ˳�����Լ����Ǿ��������򣬵���
// ���ڵ����ǳ���������Ƚϸ���ʱ����Ȼ�п��ܳ���Ƭ�ζ�ʧ�������
#define GINKGO_SORT_BY_Z_INDEX

#ifdef EXPORT
// ����Ҫ�����ĺ������඼��ǰ����ϴ�ǰ׺
#define DLL		__declspec(dllexport)
#else
//#define DLL		__declspec(dllimport)
#define DLL
#endif // EXPORT

/*�������ǵ������������������STL�е�ģ��ģ����յ�����һ�����棺
Warning	C4251 xxx needs to have dll-interface to be used by clients of class 'xxx'
���ڵ��÷������������ӣ��������������ε��������*/
#pragma warning(disable:4251)