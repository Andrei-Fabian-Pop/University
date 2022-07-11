#!/bin/bash

for var in $(find ~/GitHub/ -maxdepth 1); do if [ ! $(find $var -type f -name "*.py" | wc -l) -eq 0 ]; then cp -r "$var" . ; fi ; done
