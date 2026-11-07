#!/bin/bash
# Opencv installation script for linux
# Made by: @MenuuTUX with ❤️ on GitHub
# Check out: https://github.com/MenuuTUX

# Check type of linux distribution
if [[ -f /etc/os-release ]]; then
    # shellcheck source=/dev/null
    source /etc/os-release
    OS=$NAME
    VER=$VERSION_ID
elif type lsb_release >/dev/null 2>&1; then
    OS=$(lsb_release -si)
    VER=$(lsb_release -sr)
elif [[ -f /etc/lsb-release ]]; then
    # shellcheck source=/dev/null
    source /etc/lsb-release
    OS=$DISTRIB_ID
    VER=$DISTRIB_RELEASE
elif [[ -f /etc/debian_version ]]; then
    OS=Debian
    VER=$(cat /etc/debian_version)
elif [[ -f /etc/SuSe-release ]]; then
    OS=SuSe
elif [[ -f /etc/redhat-release ]]; then
    OS=RedHat
else
    OS=$(uname -s)
    VER=$(uname -r)
fi

# Update package lists depending on the linux distribution
if [[ "$OS" == "Ubuntu" ]]; then
    sudo apt-get update
elif [[ "$OS" == "Debian GNU/Linux" ]]; then
    sudo apt-get update
elif [[ "$OS" == "Linux Mint" ]]; then
    sudo apt-get update
elif [[ "$OS" == "elementary OS" ]]; then
    sudo apt-get update
elif [[ "$OS" == "Raspbian GNU/Linux" ]]; then
    sudo apt-get update
elif [[ "$OS" == "Fedora" ]]; then
    sudo dnf update
elif [[ "$OS" == "CentOS Linux" ]]; then
    sudo yum update
elif [[ "$OS" == "openSUSE Leap" ]]; then
    sudo zypper update
elif [[ "$OS" == "openSUSE Tumbleweed" ]]; then
    sudo zypper update
else
    echo "Your linux distribution is not supported."
    echo "Please leave an issue on on my GitHub:"
    echo "https://github.com/MenuuTUX/Theia/issues"
    echo "For now please install the required dependencies manually."
    exit 1
fi
[ "$DEBUG" == true ] && echo "OS: $OS"
[ "$DEBUG" == true ] && echo "Version: $VER"

# Install required dependencies depending on the linux distribution
if [[ "$OS" == "Ubuntu" ]]; then
    sudo apt-get install -y build-essential cmake git pkg-config libgtk-3-dev libavcodec-dev libavformat-dev libswscale-dev libv4l-dev libxvidcore-dev libx264-dev libjpeg-dev libpng-dev libtiff-dev gfortran openexr libatlas-base-dev python3-dev python3-numpy libtbb2 libtbb-dev libdc1394-22-dev
elif [[ "$OS" == "Arch Linux" ]]; then
    sudo pacman -S --noconfirm base-devel cmake git pkg-config gtk3 ffmpeg libv4l libxvidcore libx264 libjpeg-turbo libpng libtiff openexr atlas python python-numpy tbb
elif [[ "$OS" == "Fedora" ]]; then
    sudo dnf install -y @development-tools cmake git pkg-config gtk3 ffmpeg libv4l libxvidcore libx264 libjpeg-turbo libpng libtiff openexr atlas python python-numpy tbb
elif [[ "$OS" == "CentOS Linux" ]]; then
    sudo yum groupinstall -y "Development Tools"
    sudo yum install -y cmake git pkg-config gtk3 ffmpeg libv4l libxvidcore libx264 libjpeg-turbo libpng libtiff openexr atlas python python-numpy tbb
elif [[ "$OS" == "openSUSE Leap" ]]; then
    sudo zypper install -y -t pattern devel_basis
    sudo zypper install -y cmake git pkg-config gtk3 ffmpeg libv4l libxvidcore libx264 libjpeg-turbo libpng libtiff openexr atlas python python-numpy tbb
elif [[ "$OS" == "openSUSE Tumbleweed" ]]; then
    sudo zypper install -y -t pattern devel_basis
    sudo zypper install -y cmake git pkg-config gtk3 ffmpeg libv4l libxvidcore libx264 libjpeg-turbo libpng libtiff openexr atlas python python-numpy tbb
else
    echo "Your linux distribution is not supported."
    echo "Please leave an issue on on my GitHub:"
    echo "https://github.com/MenuuTUX/Theia/issues"
    echo "For now please install the required dependencies manually."
    exit 1
fi

# Clone OpenCV repository
git clone https://github.com/opencv/opencv.git

# Navigate to the cloned directory
cd opencv || exit 1

# Create a build directory and navigate to it
mkdir build
cd build || exit 1

# Configure OpenCV build with cmake
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local ..

# Compile and install OpenCV
make
sudo make install

# Verify OpenCV installation
opencv_version=$(pkg-config --modversion opencv)

# Print OpenCV version
if [[ -n "$opencv_version" ]]; then
    echo "OpenCV version $opencv_version has been successfully installed."
else
    echo "OpenCV installation failed."
fi
