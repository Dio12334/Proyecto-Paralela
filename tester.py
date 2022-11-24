from subprocess import Popen, PIPE
from glob import glob

iterations = 4
program_path = "./a.out -noevalprints"

def parse_result(response: str):
    nano_idx, mil_idx = 1 , 3
    return response.split()[mil_idx]
    

file_names = glob("./DataSets/*")

for n in file_names:
  print("OMP, n:",n)
  print("   processors", "  |\t","average(miliseconds)")
  print("-------------------------------------")
  for pr_i in [10, 16, 20, 24, 32]:
    avg = 0
    for i in range(iterations):
      p = Popen([program_path], shell=True, stdout=PIPE, stdin=PIPE)
      p.stdin.write((str(pr_i)+"\n").encode())
      p.stdin.write((str(n)+"\n").encode())
      p.stdin.flush()
      result = p.stdout.readline().strip().decode()
      print(result)
    #   avg += float(parse_result(result))
    # avg = avg / iterations
    print("\t",pr_i, "\t|  ",f'{avg:.20f}')

