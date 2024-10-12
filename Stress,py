import subprocess

def run_command(command, input_data=None):
    process = subprocess.Popen(command, stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
    stdout, _ = process.communicate(input_data)
    return stdout.strip()

def compile_cpp(source_file, output_file):
    compile_command = ["g++", source_file, "-o", output_file, "-O2", "-std=c++11"]  
    result = subprocess.run(compile_command)
    return result.returncode == 0  

compile_cpp("brute.cpp", "brute") 
compile_cpp("main.cpp", "main") 
compile_cpp("gen.cpp", "gen")

for i in range(100000):
    testcase = run_command(["./gen"])    
    brute_output = run_command(["./brute"], testcase)
    main_output = run_command(["./main"], testcase)
    if brute_output != main_output:
        print("Testcase:\n", testcase)
        print("Output brute:\n", brute_output)
        print("Output sol:\n", main_output)
        break
    else :
        print("Testcase", i, "OK")

