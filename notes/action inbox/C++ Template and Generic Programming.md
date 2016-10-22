# C++模板与泛型编程

模板到特定函数或者类的转化发生在**编译时**。

# 定义模板

## 函数模板

在模板定义中，模板参数列表包含第一个或多个模板参数，且列表不能为空。模板参数列表表示在类或函数定义中用到的**类型或值**。

使用模板时，**隐式或显式地**定义**模板实参**，将其绑定到模板参数上。

当使用一个函数模板时，编译器通常用函数实参了来推断模板实参，编译器用推断出的模板参数来为**实例化**一个特定版本的函数。实例化时，编译器使用**实际的模板实参**代替对应的模板参数来创建一个新*实例*。

```cpp
template <typename T>
int compare(const T &v1, const T &v2) {
  if (v1 < v2) {
    return -1;
  }

  if (v1 > v2) {
    return 1;
  }

  return 0;
}

// 实例化为int compare(const int&, const int&)
compare(1, 0);
```

### 模板类型参数

模板类型参数前必须使用class或typename。在模板参数列表中，这两个关键字的**含义相同**，可以**互换使用**和在同一个模板参数列表中**同时使用**。

```cpp
template <typename T>
int compare(const T &v1, const T &v2) // ...
```

compare有一个模板类型参数T，一般来说，可以将类型参数看作类型说明符，类似内置类型或类类型说明符。

类型参数可用于，

* 指定返回类型或函数的参数类型
* 函数体内的变量声明或类型转换

### 非模板类型参数

非模板类型参数表示一个**值**，使用一个**特定的类型名**来指定非类型参数。

当一个模板被实例化时，非类型参数被一个用户提供或编译器推断出的值所代替，这个值必须是**常量表达式**，因为编译器在编译时需要实例化模板，此时必须知道值是多少。

```cpp
template <typename T, size_t N>
T *arr_begin(T(&arr)[N]) {
  return static_cast<T *>(arr);
}
```

一个非类型参数可以是，

* 一个整型
* 一个指向对象或函数类型的指针
* 左值引用

关于绑定到非类型参数的实参，要注意，

* **必须是一个常量表达式**
* 绑定到指针或非类型参数的实参必须有**静态的生存期**，**不能**用一个普通的局部变量或动态对象作为指针或引用非类型模板参数的实参
* 指针参数可用nullptr或值为0的常量表达式来实例化

由于模板非类型参数是一个常量值，在**需要常量表达式的地方**，可以使用非类型参数。

```cpp
template <typename T, size_t N>
constexpr size_t constexpr_arr_size(T(&arr)[N]) {
  return N;
}

constexpr int size = constexpr_arr_size(arr);
```

### 模板编译

编译器遇到模板定义时，**并不生成代码**。只有当实例化出一个特定版本时，编译器才会生成代码。

不同于调用函数（只需要函数声明）和使用类对象（只需要类定义，但成员函数的定义不必出现），为了生成一个实例，编译器**必须知道**函数模板或类模板成员函数的定义，也就是说，模板的头文件通常**既包括声明也包括定义**。

模板包含两种名字，

* 不依赖于模板参数的名字
    * 在使用模板时，不依赖于模板参数的名字**必须是**可见的。同时必须保证，实例化时，模板的定义，包括类模板的成员的定义，都必须是可见的
* 依赖于模板参数的名字

## 类模板

编译器**不能**为类模板**推断模板参数类型**。

### 定义

类似函数模板。

### 实例化类模板

当使用类模板是，必须提供**显式模板实参**列表。

一个模板类的**每个实例**都形成一个**独立的类**，每个实例化出的类与任何其他实例化出的类**都没有关联**，也不会对任何其他类型的成员有特殊访问权限。

### 在模板作用域中引用模板类型

类模板的名字**不是**一个类型名。一个类模板中如果使用了另一个模板，通常**不将实际类型（或值）**的名字用作其模板实参，而是用模板自己的参数。

### 类模板的成员函数

* 定义在**类模板内**的成员函数被**隐式**声明为**内联函数**
* 类模板的成员函数具有和类模板**相同的模板参数**
* 类模板的每个实例都有**自己版本**的成员函数

从一个类模板生成的类的名字中必须**包含其模板实参**。在类外定义一个成员函数时，模板实参与模板形参相同。

```cpp
template <typename T>
void Blob<T>::check(size_type i, const std::string& msg) const {
  if (i >= data_->size()) {
    throw std::out_of_range(msg);
  }
}
```

### 类模板成员函数的实例化

默认情况下，一个类模板的成员函数**只有当程序用到它**的时候才进行实例化。

即使某种类型**不能完全符合模板操作的要求**，仍可以用该类型实例化类。如：容器的关系运算符，即使元素类型不支持关系运算符，但仍可以用这个元素类型实例化容器，只是无法对这个容器对象用关系运算符（在比较容器对象的时候会报错）。

### 在类代码内简化模板类名的使用

当处于类模板的作用域中时，可以**直接使用模板名**而不必指定模板实参。在类模板外时（如：类模板外定义成员时），**直到遇到类名**才表示进入类的作用域，其他情况（如：返回值）都需要指定模板实参。

```cpp
template <typename T>
class BlobPtr {
 public:
  // ...
  BlobPtr& operator++();
  BlobPtr& operator--();
  // ...
}
```

### 类模板和友元

#### 一对一友元关系

下面的代码中，友元关系被**限定**在用**相同类型实例化的Blob与BlobPtr，以及Blob与相等运算符之间。

```cpp
template <typename T>
class BlobPtr;

template <typename T>
class Blob;

template <typename T>
bool operator==(const Blob<T>&, const Blob<T>&);

template <typename T>
class Blob {
  friend class BlobPtr<T>;
  friend bool operator==<T>(const Blob<T>&, const Blob<T>&);
  // ...
}
```

注意：上面对`operator==`的友元声明中，**必须显式指定模板实参**，即使用`<T>`

#### 通用和特定的模板友元关系

1. 将模板的每个实例声明为自己的友元

  ```cpp
  template <typename T> class Pal;
  class C {
    // 用类C实例化的Pal是C的一个友元
    friend class Pal<C>;

    // Pal2的所有实例都是C的友元，这里无需前置声明
    template <typename T> friend class Pal2;

    // Pal3是C所有实例的友元，不需要前置声明
    friend class Pal3;
  }
  ```

  为了让**所有实例成为友元**，友元声明中必须使用与类模板本身**不同的模板参数**。

2. 令模板自己的类型参数成为友元

  ```cpp
  template <typename T> class Bar {
    friend T;
  }
  ```

  可以使用**内置类型**来实例化Bar。

### 模板类型别名

由于模板不是类型，不能定义typedef引用一个模板。

```cpp
template <typename T> using twin = pair<T, T>;
twing<string> authors;

template <typename T> using partNo = pair<T, unsigned int>;
// 可以固定一个或多个模板参数
partNo<string> books;
```

### 类模板的static成员

每个Foo实例都有自己的static成员实例，所有Foo<X>类型的对象**共享相同的**ctr对象和count函数。

```cpp
template <typename T>
class Foo {
 public:
  static size_t count() { return ++ctr; }

  static size_t ctr;
};

template <typename T>
size_t Foo<T>::ctr = 0;

Foo<int> f1, f2, f3;
f1.count();
f2.count();
f3.count();
cout << f1.ctr << endl; // 3

Foo<string> s1, s2;
s1.count();
s2.count();
cout << s1.ctr << endl; //2

cout << Foo<double>::count() << endl; // 1
```

上面的代码中，模板类（实例化得到的）static数据成员**必须有且仅有**一个定义，但类模板的每个实例有一个独有的static对象，因此static数据成员也定义为模板`template <typename T> size_t Foo<T>::ctr = 0;`。

## 模板参数

### 模板参数与作用域

一个模板名的可用范围是在**其声明之后，至模板声明或定义结束之前**。在模板内**不能重用模板参数名**。

```cpp
typedef double A;
template <typename A, typename B> void f(A a, B b) {
  A tmp = a;
  double B; // 错误
}
```

类似函数参数，声明中的模板参数的名字**不必与定义中的相同**。下面的两个声明都指向相同的函数模板，

```cpp
template <typename A> void f(A);
template <typename B> void f(B);
```

### 使用类的类型成员

对于非类模板，编译器**知道**类的定义，通过作用域运算符访问static成员和类型成员时，编译器知道访问的是什么。

但对于类模板，编译器**直至**实例化时才知道，且C++**假定通过作用域运算符访问的名字不是类型**，因此必须**显式**告诉编译器该名字是一个类型。

```cpp
template <std::size_t H, std::size_t W>
std::ostream &operator<<(std::ostream &os, const Screen<H, W> &sc) {
  for (typename Screen<H, W>::pos i = 0; i < sc.height_; ++i) {
    os << sc.contents_.substr(i * sc.width_, sc.width_) << std::endl;
  }
  return os;
}

template <typename T>
void print_container2(const T &c) {
  // const auto won't work, as the `const auto it` is
  //`const typename T::const_iterator it`
  // for (typename T::const_iterator it = c.cbegin(); it != c.cend(); ++it) {
  for (auto it = c.cbegin(); it != c.cend(); ++it) {
    cout << *it << " ";
  }
  cout << endl;
}
```

这里必须使用typename来指明，而**不能使用class**。

### 默认模板实参

```cpp
template <typename T, typename F = less<T>>
int compare_default(const T &v1, const T &v2, F f = F()) {
  if (f(v1, v2)) {
    return -1;
  }

  if (f(v2, v1)) {
    return 1;
  }

  return 0;
}
```

要注意的是：

* 传递给compare三个实参时，第三个**必须是一个可调用对象**
* 与函数默认实参一样，对于一个模板参数，只有当它**右侧的所有参数都有默认实参时**，它才可以有默认实参

使用方式如下，

```cpp
cout << greater<int>()(1, 4) << endl;  // 1
cout << compare_default(1, 4, greater<int>()) << endl;  // 2
cout << compare_default<int, greater<int>>(1, 4) << endl;  // 3
// cout << compare_default<int, bool (*)(int, int)>(1, 4) << endl; // core
// dump  // 4
cout << compare_default<int, bool (*)(int, int)>(1, 4, [](int, int) {
  return true;
}) << endl;  // 5
```

上述代码中，

1. 使用标准库函数对象
2. 使用默认函数实参，T的类型被推断为int，F被推断为less<int>类型
3. 调用的f与2相同，只是这里没有让编译器推断T和F的类型
4. 错误，lldb中bt后，会发现
    
    ```bash
    * thread #1: tid = 7083, 0x0000000000000000, name = 'a.out', stop reason = signal SIGSEGV: invalid address (fault address: 0x0)
      * frame #0: 0x0000000000000000
        frame #1: 0x00000000004008e6 a.out`int compare_default<int, bool (*)(int, int)>(v1=0x00007fffffffd49c, v2=0x00007fffffffd498, f=0x0000000000000000)(int, int)) + 38 at a.cc:11
        frame #2: 0x0000000000400887 a.out`main + 39 at a.cc:26
        frame #3: 0x00007ffff71bb710 libc.so.6`__libc_start_main + 240
        frame #4: 0x0000000000400789 a.out`_start + 41
    ```

    这里仅仅显式指明了F的类型，但并未给出F的定义，且从这个类型**无法初始化出可调用对象**，因此不知道调用什么

5. 指明了F的类型，且给出了F的定义

### 模板默认实参与类模板

如果类模板的**所有模板参数**都有默认实参，且希望使用这些默认实参，则模板名后面使用**空尖括号对**即可，不需要显式指明模板实参类型。

#### 成员模板

1. 非模板类

    ```cpp
    class DebugDelete {
     public:
      DebugDelete(std::ostream& s = std::cerr) : os(s) {}
      template <typename T>
      void operator()(T* p) const {
        os << "deleting unique_ptr" << std::endl;
        delete p;
      }
    
     private:
      std::ostream& os;
    };
    
    double *pd = new double(10);
    DebugDelete d;
    d(pd);
    
    unique_ptr<vector<string>, DebugDelete> upv(new vector<string>,
                                                DebugDelete());
    upv->push_back("awef");
    
    // deleting unique_ptr
    // deleting unique_ptr
    ```

2. 类模板

    类和成员各自有**自己的、独立的**模板参数。在**类模板外定义**一个成员模板时，必须**同时**为类模板和成员模板**提供模板参数列表**，类模板的参数列表在前，成员自己的在后。
    
    ```cpp
    template <typename T>
    class Blob {
      // ...
      template <typename It>
      Blob(It, It);
      // ...
    }
    
    template <typename T>
    template <typename It>
    Blob<T>::Blob(It b, It e)
        : data_(std::make_shared<std::vector<T>>(b, e)) {}
    ```

3. 实例化与成员模板

实例化一个类模板的成员模板时，必须**同时**提供类和函数模板实参。

```cpp
vector<string> vs{"awef", "qwer", "zxcv"};
Blob<string> b(vs.begin(), vs.end());
```

定义b时，显式地指出Blob的模板实参，构造函数自己的类型参数由vs.begin和vs.end()的类型来推断。

## 控制实例化

模板在使用时才会实例化，如果多个**独立编译**的源文件使用了相同的模板，且提供了相同的模板参数时，每个文件中就会该模板的一个实例，进而带来额外的开销，可以用**显式实例化**来避免这种开销。

1. 实例化声明

```cpp
extern template declaration;
```

编译器遇到extern模板声明时，**不会在本文件中生成**实例化代码，此时即**承诺**在程序其他位置有该实例化的一个**非extern声明（定义）**。

由于编译器在使用模板时自动实例化，因此extern声明必须放在**使用此模板的代码之前**。

2. 实例化定义

```cpp
template declaration;
```

* 实例化定义会**实例化所有成员**，包括内联的成员函数。因此使用一个类型来显式实例化类模板时，必须保证此类型能用于模板的所有成员。
* 如果有**提供了模板实参的类模板**， 且定义了这种类型的指针或引用，或**声明**（不能定义）以其**作为参数或者返回类型**的函数，**并不会**实例化模板。

## 效率与灵活性

unique_ptr和shared_ptr的区别，

1. 管理所保存的指针的策略
2. 重载默认删除器的方式
        
    * 运行时绑定删除器
        重载方便
    * 编译时绑定删除器
        避免间接调用的开销

# 模板实参推断

即从**函数实参来确定模板实参**的过程。用模板实参**生成的函数版本**与给定的函数调用**最为匹配**。

## 类型转换与模板类型参数

传递给调用一个函数模板的实参被用于初始化函数的形参，**使用了模板类型参数的**函数形参有特殊的初始化规则。只有**有限的几种类型转换**会自动地应用于这些实参，编译器**通常不是对实参进行类型转换**，而是**生成一个新的模板实例**。

发生转换的情况，

* 忽略top const
    
    ```cpp
    template <typename T> T fobj(T, T);
    template <typename T> T fref(const T&, const T&);
    
    string a("a");
    const string b("b");
    fobj(a, b); // ok, fobj(string, string)
    fref(a, b); // ok, fref(const string&, const string&)
    ```

* const转换：非constant对象的引用或指针传递给一个const的引用或指针
* 数组或函数指针转换：如果函数形参不是引用类型，则可以对数组或函数类型的实参应用正常的指针转换
    
```cpp
template <typename T> T fobj(T, T);
template <typename T> T fref(const T&, const T&);
template <typename T> T& fref2(const T&, const T&);

int a[10];
int b[42];
fobj(a, b); // ok, fobj(int*, int*)
fref(a, b); // 错误
fref2(a, b); // 错误

int c[10];
fref(a, c); // 错误，不能返回int[10]
fref2(a, c); // ok, int(&f(int(&)[10], int(&)[10]))[10];
```

**其他类型转换**（算数转换、派生类向基类的转换，用户定义的转换）都不能用于函数模板。

### 使用相同模板参数类型的函数形参

传递给形参的实参必须**具有相同的类型**。如果希望对不同类型的实参进行类型转换，可以将函数模板定义为多个类型参数。

```cpp
template <typename T> T f(T, T);

long l;
f(l, 10); // 错误

template <typename T, typename U> T f(T, U);

long l;
f(l, 10); // ok, f(long, int)
```

### 正常类型转换应用于普通函数实参

```cpp
template <typename T> T f(ostream&, int);
```

调用上述函数时，第一个实参会进行正常的类型转换（如果有的话）。

## 函数模板显式实参

常见的需要显式指定的情况，

* 编译器无法推断模板实参的类型
* 函数返回类型与参数列表中任何类型都不相同时

### 指定显示模板实参

```cpp
template <typename T1, typename T2, typename T3>
T1 sum(T2, T3) {}

auto val = sum<long>(1, 10);
```

由于调用sum时，无法从任何实参推断T1的类型，因此必须给T1提供一个显式模板实参。如果**尾部的模板参数可以由函数实参推断出来**，那么可以忽略。

### 正常类型转换应用于显式指定的实参

```cpp
template <typename T> T f(T, T);

long l;
f(l, 10);
```

前面说过，这样的调用是错误的，因为两个实参的类型并不相同，且无法进行类型转换。

```cpp
f<long>(l, 10);
```

显式指定实参后，就是正确的，int被转换为long。

## 尾置返回类型与类型转换

```cpp
template <typename It>
auto fcn(It beg, It end) -> decltype(*beg) {
  return *beg;
}
```

之所以要使用尾置返回类型，是因为**编译器在遇到函数参数列表之前**，beg都是不存在的，也就无法decltype。

### 进行类型转换的标准库模板类

上面的代码中，由于`*beg`是lvalue，因此decltype得到的是一个引用，但有时希望返回的是元素类型本身，而不带引用。

```cpp
template <typename It>
auto fcn2(It beg, It end) -> typename remove_reference<decltype(*beg)>::type {
  return *beg;
}
```

## 函数指针与实参推断

下面pf1的中的参数类型**决定了**comp模板实参的类型。

```cpp
template <typename T>
int comp(const T &, const T &) {
  return 100;
}

int funcomp(int (*)(const int &, const int &)) { return 0; }
int funcomp(int (*)(const string &, const string &)) { return 0; }

int (*pf1)(const int &, const int &) = comp; // ok
funcomp(comp); // 错误
```

而funcomp的调用是无法确定模板实参的类型的，因为两个重载分别可以接受int和string实例化的版本，因此需要显式模板实参`funcomp(comp<int>);`。

当参数是一个函数模板实例的地址时，程序上下文必须满足：对每个模板参数，能**唯一确定其类型或值**。

## 模板实参推断和引用

### 从左值引用函数参数推断类型

* `template <typename T> void f1(T&);`

对于这种情况，只能传递一个**左值**。实参可以是const，也可以不是。如果是，那么T被推断为（low level）const类型。

```cpp
int i = 10;
const int ci = 20;

f1(i); // T是int
f1(ci); // T是const int
f1(30); // 错误
```

* `template <typename T> void f2(const T&);`

这时，可以传递**任何类型**的实参。这里要注意的是，函数参数类型本身就是const了，由于const已经是函数参数类型的一部分，因此，就算实参是const的，const也**不是模板参数类型的一部分**。

```cpp
int i = 10;
const int ci = 20;

f2(i); // T是int
f2(ci); // T是int
f2(30); // T是int
```

### 从右值引用函数参数推断类型

* `template <typename T> void f3(T&&);`

```cpp
f3(30); // T是int
```

### 引用折叠和右值引用参数

```cpp
f3(i); // T是int&
f3(ci); // T是const int&
```

通常将右值引用绑定到左值是不合法的，但有两个例外：

1. 将一个左值传递给函数的右值引用参数，**且**此右值引用指向模板类型参数时，编译器推断模板类型参数为**实参的左值引用类型**。对于上面的调用，T被推断为int&。
2. 一般来说是不能直接定义引用的引用的，但通过*类型别名或模板类型参数间接定义*是可行的。如果创建了一个引用的引用，则这些引用会形成“折叠”，
        
    * **右值引用的右值引用**，折叠为右值引用
    * **其他全部**，折叠为普通的左值引用
    
    引用折叠**只能**应用于间接创建的引用的引用。

使用右值引用的函数模板通常应该有以下两个重载：

```cpp
template <typename T> void f(T&&); // 绑定非const右值
template <typename T> void f(const T&); // 绑定左值和const右值
```

要注意：

下面对f的几个调用，除了第一个的参数是左值引用，其他的都是右值或右值引用。但实例化以后，**只有最后两个调用**实例化后的模板参数是右值引用。

```cpp
template <typename T>
void f(T &&) {}

using l = int &;
using ll = l &;
using r = int &&;
using lr = l &&;
using rr = r &&;
using rrr = rr &&;
using rrrr = rrr &&;

l li = i;
r ri = 20;
rr rri = 20;
rrr rrri = 20;
rrrr rrrri = 20;

f(li); // void f<int&>(int&)
f(ri); // void f<int&>(int&)
f(rri); // void f<int&>(int&)
f(rrri); // void f<int&>(int&)
f(rrrri); // void f<int&>(int&)

f(20); // void f<int>(int&&)
f(std::move(li)); // void f<int>(int&&)
```

原因是**变量表达式**是**左值**（[参考](http://stackoverflow.com/questions/12606574/understanding-rvalue-references)）。

## 理解std::move

```cpp
  /**
   *  @brief  Convert a value to an rvalue.
   *  @param  __t  A thing of arbitrary type.
   *  @return The parameter cast to an rvalue-reference to allow moving it.
  */
  template<typename _Tp>
    constexpr typename std::remove_reference<_Tp>::type&&
    move(_Tp&& __t) noexcept
    { return static_cast<typename std::remove_reference<_Tp>::type&&>(__t); }
```

对于`remove_reference`只要实例化时，模板参数类型为引用（左值或右值引用），那么`remove_reference<T>::type`就是被引用类型。

在move的实参是左值的情况下，用于实例化`remove_reference`的模板实参是int&，进行引用折叠后，`__t`的类型为`int&`。因此通过`static_cast`，发生了从**左值向右值引用的转换**。这样的转换不能隐式发生，但可以用`static_cast`显式的进行。

```cpp
int i = 10;
int &&ri1 = static_cast<int &&>(i);
```

换句话说，虽然可以手动进行左值向右值引用的转换，但使用move更为统一，且容易查找**截断左值（clobber the lvalue，理解为不再需要这个左值）**的代码。

## 转发

如果一个函数参数是**指向模板类型的右值引用**，那么它对应的实参的*const属性和左值/右值属性*将得到**保持**。

用`std::forward`可以保持类型信息，使用时需要通过显式模板实参类调用，forward返回这个**显式实参类型的右值引用**。

通常使用forward传递这样的函数参数，这些参数是，模板类型参数的右值引用。通过其返回类型上的引用折叠，forward可以保持给定实参的左值/右值属性。

当用于一个指向模板参数类型的右值引用函数参数时，forward会**保持实参类型的所有细节**。

```cpp
template <typename F, typename T1, typename T2>
void flip1(F f, T1 &&t1, T2 &&t2) {
  f(t1, t2);
}

template <typename F, typename T1, typename T2>
void flip2(F f, T1 &&t1, T2 &&t2) {
  f(std::forward<T1>(t1), std::forward<T2>(t2));
}

void ff1(int v1, int v2) {}

void ff2(int &&v1, int v2) {}

int v1 = 1;
int v2 = 5;

flip1(ff1, v1, v2);
flip2(ff1, v1, v2);

flip1(ff2, 10, v2); // 错误
flip2(ff2, 10, v2);
```

# 重载与模板

函数模板可以被**另一个模板或一个普通非模板函数**重载。

涉及函数模板时，函数匹配规则会在多个方面收到影响：
