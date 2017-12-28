# aero-ros-pkg

## Pre-requirement

### Install ROS

```
sudo apt-get install ros-indigo-desktop-full
sudo apt-get install ros-indigo-pr2-controller-msgs ros-indigo-move-base-msgs
sudo apt-get install ros-indigo-map-server ros-indigo-amcl ros-indigo-move-base ros-indigo-eband-local-planner
sudo apt-get install ros-indigo-moveit
sudo apt-get install ros-indigo-moveit-ros-planning-interface ros-indigo-moveit-ros-planning ros-indigo-moveit-core ros-indigo-moveit-ros-perception ros-indigo-moveit-ros-warehouse ros-indigo-moveit-kinematics
```

### Setup catkin workspace

```
sudo apt-get install python-wstool python-catkin-tools
mkdir -p ~/ros/indigo
cd ~/ros/indigo
wstool init src
catkin init
catkin build
source ~/ros/indigo/devel/setup.bash
```

## Install

### Clone repository

```
cd ~/ros/indigo/src
wstool set aero-ros-pkg https://github.com/seed-solutions/aero-ros-pkg.git --git
wstool up aero-ros-pkg
```

### Build packge

#### Build aero_description

```
cd aero-ros-pkg
catkin build aero_description
soure ~/.bashrc
```

#### Setup aero_startup

In the initial stage, `aero_startup` is not ros package, it has no `CMakeLists.txt`.
`CMakeLists.txt` and some controller modules are generated by `aero_description/setup.sh`.
`setup.sh` requires robot directory as an argument e.g. `setup.sh typeF`.

```
roscd aero_description
./setup.sh typeF  # including catkin build aero_startup
source ~/.bashrc
```

If you need clean up `aero_startup`, please use `aero_description/clean.sh`.

## Control AERO

### Setup udev

T.B.D.

### Run controllers

```
roslaunch aero_startup aero_bringup.launch
```

### View Robot Model

```
rosrun rviz rviz
```

then add RobotModel, change Robot Description to `aero_description`.


## Samples

### Build Samples

```
catkin build aero_samples
```

### Run Minimum Sample

```
rosrun aero_samples minimum_sample_node
```

### Control from Command Line

#### Move Joint

```
rostopic pub /aero_controller/command trajectory_msgs/JointTrajectory "header:
  seq: 0
  stamp:
    secs: 0
    nsecs: 0
  frame_id: ''
joint_names:
- 'r_wrist_y_joint'
points:
- positions: [0.5]
  velocities: [0]
  accelerations: [0]
  effort: [0]
  time_from_start: {secs: 1, nsecs: 0}"
```

#### Move Torso

```
rosservice call /aero_torso_controller  "x: 0.0
z: -200.0
coordinate: 'world:2000'"
```

### Writing Codes

see `aero_samples` and `aero_std` documentation
