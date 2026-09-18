Et programm läks käima, on vaja download selliseid faile:

  1) https://www.libsdl.org/projects/SDL_mixer/release/  - SDL2_mixer-devel-2.8.0-VC.zip

  2) https://github.com/libsdl-org/SDL/releases - SDL2-devel-2.30.2-VC.zip

  3) https://www.libsdl.org/projects/SDL_image/release/ - SDL2_image-devel-2.0.5-VC.zip

  4) https://www.libsdl.org/projects/SDL_ttf/release/ - SDL2_ttf-devel-2.22.0-VC.zip


Kui kõik on käes, siis vaadake, et kas Teil on (soovituslikult) Visual Studio 2022. Kui ei, siis download seda.

Avake 1.Project_Game.zip, unzip ja leidke 1.Project_Game/Project2/Game.sln

Parem panna selline projekt Debug'is aga kui ei tööta siis Release's

Minge Properties ja VC++ Directories, seal kus on Include Directories avage ja edit. Sinna lisage iga "new line" peab olema sdl2 tüüp ehk niimoodi ( C:\Users\...\source\libs\SDL2_mixer-2.8.0\include , C:\Users\...\source\libs\SDL2-2.30.2\include jne.)

Minge Properties ja VC++ Directories, seal kus on Library Directories avage ja edit. Iga sld2 fail ehk niimoodi ( C:\Users\...\source\libs\SDL2_mixer-2.8.0\lib\x64 jne. )

Minge Linker ja Input, seal kus on Additional Dependencies avage ja edit. Iga sdl2 nimetus ehk niimoodi ( SDL2.lib , SDL2main.lib , SDL2_image.lib , SDL2_mixer.lib). Kirjutage iga nimetust uuele reale.


Kui Teil on küsimusi, palun pöörake mulle: jakovlen@ut.ee

