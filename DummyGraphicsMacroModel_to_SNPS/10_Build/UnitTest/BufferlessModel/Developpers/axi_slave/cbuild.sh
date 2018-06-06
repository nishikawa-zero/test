#!/bin/sh

 VHM=VHM

 [ -d $VHM ] && rm -rf $VHM
 mkdir $VHM

 cbuild -q axi_slave.v -o $VHM/libdesign.a -enableOutputSysTasks -g

