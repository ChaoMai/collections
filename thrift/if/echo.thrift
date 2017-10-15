namespace cpp echo
namespace py echo

enum ErrorCode {
    EMPTY_MSG,
    OTHER_ERROR,
}

struct EchoMsg {
    1: i64 id,
    2: string msg,
}

exception EchoException {
    1: i32 id,
    2: string msg,
}

service EchoServer {
    string ping(),
    EchoMsg echo(1:string str) throws(1:EchoException exp),
}
