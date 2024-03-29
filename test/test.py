import attrs, pathlib, subprocess

@attrs.define
class Testcase:
  pattern: str
  filename: str
  expected: str

# TODO: more testcases
TESTCASES = (
  Testcase(pattern='hello', filename='test_hello.in', expected='hello\n'),
  Testcase(pattern='henlo', filename='test_hello.in', expected=''),
  Testcase(pattern='hel.o', filename='test_hello.in', expected='hello\n'),
  Testcase(pattern='^hel.o', filename='test_hello.in', expected=''), # TODO: not implemented yet
  Testcase(pattern='hello$', filename='test_hello.in', expected='hello\n'),
  Testcase(pattern='hello\n$', filename='test_hello.in', expected=''),
  Testcase(pattern='..l*o.*', filename='test_hello.in', expected='hello\n'),
  Testcase(
    pattern='.*annotate.*',
    filename='test_rust_excerpt.in',
    expected=
      'Rust won’t let us annotate a type with Copy if the type,'
      ' or any of its parts, has implemented the Drop trait.\n'
  )
)

def run_cmd(argv):
  return subprocess.run(argv, stdout=subprocess.PIPE, text=True, check=False).stdout

def run_crep(*argv):
  argv = ['../crep', *argv]
  try:
    return run_cmd(argv)
  except Exception as e:
    print(f"Error: run_crep(): {e}")

def run_test(testcase):
  pattern, filename, expected = attrs.astuple(testcase)
  filename = f'testcases/{filename}'
  result = run_crep(pattern, filename)
  passed = result == expected
  passed_str = 'PASSED' if passed else 'FAILED'
  print(f'TEST {passed_str}: {pattern=}, {filename=}, {expected=}, {result=}')
  return passed

def run_tests(testcases):
  results = list(map(run_test, testcases))
  passed = sum(results)
  total = len(results)
  percentage = passed / total
  stats = f'TEST STATS: passed {passed} of {total} = {percentage:.2f}% of tests.'
  stats = '_' * len(stats) + '\n' + stats
  print(stats)

def main():
  run_tests(TESTCASES)

if __name__ == '__main__':
  main()
