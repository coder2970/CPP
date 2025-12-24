#include <iostream>
#include <algorithm>
#include <set>

// int main()
//{
//	// 初始化:initializer_lists
//	//std::set<int> s = { 10, 4, 7, 2, 6 };
//
//	// 去重 + 升序
//	//std::set<int> s;
//
//	// 去重 + 降序 - 修改仿函数
//	//std::set<int, std::greater<int>> s;
//	//s.insert(10);
//	//s.insert(5);
//	//s.insert(9);
//	//s.insert(4);
//	//s.insert(6);
//	//s.insert(4);
//
//	// 插入:initializer_lists
//	//s.insert({ 2, 4, 1, 3 });
//
//	// 迭代器 - 双向迭代器
//	//for (auto e : s)
//	//	std::cout << e << std::endl;
//
//	//std::set<int>::iterator it = s.begin();
//	//auto it = s.begin();
//	//while (it != s.end())
//	//{
//	//	std::cout << *it << " ";
//	//	it++;
//
//	//	// 不可修改
//	//	// *it = 1;
//	//}
//
//	// find : 算法库中的find和此处的find的区别
//	//auto it1 = find(s.begin(), s.end(), 6);
//	//std::cout << *it1;
//
//	//auto it2 = s.find(6);
//	//std::cout << *it2;
//
//	//// 删除set中最小的值 - 删 begin
//	//auto it = s.begin();
//	////s.erase(it);
//	//for (auto e : s)
//	//	std::cout << e <<" ";
//	//std::cout << std::endl;
//
//	//int n = s.erase(2);
//	//if (n == 0)
//	//{
//	//	std::cout << "删除失败, 元素不存在" << std::endl;
//	//}
//	//for (auto e : s)
//	//	std::cout << e <<" ";
//	//std::cout << std::endl;
//
//	//int x;
//	//std::cin >> x;
//	//auto it = s.find(x);
//	//if (it != s.end())
//	//{
//	//	// 传入的迭代器必须有效
//	//	s.erase(it);
//	//}
//	//else
//	//{
//	//	std::cout << x << "不存在" << std::endl;
//	//}
//	//for (auto e : s)
//	//	std::cout << e << " ";
//	//std::cout << std::endl;
//
//	// 判断元素是否存在
//	//int x;
//	//std::cin >> x;
//	//if (s.count(x))
//	//	std::cout << x << "存在" << std::endl;
//	//else
//	//	std::cout << x << "不存在" << std::endl;
//
//	return 0;
// }

// lower_bond upper_bond
// int main()
//{
//	//std::set<int> s = { 10, 20, 30 ,40, 50, 60, 70 ,80,90,100 };
//	std::set<int> s = { 10, 20, 35 ,40, 50, 65, 70 ,80,90,100 };
//
//	for (auto e : s)
//		std::cout << e << " ";
//	std::cout << std::endl;
//
//	// 实现itlow 到 itupper 区间的删除
//	// 返回 >=30
//	auto itlow = s.lower_bound(30);
//
//	// 返回 >60
//	auto itupper = s.upper_bound(60);
//
//	// 删除这段区间的值
//	s.erase(itlow, itupper);
//
//	for (auto e : s)
//		std::cout << e << " ";
//	std::cout << std::endl;
//
//	return 0;
// }

// int main()
//{
//	std::multiset<int> s = { 1,3 ,4, 13, 7,3,6,1 };
//	//std::multiset<int>::iterator it = s.begin();
//	//// auto it = s.begin();
//	//// 结果:1 1 3 3 4 6 7 13
//	//while (it != s.end())
//	//{
//	//	std::cout << *it << " ";
//	//	it++;
//	//}
//
//	int x;
//	std::cin >> x;
//	// find查找中序遍历的第一个值为x的节点
//	auto it = s.find(x);
//	while (it != s.end() && *it == x)
//	{
//		std::cout << *it << " ";
//		it++;
//	}
//	std::cout << std::endl;
//
//	// count 统计值为x的个数
//	std::cout << s.count(x) << std::endl;
//
//	// erase 删除所有值为x的节点
//	s.erase(x);
//
//	for (auto e : s)
//		std::cout << e << " ";
//	std::cout << std::endl;
//	return 0;
// }
#include <string>
#include <map>
// int main()
// {
//     // 定义简单的字典
//     // insert
//     std::map<std::string, std::string> dict;

//     // 有名对象
//     std::pair<std::string, std::string> kv1("sort", "排序");
//     dict.insert(kv1);

//     // 匿名对象
//     dict.insert(std::pair<std::string, std::string>("apple", "苹果"));

//     // c++98:make_pair
//     dict.insert(std::make_pair("red", "红色"));

//     // c++11:不是initializer_lists
//     // 多参数构造函数的隐式类型转换
//     // pair(const T1&a,const T2&b):first(a),second(b) {}
//     // 过程 : {"house", "房子"} -> pair对象 -> dict.insert(pair对象)
//     dict.insert({"house", "房子"});
//     //	// 已经存在的值再次插入会失败
//     //	dict.insert({ "house" , "屋子" });
//     // 迭代器
//     auto it = dict.begin();
//     while (it != dict.end())
//     {
//         // 实际上是: it.operator->()->first 编译器省略了一个(优化)
//         std::cout << it->first << " " << it->second << std::endl;
//         it++;
//     }
//     return 0;
// }

// int main()
//{
//	// 外层{}:initializer_lists
//	// 内层{}:多参数构造支持隐式类型转换,转化为pair类型
//	std::map<std::string, std::string > dict = { {"sort", "排序" } ,{"apple", "苹果"} ,{"house", "房子"} };
//
//	// 这里最好加上&,否则拷贝代价很大
//	for (auto& kv : dict)
//	{
//		// kv相当于*it的别名
//		std::cout << kv.first << kv.second << std::endl;
//	}
//	return 0;
// }

// int main()
//{
//	// 统计次数
//	std::string arr[] = { "苹果","西瓜","苹果","西瓜","苹果","苹果","西瓜","苹果","香蕉","苹果","香蕉" };
//	std::map<std::string, int> count;
//	for (auto& e : arr)
//	{
//		//auto it = count.find(e);
//		//if (it == count.end())
//		//{
//		//	// 第一次出现
//		//	count.insert({ e, 1 });
//		//}
//		//else
//		//{
//		//	it->second++;
//		//}
//
//		// []
//		count[e]++;
//	}
//
//	std::pair< std::map<std::string, int>::iterator, bool> ret1 = count.insert({ "苹果",1 });
//	std::pair< std::map<std::string, int>::iterator, bool> ret2 = count.insert({ "草莓",1 });
//
//	//V& operator[](const K& key)
//	//{
//	//	// 直接插入Value的默认构造
//	//	// 自定义类型调用其对应的默认构造(vector-空数组,string-空字符串
//	//	// 内置类型也有其默认构造(int-0, double-0.0,ptr-nullptr)
//	//	pair<iteraotr, bool> ret = insert(key, V());
//
//	//	// 无论insert成功失败,该迭代器都是指向key的迭代器
//
//	//	// ret.first:取pair中的迭代器,再由迭代器取key对应的value(通过迭代器中节点的指针访问)
//	//	return ret.first->second;
//	//}
//
//	for (auto& e : count)
//		std::cout << e.first << e.second << std::endl;
//	return 0;
// }

// int main()
//{
//	std::map<std::string, std::string> dict;
//
//	// 1.插入
//	dict["left"];
//
//	// 2.插入 + 修改
//	dict["right"] = "右边";
//
//	// 3.修改
//	dict["left"] = "左边";
//
//	// 4.查找
//	std::cout << dict["left"] << std::endl;
//	return 0;
// }

int main()
{
    std::multimap<std::string, std::string> dict;
    dict.insert({"apple", "苹果"});
    dict.insert({"sort", "排序"});

    dict.insert({"apple", "xxx"});

    for (auto &e : dict)
        std::cout << e.first << e.second << std::endl;
    return 0;
}