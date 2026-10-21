#!/bin/bash
find cst -type f \( -name '*.h' -o -name '*.cpp' -o -name 'meson.build' \) -print0 \
  | sort -z \
  | while IFS= read -r -d '' f; do
      echo "===== $f ====="
      cat "$f"
      echo
    done > /tmp/tree.txt
