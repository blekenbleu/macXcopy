---
title: MacCopy - X11-style Mouse Copy Applet for macOS
---
7 November 2018  

## maccopy - X mouse copy for macOS
This is a hack of [https://github.com/lodestone/macpaste](https://github.com/lodestone/macpaste)  
`maccopy` approximates left mouse button copy implementation by Unix/Linux X11 window managers.  
Unlike X11, `maccopy` alters Mac's *system* clipboard.  
Like X11, macOS Terminal uses *another* buffer for X11-style copy and paste.  

`maccopy` works with [a special JSON file](KarabinerButton3.json) that enables [Karabiner Elements](https://pqrs.org/osx/karabiner/) to paste  
from macOS clipboard to macOS applications *other than* Safari, Firefox and Chrome web browsers,  
for which mouse middle button opens hyperlinks in new tabs.  

- first, highlight arbitrary text or visual elements by double-click or drag with left button depressed,
- then [control]+c or middle mouse button click, if using customized Karabiner, to paste those elements in the same or another window.  

It works well fairly for me with [MacVim](https://macvim-dev.github.io/macvim/), but *NOT* Terminal, on macOS 10.3 **High Sierra**  

#### How?
This program works *only* with applications that support key combination [Command]+C for copy to macOS clipboard,  
because `maccopy` simply posts the following events: 

1. `[command]+[c] down & up` (which copies selected text or objects) for left mouse button releases.  
   This allows copying text that is drag highlighted, or double-clicked to highlight words or lines.  
2. Left Mouse Button down & up (which positions mouse cursor for paste insertion)

For different mouse button double-click or debounce timing and/or left-handed or otherwise remapped mice, edit the C program and `make`.  

## Usage
Install [Karabiner Elements](https://pqrs.org/osx/karabiner/) and copy [`KarabinerButton3.json`](KarabinerButton3.json) to `~/.config/karabiner/assets/complex_modifications`,  
then open `Karabiner-Elements Preferences > Complex Modifications > Rules > Add rule`

Run `maccopy &` in the background from e.g. Terminal  
or add it as a startup "Login Item"  
`(System Preferences > Users & Groups > Login Items` **[+]** *Navigate to file*).

## Building
    `make`

## Running temporarily
    `./maccopy`

## License
Public Domain 2018

