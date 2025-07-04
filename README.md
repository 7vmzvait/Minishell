## ❗ Known Issues / Not Yet Implemented

The following features or behaviors are not fully implemented yet:

- `export` does not update variables correctly
  - Repeated `export VAR=value` does not overwrite previous value
- `env` prints variables with only values (non-standard behavior)
  - Should only show variables in `key=value` format
- Exit status `$?` is not tracked
  - Shell always returns 0 even after failed commands
- Signal handling is incomplete
  - Ctrl+C does not interrupt or reset prompt
  - Ctrl+\ is not ignored as in Bash
