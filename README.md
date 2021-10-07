# IGME690_Chess

# Setting Up Visual Studio to Work with SFML

1) Download the latest version of SFML from https://www.sfml-dev.org/download.php
	(feel free to reference the tutorial on the site as well)

2) Unzip and store in a known place

3) Open up the project in VS

4) Open up the Project Propterties

	For All Configurations you want:

		> C++
			> General
				add <path to sfml>\include to the Additional Dependancies

			> Preprocessing 
				add SFML_STATIC to Preprocessor Definitions

		> Linker
			> General
				add <paht to sfml>\lib to the Additional Libraries

	For Debug you want:

		> Linker
			>Input 
				sfml-graphics-s-d.lib
				sfml-window-s-d.lib
				sfml-system-s-d.lib
				opengl32.lib
				freetype.lib
				winmm.lib
				gdi32.lib

	For Release you want:

		> Linker
			>Input
				sfml-graphics-s.lib
				sfml-window-s.lib
				sfml-system-s.lib
				opengl32.lib
				freetype.lib
				winmm.lib
				gdi32.lib
