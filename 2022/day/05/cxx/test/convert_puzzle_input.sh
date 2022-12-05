#!/usr/bin/env bash

set -ue

declare -r PUZZLE_INPUT="${1:-}"
declare -r PUZZLE_INPUT_STACKS="${PUZZLE_INPUT}.stacks"
declare -r PUZZLE_INPUT_WORK="${PUZZLE_INPUT}.work"

: > "$PUZZLE_INPUT_STACKS"
for i in 2 6 10 14 18 22 26 30 34; do
  head -n 9 "$PUZZLE_INPUT" | tac | cut -b "$i" | tr -d '\n' >> "$PUZZLE_INPUT_STACKS"
  echo "" >> "$PUZZLE_INPUT_STACKS"
done

tail -n +11 "$PUZZLE_INPUT" > "$PUZZLE_INPUT_WORK"

exit 0

### EOF ###

