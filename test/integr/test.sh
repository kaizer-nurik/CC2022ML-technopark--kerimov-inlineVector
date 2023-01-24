#!/bin/sh
NULL=/dev/null
PASSED=0
TEST_N=0
Yellow='\033[1;33m'
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

echo "\n${Yellow}Integration testing:${NC}"
echo "${GREEN}[==========]${NC}"

TEST_N=$((${TEST_N} + 1))
echo "${GREEN}[ RUN      ]${NC} test ${TEST_N}"
if echo "9 a 1 a 2 a 3 a 4 a 5 a 6 a 7 a 8 p" | ./tmp/demo 2>${NULL} 1>${NULL} == "1 2 3 4 5 6 7 8 " ; then
    echo "${GREEN}[       OK ]${NC} test ${TEST_N}"
    PASSED=$((${PASSED} + 1))
else
    echo "${RED}[  FAILED  ]${NC} test ${TEST_N}"
fi

TEST_N=$((${TEST_N} + 1))
echo "${GREEN}[ RUN      ]${NC} test ${TEST_N}"
if echo "11 a 1 a 2 a 3 a 4 a 5 a 6 a 7 a 8 b b p" | ./tmp/demo 2>${NULL} 1>${NULL} == "1 2 3 4 5 6 "  ; then
    echo "${GREEN}[       OK ]${NC} test ${TEST_N}"
    PASSED=$((${PASSED} + 1))
else
    echo "${RED}[  FAILED  ]${NC} test ${TEST_N}"
fi

TEST_N=$((${TEST_N} + 1))
echo "${GREEN}[ RUN      ]${NC} test ${TEST_N}"
if echo "13 a 1 a 2 a 3 a 4 a 5 a 6 a 7 a 8 b b b b p" | ./tmp/demo 2>${NULL} 1>${NULL} == '1 2 3 4 '  ; then
    echo "${GREEN}[       OK ]${NC} test ${TEST_N}"
    PASSED=$((${PASSED} + 1))
else
    echo "${RED}[  FAILED  ]${NC} test ${TEST_N}"
fi

TEST_N=$((${TEST_N} + 1))
echo "${GREEN}[ RUN      ]${NC} test ${TEST_N}"
if echo "15 a 1 a 2 a 3 a 4 a 5 a 6 a 7 a 8 b b b b a 10 a 11 p" | ./tmp/demo 2>${NULL} 1>${NULL} == "1 2 3 4 10 11 "  ; then
    echo "${GREEN}[       OK ]${NC} test ${TEST_N}"
    PASSED=$((${PASSED} + 1))
else
    echo "${RED}[  FAILED  ]${NC} test ${TEST_N}"
fi



echo "${GREEN}[==========]${NC}"
if [ ${PASSED} -ne 0 ] ; then
echo "${GREEN}[  PASSED  ]${NC} ${PASSED} tests."
fi
if [ $((${TEST_N} - ${PASSED})) -ne 0 ] ; then
echo "${RED}[  FAILED  ]${NC} $((${TEST_N} - ${PASSED})) tests."
fi