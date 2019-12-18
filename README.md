## Installation instructions:

## Docker setup (Linux):
``
root@user# docker run -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix -v /PATH_TO_TPC:/TPCReco --rm -it --user USERID akalinow/root-fedora30
``

## Compiling from source:
```
git clone https://github.com/akalinowski/TPCReco.git
cd TPCReco
git checkout relevant_tag
mkdir build; cd build
cmake ../
make install -j 4
```
## Run instructions:

```
./bin/tpcGUI config/config_GUI.json
```
