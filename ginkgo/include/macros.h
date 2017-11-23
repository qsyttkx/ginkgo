#pragma once

// 版本信息
#define GINKGO_VERSION	"0.2.1"

/// 选择节点排序方式。对于2D游戏，请定义该宏使用按z值排序；对于3D游戏，请注释掉这个宏使用
/// 按距离排序。这个主要是为了[一定程度上]解决透明贴图和深度缓冲之间的冲突，因为我没有使用
/// 更加有效的处理方式，而只是简单的根据其节点位置来排列渲染顺序，所以即便是经过了排序，当
/// 两个节点距离非常近且网格比较复杂时，仍然有可能出现片段丢失的情况。
#define GINKGO_SORT_BY_Z_INDEX

#ifdef EXPORT
// 对于要导出的函数或类都在前面加上此前缀
#define DLL		__declspec(dllexport)
#else
// 貌似不写__declspec(dllimport)也是好使的那就不脱裤子放屁了
//#define DLL		__declspec(dllimport)
#define DLL
#endif // EXPORT

/// 对于我们的类中用了其他类或者STL中的模板的，会收到这样一条警告：
/// Warning	C4251 xxx needs to have dll-interface to be used by clients of class 'xxx'
/// 由于调用方可以正常链接，所以我们先屏蔽掉这个警告
#pragma warning(disable:4251)