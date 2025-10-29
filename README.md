### What is it ?
Vimktor is simple Vim-like text editor written in c++. Vimktor provides fast, memory efficient and efective text editing enviorment

## How to build ?
### Dependencies
- cmake
- curses


### Linux
run these  commands: 
```sh
cd Vimktor  
cmake -B build 
cmake --build build 
cd build 
./Vimktor [file you want to edit]
```


### Keymaps
"W" -> Jump to another word \
"$" -> Jump to end of line \
"0" -> Jump to first char \
"x" -> delete current char \
":" -> use command 

### Commands
"w" -> save file \
"q" -> quit 
