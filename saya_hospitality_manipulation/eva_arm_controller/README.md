# saya_hospitality_arm_motion #

This packages contains codes for recording the motion of cool400arm and play back the recorded motion of arm.


## Scripts: ##
* set_all_torque
* pose_zero_with_gripper
* joint1_current_position_publisher
* joint2_current_position_publisher
* joint3_current_position_publisher
* joint4_current_position_publisher
* joint5_current_position_publisher
* joint6_current_position_publisher
* gripper_current_position_publisher

## Launch Files: ##
* __cool400_controller.launch__
	It initiates controller manager node for the dynamixel motors in arm
* __current_position_publisher.launch__
	It launches the current_position_publisher node of all dynamixel motors in arm. 
* __record.launch__
	It records the position of all motors while moving the arm manually.
* __play.launch__
	It playbacks the recorded motion of the arm.	

## Bag File: ##
* __saya_hospitality_arm_motion_recorded_file.bag__ 
	It stores the recorded motion of arm as ros messages.
	To know more about bag file, clik [here](http://wiki.ros.org/Bags)

## Procedure: ##
1. Launch the __cool400_controller.launch file__.
2. Launch the __current_position_publisher.launch file__.
3. Launch the __record.launch__ (Edit the file name in launch file before launching it)
4. Now move the arm manually in moderate speed.
5. After moving the arm, stop the __record.launch file__ and __cureent_position_publisher.launch__ file.
6. Now the recorded bag file will be in __.ros__ directory in __HOME__ directory. goto the __.ros__ directory and copy the bag file then paste it in the bag folder in this package.
__NOTE:__ .ros directory will be hidden. To view the directory use shortcut key ctrl+H, this will show the hidden folders in HOME directory.
7. Now to playback the recorded motion launch the __play.launch__ file in the terminal.

#### Links for References ###
* rosbag command line - [link](http://wiki.ros.org/rosbag/Commandline)
	
	




