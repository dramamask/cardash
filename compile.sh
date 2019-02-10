#! /usr/bin/env bash
set -e

g++ cpp/*.cpp -o bin/cardash `pkg-config gtkmm-3.0 --cflags --libs`
