### piml idiom
piml idiom的一种解释为private implementation idiom(私有实现编程风格)，另一种解释为pointer to implementation idiom(指向实现的指针编程风格).

### 优点
- 如果只修改实现，不改变接口，可以大幅缩短项目构建时间
- 将接口和实现分离
- 可移植性

### 缺点
- 代码繁琐
- 由于多一层方法调用，应该会有性能损耗，但是大多数情况下应该可以忽略不计
- 应该会占用更多内存