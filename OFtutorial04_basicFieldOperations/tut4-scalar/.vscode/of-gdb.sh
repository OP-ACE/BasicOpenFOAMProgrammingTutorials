#!/bin/bash
. /home/dyfluid/OpenFOAM/OpenFOAM-9/etc/bashrc WM_NCOMPROCS=2; export WM_COMPILE_OPTION=Debug
. /home/dyfluid/OpenFOAM/OpenFOAM-9/etc/bashrcDebug
/usr/bin/gdb "$@"
