from bs4 import BeautifulSoup
from queue import Queue
from thread_pool import ThreadPool
from threading import Lock
from threading import Thread
from time import time
from urllib.parse import urldefrag
from urllib.parse import urljoin
from urllib.parse import urlparse
from urllib3 import PoolManager
import logging


class Fetcher(object):

    def __init__(self, queue_urls, is_extended_fetch=True):
        super(Fetcher).__init__()
        self.seen_urls = set()
        self.queue_urls = queue_urls
        self.lock = Lock()

        self.is_extended_fetch = is_extended_fetch
        self.seeds_netlocs = set([urlparse(seed).netloc for seed in seeds])

        self.daemon = True

    def fetch(self):
        http = PoolManager()

        while True:
            url = self.queue_urls.get()

            try:
                response = http.request('GET', url)
                logging.info('getting {}'.format(url))

                header = response.headers
                body = response.data

                if response.status != 404:
                    page_urls = self._parse(url, header, body)

                    self.lock.acquire()
                    for item in (page_urls - self.seen_urls):
                        self.queue_urls.put(item)
                    self.seen_urls.update(page_urls)
                    self.lock.release()
                else:
                    logging.info('status: {}, {}'.format(response.status, url))

            except Exception as e:
                logging.warn('{}: cannot get {}'.format(e, url))

            self.queue_urls.task_done()

    def _parse(self, url, header, body):
        if not header['Content-type'].startswith('text/html'):
            return set()

        page_urls = set()
        soup = BeautifulSoup(body.decode('utf-8'), 'html5lib')

        for a in soup.findAll('a'):
            page_url = a.get('href')
            normalized_url = urldefrag(urljoin(url, page_url)).url

            if not self.is_extended_fetch and not urlparse(
                    normalized_url).netloc in self.seeds_netlocs:
                continue

            page_urls.add(normalized_url)

        return page_urls


if __name__ == '__main__':
    logging.basicConfig(
        format='%(asctime)s - %(levelname)s - %(message)s', level=logging.INFO)

    num_threads = 4
    pool = ThreadPool(num_threads)

    start = time()

    seeds = ['http://localhost:8000/']
    queue_urls = Queue()

    for url in seeds:
        queue_urls.put(url)

    fetcher = Fetcher(queue_urls, is_extended_fetch=False)

    for _ in range(num_threads):
        pool.add_task(fetcher.fetch)

    # 不能使用ThreadPool自己的wait，这里结束等待的条件是待抓取队列里面没有url了
    queue_urls.join()

    logging.info('fetched {} urls in {:.1f} seconds'.format(
        len(fetcher.seen_urls), time() - start))
