# MacMark - X11-style Mouse Copy Feature for macOS

## Overview
This is a subset of https://github.com/lodestone/macpaste  
It simulates the left mouse button copy found in Unix/Linux X11 window managers.  
Unlike X11, this program alters the *system* clipboard.  
Like X11, macOS Terminal has *another* buffer for X11-style copy and paste.  

It works with a special JSON file for Karabiner Elements to paste from the clipboard  
to macOS applications *other than* Safari, Firefox and Chrome web browsers,  
for which mouse middle button opens hyperlinks in new tabs.  

If you first highlight arbitrary text or visual elements, [control]+c or  
customized Karabiner middle click can then paste those elements in the same or another window.  

#### How?
This program works for applications that support key combination [Command]+C as copy to macOS clipboard.  
If they do not, then this will not work, because the program simply posts the following events: 

1. Cmd+C down & up (copies your selected text or objects) whenever your left mouse button releases.  
   This allows copying text that is drag highlighted, or double-clicked to highlight words or lines.  
2. Left Mouse Button down & up (position mouse cursor for paste insertion)

For left-handed, or otherwise remapped mice, just edit the C program and recompile.

## Usage
Run the executable in the background from your shell command-line interface,  
or run it as a "Login Item" at startup  
`(System Preferences > Users & Groups > Login Items` **[+]** *Navigate to file*).

## Building
    `make macmark`

## Running
    `./macmark &`

## License
Public Domain 2016

