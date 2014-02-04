----------------------------Controls----------------------------
UP arrow    :   accelerate forward camera motion
DOWN arrow  :   decelerate forward camera motion
SPACE       :   stop all forward motion
LEFT Arrow  :   rotate towards the left
RIGHT Arrow :   rotate towards the right
PAGE UP     :   increase camera elevation
PAGE DOWN   :   decrease camera elevation
P           :   go to location used to take the screenshot
T           :   run the tour
E           :   exit the tour.
ESC or Q    :   exit the program.

NB : The mouse is not used.

Apologies if the landscape takes time to load

----------------------------Files-------------------------------
   ------------------------Top folder------------------------
camera.cpp                  :   source for the camera class
camera.h                    :   camera header
credits.txt                 :   attributions
glfw3.txt                   :   flag to use GLFW3 when compiling
main.cpp                    :   main method
object.cpp                  :   source for the object class
object.h                    :   object header
objectfragmentshader.frag   :   fragment shader for world elements
objectvertexshader.vert     :   vertex shader for elements
readme.txt                  :   this file
screenshot.jpg              :   screenshot of interesting location
skyboxvertexshader.frag     :   fragment shader for skybox
util.cpp                    :   source for helper functions such as loading shaders, .obj files and textures
util.h                      :   header for helper functions

    ------------------------objects folder------------------------
celing.obj                  :   model ceiling of our skybox/world
clanger-boat*.obj(2)        :   models of the clangers' boats
clanger-in-boat*.obj(2)     :   models of the clangers on the boats
clanger-in-crater*.obj(2)   :   models of the clangers in the craters
clanger-standing*.obj(2)    :   models of the clangers standing
clangers-text.obj           :   model of the 'Clangers' text
crater-top*.obj(3)          :   models of the tops on the craters
landscape.obj               :   smodel of the moon landscape
skybox*.obj(4)              :   models of each skybox side
    ------------------------textures folder------------------------
clanger.bmp                 :   texture for clangers
clanger-boat.bmp            :   texture for the clangers' boats
clangers-text.bmp           :   texture for the 'Clangers' text
crater-top.bmp              :   texture for the crater tops
moon.bmp                    :   texture for the landscape
space.bmp                   :   texture for the skybox
space-earth.bmp             :   texture for the skybox showing the earth
space-mars.bmp          	:   texture for the skybox showing mars


----------------------------Building-------------------------------
Built with standard options, including OpenGL, GLM, GLFW3 and GLEW.


----------------------------Working-------------------------------
Obj files are parsed for vertices, uv coords and normals, and loaded into vbos, which are then referenced by vaos. These vaos are drawn out each render tick. Textures are loaded through and drawn onto each model in each render tick. Animation is achieved by manipulating and updating each objects' model matrix on each render tick.

----------------------------Inspiration-------------------------------
Code for object class use and manipulated from http://ogldev.atspace.co.uk/
Camera and controls used and manipulated from http://ogldev.atspace.co.uk/ and http://www.opengl-tutorial.org/
Loading of .obj files, textures and shaders taken from http://www.opengl-tutorial.org/
