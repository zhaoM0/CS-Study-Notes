# 使用 `const`

`const`在**左边，被指物为常量；`const`在**右边，指针本身是常量

```cpp
char greeting[] = "hello";
char *p1 = greeting;        // p1可以修改greeting，也可以绑定其他区域
const char *p2 = 指向内容;  // p2不可以修改greeting，但可以绑定其他区域
char* const p3 = greeting;  // p3可以修改greeting, 但与greeting绑定
const char* const p4 = greeting;   // p4不能修改greeting，同时与greeting绑定
```

STL的示例
```cpp
vector<int>::const_iterator;    // 类似 const int *
const vector<int>::iterator;    // 类似 int * const
```

返回值和参数示例
```cpp
class Rational { ... };
const Rational operator*(const Rational& lhs, const Rational& rhs);
// 返回值 const 可以防止 if(a * b = c) 这样的行为，如果是非 const 返回值，则会
// 成为 (a * b) 调用 operator=
```

`const` 成员函数
```cpp
class TextBlock {
	const char& operator[](size_t pos) const           // 用于 const 对象
	{ return text[pos]; }                              // 
	char& operator[](size_t pos) { return text[pos]; } // 用于 non-const 对象
private:
	string text;
};
```

```cpp
TextBlock tb("hello");
cout << tb[0];				// 调用 non-const 的方法
TextBlock ctb("world");
cout << ctb[0];             // 调用 const 的方法
```

`const`成员函数与non-const成员函数的重用
```cpp
// 常量性转除 (casting away constness)
class TextBlock {
	const char& operator[](size_t pos) const 
	{ return text[pos]; } 
	char& operator[](size_t pos) 
	{ 
		return const_cast<char&>(
			static_cast<const TextBlock&>(*this)[pos]
		);
	}
private:
	string text;
};
```

若是non-const `operator[]`内部只是调用 `operator[]`，则会发生递归。转化为 `const` 版本
则会正常调用 `const operator[]`。

如果是 `const operator[]` 去调用 `non-const operator[]`，则非常量的版本可能会修改对象，
这就违反了 `const` 的含义。