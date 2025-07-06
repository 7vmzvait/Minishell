#!/bin/bash
# Minishell Quote and Syntax Error Test Suite
# Comprehensive testing of quote handling, syntax errors, and edge cases

# Color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
GRAY='\033[0;37m'
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
print_syntax_error() {
    echo -e "${RED}🚨 SYNTAX ERROR TEST: $1${NC}"
}

# Test execution function for valid commands
run_test() {
    local test_name="$1"
    local test_command="$2"
    local expected_output="$3"
    
    print_info "Testing: $test_name"
    echo -e "${GRAY}Command: $test_command${NC}"
    
    if output=$(eval "$test_command" 2>&1); then
        if [[ -n "$expected_output" ]]; then
            if [[ "$output" == "$expected_output" ]]; then
                print_success "$test_name - PASSED (Output matches)"
                ((PASSED++))
            else
                print_error "$test_name - FAILED (Output mismatch)"
                echo -e "${RED}Expected: '$expected_output'${NC}"
                echo -e "${RED}Got: '$output'${NC}"
                ((FAILED++))
            fi
        else
            print_success "$test_name - PASSED"
            if [[ -n "$output" ]]; then
                echo -e "${GREEN}Output: '$output'${NC}"
            fi
            ((PASSED++))
        fi
    else
        print_error "$test_name - FAILED (Command failed)"
        echo -e "${RED}Error: $output${NC}"
        ((FAILED++))
    fi
    echo
}

# Test execution function for syntax error commands (should fail)
run_syntax_error_test() {
    local test_name="$1"
    local test_command="$2"
    
    print_syntax_error "$test_name"
    echo -e "${GRAY}Command: $test_command${NC}"
    
    if output=$(eval "$test_command" 2>&1); then
        print_error "$test_name - FAILED (Should have syntax error but succeeded)"
        echo -e "${RED}Unexpected output: '$output'${NC}"
        ((FAILED++))
    else
        print_success "$test_name - PASSED (Correctly detected syntax error)"
        echo -e "${GREEN}Error message: '$output'${NC}"
        ((PASSED++))
    fi
    echo
}

# Initialize counters
PASSED=0
FAILED=0

echo -e "${CYAN}=== MINISHELL QUOTE AND SYNTAX ERROR TEST SUITE ===${NC}"
echo -e "${CYAN}Testing quote handling, syntax errors, and edge cases${NC}"
echo

# =============================================================================
# 1. BASIC QUOTE TESTS
# =============================================================================
print_section "1. BASIC QUOTE TESTS"

# Test 1: Simple double quotes
run_test "Simple double quotes" 'echo "Hello World"' "Hello World"

# Test 2: Simple single quotes
run_test "Simple single quotes" "echo 'Hello World'" "Hello World"

# Test 3: Empty double quotes
run_test "Empty double quotes" 'echo ""' ""

# Test 4: Empty single quotes
run_test "Empty single quotes" "echo ''" ""

# Test 5: Double quotes with spaces
run_test "Double quotes with spaces" 'echo "Hello    World"' "Hello    World"

# Test 6: Single quotes with spaces
run_test "Single quotes with spaces" "echo 'Hello    World'" "Hello    World"

# Test 7: Mixed quotes
run_test "Mixed quotes" 'echo "Hello" '\''World'\''' "Hello World"

# Test 8: Quotes with special characters
run_test "Quotes with special chars" 'echo "!@#$%^&*()"' "!@#$%^&*()"

# Test 9: Single quotes with special characters
run_test "Single quotes special chars" "echo '!@#\$%^&*()'" '!@#$%^&*()'

# Test 10: Quotes preserving whitespace
run_test "Quotes preserving whitespace" 'echo "  leading and trailing  "' "  leading and trailing  "

# =============================================================================
# 2. QUOTE SYNTAX ERROR TESTS
# =============================================================================
print_section "2. QUOTE SYNTAX ERROR TESTS"

# Test 11: Unclosed double quote
run_syntax_error_test "Unclosed double quote" 'echo "unclosed quote'

# Test 12: Unclosed single quote
run_syntax_error_test "Unclosed single quote" "echo 'unclosed quote"

# Test 13: Mismatched quotes 1
run_syntax_error_test "Mismatched quotes 1" 'echo "single quote inside'\''

# Test 14: Mismatched quotes 2
run_syntax_error_test "Mismatched quotes 2" "echo 'double quote inside\""

# Test 15: Multiple unclosed quotes
run_syntax_error_test "Multiple unclosed quotes" 'echo "first quote "second quote'

# Test 16: Nested unclosed quotes
run_syntax_error_test "Nested unclosed quotes" 'echo "outer '\''inner'

# Test 17: Quote at end of line
run_syntax_error_test "Quote at end of line" 'echo test"'

# Test 18: Quote in middle unclosed
run_syntax_error_test "Quote in middle unclosed" 'echo "middle unclosed and more text'

# Test 19: Complex unclosed structure
run_syntax_error_test "Complex unclosed structure" 'echo "start '\''middle'

# Test 20: Backslash before unclosed quote
run_syntax_error_test "Backslash before unclosed" 'echo \"unclosed'

# =============================================================================
# 3. ADVANCED QUOTE HANDLING
# =============================================================================
print_section "3. ADVANCED QUOTE HANDLING"

# Test 21: Escaped quotes in double quotes
run_test "Escaped quotes in double quotes" 'echo "He said \"Hello\""' 'He said "Hello"'

# Test 22: Single quote inside double quotes
run_test "Single quote in double quotes" 'echo "don'\''t"' "don't"

# Test 23: Double quote inside single quotes
run_test "Double quote in single quotes" "echo 'He said \"Hello\"'" 'He said "Hello"'

# Test 24: Multiple escaped quotes
run_test "Multiple escaped quotes" 'echo "\"Hello\" and \"World\""' '"Hello" and "World"'

# Test 25: Alternating quotes
run_test "Alternating quotes" 'echo "Hello" '\''World'\'' "Test"' "Hello World Test"

# Test 26: Quotes with pipe
run_test "Quotes with pipe" 'echo "Hello World" | cat' "Hello World"

# Test 27: Quotes with redirection
run_test "Quotes with redirection" 'echo "test content" > "test file.txt"; cat "test file.txt"' "test content"

# Test 28: Empty quotes in arguments
run_test "Empty quotes in arguments" 'echo hello "" world' "hello  world"

# Test 29: Consecutive quotes
run_test "Consecutive quotes" 'echo "Hello""World"' "HelloWorld"

# Test 30: Quotes with variables
run_test "Quotes with variables" 'VAR="test"; echo "Value: $VAR"' "Value: test"

# =============================================================================
# 4. COMPLEX QUOTE COMBINATIONS
# =============================================================================
print_section "4. COMPLEX QUOTE COMBINATIONS"

# Test 31: Triple nested quotes
run_test "Triple nested quotes" 'echo "outer '\''inner \"deep\" inner'\'' outer"' 'outer inner "deep" inner outer'

# Test 32: Quotes with command substitution
run_test "Quotes with command substitution" 'echo "Date: $(date +%Y-%m-%d)"'

# Test 33: Single quotes preventing expansion
run_test "Single quotes prevent expansion" 'VAR="test"; echo '\''$VAR'\''' '$VAR'

# Test 34: Double quotes allowing expansion
run_test "Double quotes allow expansion" 'VAR="test"; echo "$VAR"' "test"

# Test 35: Mixed quotes with variables
run_test "Mixed quotes with variables" 'VAR="world"; echo "Hello $VAR"'\'' and more'\''' "Hello world and more"

# Test 36: Quotes in command substitution
run_test "Quotes in command substitution" 'echo "Result: $(echo "inner quotes")"' "Result: inner quotes"

# Test 37: Complex escaping
run_test "Complex escaping" 'echo "Line 1\nLine 2\tTabbed"'

# Test 38: Quotes with special characters
run_test "Quotes with special chars" 'echo "Symbols: \$HOME \`whoami\`"' 'Symbols: $HOME `whoami`'

# Test 39: Backslash escaping
run_test "Backslash escaping" 'echo "Path: C:\\Users\\Test"' 'Path: C:\Users\Test'

# Test 40: Unicode in quotes
run_test "Unicode in quotes" 'echo "Unicode: áéíóú"' "Unicode: áéíóú"

# =============================================================================
# 5. QUOTE SYNTAX ERRORS IN COMPLEX SCENARIOS
# =============================================================================
print_section "5. QUOTE SYNTAX ERRORS IN COMPLEX SCENARIOS"

# Test 41: Unclosed quote with pipe
run_syntax_error_test "Unclosed quote with pipe" 'echo "unclosed | cat'

# Test 42: Unclosed quote with redirection
run_syntax_error_test "Unclosed quote with redirection" 'echo "unclosed > file.txt'

# Test 43: Unclosed quote in command substitution
run_syntax_error_test "Unclosed quote in command sub" 'echo "$(echo "unclosed)'

# Test 44: Mismatched quotes in pipeline
run_syntax_error_test "Mismatched quotes in pipeline" 'echo "start | echo '\''end'

# Test 45: Unclosed quote with semicolon
run_syntax_error_test "Unclosed quote with semicolon" 'echo "first; echo second'

# Test 46: Multiple commands with unclosed quote
run_syntax_error_test "Multiple commands unclosed" 'echo "first"; echo "second unclosed'

# Test 47: Unclosed quote in variable assignment
run_syntax_error_test "Unclosed quote in variable" 'VAR="unclosed; echo $VAR'

# Test 48: Unclosed quote in function-like structure
run_syntax_error_test "Unclosed quote in function" 'echo "start; { echo "inner; }'

# Test 49: Complex nested unclosed
run_syntax_error_test "Complex nested unclosed" 'echo "outer $(echo "inner unclosed)'

# Test 50: Unclosed quote with here document
run_syntax_error_test "Unclosed quote with heredoc" 'cat << "EOF
test
EOF'

# =============================================================================
# 6. EDGE CASES AND SPECIAL SCENARIOS
# =============================================================================
print_section "6. EDGE CASES AND SPECIAL SCENARIOS"

# Test 51: Quote only
run_test "Quote only double" 'echo '\''"'\'''' '"'

# Test 52: Quote only single
run_test "Quote only single" "echo \"'\"" "'"

# Test 53: Backslash at end
run_test "Backslash at end" 'echo "test\\"' 'test\'

# Test 54: Multiple backslashes
run_test "Multiple backslashes" 'echo "\\\\test\\\\"' '\\test\\'

# Test 55: Quote with newline
run_test "Quote with newline" 'echo "line1
line2"' "line1
line2"

# Test 56: Tab characters in quotes
run_test "Tab in quotes" 'echo "before	after"' "before	after"

# Test 57: Null character handling
run_test "Null character" 'echo "before\0after"' "beforeafter"

# Test 58: Very long quoted string
run_test "Very long quoted string" 'echo "$(seq 1 100 | tr "\n" " ")"'

# Test 59: Quotes with arithmetic
run_test "Quotes with arithmetic" 'echo "Result: $((2 + 3))"' "Result: 5"

# Test 60: Quotes in conditional
run_test "Quotes in conditional" 'test "hello" = "hello"; echo $?' "0"

# =============================================================================
# 7. REDIRECTION WITH QUOTES
# =============================================================================
print_section "7. REDIRECTION WITH QUOTES"

# Test 61: Quoted filename redirection
run_test "Quoted filename redirection" 'echo "content" > "test file.txt"; cat "test file.txt"' "content"

# Test 62: Quotes in heredoc delimiter
run_test "Quotes in heredoc delimiter" 'cat << "END"
quoted delimiter
END' "quoted delimiter"

# Test 63: Quotes with stderr redirection
run_test "Quotes with stderr redirection" 'echo "error message" >&2' ""

# Test 64: Complex redirection with quotes
run_test "Complex redirection quotes" 'echo "stdout" > "out.txt" 2> "err.txt"; cat "out.txt"' "stdout"

# Test 65: Quoted pipe destination
run_test "Quoted pipe destination" 'echo "test" | cat > "pipe_out.txt"; cat "pipe_out.txt"' "test"

# Test 66: Here string with quotes
run_test "Here string with quotes" 'tr "a-z" "A-Z" <<< "hello world"' "HELLO WORLD"

# Test 67: Quotes in here document content
run_test "Quotes in heredoc content" 'cat << EOF
"quoted content"
'\''single quoted'\''
EOF' '"quoted content"
'\''single quoted'\'''

# Test 68: Multiple quoted redirections
run_test "Multiple quoted redirections" 'echo "data" > "file1.txt"; echo "more" > "file2.txt"; cat "file1.txt" "file2.txt"' "data
more"

# Test 69: Quoted redirection with variables
run_test "Quoted redirection with vars" 'FILE="test"; echo "content" > "$FILE.txt"; cat "$FILE.txt"' "content"

# Test 70: Quotes with append redirection
run_test "Quotes with append" 'echo "line1" > "append.txt"; echo "line2" >> "append.txt"; cat "append.txt"' "line1
line2"

# =============================================================================
# 8. REDIRECTION SYNTAX ERRORS
# =============================================================================
print_section "8. REDIRECTION SYNTAX ERRORS"

# Test 71: Unclosed quote in redirection
run_syntax_error_test "Unclosed quote in redirection" 'echo "test" > "unclosed.txt'

# Test 72: Mismatched quotes in redirection
run_syntax_error_test "Mismatched quotes in redirection" 'echo "test" > "file.txt'\'''

# Test 73: Unclosed quote in heredoc
run_syntax_error_test "Unclosed quote in heredoc" 'cat << "EOF
content
EOF'

# Test 74: Invalid redirection syntax
run_syntax_error_test "Invalid redirection syntax" 'echo "test" >> > "file.txt"'

# Test 75: Multiple redirection errors
run_syntax_error_test "Multiple redirection errors" 'echo "test" > "file1.txt > "file2.txt'

# Test 76: Pipe syntax error
run_syntax_error_test "Pipe syntax error" 'echo "test" | | cat'

# Test 77: Pipe at end
run_syntax_error_test "Pipe at end" 'echo "test" |'

# Test 78: Pipe at beginning
run_syntax_error_test "Pipe at beginning" '| cat'

# Test 79: Multiple pipes
run_syntax_error_test "Multiple pipes" 'echo "test" || cat'

# Test 80: Redirection without command
run_syntax_error_test "Redirection without command" '> "file.txt"'

# =============================================================================
# 9. VARIABLE AND EXPANSION ERRORS
# =============================================================================
print_section "9. VARIABLE AND EXPANSION ERRORS"

# Test 81: Unclosed variable expansion
run_syntax_error_test "Unclosed variable expansion" 'echo "${VAR"'

# Test 82: Invalid variable name
run_syntax_error_test "Invalid variable name" 'echo "$1invalid"'

# Test 83: Unclosed command substitution
run_syntax_error_test "Unclosed command substitution" 'echo "$(echo test"'

# Test 84: Nested unclosed substitution
run_syntax_error_test "Nested unclosed substitution" 'echo "$(echo "$(echo test")"'

# Test 85: Invalid substitution syntax
run_syntax_error_test "Invalid substitution syntax" 'echo "$((2 + )"'

# Test 86: Unclosed arithmetic expansion
run_syntax_error_test "Unclosed arithmetic expansion" 'echo "$((2 + 3"'

# Test 87: Invalid arithmetic syntax
run_syntax_error_test "Invalid arithmetic syntax" 'echo "$((2 + + 3))"'

# Test 88: Unclosed parameter expansion
run_syntax_error_test "Unclosed parameter expansion" 'echo "${VAR:-default"'

# Test 89: Invalid parameter expansion
run_syntax_error_test "Invalid parameter expansion" 'echo "${VAR:}"'

# Test 90: Complex expansion error
run_syntax_error_test "Complex expansion error" 'echo "${VAR:-$(echo "unclosed}"'

# =============================================================================
# 10. EXTREME EDGE CASES
# =============================================================================
print_section "10. EXTREME EDGE CASES"

# Test 91: Deeply nested quotes
run_test "Deeply nested quotes" 'echo "l1 '\''l2 \"l3 \\\"l4\\\" l3\" l2'\'' l1"' 'l1 l2 "l3 \"l4\" l3" l2 l1'

# Test 92: Maximum quote nesting
run_test "Maximum quote nesting" 'echo "a'\''b\"c\\\"d\\\"c\"b'\''a"' 'ab"c\"d\"c"ba'

# Test 93: Quote with all special chars
run_test "Quote with all special chars" 'echo "~!@#$%^&*()_+-={}[]|\\:;\"'\''<>?,./"' "~!@#$%^&*()_+-={}[]|\\:;\"'<>?,./"

# Test 94: Empty command with quotes
run_syntax_error_test "Empty command with quotes" '""'

# Test 95: Only quotes
run_syntax_error_test "Only quotes" '""'

# Test 96: Quote in arithmetic
run_test "Quote in arithmetic" 'echo $(("2" + "3"))' "5"

# Test 97: Massive quote complexity
run_test "Massive quote complexity" 'echo "start $(echo "mid '\''inner \"deep \\\"core\\\" deep\" inner'\'' mid") end"' 'start mid inner "deep \"core\" deep" inner mid end'

# Test 98: Quote with control characters
run_test "Quote with control chars" 'echo "bell:\a tab:\t newline:\n"'

# Test 99: International characters
run_test "International characters" 'echo "中文 العربية русский"' "中文 العربية русский"

# Test 100: Ultimate quote test
run_test "Ultimate quote test" 'echo "\"'\''$(echo "nested $(echo "deep \"quotes\" deep") nested")'\''\"" | cat' "\"'nested deep \"quotes\" deep nested'\""

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

# Calculate success rate
if [[ $((PASSED + FAILED)) -gt 0 ]]; then
    success_rate=$(( (PASSED * 100) / (PASSED + FAILED) ))
    echo -e "${CYAN}Success rate: ${success_rate}%${NC}"
fi

echo
if [[ $FAILED -eq 0 ]]; then
    echo -e "${GREEN}🎉 ALL TESTS PASSED! 🎉${NC}"
    echo -e "${GREEN}Your minishell quote handling is PERFECT!${NC}"
    echo -e "${GREEN}You've mastered the most challenging part of shell parsing!${NC}"
    exit 0
else
    echo -e "${RED}⚠️  $FAILED TESTS FAILED ⚠️${NC}"
    echo -e "${YELLOW}Quote handling is tricky - keep refining your parser!${NC}"
    echo -e "${YELLOW}Focus on the failed syntax error tests for better error handling${NC}"
    exit 1
fi
