#!/usr/bin/env python3

#
# Test script for codeword coursework submission.
#
# This script is supposed to be run with the name of the codeword.exe
# executable as first argument. It will then run the codeword.exe executable
# with many different inputs to check the output of the --spellcheck and
# --anagram modes of the program.
#

import sys
from os.path import join, abspath, exists, dirname, isdir, basename
from subprocess import Popen, PIPE


class TestFailed(Exception):
    '''Raised to indicate a test failure'''


EXENAME = 'codeword.exe'
TEST_FILES_DIR = dirname(__file__)  # The folder containing this script


#:::::::::::::::::::::
# The main script.
#:::::::::::::::::::::

def main(args):
    '''Test the codeword.exe executable with different inputs'''

    # Check the arguments supplied on the command line
    if len(args) != 1:
        print('Usage: ./testcodeword.py CODEWORDEXE', file=sys.stderr)
        return 1

    exename = args[0]

    # Check that the correct files are in place
    if basename(exename) != EXENAME:
        print('Executable file should be called %r' % EXENAME)
        return 1
    elif not exists(exename):
        print('Executable file %r does not exist' % exename)
        return 1

    if not exists(TEST_FILES_DIR) or not isdir(TEST_FILES_DIR):
        print('Test files directory not found at %r' % TEST_FILES_DIR)
        return 1

    # Actually run the tests
    return run_tests(exename)

def run_tests(exename):
    '''Run tests an executable named in exename'''
    tests = [
        # Test general usage message
        test_usage_message,
        # Test spellcheck mode
        test_spellcheck_invalid_args,
        test_spellcheck_nonexistent_file,
        test_spellcheck_one_word,
        test_spellcheck_multiple_words,
        test_spellcheck_alternate_file,
        # Test anagram mode
        test_anagram_invalid_args,
        test_anagram_nonexistent_file,
        test_anagram_one_word,
        test_anagram_multiple_words,
        test_anagram_alternate_file,
    ]

    failed = 0
    for t in tests:
        try:
            t(exename)
        except TestFailed:
            failed += 1
            print(t.__name__, 'failed.')
        else:
            print(t.__name__, 'passed.')

    print('\n-------------------------------------')
    print('Passed %d out of %d tests' % (len(tests) - failed, len(tests)))
    if failed:
        print('%d test failures' % (failed,))
        return 1
    else:
        print('All tests passed!!!!!')
        return 0


#:::::::::::::::::::::
# Test usage and help
#:::::::::::::::::::::


USAGE_MESSAGE = '''Usage:
codeword.exe [-h/--help]                 : Print this message.
codeword.exe --spellcheck DICTFILE WORDS : Check spelling of words.
codeword.exe --anagram DICTFILE WORD     : Find anagrams of a word.
'''

def test_usage_message(exename):
    '''Test that the program produces the correct usage message.'''
    test_stdout([exename], USAGE_MESSAGE)
    test_stdout([exename, '-h'], USAGE_MESSAGE)
    test_stdout([exename, '--help'], USAGE_MESSAGE)


#:::::::::::::::::::::
# Test --spellcheck mode
#:::::::::::::::::::::


SPELLCHECK_USAGE = 'Usage: codeword.exe --spellcheck DICTFILE WORDS\n'

def test_spellcheck_invalid_args(exename):
    '''Test giving invalid input to the spellcheck mode'''
    test_failure([exename, '--spellcheck'], SPELLCHECK_USAGE)
    test_failure([exename, '--spellcheck', 'dictfile'], SPELLCHECK_USAGE)

def test_spellcheck_nonexistent_file(exename):
    '''Test specifyin a non-existent dictionary file to spellcheck mode'''
    test_failure([exename, '--spellcheck', '..dictfile', 'foo'],
            'Error: "..dictfile" does not exist.\n')

def test_correct(exename, words_file, words):
    '''Test a list of correctly spelled words'''
    expected = ''.join('"%s" is correct.\n' % w for w in words)
    cmdline = [exename, '--spellcheck', words_file] + list(words)
    test_stdout(cmdline, expected)

def test_incorrect(exename, words_file, words, incorrect_word):
    '''Test a list with an incorrectly spelled word'''
    expected = '"%s" is incorrect.\n' % incorrect_word
    cmdline = [exename, '--spellcheck', words_file] + list(words)
    test_failure(cmdline, expected)

def test_spellcheck_one_word(exename):
    '''Test --spellcheck with individual words'''
    wfile = join(TEST_FILES_DIR, 'words3.txt')

    # Test with 1 word
    test_correct(exename, wfile, ['try'])
    test_correct(exename, wfile, ['zoo'])
    test_incorrect(exename, wfile, ['foo'], 'foo')
    test_incorrect(exename, wfile, ['baz'], 'baz')
    test_incorrect(exename, wfile, ['fish'], 'fish')

def test_spellcheck_multiple_words(exename):
    '''Test --spellcheck with multiple words'''
    wfile = join(TEST_FILES_DIR, 'words3.txt')

    # Test with 2 words
    test_correct(exename, wfile, ['try', 'zoo'])
    test_correct(exename, wfile, ['zoo', 'try'])
    test_incorrect(exename, wfile, ['foo', 'baz'], 'foo')
    test_incorrect(exename, wfile, ['baz', 'foo'], 'baz')
    test_incorrect(exename, wfile, ['try', 'baz'], 'baz')
    test_incorrect(exename, wfile, ['baz', 'try'], 'baz')

    # Test with 3 words
    test_correct(exename, wfile, ['try', 'zoo', 'sap'])
    test_correct(exename, wfile, ['sap', 'zoo', 'try'])
    test_incorrect(exename, wfile, ['sap', 'foo', 'baz'], 'foo')
    test_incorrect(exename, wfile, ['foo', 'sap', 'baz'], 'foo')
    test_incorrect(exename, wfile, ['try', 'zoo', 'baz'], 'baz')

def test_spellcheck_alternate_file(exename):
    wfile = join(TEST_FILES_DIR, 'words.txt')

    # Test using a different dictionary file
    test_correct(exename, wfile, ['Siamese', 'fighting', 'fish'])
    test_incorrect(exename, wfile, ['Petricola', 'catfish'], 'Petricola')


#:::::::::::::::::::::
# Test --anagram mode
#:::::::::::::::::::::

ANAGRAM_USAGE = 'Usage: codeword.exe --anagram DICTFILE WORDS\n'

def test_anagram_invalid_args(exename):
    '''Test giving invalid input to the spellcheck mode'''
    test_failure([exename, '--anagram'], ANAGRAM_USAGE)
    test_failure([exename, '--anagram', 'dictfile'], ANAGRAM_USAGE)

def test_anagram_nonexistent_file(exename):
    '''Test specifyin a non-existent dictionary file to spellcheck mode'''
    test_failure([exename, '--anagram', '..dictfile', 'foo'],
            'Error: "..dictfile" does not exist.\n')

def test_anagram(exename, words_file, words, anagrams):
    '''Test expected output of anagrams'''
    lines = []
    for word, anagrams_word in zip(words, anagrams):
        if anagrams_word:
            line = '"%s": %s\n' % (word, ' '.join('"%s"' % a for a in anagrams_word))
        else:
            line = '"%s":\n' % word
        lines.append(line)
    expected = ''.join(lines)
    cmdline = [exename, '--anagram', words_file] + list(words)
    test_stdout(cmdline, expected)

def test_anagram_one_word(exename):
    '''Test --spellcheck with individual words'''
    wfile = join(TEST_FILES_DIR, 'words3.txt')
    t = lambda w, a: test_anagram(exename, wfile, w, a)

    # Test with 1 word
    t(['try'], [['try']])
    t(['zoo'], [['zoo']])
    t(['bar'], [['bar', 'bra']])
    t(['nap'], [['nap', 'pan']])
    t(['fish'], [[]])

def test_anagram_multiple_words(exename):
    '''Test --spellcheck with individual words'''
    wfile = join(TEST_FILES_DIR, 'words3.txt')
    t = lambda w, a: test_anagram(exename, wfile, w, a)

    # Test with 1 word
    t(['try', 'zoo'], [['try'], ['zoo']])
    t(['zoo', 'try'], [['zoo'], ['try']])
    t(['nap', 'bar'], [['nap', 'pan'], ['bar', 'bra']])
    t(['nap', 'fish'], [['nap', 'pan'], []])

def test_anagram_alternate_file(exename):
    wfile = join(TEST_FILES_DIR, 'words.txt')
    t = lambda w, a: test_anagram(exename, wfile, w, a)

    # Test using a different dictionary file
    t(['warned'], [['wander', 'warden', 'warned']])
    t(['beast'], [['abets', 'baste', 'bates', 'beast', 'beats', 'betas']])
    t(['sheet'], [['sheet', 'thees', 'these']])
    t(['finito'], [[]])


#::::::::::::::::::::::
#     Utility functions
#::::::::::::::::::::::


def error_msg(msg, cmdline, out1, out2, name1='stdout', name2='stderr'):
    print('\nError: %s from %r' % (msg, cmdline))
    fmt = '''<- %s ---------------------------------------------
%s
<- %s ---------------------------------------------'''
    out1 = '@' + out1.replace('\n', '@\n@') + '@'
    out2 = '@' + out2.replace('\n', '@\n@') + '@'
    print(fmt % (name1, out1, name1))
    print(fmt % (name2, out2, name2))
    raise TestFailed


def test_stdout(cmdline, expected):
    '''Run command specified in cmdline and verify output.

    Raises TestFailed if:
    1) Non-zero return code from command.
    2) Output on stderr from command.
    3) Output on stdout doesn't match expected.
    '''
    # Run the subprocess and get all output
    stdout, stderr, returncode = run_out_err_ret(cmdline)

    # Error in return code
    if returncode != 0:
        error_msg('non-zero return code', cmdline, stdout, stderr)

    # Output on stderr
    elif stderr:
        error_msg('output on stderr', cmdline, stdout, stderr)

    # Success exit code and nothing on stderr so return stdout
    elif stdout != expected:
        error_msg('output incorrect', cmdline, expected, stdout, 'expected', 'found')

    # Success!
    else:
        print('Passed with %r' % cmdline)

def test_failure(cmdline, expected):
    '''Run command specified in cmdline and verify output.

    The command is expected to fail and return a non-zero exit code and some
    message on stderr.

    Raises TestFailed if:
    1) Zero return code from command.
    2) No output on stderr from command.
    '''
    # Run the subprocess and get all output
    stdout, stderr, returncode = run_out_err_ret(cmdline)

    # Error in return code
    if returncode == 0:
        error_msg('Zero return code', cmdline, stdout, stderr)

    # Success exit code and nothing on stderr so return stdout
    elif stderr != expected:
        error_msg('Output on stderr incorrect', cmdline, expected, stderr,
                  'expected', 'stderr')

    # Success!
    else:
        print('Passed with %r' % cmdline)

def run_out_err_ret(cmdline):
    '''Run command given by cmdline and return stdout, stderr and retcode'''
    cmdline = [abspath(cmdline[0])] + cmdline[1:]
    process = Popen(cmdline, stdout=PIPE, stderr=PIPE)
    (stdout, stderr) = process.communicate()

    # .communicate() returns bytes not text
    # Fold Windows newline-characters
    stdout = stdout.decode('utf-8').replace('\r\n', '\n')
    stderr = stderr.decode('utf-8').replace('\r\n', '\n')

    return stdout, stderr, process.returncode


# Actually run the program
if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
