FROM ros:noetic-robot

ENV DEBIAN_FRONTEND=noninteractive
ENV GIT_SSL_NO_VERIFY 1

RUN apt-get update && apt-get install -y \
    vim git python curl  wget \
    software-properties-common \
     libgoogle-glog-dev libgflags-dev \
     libatlas-base-dev libeigen3-dev libsuitesparse-dev \
      python3-catkin-tools python3-osrf-pycommon \
      ros-noetic-pcl-ros \
      libyaml-cpp-dev  libtbb-dev

ENV WORKDIR /workdir
ENV SHARED /shared

ARG USERNAME=user
ARG USER_UID=1000
ARG USER_GID=$USER_UID
RUN groupadd -o --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME

RUN mkdir -p ${SHARED} ${WORKDIR} \
    && chown user:user ${SHARED} ${WORKDIR} \
    && chmod 744 ${SHARED} ${WORKDIR}

USER user:user
WORKDIR /home/user
SHELL ["/bin/bash", "-c"]

RUN mkdir -p ~/catkin_ws/src
RUN cd ~/catkin_ws/src && \
    git clone https://github.com/mu-mu-mu/ros1_pcl_e2e.git
RUN cd ~/catkin_ws/ && \
    source /ros_entrypoint.sh &&\
    catkin_make
RUN echo 'source /ros_entrypoint.sh' >> ~/.bashrc
RUN echo 'source /home/user/catkin_ws/devel/setup.bash' >> ~/.bashrc
RUN echo 'set +eux' >> ~/.bashrc
