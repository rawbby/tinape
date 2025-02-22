import os

__all__ = ['FileLock']

if os.name == 'nt':
    import msvcrt
else:
    import fcntl


class FileLock:
    def __init__(self, filename: str):
        self.filename: str = filename

    def __enter__(self):
        self.fp = open(self.filename, 'wb')
        if os.name == 'nt':
            self.fp.seek(0)
            msvcrt.locking(self.fp.fileno(), msvcrt.LK_LOCK, 1)
        else:
            fcntl.flock(self.fp.fileno(), fcntl.LOCK_EX)

    def __exit__(self, _type, value, tb):
        if os.name == 'nt':
            self.fp.seek(0)
            msvcrt.locking(self.fp.fileno(), msvcrt.LK_UNLCK, 1)
        else:
            fcntl.flock(self.fp.fileno(), fcntl.LOCK_UN)
        self.fp.close()
