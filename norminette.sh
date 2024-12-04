#!/bin/bash
find . -type f \( -name "*.c" -o -name "*.h" \) ! -path "./src/tests/*" | xargs norminette
