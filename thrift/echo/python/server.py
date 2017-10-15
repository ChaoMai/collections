#!/usr/bin/env python3

import sys
sys.path.append('/Users/chaomai/Documents/codes/github/learning/thrift/gen-py')

from echo import EchoServer
from echo.ttypes import *

from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol
from thrift.server import TServer
from thrift.server import TNonblockingServer

class EchoHandler(object):
    def __init__(self):
        self._count = 0

    def ping(self):
        return self.echo('pong').msg

    def echo(self, str):
        self._count += 1

        echo_msg = EchoMsg()
        echo_msg.id = self._count
        echo_msg.msg = str

        #  raise EchoException(12, '12311114')

        return echo_msg

if __name__ == "__main__":
    handler = EchoHandler()
    processor = EchoServer.Processor(handler)
    transport = TSocket.TServerSocket(port = 9090)
    #  tfactory = TTransport.TBufferedTransportFactory()
    #  pfactory = TBinaryProtocol.TBinaryProtocolFactory()

    #  server = TServer.TSimpleServer(processor, transport, tfactory, pfactory)
    server = TNonblockingServer.TNonblockingServer(processor=processor, lsocket=transport, threads=4)
    server.serve()
