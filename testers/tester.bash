#!/bin/bash

# Color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
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

# Test execution function
run_test() {
    local test_name="$1"
    local test_command="$2"
    
    print_info "Running: $test_name"
    
    # Execute the test and capture output and exit code
    if output=$(eval "$test_command" 2>&1); then
        print_success "$test_name - PASSED"
        if [[ -n "$output" ]]; then
            echo -e "${GREEN}Output: $output${NC}"
        fi
    else
        print_error "$test_name - FAILED"
        if [[ -n "$output" ]]; then
            echo -e "${RED}Error: $output${NC}"
        fi
    fi
    echo
}

# Initialize counters
PASSED=0
FAILED=0

echo -e "${BLUE}=== BASH REDIRECTION, PIPES, AND BUILT-IN COMMANDS TEST ===${NC}"
echo

# =============================================================================
# 1. BASIC REDIRECTION TESTS
# =============================================================================
print_info "=== 1. BASIC REDIRECTION TESTS ==="

# Test 1: Output redirection
run_test "Output redirection" 'echo "Hello World" > test_output.txt && cat test_output.txt'
if [[ $? -eq 0 ]]; then ((PASSED++)); else ((FAILED++)); fi

# Test 2: Append redirection
run_test "Append redirection" 'echo "First line" > test_append.txt && echo "Second line" >> test_append.txt && cat test_append.txt'
if [[ $? -eq 0 ]]; then ((PASSED++)); else ((FAILED++)); fi

# Test 3: Input redirection
run_test "Input redirection" 'echo -e "line3\nline1\nline2" > test_input.txt && sort < test_input.txt'
if [[ $? -eq 0 ]]; then ((PASSED++)); else ((FAILED++)); fi

# Test 4: Error redirection
run_test "Error redirection" 'ls nonexistent_file_12345 2> test_error.txt && cat test_error.txt'
if [[ $? -eq 0 ]]; then ((PASSED++)); else ((FAILED++)); fi

# Test 5: Combined stdout and stderr
run_test "Combined stdout/stderr" '{ echo "stdout"; echo "stderr" >&2; } > test_combined.txt 2>&1 && cat test_combined.txt'
if [[ $? -eq 0 ]]; then ((PASSED++)); else ((FAILED++)); fi

# =============================================================================
# 2. PIPE TESTS
# =============================================================================
print_info "=== 2. PIPE TESTS ==="

# Test 6: Basic pipe
run_test "Basic pipe" 'echo "hello world" | tr "[:lower:]" "[:upper:]"'
if [[ $? -eq 0 ]]; then ((PASSED++)); else ((FAILED++)); fi

# Test 7: Multiple pipes
run_test "Multiple pipes" 'echo "one two three four five" | tr " " "\n" | sort | head -3'
if [[ $? -eq 0 ]]; then ((PASSED++)); else ((FAILED++)); fi

# Test 8: Pipe with grep
run_test "Pipe with grep" 'echo -e "apple\nbanana\ncherry\napricot" | grep "^a"'
if [[ $? -eq 0 ]]; then ((PASSED++)); else ((FAILED++)); fi

# Test 9: Pipe with wc
run_test "Pipe with wc" 'echo "This is a test line with several words" | wc -w'
if [[ $? -eq 0 ]]; then ((PASSED++)); else ((FAILED++)); fi

# Test 10: Complex pipe chain
run_test "Complex pipe chain" 'echo "3 1 4 1 5 9 2 6 5 3 5" | tr " " "\n" | sort -n | uniq -c'
if [[ $? -eq 0 ]]; then ((PASSED++)); else ((FAILED++)); fi

# =============================================================================
# 3. HERE DOCUMENT TESTS
# =============================================================================
print_info "=== 3. HERE DOCUMENT TESTS ==="

# Test 11: Basic here document
run_test "Basic here document" 'cat << EOF
This is a here document
with multiple lines
EOF'
if [[ $? -eq 0 ]]; then ((PASSED++)); else ((FAILED++)); fi

# Test 12: Here document with variables
run_test "Here document with variables" 'NAME="TestUser"; cat << EOF
Hello $NAME
Welcome to the system
EOF'
if [[ $? -eq 0 ]]; then ((PASSED++)); else ((FAILED++)); fi

# Test 13: Here document without expansion
run_test "Here document without expansion" 'cat << '\''EOF'\''
This will not expand $HOME
EOF'
if [[ $? -eq 0 ]]; then ((PASSED++)); else ((FAILED++)); fi

# Test 14: Here document with pipe
run_test "Here document with pipe" 'cat << EOF | grep "Subject"
To: user@example.com
Subject: Test Message
From: admin@example.com
EOF'
if [[ $? -eq 0 ]]; then ((PASSED++)); else ((FAILED++)); fi

# =============================================================================
# 4. HERE STRING TESTS
# =============================================================================
print_info "=== 4. HERE STRING TESTS ==="

# Test 15: Basic here string
run_test "Basic here string" 'tr "[:lower:]" "[:upper:]" <<< "hello world"'
if [[ $? -eq 0 ]]; then ((PASSED++)); else ((FAILED++)); fi

# Test 16: Here string with variable
run_test "Here string with variable" 'TEXT="reverse this text"; rev <<< "$TEXT"'
if [[ $? -eq 0 ]]; then ((PASSED++)); else ((FAILED++)); fi

# Test 17: Here string with wc
run_test "Here string with wc" 'wc -w <<< "count these words"'
if [[ $? -eq 0 ]]; then ((PASSED++)); else ((FAILED++)); fi

# =============================================================================
# 5. BUILT-IN COMMANDS TESTS
# =============================================================================
print_info "=== 5. BUILT-IN COMMANDS TESTS ==="

# Test 18: Echo variations
run_test "Echo with -n option" 'echo -n "No newline"'
if [[ $? -eq 0 ]]; then ((PASSED++)); else ((FAILED++)); fi

# Test 19: Echo with -e option
run_test "Echo with -e option" 'echo -e "Tab:\tNewline:\nDone"'
if [[ $? -eq 0 ]]; then ((PASSED++)); else ((FAILED++)); fi

# Test 20: Printf
run_test "Printf formatting" 'printf "Name: %s, Age: %d\n" "Alice" 25'
if [[ $? -eq 0 ]]; then ((PASSED++)); else ((FAILED++)); fi

# Test 21: Type command
run_test "Type command" 'type echo'
if [[ $? -eq 0 ]]; then ((PASSED++)); else ((FAILED++)); fi

# Test 22: PWD command
run_test "PWD command" 'pwd'
if [[ $? -eq 0 ]]; then ((PASSED++)); else ((FAILED++)); fi

# =============================================================================
# 6. ADVANCED REDIRECTION TESTS
# =============================================================================
print_info "=== 6. ADVANCED REDIRECTION TESTS ==="

# Test 23: File descriptor redirection
run_test "File descriptor redirection" 'exec 3> test_fd.txt && echo "Writing to FD 3" >&3 && exec 3>&- && cat test_fd.txt'
if [[ $? -eq 0 ]]; then ((PASSED++)); else ((FAILED++)); fi

# Test 24: Redirect to /dev/null
run_test "Redirect to /dev/null" 'echo "This disappears" > /dev/null'
if [[ $? -eq 0 ]]; then ((PASSED++)); else ((FAILED++)); fi

# Test 25: Tee command
run_test "Tee command" 'echo "Split output" | tee test_tee.txt'
if [[ $? -eq 0 ]]; then ((PASSED++)); else ((FAILED++)); fi

# =============================================================================
# 7. PIPE WITH BUILT-IN COMMANDS
# =============================================================================
print_info "=== 7. PIPE WITH BUILT-IN COMMANDS ==="

# Test 26: Echo with pipe and read
run_test "Echo with pipe and read" 'echo "apple banana cherry" | { read a b c; echo "First: $a"; }'
if [[ $? -eq 0 ]]; then ((PASSED++)); else ((FAILED++)); fi

# Test 27: Printf with pipe
run_test "Printf with pipe" 'printf "1\n2\n3\n" | head -2'
if [[ $? -eq 0 ]]; then ((PASSED++)); else ((FAILED++)); fi

# =============================================================================
# 8. ERROR HANDLING TESTS
# =============================================================================
print_info "=== 8. ERROR HANDLING TESTS ==="

# Test 28: Empty input
run_test "Empty input handling" 'echo "" | wc -l'
if [[ $? -eq 0 ]]; then ((PASSED++)); else ((FAILED++)); fi

# Test 29: Binary data
run_test "Binary data handling" 'echo "Hello World" | base64 | base64 -d'
if [[ $? -eq 0 ]]; then ((PASSED++)); else ((FAILED++)); fi

# Test 30: Large input
run_test "Large input handling" 'seq 1 100 | tail -3'
if [[ $? -eq 0 ]]; then ((PASSED++)); else ((FAILED++)); fi

# =============================================================================
# CLEANUP AND SUMMARY
# =============================================================================
print_info "=== CLEANUP ==="
cleanup_result=$(rm -f test_*.txt 2>&1)
if [[ $? -eq 0 ]]; then
    print_success "Cleanup completed successfully"
else
    print_error "Cleanup failed: $cleanup_result"
fi

echo
print_info "=== TEST SUMMARY ==="
echo -e "${BLUE}Total tests run: $((PASSED + FAILED))${NC}"
echo -e "${GREEN}Tests passed: $PASSED${NC}"
echo -e "${RED}Tests failed: $FAILED${NC}"

if [[ $FAILED -eq 0 ]]; then
    echo -e "${GREEN}🎉 ALL TESTS PASSED! 🎉${NC}"
    exit 0
else
    echo -e "${RED}⚠️  SOME TESTS FAILED ⚠️${NC}"
    exit 1
fi
