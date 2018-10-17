

import roslib
import rospy
import smach
import smach_ros
import os, sys
from std_msgs.msg import Bool
from sound_play.msg import SoundRequest

from sound_play.libsoundplay import SoundClient


class Speech5(smach.State):
    def __init__(self):
        smach.State.__init__(self, outcomes=['completed']) # Outcome
	
    def execute(self, userdata):
       	os.system("rosrun saya_hospitality_audio speech5.py") # launches the play back file
	return 'completed'
