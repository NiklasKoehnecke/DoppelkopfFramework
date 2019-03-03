import subprocess

from subprocess import Popen, PIPE, run
from pathlib import Path
path = Path('..\cmake-build-release\doppelkopf')

p = Popen([str(path)], shell=True, stdout=PIPE, stdin=PIPE)
for ii in range(10):
    value = str(ii) + '\n'
    value = bytes(value, 'UTF-8')  # Needed in Python 3.
    p.stdin.write(value)
    print('written ' + str(value))
    p.stdin.flush()
    result = p.stdout.readline().strip()
    print(result)