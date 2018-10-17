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

class Map2(smach.State):
	def __init__(self):
		smach.State.__init__(self, outcomes=['complete_repeat','complete_thank', 'complete_guide', 'incomplete']) # Outcome

	def callback(self,data):
		rospy.logerr("Success %d",i)	

	def listener(self):	
		global i
		i=0                #to reset the value everytime
		try:	
			k=rospy.wait_for_message("ui_options", Int32, timeout=18)		
			rospy.Subscriber("ui_options", Int32, self.callback) 
			i=k.data 
		except(rospy.ROSException), e:
			rospy.logerr("No publish")
		
		


	def execute(self, userdata):
		global i
		self.listener()	
		if i==1:
			return 'complete_repeat'
		elif i==2:
			return 'complete_guide'
		elif i==3:
			return 'complete_thank'

		if i==0:
			return 'incomplete'
 
