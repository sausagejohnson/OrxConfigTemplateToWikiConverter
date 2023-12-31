# OrxConfigTemplateToWikiConverter

## Who is this for?

This project is created specifically for maintainers of the Orx Portable Game Engine Wiki.

## What does it do?

The https://github.com/orx/orx/blob/master/code/bin/SettingsTemplate.ini and https://github.com/orx/orx/blob/master/code/bin/CreationTemplate.ini are our source of truth when data config properties are added or changed on the wiki pages. We change the format a little on the wiki by hand. This is very labourious.

The program simple takes both files and creates a new formatted versions suitable for cutting and pasting into the wiki to reduce the effort required to keep the wiki in sync with the data config files.

## How to use it?

You can either take the source file (main.cpp) and compile this yourself, or take a copy of the .exe. When you have an executable, simply run it. The program will use your $ORX environment variable to locate the .ini files in your orx repo and create the wiki formatted file for you automatically. They are created next to the original files.

## Where is the wiki?

https://wiki.orx-project.org

## Community

We would love to have you join us to write games using Orx or to be a maintainer of our documentation, provide tutorials, tips etc. Our discord is at: https://orx-project.org/discord