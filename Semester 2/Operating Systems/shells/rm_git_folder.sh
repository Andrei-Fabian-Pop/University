#!/bin/bash

find . -maxdepth 2 -type d -name ".git" -exec rm -rf {} \;
