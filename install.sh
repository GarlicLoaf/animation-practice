new_echo () {
    echo "[RPG INSTALLER] $*"
}

new_echo "Installing submodules..."
git submodule update --init

new_echo "Setting up the project..."
cd build || { echo "Failed to enter build directory"; exit 1; }
cmake ..

new_echo "Do you want to build and execute the project right now? [y/n]"
read
if [[ $REPLY =~ ^[Yy]$ ]]
then
    cmake --build . && ./animations
fi
