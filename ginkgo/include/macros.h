#pragma once

// 版本信息
#define GINKGO_VERSION	"0.1.0"

#define EXPORT
#ifdef EXPORT
// 对于要导出的函数或类都在前面加上此前缀
#define DLL		__declspec(dllexport)
#else
#define DLL		__declspec(dllimport)
#endif // EXPORT

/*对于我们的类中用了其他类或者STL中的模板的，会收到这样一条警告：
Warning	C4251 xxx needs to have dll-interface to be used by clients of class 'xxx'
由于调用方可以正常链接，所以我们先屏蔽掉这个警告*/
#pragma warning(disable:4251)