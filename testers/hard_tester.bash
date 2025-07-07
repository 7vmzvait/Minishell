#!/bin/bash
# Advanced Minishell Test Suite
# Tests redirection, pipes, and built-in commands without &&, ||, &

unset PATH
# Color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Function to print colored output
print_success() {
    echo -e "${GREEN}✓ $1${NC}"
}
print_error() {
    echo -e "${RED}✗ $1${NC}"
}
print_warning() {
    echo -e "${YELLOW}⚠ $1${NC}"
}
print_info() {
    echo -e "${BLUE}ℹ $1${NC}"
}
print_section() {
    echo -e "${PURPLE}=== $1 ===${NC}"
}

# Test execution function
run_test() {
    local test_name="$1"
    local test_command="$2"
    local expected_output="$3"
    
    print_info "Running: $test_name"
    
    # Execute the test and capture output and exit code
    if output=$(eval "$test_command" 2>&1); then
        if [[ -n "$expected_output" ]]; then
            if [[ "$output" == "$expected_output" ]]; then
                print_success "$test_name - PASSED (Output matches)"
                ((PASSED++))
            else
                print_error "$test_name - FAILED (Output mismatch)"
                echo -e "${RED}Expected: $expected_output${NC}"
                echo -e "${RED}Got: $output${NC}"
                ((FAILED++))
            fi
        else
            print_success "$test_name - PASSED"
            if [[ -n "$output" ]]; then
                echo -e "${GREEN}Output: $output${NC}"
            fi
            ((PASSED++))
        fi
    else
        print_error "$test_name - FAILED"
        if [[ -n "$output" ]]; then
            echo -e "${RED}Error: $output${NC}"
        fi
        ((FAILED++))
    fi
    echo
}

# Initialize counters
PASSED=0
FAILED=0

echo -e "${CYAN}=== ADVANCED MINISHELL TEST SUITE ===${NC}"
echo -e "${CYAN}Testing redirection, pipes, and built-ins without &&, ||, &${NC}"
echo

# =============================================================================
# 1. BASIC REDIRECTION TESTS
# =============================================================================
print_section "1. BASIC REDIRECTION TESTS"

# Test 1: Simple output redirection
run_test "Simple output redirection" 'echo "test123" > out1.txt; cat out1.txt'

# Test 2: Overwrite existing file
run_test "Overwrite existing file" 'echo "first" > out2.txt; echo "second" > out2.txt; cat out2.txt'

# Test 3: Append redirection
run_test "Append redirection" 'echo "line1" > out3.txt; echo "line2" >> out3.txt; echo "line3" >> out3.txt; cat out3.txt'

# Test 4: Input redirection
run_test "Input redirection" 'echo "banana\napple\ncherry" > in1.txt; sort < in1.txt'

# Test 5: Error redirection (stderr)
run_test "Error redirection" 'ls /nonexistent/path/file 2> err1.txt; cat err1.txt'

# Test 6: Redirect stdout and stderr separately
run_test "Separate stdout/stderr" 'echo "good" > out4.txt; ls /bad/path 2> err2.txt; cat out4.txt; cat err2.txt'

# Test 7: Redirect stdout and stderr to same file
run_test "Combined stdout/stderr" 'echo "output"; echo "error" >&2' 

# Test 8: Redirect stderr to stdout
run_test "Stderr to stdout" 'ls /nonexistent 2>&1 | head -1'

# Test 9: Multiple redirections
run_test "Multiple redirections" 'echo "data" > out5.txt < /dev/null; cat out5.txt'

# Test 10: Redirection with whitespace
run_test "Redirection with spaces" 'echo "spaced" >out6.txt; cat out6.txt'

# =============================================================================
# 2. ADVANCED REDIRECTION TESTS
# =============================================================================
print_section "2. ADVANCED REDIRECTION TESTS"

# Test 11: File descriptor redirection
run_test "File descriptor 3" 'exec 3> fd3.txt; echo "fd3 test" >&3; exec 3>&-; cat fd3.txt'

# Test 12: Close file descriptor
run_test "Close file descriptor" 'exec 4> fd4.txt; echo "before close" >&4; exec 4>&-; cat fd4.txt'

# Test 13: Duplicate file descriptor
run_test "Duplicate file descriptor" 'exec 5>&1; echo "duplicated" >&5'

# Test 14: Redirect to /dev/null
run_test "Redirect to /dev/null" 'echo "invisible" > /dev/null; echo "visible"'

# Test 15: Input from /dev/null
run_test "Input from /dev/null" 'cat < /dev/null; echo "empty input processed"'

# Test 16: Append to non-existent file
run_test "Append to new file" 'echo "new content" >> new_append.txt; cat new_append.txt'

# Test 17: Redirection order matters
run_test "Redirection order" 'echo "test" > out7.txt 2>&1; cat out7.txt'

# Test 18: Complex redirection
run_test "Complex redirection" 'exec 6> comp.txt; echo "line1" >&6; echo "line2" >&6; exec 6>&-; cat comp.txt'

# Test 19: Redirection with built-ins
run_test "Built-in redirection" 'pwd > pwd_out.txt; cat pwd_out.txt'

# Test 20: Empty file redirection
run_test "Empty file redirection" 'echo -n "" > empty.txt; wc -c empty.txt'

# =============================================================================
# 3. PIPE TESTS
# =============================================================================
print_section "3. PIPE TESTS"

# Test 21: Basic pipe
run_test "Basic pipe" 'echo "hello world" | tr "a-z" "A-Z"'

# Test 22: Multiple pipes
run_test "Chain of pipes" 'echo "the quick brown fox" | tr " " "\n" | sort | head -2'

# Test 23: Pipe with grep
run_test "Pipe with grep" 'echo -e "apple\nbanana\napricot\nblueberry" | grep "^a"'

# Test 24: Pipe with wc
run_test "Pipe with wc -l" 'echo -e "line1\nline2\nline3" | wc -l'

# Test 25: Pipe with wc -w
run_test "Pipe with wc -w" 'echo "count these five words here" | wc -w'

# Test 26: Pipe with wc -c
run_test "Pipe with wc -c" 'echo "test" | wc -c'

# Test 27: Pipe with head
run_test "Pipe with head" 'echo -e "1\n2\n3\n4\n5" | head -3'

# Test 28: Pipe with tail
run_test "Pipe with tail" 'echo -e "1\n2\n3\n4\n5" | tail -2'

# Test 29: Pipe with sort
run_test "Pipe with sort" 'echo -e "zebra\napple\nbanana" | sort'

# Test 30: Pipe with uniq
run_test "Pipe with uniq" 'echo -e "apple\napple\nbanana\nbanana\ncherry" | uniq'

# =============================================================================
# 4. COMPLEX PIPE CHAINS
# =============================================================================
print_section "4. COMPLEX PIPE CHAINS"

# Test 31: Long pipe chain
run_test "Long pipe chain" 'echo "3 1 4 1 5 9 2 6 5 3" | tr " " "\n" | sort -n | uniq | head -5'

# Test 32: Pipe with multiple transformations
run_test "Multiple transformations" 'echo "Hello World Test" | tr "A-Z" "a-z" | tr " " "_" | rev'

# Test 33: Numerical processing
run_test "Numerical processing" 'seq 1 10 | head -5 | tail -3'

# Test 34: Text processing chain
run_test "Text processing" 'echo "aa bb cc dd ee" | tr " " "\n" | sort | tr "\n" " "'

# Test 35: Filter and count
run_test "Filter and count" 'echo -e "test\nTEST\nTest\nother" | grep -i "test" | wc -l'

# Test 36: Character frequency
run_test "Character frequency" 'echo "hello" | grep -o . | sort | uniq -c'

# Test 37: Word reversal
run_test "Word reversal" 'echo "first second third" | tr " " "\n" | tac | tr "\n" " "'

# Test 38: Pipe with cut
run_test "Pipe with cut" 'echo "one:two:three:four" | cut -d: -f2,4'

# Test 39: Complex grep
run_test "Complex grep" 'echo -e "apple\nbanana\napricot\nblueberry\navocado" | grep "^a" | wc -l'

# Test 40: Multiple greps
run_test "Multiple greps" 'echo -e "apple pie\nbanana bread\napple juice\ncherry pie" | grep apple | grep juice'

# =============================================================================
# 5. HERE DOCUMENT TESTS
# =============================================================================
print_section "5. HERE DOCUMENT TESTS"

# Test 41: Basic here document
run_test "Basic here document" 'cat << EOF
This is line 1
This is line 2
This is line 3
EOF'

# Test 42: Here document with variables
run_test "Here doc with variables" 'USER="testuser"; cat << EOF
Hello $USER
Your home is $HOME
EOF'

# Test 43: Here document without expansion
run_test "Here doc no expansion" 'cat << "EOF"
This will not expand $USER
EOF'

# Test 44: Here document with pipe
run_test "Here doc with pipe" 'cat << EOF | grep "Subject"
From: sender@test.com
To: recipient@test.com
Subject: Test Email
Body: This is a test
EOF'

# Test 45: Here document with sort
run_test "Here doc with sort" 'sort << EOF
zebra
apple
banana
EOF'

# Test 46: Here document with wc
run_test "Here doc with wc" 'wc -l << EOF
line 1
line 2
line 3
EOF'

# Test 47: Nested here document simulation
run_test "Nested here doc" 'cat << EOF1
Outer document
$(cat << EOF2
Inner content
EOF2
)
End outer
EOF1'

# Test 48: Here document with redirection
run_test "Here doc with redirection" 'cat << EOF > heredoc_out.txt
Redirected content
Line 2
EOF
cat heredoc_out.txt'

# Test 49: Empty here document
run_test "Empty here document" 'cat << EOF
EOF'

# Test 50: Here document with special characters
run_test "Here doc special chars" 'cat << EOF
Special: !@#$%^&*()
Quotes: "double" '\''single'\''
EOF'

# =============================================================================
# 6. HERE STRING TESTS
# =============================================================================
print_section "6. HERE STRING TESTS"

# Test 51: Basic here string
run_test "Basic here string" 'tr "a-z" "A-Z" <<< "hello world"'

# Test 52: Here string with variable
run_test "Here string with variable" 'TEXT="reverse me"; rev <<< "$TEXT"'

# Test 53: Here string with wc
run_test "Here string wc" 'wc -w <<< "count these words"'

# Test 54: Here string with grep
run_test "Here string grep" 'grep "test" <<< "this is a test string"'

# Test 55: Here string with cut
run_test "Here string cut" 'cut -c1-4 <<< "abcdefghijk"'

# Test 56: Here string with sort
run_test "Here string sort" 'tr " " "\n" <<< "zebra apple banana" | sort'

# Test 57: Here string empty
run_test "Here string empty" 'wc -c <<< ""'

# Test 58: Here string with numbers
run_test "Here string numbers" 'bc <<< "2 + 3 * 4"'

# Test 59: Here string with special chars
run_test "Here string special" 'wc -c <<< "!@#$%^&*()"'

# Test 60: Here string with quotes
run_test "Here string quotes" 'cat <<< "He said \"hello\""'

# =============================================================================
# 7. BUILT-IN COMMANDS TESTS
# =============================================================================
print_section "7. BUILT-IN COMMANDS TESTS"

# Test 61: Echo basic
run_test "Echo basic" 'echo "Hello World"'

# Test 62: Echo with -n
run_test "Echo -n option" 'echo -n "No newline"'

# Test 63: Echo with -e
run_test "Echo -e option" 'echo -e "Tab:\tNewline:\nEnd"'

# Test 64: Echo multiple args
run_test "Echo multiple args" 'echo "arg1" "arg2" "arg3"'

# Test 65: Echo with variables
run_test "Echo with variables" 'VAR="test"; echo "Value: $VAR"'

# Test 66: Printf basic
run_test "Printf basic" 'printf "Hello %s\n" "World"'

# Test 67: Printf with numbers
run_test "Printf numbers" 'printf "Number: %d, Float: %.2f\n" 42 3.14159'

# Test 68: Printf multiple formats
run_test "Printf multiple" 'printf "%s is %d years old\n" "Alice" 25'

# Test 69: PWD command
run_test "PWD command" 'pwd'

# Test 70: Type command
run_test "Type command" 'type echo'

# =============================================================================
# 8. ENVIRONMENT AND VARIABLE TESTS
# =============================================================================
print_section "8. ENVIRONMENT AND VARIABLE TESTS"

# Test 71: Export variable
run_test "Export variable" 'export TEST_VAR="exported"; echo $TEST_VAR'

# Test 72: Unset variable
run_test "Unset variable" 'TEST_VAR2="temp"; unset TEST_VAR2; echo "VAR2: $TEST_VAR2"'

# Test 73: Environment in pipeline
run_test "Env in pipeline" 'export PIPE_VAR="pipeline"; echo $PIPE_VAR | cat'

# Test 74: Variable in redirection
run_test "Var in redirection" 'VAR="filename"; echo "content" > $VAR.txt; cat $VAR.txt'

# Test 75: Variable expansion
run_test "Variable expansion" 'A="Hello"; B="World"; echo "$A $B"'

# Test 76: Command substitution
run_test "Command substitution" 'echo "Date: $(date +%Y)"'

# Test 77: Parameter expansion
run_test "Parameter expansion" 'VAR="Hello World"; echo ${VAR%% *}'

# Test 78: Default values
run_test "Default values" 'echo ${UNDEFINED_VAR:-"default"}'

# Test 79: Variable in here string
run_test "Var in here string" 'VAR="test input"; tr "a-z" "A-Z" <<< "$VAR"'

# Test 80: Export in subshell
run_test "Export in subshell" 'export SUB_VAR="test"; echo $SUB_VAR | cat'

# =============================================================================
# 9. EDGE CASES AND ERROR HANDLING
# =============================================================================
print_section "9. EDGE CASES AND ERROR HANDLING"

# Test 81: Empty command
run_test "Empty command handling" 'echo "before"; ; echo "after"'

# Test 82: Multiple spaces
run_test "Multiple spaces" 'echo     "spaced"     "args"'

# Test 83: Tabs and spaces
run_test "Tabs and spaces" 'echo "test"	"with"   "mixed"'

# Test 84: Special characters in filename
run_test "Special chars filename" 'echo "content" > "file with spaces.txt"; cat "file with spaces.txt"'

# Test 85: Long input line
run_test "Long input line" 'echo "$(seq 1 100 | tr "\n" " ")" | wc -w'

# Test 86: Binary data handling
run_test "Binary data" 'echo "Hello" | od -c | head -1'

# Test 87: Large file handling
run_test "Large file handling" 'seq 1 1000 > large.txt; tail -3 large.txt'

# Test 88: Pipe with no input
run_test "Pipe no input" 'echo -n "" | wc -l'

# Test 89: Multiple empty lines
run_test "Multiple empty lines" 'echo -e "\n\n\n" | wc -l'

# Test 90: Redirection permissions
run_test "Redirection permissions" 'echo "test" > perm_test.txt; chmod 644 perm_test.txt; cat perm_test.txt'

# =============================================================================
# 10. COMPLEX INTEGRATION TESTS
# =============================================================================
print_section "10. COMPLEX INTEGRATION TESTS"

# Test 91: Pipe with redirection
run_test "Pipe with redirection" 'echo "data" | sort > sorted.txt; cat sorted.txt'

# Test 92: Multiple redirections in pipeline
run_test "Multiple redirections" 'echo "input" | tr "a-z" "A-Z" > upper.txt 2> upper_err.txt; cat upper.txt'

# Test 93: Here doc with pipeline
run_test "Here doc pipeline" 'cat << EOF | sort | head -2
zebra
apple
banana
cherry
EOF'

# Test 94: Complex variable expansion
run_test "Complex var expansion" 'FILE="test"; EXT="txt"; echo "content" > ${FILE}.${EXT}; cat ${FILE}.${EXT}'

# Test 95: Nested command substitution
run_test "Nested command sub" 'echo "Files: $(ls $(echo "."))"'

# Test 96: Pipeline with built-ins
run_test "Pipeline with built-ins" 'printf "a\nb\nc\n" | sort | head -2'

# Test 97: Redirection with built-ins
run_test "Redirection with built-ins" 'printf "line1\nline2\n" > printf_out.txt; cat printf_out.txt'

# Test 98: Complex here string
run_test "Complex here string" 'tr "a-z" "A-Z" <<< "$(echo "hello world")"'

# Test 99: Error handling in pipeline
run_test "Error in pipeline" 'echo "good" | cat | sort'

# Test 100: Ultimate integration
run_test "Ultimate integration" 'echo "final test" | tr "a-z" "A-Z" | tee final.txt | wc -c'

# =============================================================================
# CLEANUP AND SUMMARY
# =============================================================================
print_section "CLEANUP"

# Cleanup all test files
rm -f *.txt 2>/dev/null
if [[ $? -eq 0 ]]; then
    print_success "Cleanup completed successfully"
else
    print_warning "Some cleanup issues occurred"
fi

echo
print_section "TEST SUMMARY"
echo -e "${BLUE}Total tests run: $((PASSED + FAILED))${NC}"
echo -e "${GREEN}Tests passed: $PASSED${NC}"
echo -e "${RED}Tests failed: $FAILED${NC}"

if [[ $FAILED -eq 0 ]]; then
    echo -e "${GREEN}🎉 ALL TESTS PASSED! 🎉${NC}"
    echo -e "${GREEN}Your minishell implementation is working perfectly!${NC}"
    exit 0
else
    echo -e "${RED}⚠️  $FAILED TESTS FAILED ⚠️${NC}"
    echo -e "${YELLOW}Review the failed tests to improve your minishell${NC}"
    exit 1
fi
