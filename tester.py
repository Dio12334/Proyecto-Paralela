from subprocess import Popen, PIPE
from glob import glob

output_offset = 4
iterations = 4

program_path = "./tsp.out"
output_path = "runtimes.txt"
    
data_files = sorted(glob("./DataSets/*"))

with open(output_path, "w") as runtimes:
  for file in data_files:
    file_name = file.split("/")[-1]
    file_size = file_name[3:-4]
    runtimes.write(f"file: {file_name}, N = {file_size}\n")
    for pr_i in [1]:
      avg = 0
      runtimes.write(f"{pr_i} ")
      for i in range(iterations):
        p = Popen([program_path], shell=True, stdout=PIPE, stdin=PIPE)
        p.stdin.write(f"{file_name} {pr_i}\n".encode())
        p.stdin.flush()
        for _ in range(output_offset):
          result = p.stdout.readline().strip().decode()
        avg += float(result.split(" ")[-2])
      avg = avg / iterations
      runtimes.write(f"{avg:.7f}\n")