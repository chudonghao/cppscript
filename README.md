# cppscript

## 需求与价值分析
1. 远程函数调用
## 过程分析
```flow
st=>start: Start
i=>inputoutput: 输入年份n
cond1=>condition: n能否被4整除？
cond2=>condition: n能否被100整除？
cond3=>condition: n能否被400整除？
o1=>inputoutput: 输出非闰年
o2=>inputoutput: 输出非闰年
o3=>inputoutput: 输出闰年
o4=>inputoutput: 输出闰年
e=>end
st->i->cond1
cond1(no)->o1->e
cond1(yes)->cond2
cond2(no)->o3->e
cond2(yes)->cond3
cond3(yes)->o2->e
cond3(no)->o4->e
```
字符串<br>
↓


## function stack
example: i = foo(foo(j,k),foo(j,k))

1. 确定**优先级** **结合律**
1. 依次入栈
* 后者**优先级**低于前者时，前者出栈
* **优先级**相等时，按**结合律**选择前者出栈还是后者入栈