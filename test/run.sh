#!/bin/bash

SRCS_DIR=srcs
BIN_DIR=.bin
FILES=($(find ${SRCS_DIR} -type f))

ESC="\x1b"
RUNS="${ESC}[7;33m RUNS ${ESC}[0m"
PASS="${ESC}[7;32m PASS ${ESC}[0m"
FAIL="${ESC}[7;31m FAIL ${ESC}[0m"

if [ ! -d ${BIN_DIR} ]; then
	mkdir ${BIN_DIR}
fi

if ! make -C .. ; then
exit 1
fi

for file in ${FILES[@]}; do
	OUTPUT_NAME=${BIN_DIR}/$(echo ${file} | sed "s/${SRCS_DIR}\\///;s/\\.c//" | sed "s/\\//_/g")
	# echo "compile ${file} -> ${OUTPUT_NAME}"
	make --quiet SRC_FILE=${file} BIN_FILE=${OUTPUT_NAME} &
done

wait

BIN_FILE=($(find ${BIN_DIR} -maxdepth 1 -type f | sort))
FAILED=0
NB_TEST=${#BIN_FILE[@]}
TMP_FILE_ERR=$(mktemp)
TMP_FILE_OUT=$(mktemp)

# calcul the max len of bin filename
MAX_LEN=-1
for bin in ${BIN_FILE[@]}; do
	len=${#bin}
	if [ ${MAX_LEN} -lt ${len} ]; then
		MAX_LEN=${len}
	fi
done

printf "Begin Test, ${NB_TEST} test will be run\n\n"
for bin in ${BIN_FILE[@]}; do
	printf "${RUNS} ${bin}\r"
	{ ${bin} ; }  > ${TMP_FILE_OUT} 2>${TMP_FILE_ERR}
	exit_with=$?
	if [ ${exit_with} -ne 0 ]; then # failed
		FAILED=$((${FAILED} + 1))
		printf "${FAIL} %-*s  exit(${exit_with})\n" ${MAX_LEN} ${bin}
		echo "stdout :"
		cat ${TMP_FILE_OUT}
		echo
		echo "stderr :"
		cat ${TMP_FILE_ERR}
		echo
	else
		printf "${PASS} %-*s  exit(${exit_with})\n" ${MAX_LEN} ${bin}
	fi
done
echo $((${NB_TEST} - ${FAILED})) / ${NB_TEST} Test passed

rm ${TMP_FILE_ERR} ${TMP_FILE_OUT}
