#!/bin/bash

export LOG_FILE_NAME="test.log"
export VCD_FILE_NAME="test.vcd"
 
export RESET_GENERATOR_SCRIPT_FILE_NAME="./script/ahbv2_stub_reset_generator.mxscr"
export INTERRUPT_SENDER_SCRIPT_FILE_NAME="./script/ahbv2_stub_interrupt_sender.mxscr"
export INTERRUPT_RECEIVER_SCRIPT_FILE_NAME="./script/ahbv2_stub_interrupt_receiver.mxscr"

VCD_RESULT="IIP_result_vcd.vcd"
CSV_RESULT="IIP_result_csv.csv"
SUMMARY_RESULT="IIP_result_summary.csv"

if [ ! -d log ]; then
  mkdir log
fi

if [ ! -d wave ]; then
  mkdir wave
fi

#sdsim --script ./script/Project.mxscr | tee $LOG_FILE_NAME
sdsim --script ./script/Project.mxscr -dbg -debugger=gdb | tee $LOG_FILE_NAME

if [ -e $LOG_FILE_NAME ]; then
  mv $LOG_FILE_NAME log
fi

if [ -e $VCD_FILE_NAME ]; then
  mv $VCD_FILE_NAME wave
fi

if [ -e $VCD_RESULT ]; then
  mv $VCD_RESULT wave
fi

if [ -e $CSV_RESULT ]; then
  mv $CSV_RESULT log
fi

if [ -e $SUMMARY_RESULT ]; then
  mv $SUMMARY_RESULT log
fi

unset LOG_FILE_NAME
unset VCD_FILE_NAME

unset RESET_GENERATOR_SCRIPT_FILE_NAME
unset INTERRUPT_SENDER_SCRIPT_FILE_NAME
unset INTERRUPT_RECEIVER_SCRIPT_FILE_NAME

