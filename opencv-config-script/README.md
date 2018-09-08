# opencv-config-script

feeling tired for me to always configure the opencv include or library path and the input files blabla... in order to run code based on opencv, and then I code this script, which could help me initialize my all configuration if I have a mini configured project. Although this script just change the content of \*.sln and the name of  \*.vcxproj & \*.filters(I dont know what is use for ,but I kept it), it help me a lot. 
<br>
If I want to change the project name into 'second-opencv', I need to do just like this:

``` python init.py second-opencv ```

ok, now I have a project called 'second-opecv'.