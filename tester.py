from subprocess import Popen, PIPE
from glob import glob

iterations = 4
program_path = "./a.out "

def parse_result(response: str):
    mil_idx = 1
    return response.split()[mil_idx]
    
data_files = glob("./DataSets/*")

for file in data_files:

  file_name = file.split("/")[-1]
  file_size = file_name[3:-4]
  print("OMP, n:",file_size)
  print("   processors", "  |\t","average(miliseconds)")
  print("-------------------------------------")
  for pr_i in [10, 16, 20, 24, 32]:
    avg = 0
    for i in range(iterations):
      p = Popen([program_path], shell=True, stdout=PIPE, stdin=PIPE)
      p.stdin.write(f"{file_name} {pr_i}\n".encode())
      p.stdin.flush()
      result = p.stdout.readline().strip().decode()
      result = p.stdout.readline().strip().decode()
      avg += float(parse_result(result))
    avg = avg / iterations
    print("\t",pr_i, "\t|  ",f'{avg:.20f}')

