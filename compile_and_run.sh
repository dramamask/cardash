#! /usr/bin/env bash
set -e

sh ./compile.sh

# Note that this bash script will automatially exit if the compile script fails

sh ./run.sh