FROM codercom/code-server:latest

USER root

RUN apt-get update && apt-get install -y \
    python3 \
    python3-pip \
    git \
    udev \
    usbutils \
    && rm -rf /var/lib/apt/lists/*

RUN pip3 install --upgrade platformio

RUN usermod -aG dialout coder

USER coder
WORKDIR /workspace
