# 绑定到临时对象的non-const左值引用

绑定到临时对象的non-const左值引用是不可以的，但写代码的时候被引用以及指针蒙蔽了双眼。。。这里简单做个记录。

问题简化如下：

```cpp
string s("chaomai");
string const *&rps = &s; // 错误，a non-const reference to pointer to const string
```

`rps`是绑定到pointer to const string的引用，这是一个non-const引用，表示后续代码中可能会对所绑定对象做操作，但语句结束后，临时对象（值为`&s`）会被销毁，`rps`变成一个dangling reference，任何对其进行的操作都是undefined behavior。

 因此正确的写法是，

```cpp
string const *const &rcps = &s;
```

这里插一句，C++Primer上的写法是`const string *const &rcps = &s;`，但读起来略微不方便，尤其是声明很复杂时（这里不考虑使用type alias）。但按上面的写法，结合[right-left rule](http://chaomai.me/2015/09/17/2015-2015-09-17-char-foo-8/)以后，相对来说是更容易都的（in my opinion）。

上面的写法延长了临时对象的声明周期，因此关于non-const左值引用的另一个问题是变量的生命周期。

下面的代码输出会是什么（取自[stackoverflow](http://stackoverflow.com/questions/2784262/does-a-const-reference-prolong-the-life-of-a-temporary)）？

```cpp
class Sandbox {
 public:
  Sandbox(const string& n) : member(n) {}
  const string& member;
};

int main() {
  Sandbox sandbox(string("four"));
  cout << "The answer is: " << Sandbox(string("four")).member << endl;
  cout << "The answer is: " << sandbox.member << endl;
  return 0;
}
```

先说答案，

```cpp
The answer is: four
The answer is:  // 这里其实是undefined behavior
```

原因，

1. 对于第一个输出

最后附上stackoverflow上关于non-const引用比较不错的几个问题和解答：

1. [Non-const reference may only be bound to an lvalue](http://stackoverflow.com/questions/6967927/non-const-reference-may-only-be-bound-to-an-lvalue)
2. [prolonging the lifetime of temporaries](http://stackoverflow.com/questions/4670137/prolonging-the-lifetime-of-temporaries)
3. [Does a const reference prolong the life of a temporary?](http://stackoverflow.com/questions/2784262/does-a-const-reference-prolong-the-life-of-a-temporary)