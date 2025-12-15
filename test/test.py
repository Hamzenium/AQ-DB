import socket
import time
import multiprocessing

HOST = "127.0.0.1"
PORT = 6379
OPS_PER_PROCESS = 150000
PROCESSES = 1

def recv_line(sock):
    buf = b""
    while True:
        data = sock.recv(4096)
        if not data:
            return None
        buf += data
        if b"\n" in buf:
            line, _, rest = buf.partition(b"\n")
            return line

def worker(pid, result_queue):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((HOST, PORT))

    start = time.time()
    for i in range(OPS_PER_PROCESS):
        cmd = f"SET Hamza_{i} v{i}\n".encode()
        sock.sendall(cmd)
        recv_line(sock)
    end = time.time()

    ops = OPS_PER_PROCESS / (end - start)
    result_queue.put(ops)

    sock.close()

if __name__ == "__main__":
    result_queue = multiprocessing.Queue()
    processes = []

    start_all = time.time()

    for i in range(PROCESSES):
        p = multiprocessing.Process(target=worker, args=(i, result_queue))
        p.start()
        processes.append(p)

    for p in processes:
        p.join()

    end_all = time.time()

    results = []
    while not result_queue.empty():
        results.append(result_queue.get())

    print("Processes:", PROCESSES)
    print("Per-process OPS:", [int(x) for x in results])
    print("Total OPS:", int(sum(results)))
    print("Total time:", round(end_all - start_all, 2), "s")
