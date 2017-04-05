from queue import Queue
from threading import Thread


class Worker(Thread):

    def __init__(self, task_queue):
        super(Worker, self).__init__()
        self.task_queue = task_queue
        # daemon线程会随着主线程的退出而退出，不必显示的去停止
        # 如果不设置daemon，那么就必须实现一个stop worker的方法，
        # 类似self.is_run = False
        self.daemon = True
        self.start()

    def run(self):
        while True:
            func, args, kwargs = self.task_queue.get()

            try:
                func(*args, **kwargs)
            except Exception as e:
                raise e

            self.task_queue.task_done()


class ThreadPool(object):

    def __init__(self, num_threads):
        super(ThreadPool, self).__init__()
        self.task_queue = Queue()
        for _ in range(num_threads):
            Worker(self.task_queue)

    def add_task(self, func, *args, **kwargs):
        self.task_queue.put((func, args, kwargs))

    def wait(self):
        self.task_queue.join()
