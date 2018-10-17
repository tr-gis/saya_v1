import roslib
import rospy
import smach
import smach_ros
import os, sys
from std_msgs.msg import Bool
from sound_play.msg import SoundRequest

from sound_play.libsoundplay import SoundClient

from std_msgs.msg import Int32
i=0

class shutdown(smach.State):
    def __init__(self):
        smach.State.__init__(self, outcomes=['waiting_for_command','shutdown_initiated']) # Outcome
	
    def callback(self,data):
		rospy.logerr("Success %d",i)	

    def listener(self):
		global i
		i=0
		try:	
			k=rospy.wait_for_message("ui_shutdown", Int32, timeout=12)
			rospy.Subscriber("ui_shutdown", Int32, self.callback)
			i=k.data 
		except(rospy.ROSException), e:
			rospy.logerr("")
		

    def execute(self, userdata):
	global i
	self.listener()
	if i==1:	
		os.system("shutdown -h now ") 
		return 'shutdown_initiated'
	else:
		return 'waiting_for_command'
	