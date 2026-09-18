# Squawk-
Для запуска программы необходимо загрузить следующие файлы:

1) https://www.libsdl.org/projects/SDL_mixer/release/ - SDL2_mixer-devel-2.8.0-VC.zip

2) https://github.com/libsdl-org/SDL/releases - SDL2-devel-2.30.2-VC.zip

3) https://www.libsdl.org/projects/SDL_image/release/ - SDL2_image-devel-2.0.5-VC.zip

4) https://www.libsdl.org/projects/SDL_ttf/release/ - SDL2_ttf-devel-2.22.0-VC.zip

После загрузки всех необходимых файлов проверьте наличие (рекомендуется) Visual Studio 2022. Если нет, скачайте её.

Откройте 1.Project_Game.zip, распакуйте и найдите 1.Project_Game/Project2/Game.sln

Лучше поместить такой проект в режим отладки (Debug), но если это не сработает, то в режим релиза (Release).

Перейдите в Properties ja VC++ Directories, где находится Include Directories, откройте и отредактируйте. Добавьте туда каждую «новую строку», которая должна быть типа sdl2, или примерно так (C:\Users\...\source\libs\SDL2_mixer-2.8.0\include, C:\Users\...\source\libs\SDL2-2.30.2\include и т. д.).

Перейдите в Properties ja VC++ Directories, где находится Library Directories, откройте и отредактируйте. Каждый файл sld2, или, например, такой (C:\Users\...\source\libs\SDL2_mixer-2.8.0\lib\x64 и т. д.)

Перейдите в раздел Linker and Input, где находится dditional Dependencies, откройте и отредактируйте. Укажите имя каждого файла sld2, например, (SDL2.lib, SDL2main.lib, SDL2_image.lib, SDL2_mixer.lib). Каждое имя записывайте на новой строке.
