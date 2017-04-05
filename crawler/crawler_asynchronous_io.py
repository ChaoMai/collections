from bs4 import BeautifulSoup
from queue import Queue
from time import time
from urllib.parse import urldefrag
from urllib.parse import urljoin
from urllib.parse import urlparse
import logging
import selectors
import socket

# 问题
# 1. 回调函数传递参数
# 可以考虑使用闭包，但是会导致嵌套多层的情况
# 2. 事件循环和fetch
# 光有fetch里的注册事件和回调函数是不够的，还需要loop读取事件
# 这里表面上可以使用多线程来处理，但是select并非线程安全的

class Fetcher(object):

    def __init__(self, seeds, is_extended_fetch):
        super(Fetcher, self).__init__()
        self.seen_urls = set()
        self.queue_urls = seeds

        self.is_extended_fetch = is_extended_fetch
        self.seeds_netlocs = set([urlparse(seed).netloc for seed in seeds])

        self.selector = selectors.DefaultSelector()

    def fetch(self):
        for url in self.queue_urls:
            self._fetch(url)

    def _fetch(self, url):
        parsed = urlparse(url)
        netloc = parsed.netloc.split(':')[0]
        port = parsed.port
        path = parsed.path

        address = socket.gethostbyname(netloc)

        sock = socket.socket()
        sock.setblocking(False)

        try:
            sock.connect((address, port))
        except Exception as e:
            pass

        self.selector.register(sock.fileno(), selectors.EVENT_WRITE, self._on_connected)

    def _on_connected(key, mask):
        self.selector.unregister(key.fd)
        get = 'GET {} HTTP/1.1\r\nHost: localhost\r\n\r\n'.format(path)
        print(get)


if __name__ == '__main__':
    logging.basicConfig(
        format='%(asctime)s - %(levelname)s - %(message)s', level=logging.INFO)

    start = time()

    seeds = ['http://0.0.0.0:8000/']

    fetcher = Fetcher(seeds, is_extended_fetch=False)
    fetcher.fetch()

    logging.info('fetched {} urls in {:.1f} seconds'.format(
        len(fetcher.seen_urls), time() - start))
