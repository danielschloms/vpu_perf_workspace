#!/usr/bin/env bash

SOURCE_DIR="$HOME/sources/nvim"

git clone git@github.com:neovim/neovim.git $SOURCE_DIR
cd $SOURCE_DIR || exit
git checkout v0.11.7
make CMAKE_BUILD_TYPE=Release CMAKE_INSTALL_PREFIX=$HOME/opt
make install

git clone --depth 1 https://github.com/AstroNvim/template $HOME/.config/nvim
rm -rf $HOME/.config/nvim/.git

cat >$HOME/.config/nvim/lua/community.lua <<EOF
---@type LazySpec
return {
  "AstroNvim/astrocommunity",
  { import = "astrocommunity.pack.python" },
  { import = "astrocommunity.pack.cpp" },
  { import = "astrocommunity.pack.bash" },
  { import = "astrocommunity.pack.verilog" },
  { import = "astrocommunity.pack.cmake" },
  -- import/override with your plugins folder
}
EOF
