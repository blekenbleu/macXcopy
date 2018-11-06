---
title: MacCopy - X11-style Mouse Copy Feature for macOS
---

## maccopy - verview
This is a hack of [https://github.com/lodestone/macpaste](https://github.com/lodestone/macpaste)  
`maccopy` approximates the left mouse button copy implemented by Unix/Linux X11 window managers.  
Unlike X11, `maccopy` alters Mac's *system* clipboard.  
Like X11, macOS Terminal has *another* buffer for X11-style copy and paste.  

`maccopy` works with [a special JSON file](KarabinerButton3.json) enabling [Karabiner Elements](https://pqrs.org/osx/karabiner/) to paste  
from macOS clipboard to macOS applications *other than* Safari, Firefox and Chrome web browsers,  
for which mouse middle button opens hyperlinks in new tabs.  

- first highlight arbitrary text or visual elements,
- then [control]+c or middle mouse button click using customized Karabiner to paste those elements in the same or another window.  

It works well fairly for me with [MacVim](https://macvim-dev.github.io/macvim/)  

#### How?
This program works with applications that support key combination [Command]+C for copy to macOS clipboard.  
If they do not, then this will not work, because the program simply posts the following events: 

1. Cmd+C down & up (copies your selected text or objects) whenever your left mouse button releases.  
   This allows copying text that is drag highlighted, or double-clicked to highlight words or lines.  
2. Left Mouse Button down & up (position mouse cursor for paste insertion)

For left-handed, or otherwise remapped mice, edit the C program and `make`.  
Numerous warning messages are seemingingly benign...

## Usage
Install Karabiner and copy [`KarabinerButton3.json`](KarabinerButton3.json) to `~/.config/karabiner/assets/complex_modifications`,  
then open `Karabiner-Elements Preferences > Complex Modifications > Rules > Add rule`

Run `maccopy &` in the background from e.g. Terminal  
or add it as a startup "Login Item"  
`(System Preferences > Users & Groups > Login Items` **[+]** *Navigate to file*).

## Building
    `make maccopy`

## Running
    `./maccopy &`

## License
Public Domain 2018

