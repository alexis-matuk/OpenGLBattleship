git submodule update --init --recursive
sudo apt-get install autoconf
sudo apt-get install libtool-bin
sudo apt-get install automake
cd glm
./autogen.sh
cd glm
make
cd ../..

sudo apt-get install libjpeg-dev
sudo apt-get install libpng12-dev
sudo apt-get install libfreetype6-dev
sudo apt-get install libdevil-dev

cd Simple-OpengGL-Image-Library
make
make install
sudo apt-get install libftgl-dev
ln -s /usr/include/freetype2/ft2build.h /usr/include

make


