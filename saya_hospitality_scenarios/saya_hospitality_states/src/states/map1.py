

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

class Map1(smach.State):
	def __init__(self):
		smach.State.__init__(self, outcomes=['complete','incomplete']) # Outcome

	def callback(self,data):
		rospy.logerr("Success %d",i)	

	def listener(self):
		global i
		i=0
		try:	
			k=rospy.wait_for_message("ui_nav", Int32, timeout=13)
			rospy.Subscriber("ui_nav", Int32, self.callback)
			i=k.data 
		except(rospy.ROSException), e:
			rospy.logerr("No publish")
		rospy.logerr(i)
		
	def execute(self, userdata):
		global i
		self.listener()	 
		if i==1:
			os.system("rosrun saya_hospitality_audio speech21.py")
		
		elif i==2:
			os.system("rosrun saya_hospitality_audio speech22.py")
			
		elif i==3:
			os.system("rosrun saya_hospitality_audio speech23.py")
			
		elif i==4:
			os.system("rosrun saya_hospitality_audio speech24.py")
			
		elif i==5:
			os.system("rosrun saya_hospitality_audio speech25.py")
						
		elif i==6:
			os.system("rosrun saya_hospitality_audio speech26.py")
			
		if i==0:
			rospy.logerr("Incomplete")	
			return 'incomplete'
		else:	
			rospy.logerr("Complete")
			return 'complete'
