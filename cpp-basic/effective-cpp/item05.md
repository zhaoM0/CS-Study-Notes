# 2 构造、析构、赋值

## 条款05. 了解C++默认编写调用的函数

```c++
class Empty { };

// 等价于
class Empty {
public:
    Empty() {...} // 默认构造在未声明任何构造函数时提供
    Empty(const Empty& obj) {...}
    Empty& operator=(const Empty& rhs) {...}
    ~Empty() {...}
};
```

注意：在这些函数被调用的时候编译器才会负责生成，其次编译器生成的析构函数是 non-virtual 的。

```c++
template<typename T>
class NamedObject {
public:
    NamedObject(const std::string& name, const T& val);
    ...
private:
    std::string nameValue;
    T objValue;
};

NamedObject<int> n1("foo", 42);
NamedObject<int> n2(n1);
```

上述代码编译器生成的默认构造函数会以 `n1` 内成员来设置 `n2` 对象。其中 `nameValue` 是 `string` 类型，会调用 `string` 的 copy constructor，并且以 `n1.nameValue` 为参数。

对于拷贝赋值，行为相似，但是在一些情况下，编译器会拒绝生成 `operator=`

```c++
template <typename T>
class NameObject {
    NameObject(std::string& name, const T& val);
    ...
private:
    std::string& nameValue;      // reference
    const T objValue;            // const
};

std::string newDog("Persephore");
std::string oldDog("Satch");
NameObject<std::string> p1(newDog, 42);
NameObject<std::string> p2(oldDog, 13);
p1 = p2;
```

这里如果存在默认的 `operator=`, `p1.nameValue` 会被引用到 `p2.nameValue`, 而 reference 是不可改指其他对象。其次是 `p1.objValue` 是 `const` 类型，`p1.objValue = p2.objValue` 是非法的，因而编译器会拒绝生成 `operator=`。

最后还有一种情况，基类将 copy assignment 声明为 private, 编译器也不会为 derived class 生成 copy assignment，因为派生需要使用基类的 copy assignment 来初始化基类的部分。


## 条款06. 明确拒绝编译器不想主动生成的函数

对于一些对象而言，它本身是独一无二的，不应该有副本。

```c++
class HomeForSale {...};

HomeForSale h1;
HomeForSale h2;
HomeForSale h3(h1);   // 不应该对独一无二的对象进行拷贝
h1 = h2;              // 同上
```

C++11 新增了 `= delete` 语法，可以明确拒绝编译器生成某些函数。

```c++
class HomeForSale {
    HomeForSale(const HomeForSale&) = delete;
    HomeForSale& operator=(const HomeForSale&) = delete;
};
```

C++11 之前是只声明，而不定义，并且将其定义为私有的。类内部的成员和外部都无法使用

```c++
class HomeForSale {
private:
    HomeForSale(const HomeForSale&);
    HomeForSale& operator=(const HomeForSale&);
};
```

上述做法会将发生链接错误，如果想在编译时引发错误，可以使用以下方案.

```c++
class Uncopyable {
protected:
    Uncopyable() {}                 // 允许 derived 对象构造和析构
    ~Uncopyable() {}
private:
    Uncopyable(const Uncopyable&);  // 阻止 derived 拷贝
    Uncopyable& operator=(const Uncopyable&);
};

class HomeForSale : private Uncopyable {...};
```

只要有拷贝 `HomeForSale` 的行为,编译器就会生成默认的 `copy constructor` 和 `copy assignment` 函数，进而调用 `Uncopyable` 对应的函数，从而引发编译错误。

## 条款07. 为多态基类声明 virtual 析构函数