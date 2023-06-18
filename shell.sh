#!/bin/dash
# usermod --shell "$(which zsh)" $USER
dash -lc "chsh --shell \"$(which zsh)\""
