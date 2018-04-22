# Reliable, Scalable, and Maintainable Applications

# Reliability

系统就算在遇到灾难（硬件、软件fault，人为error）的时候也应该正确的工作。如果系统能够预期并处理这些fault，那么系统就是fault-tolerant或者resilient。这里的fault指的是特定类型的fault。

fault不同于failure，fault指的是系统的某个组件偏离了要求，而failure指的是系统本身无法提供服务。fault可以减少指0，并通过设计fault-tolerance机制来避免fault导致failure。可以通过刻意的触发rate of fault，来测试系统的fault-tolerance机制。

虽然常常倾向于容忍fault而不是避免，有时避免时更好的，因为没有修复的方法。本书主要讨论了可以被修复的fault。

## Hardware Faults

硬件模块会出错，可以通过硬件模块冗余的方式（RAID、双电源供应、热插拔CPU、电池和发电机）来减少系统的falilure rate。硬件模块冗余的方式减少了单机failure的几率，使得小应用可以实现高可用。

对于大规模的系统，例如部署在云服务上的([AWS: The Good, The Bad and The Ugly]())，会出现单机不可用的情况。通过使用软件fault-tolerance机制、而非仅仅硬件冗余方式，可以实现系统的高可用。

## Software Errors

硬件模块出错一般是随机和独立的，但软件的错误往往是难以预期的。某个错误可能会引发更多的软件错误。

导致错误的bug有可能已经存在了很长时间，最终由于某个异常条件被触发。这意味着软件做出了某种假设，当假设为false的时候，就会导致错误。

系统中软件的错误并没有一个快速的解决方法，通过检查假设、测试、进程隔离、监控、分析系统行为、允许进程crash和重启，可以减少这类错误。

## Human Errors

人为错误难以避免，且占导致服务下线原因的大部分。

* 以最小化引发错误几率的方式来设计系统
* 构造一个允许发生错误，且不影响真实用户的地方来进行安全的探索和实验
* 测试
* 允许快速恢复
* 监控
* 实施良好的管理和实践

# Scalability

当系统增长（数据量、流量、复杂度）时，应该有一个合理的方法来应对这样的增长。

## 描述负载

首先需要简洁的描述系统当前的负载，这样才能套理论增长的问题。

描述负载可以使用几个数字，称之为load parameter。具体的参数取决于系统架构。

有了load parameter以后，就可以从两个方面来讨论负载增加是的情况，

* 当增加一个load parameter，并保持系统资源不变，系统的性能会如何被影响？
* 当增加一个load parameter，要增加多少系统资源，才能保持性能不变？

这里需要一种描述性能的方法。

## 描述性能

对于批处理系统，通常使用throughput（吞吐量）-每秒能处理的记录数，或者任务处理特定大小数据集的时间。
对于在线系统，常常使用response time（响应时间）。

如果多次请求同一个服务，会发现response time每次都有差别。因此response time不能被看做单一的值，而是一个值的分布。

通常使用如下统计值来描述性能：

* 平均response time：一般被认为是算术平均。但这个值不能反映请求的延迟情况。
* percentile（百分位数）：p90，p999等。

高百分位数又叫做tail latencies，tail latencies会直接影响用户体验。如果一个请求，需要多次的后端调用，即使只有小部分调用很慢，获得一个slow call的几率也会因为客户端需要多次后端调用而增加，进而导致更多的请求变慢（这叫做[tail latency amplification](https://research.google.com/pubs/pub40801.html)）。

队列延迟常常是response time在高percentile时的主要原因。因为服务器只能并行处理少量的工作，只需要少量较慢的请求处理就能拖慢后续的处理。因此，需要在客户端来测量response time。

## 负载增加时的解决方案



# Maintainability

随着时间的推移，不同的人会在系统上工作（维护和开发新功能），他们都应该能够以高效的方式进行工作。

