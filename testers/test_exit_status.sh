#!/bin/bash

# Test script for checking shell exit status handling
# Run this in your shell to test exit status propagation

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Function to check test result
check_result() {
    local expected=$1
    local actual=$2
    local test_name=$3
    
    if [ "$actual" -eq "$expected" ]; then
        echo -e "${GREEN}✓ PASS${NC}: $test_name (expected: $expected, got: $actual)"
    else
        echo -e "${RED}✗ FAIL${NC}: $test_name (expected: $expected, got: $actual)"
    fi
}

echo -e "${BLUE}=== Testing Exit Status Handling ===${NC}"
echo

# Test 1: Basic command success
echo -e "${YELLOW}Test 1: Successful command (ls)${NC}"
ls > /dev/null 2>&1
check_result 0 $? "Basic command success"
echo

# Test 2: Basic command failure
echo -e "${YELLOW}Test 2: Failed command (ls nonexistent)${NC}"
ls /nonexistent/directory > /dev/null 2>&1
check_result 2 $? "Basic command failure"
echo

# Test 3: Built-in command success
echo -e "${YELLOW}Test 3: Built-in success (echo)${NC}"
echo "hello" > /dev/null
check_result 0 $? "Built-in command success"
echo

# Test 4: Built-in command failure (if your shell supports it)
echo -e "${YELLOW}Test 4: Built-in failure (cd to nonexistent)${NC}"
cd /nonexistent/directory > /dev/null 2>&1
check_result 1 $? "Built-in command failure"
echo

# Test 5: Pipeline - success
echo -e "${YELLOW}Test 5: Pipeline success (echo | cat)${NC}"
echo "hello" | cat > /dev/null
check_result 0 $? "Pipeline success"
echo

# Test 6: Pipeline - failure in first command
echo -e "${YELLOW}Test 6: Pipeline - first command fails${NC}"
ls /nonexistent | cat > /dev/null 2>&1
check_result 0 $? "Pipeline - first command fails (last succeeds)"
echo

# Test 7: Pipeline - failure in last command
echo -e "${YELLOW}Test 7: Pipeline - last command fails${NC}"
echo "hello" | grep "world" > /dev/null 2>&1
check_result 1 $? "Pipeline - last command fails"
echo

# Test 8: Redirection success
echo -e "${YELLOW}Test 8: Redirection success${NC}"
echo "test" > /tmp/test_file
check_result 0 $? "Redirection success"
rm -f /tmp/test_file
echo

# Test 9: Redirection failure
echo -e "${YELLOW}Test 9: Redirection failure (to read-only dir)${NC}"
echo "test" > /dev/nonexistent 2>/dev/null
check_result 1 $? "Redirection failure"
echo

# Test 10: Signal handling (if supported)
echo -e "${YELLOW}Test 10: Command interrupted by signal${NC}"
sleep 1 &
SLEEP_PID=$!
kill -TERM $SLEEP_PID 2>/dev/null
wait $SLEEP_PID 2>/dev/null
check_result 143 $? "Signal handling (SIGTERM)"
echo

# Test 11: Command not found
echo -e "${YELLOW}Test 11: Command not found${NC}"
./nonexistent_program 2>/dev/null
check_result 127 $? "Command not found"
echo

# Test 12: True command
echo -e "${YELLOW}Test 12: True command${NC}"
true
check_result 0 $? "True command"
echo

# Test 13: False command
echo -e "${YELLOW}Test 13: False command${NC}"
false
check_result 1 $? "False command"
echo

# Test 14: Mixed pipeline (false | true)
echo -e "${YELLOW}Test 14: Mixed pipeline (false | true)${NC}"
false | true
check_result 0 $? "Mixed pipeline - false | true"
echo

# Test 15: Mixed pipeline (true | false)
echo -e "${YELLOW}Test 15: Mixed pipeline (true | false)${NC}"
true | false
check_result 1 $? "Mixed pipeline - true | false"
echo

echo -e "${BLUE}=== Summary ===${NC}"
echo -e "${GREEN}✓ PASS${NC} = Test passed"
echo -e "${RED}✗ FAIL${NC} = Test failed"
echo

echo -e "${BLUE}=== Manual Tests for Your Shell ===${NC}"
echo -e "${YELLOW}Try these commands manually in your shell:${NC}"
echo -e "1. ${GREEN}true${NC}; echo \$?                    # Should show 0"
echo -e "2. ${GREEN}false${NC}; echo \$?                   # Should show 1"
echo -e "3. ${GREEN}ls /${NC}; echo \$?                    # Should show 0"
echo -e "4. ${GREEN}ls /nonexistent${NC}; echo \$?         # Should show 2"
echo -e "5. ${GREEN}echo hello | cat${NC}; echo \$?        # Should show 0"
echo -e "6. ${GREEN}echo hello | grep world${NC}; echo \$? # Should show 1"
echo -e "7. ${GREEN}false | true${NC}; echo \$?           # Should show 0"
echo -e "8. ${GREEN}true | false${NC}; echo \$?           # Should show 1"
echo
echo -e "${YELLOW}Remember: Exit status should be from the LAST command in a pipeline!${NC}"
