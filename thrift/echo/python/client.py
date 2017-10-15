#!/usr/bin/env python3

import sys
sys.path.append('/Users/chaomai/Documents/codes/github/learning/thrift/gen-py')

from echo import EchoServer

from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

def main():
    socket = TSocket.TSocket('localhost', 9090)
    #  transport = TTransport.TBufferedTransport(socket)
    transport = TTransport.TFramedTransport(socket)
    protocol = TBinaryProtocol.TBinaryProtocol(transport)
    client = EchoServer.Client(protocol)

    transport.open()

    while True:
        line = sys.stdin.readline()

        if line == None:
            transport.close()
            return 0

        line = line.strip()
        if line == 'ping':
            print(client.ping())
        elif len(line) > 0:
            print(client.echo(line))
        else:
            continue


if __name__ == "__main__":
    sys.exit(main())
