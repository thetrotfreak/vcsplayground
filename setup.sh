sudo apt-get update && sudo apt-get upgrade -y

sudo apt-get install build-essential gdb

sudo apt-get install zsh
chsh -s "$(which zsh)"
sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

dash -c "curl -fsSLO https://bootstrap.pypa.io/get-pip.py && python3 get-pip.py"
rm get-pip.py
echo "export PATH=\$HOME/.local/bin:\$PATH" >> ~/.zshrc
sudo apt-get install python3.10-venv -y
source .zshrc

sh -c "$(curl --create-dirs -fsSLo ~/.vim/pack/python/start/black/plugin/black.vim https://raw.githubusercontent.com/psf/black/stable/plugin/black.vim)"
sh -c "$(curl --create-dirs -fsSLo ~/.vim/pack/python/start/black/autoload/black.vim https://raw.githubusercontent.com/psf/black/stable/autoload/black.vim)"
sh -c "$(curl --create-dirs -fsSLo ~/.vim/colors/gruvbox.vim https://raw.githubusercontent.com/thetrotfreak/.files/main/.vim/colors/gruvbox.vim)"
sh -c "$(curl --create-dirs -fsSLo ~/.vim/colors/catppuccin_mocha.vim https://raw.githubusercontent.com/thetrotfreak/.files/main/.vim/colors/catppuccin_mocha.vim
sh -c "$(curl --create-dirs -fsSLo ~/.vim/colors/catppuccin_macchiato.vim https://raw.githubusercontent.com/thetrotfreak/.files/main/.vim/colors/catppuccin_macchiato.vim
sh -c "$(curl --create-dirs -fsSLo ~/.vim/colors/catppuccin_frappe.vim https://raw.githubusercontent.com/thetrotfreak/.files/main/.vim/colors/catppuccin_latte.vimhttps://raw.githubusercontent.com/thetrotfreak/.files/main/.vim/colors/catppuccin_frappe.vim
sh -c "$(curl --create-dirs -fsSLo ~/.vim/vimrc https://raw.githubusercontent.com/thetrotfreak/.files/main/.vim/vimrc)"
# https://stackoverflow.com/a/12838963
vim +Black +qall

dash -c "$(curl -fsSL https://raw.githubusercontent.com/thetrotfreak/.files/main/.tmux.conf)"
