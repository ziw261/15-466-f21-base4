# Gamestop Simulator

Author: Zi Wang, Wenlin Mao, Tianrun(Martin) Ke

Design: (TODO: In two sentences or fewer, describe what is new and interesting about your game.)

Text Drawing: 

The text drawing pipeline is like this. The InitializeGlyaphMap will create all the 2d textures for all the ascii code from 32 to 127. And then, whenever we want to change text, SetText will regenerate the glyph position and info. Then in the DrawText, it will iterate through all the characters and calculate the positions, find the already saved texture_id and let opengl does the drawing.

Screen Shot:

![Screen Shot](screenshot.png)

How To Play:

Use mouse to click buttons to make decision. You can talk to 20 customers max. And your goal is to get $300 in profit.

Sources: 

Pipeline inspiration: https://github.com/GenBrg/MarryPrincess \
Dimbo font: https://www.dafont.com/dimbo.font?l[]=10&l[]=1 \
Pacifico font: https://fonts.google.com/specimen/Pacifico

Json loading: \
Stackoverflow: https://stackoverflow.com/a/39975809 \
nlohmann's JSON Repository on GitHub: https://github.com/nlohmann/json

This game was built with [NEST](NEST.md).

