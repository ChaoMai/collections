# 概念

Thrift 的网络栈如下，

```
+-------------------------------------------+
| Server                                    |
| (single-threaded, event-driven etc)       |
+-------------------------------------------+
| Processor                                 |
| (compiler generated)                      |
+-------------------------------------------+
| Protocol                                  |
| (JSON, compact etc)                       |
+-------------------------------------------+
| Transport                                 |
| (raw TCP, HTTP etc)                       |
+-------------------------------------------+
```

## Transport

传输层提供了读写网络的简单抽象，这使得 Thrift 将底层传输与系统解耦。Transport 接口提供了包括如下方法的接口：

* open
* close
* read
* write
* flush

除此之外，Thrift 同时使用 ServerTransport 接口来接受或者创建原始的传输对象。正如名称所示，ServerTransport 主要用于服务端创建传输对象以处理新的连接。

* open
* listen
* accept
* close

下面列出的是主流 Thrift-supported 语言提供的传输功能，

* file
* http


## Protocol

Protocol 抽象定义了将内存中的数据映射到 wire-format 的机制。换句话说，一个协议指定了数据类型如何使用下层的 Transport 来编码/解码自身。因此协议实现管理了编码方式，以及相应的序列化/反序列化。

下面是 Protocol 的接口，

```

writeMessageBegin(name, type, seq)
writeMessageEnd()
writeStructBegin(name)
writeStructEnd()
writeFieldBegin(name, type, id)
writeFieldEnd()
writeFieldStop()
writeMapBegin(ktype, vtype, size)
writeMapEnd()
writeListBegin(etype, size)
writeListEnd()
writeSetBegin(etype, size)
writeSetEnd()
writeBool(bool)
writeByte(byte)
writeI16(i16)
writeI32(i32)
writeI64(i64)
writeDouble(double)
writeString(string)

name, type, seq = readMessageBegin()
                  readMessageEnd()
name = readStructBegin()
       readStructEnd()
name, type, id = readFieldBegin()
                 readFieldEnd()
k, v, size = readMapBegin()
             readMapEnd()
etype, size = readListBegin()
              readListEnd()
etype, size = readSetBegin()
              readSetEnd()
bool = readBool()
byte = readByte()
i16 = readI16()
i32 = readI32()
i64 = readI64()
double = readDouble()
string = readString()
```

Thrift Protocol 是面向流的。无需任何显式的帧。例如，在开始序列化一个 list 之前，不必事先知道 list 中元素的数目。主流 Thrift-supported 语言支持的的协议有，

* binary
* compact
* json


## Processor

一个 Processor 封装了从输入流读取和写入输出流的功能。输入和输出流由 Protocol 对象代表。Processor 接口非常简单，

```
interface TProcessor {
    bool process(TProtocol in, TProtocol out) throws TException
}
```

特定服务的 processor 实现由 compiler 生成。Processor 主要就是从网络读取数据（使用输入接口），并将数据的处理委托给 handler （由用户实现），以及将数据写入网络（使用输出接口）。


## Server

一个 Server 将上述所有的功能整合到了一起：

* 创建一个 transport
* 为 transport 创建输出/输出 protocols
* 基于输出/输出 protocols 创建一个 processor
* 等待传入链接，并将它们转交给 processor


# 功能

* interface description language - Everything is specified in an IDL file from which bindings for many languages can be generated. See Thrift IDL
* language bindings - Thrift is supported in many languages and environments
* namespaces - Each Thrift file is in its own namespace allowing you to use the same identifier in multiple Thrift files
* language namespaces - Per Thrift file you can specify which namespace should be used for each programming language
* base types - Thrift has a small set of base types. See Thrift Types
* constants and enumerations - Constant values can be assigned logical names
* structs - Use structs to group related data. Structs can have fields of any type. See Thrift Types
* sparse structs - Optional base fields that have not been set and reference fields that are null will not be sent across the wire
* struct evolution - The addition and removal of fields is handled without breaking existing clients by using integer identifiers for fields
* containers - You can use sets, lists and maps of any type: base types, structs and other containers. See Thrift Types
* type definitions - Any type can be given a name that better describes it
* services - A service is a group of functions
* service inheritance - Subservices implement all functions of their base services and can have additional functions
* asynchronous invocations - Functions that do not return a result can be invoked asynchronously so the client is not blocked until the server has finished processing the request. The server may execute asynchronous invocations of the same client in parallel/out of order
* exceptions - If an error occurs a function can throw a standard or user-defined exception. See Thrift Types
* cyclic structs - Starting with version 0.9.2, Thrift supports structs that contain themselves, or other structs to be declared later.


