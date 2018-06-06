#!/bin/sh

simvisdbutil BufferlessModel.vcd -compress  -OVERWRITE
simvision -i simvision.svcf
