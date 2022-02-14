from subprocess import Popen, PIPE

EXECUTABLE_COMMAND = "./bek"
EXECUTABLE_COMPILE_SUB_COMMAND = "comp"
EXECUTABLE_EXECUTE_SUB_COMMAND = "exec"


def test(filepath, expected_result):
    process = Popen([
            EXECUTABLE_COMMAND,
            EXECUTABLE_COMPILE_SUB_COMMAND,
            filepath
        ],
        stdout=PIPE
    )
    (output, err) = process.communicate()
    compile_proccess = process.wait()

    if compile_proccess == 0:
        process = Popen([
                EXECUTABLE_COMMAND,
                EXECUTABLE_EXECUTE_SUB_COMMAND,
                "out.bin"
            ],
            stdout=PIPE
        )
        (output, err) = process.communicate()
        run_proccess = process.wait()

        if expected_result == run_proccess:
            print("{} OK".format(filepath))
        else:
            print("{} ERR: Unexpected result".format(filepath))
    else:
        print("{}, ERR: Failed compiling".format(filepath))


test("test/sum.bek", 115)
test("test/minus.bek", 40)
test("test/plusminus.bek", 195)
