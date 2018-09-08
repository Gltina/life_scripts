#install opencv 

#[compiler] 

sudo apt-get install build-essential -y

#[required] 

sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev -y

 

# download lastest stable opencv version 

wget https://github.com/opencv/opencv/archive/3.4.3.zip 

# unzip  

unzip 3.4.3.zip 

 

cd opencv-3.4.3 

mkdir build 

cd build 

cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local .. 

make  # make -j7 : runs 7 jobs in parallel 

sudo make install 

 

# configure env 

sudo /bin/bash -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/opencv.conf' 

sudo ldconfig 

 

sudo /bin/bash -c 'echo "PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/local/lib/pkgconfig" >> /etc/bash.bashrc' 

sudo /bin/bash -c 'echo "export PKG_CONFIG_PATH " >> /etc/bash.bashrc' 

 

# test a opencv file 

# g++ edge.cpp  -o test `pkg-config --cflags --libs opencv` 
