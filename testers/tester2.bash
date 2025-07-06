#!/bin/bash

# Color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

# Initialize counters
PASSED=0
FAILED=0

echo -e "${BLUE}=== BASH REDIRECTION AND PIPE TESTS ===${NC}"
echo

# Test function
test_cmd() {
    local name="$1"
    local cmd="$2"
    
    echo -e "${YELLOW}Testing: $name${NC}"
    
    if eval "$cmd" >/dev/null 2>&1; then
        echo -e "${GREEN}✓ PASS: $name${NC}"
        ((PASSED++))
    else
        echo -e "${RED}✗ FAIL: $name${NC}"
        ((FAILED++))
    fi
    echo
}

# =============================================================================
# BASIC TESTS
# =============================================================================

# Test 1: Basic redirection
test_cmd "Output redirection" 'echo "test" > temp.txt'

# Test 2: Input redirection  
test_cmd "Input redirection" 'echo "test" > temp.txt; cat < temp.txt'

# Test 3: Append redirection
test_cmd "Append redirection" 'echo "line1" > temp.txt; echo "line2" >> temp.txt'

# Test 4: Error redirection
test_cmd "Error redirection" 'ls nonexistent 2> error.txt'

# Test 5: Basic pipe
test_cmd "Basic pipe" 'echo "hello" | tr "[:lower:]" "[:upper:]"'

# Test 6: Multiple pipes
test_cmd "Multiple pipes" 'echo "c b a" | tr " " "\n" | sort'

# Test 7: Pipe with grep
test_cmd "Pipe with grep" 'echo -e "apple\nbanana" | grep "apple"'

# Test 8: Here document
test_cmd "Here document" 'cat << EOF > temp.txt
line1
line2
EOF'

# Test 9: Here string
test_cmd "Here string" 'tr "[:lower:]" "[:upper:]" <<< "hello"'

# Test 10: Built-in echo
test_cmd "Echo built-in" 'echo "test message"'

# Test 11: Built-in printf
test_cmd "Printf built-in" 'printf "Name: %s\n" "test"'

# Test 12: Built-in type
test_cmd "Type built-in" 'type echo'

# Test 13: Tee command
test_cmd "Tee command" 'echo "test" | tee temp.txt'

# Test 14: File descriptor
test_cmd "File descriptor" 'exec 3> temp.txt; echo "test" >&3; exec 3>&-'

# Test 15: Combined redirection
test_cmd "Combined redirection" '{ echo "out"; echo "err" >&2; } > temp.txt 2>&1'

# =============================================================================
# ADVANCED TESTS
# =============================================================================

# Test 16: Pipe with wc
test_cmd "Pipe with wc" 'echo "one two three" | wc -w'

# Test 17: Pipe with sort
test_cmd "Pipe with sort" 'echo -e "3\n1\n2" | sort -n'

# Test 18: Here doc with variables
test_cmd "Here doc with variables" 'NAME="test"; cat << EOF > temp.txt
Hello $NAME
EOF'

# Test 19: Here doc without expansion
test_cmd "Here doc without expansion" 'cat << '\''EOF'\'' > temp.txt
$HOME
EOF'

# Test 20: Complex pipe chain
test_cmd "Complex pipe chain" 'echo "1 2 1 3 2" | tr " " "\n" | sort | uniq'

# =============================================================================
# ERROR HANDLING TESTS
# =============================================================================

# Test 21: Empty input
test_cmd "Empty input" 'echo "" | wc -l'

# Test 22: Large input
test_cmd "Large input" 'seq 1 10 | tail -3'

# Test 23: Binary handling
test_cmd "Binary handling" 'echo "test" | base64 | base64 -d'

# Test 24: /dev/null redirection
test_cmd "/dev/null redirection" 'echo "invisible" > /dev/null'

# Test 25: Stderr to stdout
test_cmd "Stderr to stdout" 'echo "test" 2>&1'

# =============================================================================
# CLEANUP AND RESULTS
# =============================================================================

# Cleanup
rm -f temp.txt error.txt 2>/dev/null

echo -e "${BLUE}=== TEST RESULTS ===${NC}"
echo -e "${GREEN}Passed: $PASSED${NC}"
echo -e "${RED}Failed: $FAILED${NC}"
echo -e "${BLUE}Total: $((PASSED + FAILED))${NC}"

if [[ $FAILED -eq 0 ]]; then
    echo -e "${GREEN}🎉 ALL TESTS PASSED! 🎉${NC}"
else
    echo -e "${RED}⚠️  $FAILED TESTS FAILED ⚠️${NC}"
fi

# Show some example outputs
echo
echo -e "${BLUE}=== EXAMPLE OUTPUTS ===${NC}"

echo -e "${YELLOW}Basic redirection:${NC}"
echo "Hello World" > demo.txt
echo -e "${GREEN}$(cat demo.txt)${NC}"

echo -e "${YELLOW}Basic pipe:${NC}"
echo -e "${GREEN}$(echo "hello world" | tr '[:lower:]' '[:upper:]')${NC}"

echo -e "${YELLOW}Here document:${NC}"
cat << EOF
${GREEN}This is a here document
with multiple lines${NC}
EOF

echo -e "${YELLOW}Here string:${NC}"
echo -e "${GREEN}$(tr '[:lower:]' '[:upper:]' <<< "hello world")${NC}"

echo -e "${YELLOW}Multiple pipes:${NC}"
echo -e "${GREEN}$(echo "c b a" | tr ' ' '\n' | sort)${NC}"

# Final cleanup
rm -f demo.txt 2>/dev/null
