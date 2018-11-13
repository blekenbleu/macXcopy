---
title: MacXcopy - X11-style Mouse Copy Applet for macOS
---
10 November 2018  

## macXcopy - X (3-button) mouse copy and pseudo-X Paste for macOS web browsers
This includes a hack of [https://github.com/lodestone/macpaste](https://github.com/lodestone/macpaste), named `maccopy`.  
`maccopy` *approximates* mouse left button copy implementations by Unix/Linux X11 window managers.  
Unlike X11, `maccopy` alters Mac's *system* clipboard.  
Since, like X11, macOS Terminal uses *a private pasteboard* for X11-style copy and paste,  
an alternative terminal program using the system clipboard is wanted;  
[iTerm2](https://iterm2.com/) and [MacVim](https://macvim-dev.github.io/macvim/) both include default support
for X mouse middle-button paste from *system* clipboard.  

To support Google Chrome's `[command]+[shift]+v` hotkey for Paste,  
**macXcopy** includes [a JSON file](KarabinerButton3.json) for [Karabiner Elements](https://pqrs.org/osx/karabiner/)  
that implements Paste by `[command]+[mouse middle-button]` for compatible apps,  
e.g. Safari, Firefox and Chrome web browsers.

- first, highlight arbitrary text or other elements by double-click or drag with left button depressed,
- then `[command]+v`, or `mouse [middle-button]` to paste those elements in a **MacVim** or **iTerm2** window
- or `[command]+V` or `[command]+[middle-button]` if using customized Karabiner, to paste elements to Google Chrome.  
  Muscle memory to press `[control]` to select *Paste* vs *URL  in new tab* for **Google Chrome** is a goal.. 

This works on macOS 10.13 **High Sierra** for me with [MacVim](https://macvim-dev.github.io/macvim/), [iTerm2](https://iterm2.com/), Safari and [Google Chrome](https://www.google.com/chrome/).  

#### details
`maccopy` works *only* with applications that support key combination `[command]+c` for copy to macOS clipboard,  
because it will simply: 

- for left button double-click or pointer drag with left button depressed, *note selection*. 
- for left mouse button releases *after selection noted*, post `[command]+[c]` down & up.
  Note that *selected* element is copied even if not highlighted.

For different `mouse-button` double-click or debounce timing and/or left-handed or otherwise remapped mouse button, edit the C program and `make`.  

## HowTo
Install [Karabiner Elements](https://pqrs.org/osx/karabiner/) and copy [`KarabinerButton3.json`](KarabinerButton3.json) to `~/.config/karabiner/assets/complex_modifications`,  
then open `Karabiner-Elements Preferences > Complex Modifications > Rules > Add rule`.  
When in doubt, monitor *all* devices with a mouse icon in `Karabiner-Elements Preferences > Devices`  

Run `maccopy` in the foreground from e.g. Terminal  
or run `macXcopy.sh` to launch it in the background  
or
```
$ sudo cp macXcopy/maccopy /usr/local/bin/
Password:
```
... and add `macXcopy.app` as a startup "Login Item"  
`(System Preferences > Users & Groups > Login Items` **[+]** *Navigate to file*).

## Building maccopy
    `make`

### Building for debug
    `make debug`

### Testing
    `./maccopy`

### Building macXcopy.app
macOS does not support adding a plain bash script file as a startup "Login Item".  
**macXcopy.app** is simply a bash script disguised as a macOS .app by [Automator.app](https://support.apple.com/guide/automator/welcome/mac):  
![snapshot of macXcopy bash script](automator.png "bash script")

## License
{% include_relative LICENSE %}

###  See [these GitHub Pages](https://blekenbleu.github.io/VimTXmouse) for related documentation 
