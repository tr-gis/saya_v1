# saya_hospitality_face_tracking #

This packages contains codes for face detetction and tracking.

## Requirements ##

* __usb_cam__ package - A ROS driver for usb camera.

To know more click this [link](http://wiki.ros.org/usb_cam) 

Use following code to install:

    sudo apt-get install ros-indigo-usb-cam

## Src: ##
* face_tracking.cpp
* face_tracking_action_server.cpp

## Launch Files: ##
* controller_manager.launch - for dynamixel motor connected in neck for pan movement
* start_pan_movement.launch
* face_tracking.launch - launches usb_cam node and face tracking node. 
* face_tracking_server.launch - launches usb_cam node and face tracking node with action server for SMACH. 

## NOTE: ##

Change the location of the __clasifier__ in file __face_tracking.cpp__.

1. Goto __/include/saya_hospitality_face_tracking__ and right click on the file __haarcascade_frontalface_alt.xml__ select properties.
2. In properties window select & copy the location of the file.
3. open face_tracking.cpp from /src folder. 
4. Goto line number 60 and delete the previous loactaion of the file and paste new one.
5. Then save and catkin_make workspace. 

Change the camera port number in the launch file (both face_tracking.launch and face_tracking_server.launch)

1. check the port in which the camera is connected. use following code to find it.
    ls /dev/video*
2. open the launch file and change the port in line number 4.
3. save and exit.




	
