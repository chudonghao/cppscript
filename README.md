# cppscript

## function stack
example: i = foo(foo(j,k),foo(j,k))

1. 确定**优先级****结合律**
1. 依次入栈
* 后者**优先级**低于前者时，前者出栈
* **优先级**相等时，按**结合律**选择前者出栈还是后者入栈