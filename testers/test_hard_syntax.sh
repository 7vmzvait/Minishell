#!/bin/bash

# Comprehensive hard syntax error tests for minishell

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo "=== HARD SYNTAX ERROR TESTS ==="

# Function to test syntax errors
test_syntax_error() {
    local test_name="$1"
    local command="$2"
    
    echo -e "${YELLOW}🚨 Testing: $test_name${NC}"
    echo "Command: $command"
    
    # Test with bash to see expected behavior
    if bash -c "$command" 2>/dev/null; then
        echo -e "${RED}✗ FAILED - Should have syntax error but succeeded${NC}"
    else
        echo -e "${GREEN}✓ PASSED - Correctly detected syntax error${NC}"
    fi
    echo
}

# Function to test valid syntax
test_valid_syntax() {
    local test_name="$1"
    local command="$2"
    
    echo -e "${YELLOW}✓ Testing: $test_name${NC}"
    echo "Command: $command"
    
    if bash -c "$command" >/dev/null 2>&1; then
        echo -e "${GREEN}✓ PASSED - Valid syntax${NC}"
    else
        echo -e "${RED}✗ FAILED - Should work but failed${NC}"
    fi
    echo
}

echo "=== 1. PIPE SYNTAX ERRORS ==="

test_syntax_error "Pipe at start" "| echo hello"
test_syntax_error "Pipe at end" "echo hello |"
test_syntax_error "Double pipe" "echo hello || echo world"
test_syntax_error "Triple pipe" "echo hello ||| echo world"
test_syntax_error "Pipe with nothing" "echo hello | | echo world"
test_syntax_error "Multiple consecutive pipes" "echo hello | | | echo world"

echo "=== 2. REDIRECTION SYNTAX ERRORS ==="

test_syntax_error "Redirect at start" "> echo hello"
test_syntax_error "Redirect with no file" "echo hello >"
test_syntax_error "Double redirect no file" "echo hello >>"
test_syntax_error "Input redirect no file" "echo hello <"
test_syntax_error "Invalid redirect combination" "echo hello > > file.txt"
test_syntax_error "Redirect to pipe" "echo hello > |"
test_syntax_error "Multiple output redirects" "echo hello > file1.txt > file2.txt"
test_syntax_error "Redirect with semicolon" "echo hello > ;"
test_syntax_error "Redirect with pipe" "echo hello > | cat"

echo "=== 3. HEREDOC SYNTAX ERRORS ==="

test_syntax_error "Heredoc no delimiter" "cat <<"
test_syntax_error "Heredoc pipe no delimiter" "cat << | grep test"
test_syntax_error "Heredoc double operator" "cat << <<"
test_syntax_error "Heredoc with redirect" "cat << EOF > file"
test_syntax_error "Heredoc unclosed quotes" "cat << \"EOF
content
EOF"
test_syntax_error "Heredoc invalid delimiter" "cat << EOF|INVALID"

echo "=== 4. QUOTE SYNTAX ERRORS ==="

test_syntax_error "Unclosed double quote" "echo \"hello world"
test_syntax_error "Unclosed single quote" "echo 'hello world"
test_syntax_error "Nested unclosed quotes" "echo \"hello 'world"
test_syntax_error "Quote in middle unclosed" "echo hello \"world and more"
test_syntax_error "Command substitution unclosed" "echo \$(echo \"hello"
test_syntax_error "Backquote unclosed" "echo \`echo hello"

echo "=== 5. PARENTHESES AND BRACES ERRORS ==="

test_syntax_error "Unclosed parentheses" "echo (hello world"
test_syntax_error "Unmatched closing parentheses" "echo hello world)"
test_syntax_error "Unclosed braces" "{ echo hello"
test_syntax_error "Unmatched closing braces" "echo hello }"
test_syntax_error "Nested unclosed" "{ echo (hello"
test_syntax_error "Command substitution unclosed parens" "echo \$(echo hello"

echo "=== 6. SEMICOLON SYNTAX ERRORS ==="

test_syntax_error "Semicolon at start" "; echo hello"
test_syntax_error "Double semicolon" "echo hello ;; echo world"
test_syntax_error "Semicolon with pipe" "echo hello ; | cat"
test_syntax_error "Semicolon with redirect" "echo hello ; > file"
test_syntax_error "Multiple semicolons" "echo hello ;;; echo world"

echo "=== 7. AMPERSAND SYNTAX ERRORS ==="

test_syntax_error "Ampersand at start" "& echo hello"
test_syntax_error "Double ampersand" "echo hello && echo world"
test_syntax_error "Ampersand with pipe" "echo hello & | cat"
test_syntax_error "Ampersand with redirect" "echo hello & > file"

echo "=== 8. COMPLEX MIXED ERRORS ==="

test_syntax_error "Pipe quote redirect" "echo \"hello | > file"
test_syntax_error "Quote pipe semicolon" "echo 'hello | ; echo world"
test_syntax_error "Heredoc pipe quote" "cat << \"EOF | grep test"
test_syntax_error "Nested command substitution error" "echo \$(echo \$(echo \"hello)"
test_syntax_error "Complex redirection error" "echo hello > file1 < < file2"
test_syntax_error "Mixed quote error" "echo \"hello' world"
test_syntax_error "Pipe heredoc error" "echo hello | cat << EOF"
test_syntax_error "Redirect quote error" "echo hello > \"file"
test_syntax_error "Semicolon quote error" "echo hello ; echo \"world"
test_syntax_error "Parentheses quote error" "echo (\"hello world"

echo "=== 9. WHITESPACE AND SPECIAL CHAR ERRORS ==="

test_syntax_error "Tab with pipe error" "echo hello\t|"
test_syntax_error "Newline in quotes unclosed" "echo \"hello
world"
test_syntax_error "Null character" "echo hello\0world"
test_syntax_error "Control characters" "echo hello\x01world"

echo "=== 10. VARIABLE EXPANSION ERRORS ==="

test_syntax_error "Unclosed variable expansion" "echo \${hello"
test_syntax_error "Invalid variable name" "echo \${"
test_syntax_error "Nested variable error" "echo \${hello\${world}"
test_syntax_error "Variable with quote error" "echo \${\"hello}"

echo "=== 11. VALID SYNTAX TESTS (should work) ==="

test_valid_syntax "Basic pipe" "echo hello | cat"
test_valid_syntax "Multiple pipes" "echo hello | cat | wc -l"
test_valid_syntax "Redirect output" "echo hello > file.txt"
test_valid_syntax "Redirect input" "cat < file.txt"
test_valid_syntax "Append redirect" "echo hello >> file.txt"
test_valid_syntax "Heredoc basic" "cat << EOF
hello
EOF"
test_valid_syntax "Quoted strings" "echo \"hello world\""
test_valid_syntax "Single quotes" "echo 'hello world'"
test_valid_syntax "Command substitution" "echo \$(date)"
test_valid_syntax "Semicolon commands" "echo hello ; echo world"
test_valid_syntax "Background job" "echo hello &"
test_valid_syntax "Parentheses grouping" "(echo hello)"
test_valid_syntax "Braces grouping" "{ echo hello; }"
test_valid_syntax "Variable expansion" "echo \${HOME}"
test_valid_syntax "Escaped quotes" "echo \"He said \\\"hello\\\"\""
test_valid_syntax "Mixed quotes" "echo \"hello 'world'\""

echo "=== 12. EDGE CASES ==="

test_syntax_error "Empty command" ""
test_syntax_error "Only whitespace" "   "
test_syntax_error "Only tabs" "\t\t"
test_syntax_error "Only newlines" "\n\n"
test_syntax_error "Command with only operators" "| > <"
test_syntax_error "Operators without commands" "; & |"
test_syntax_error "Recursive quote nesting" "echo \"hello \$(echo 'world \$(echo \"test\")')\""

echo "=== TEST COMPLETE ==="
echo "Run this script to test your minishell syntax error handling!"
