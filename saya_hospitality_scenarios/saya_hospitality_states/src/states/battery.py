import roslib
import rospy
import smach
import smach_ros
import os, sys
from std_msgs.msg import Bool
from sound_play.msg import SoundRequest

from sound_play.libsoundplay import SoundClient
from std_msgs.msg import Int32
from std_msgs.msg import Float64
i=0
flag=0
class battery(smach.State):
	def __init__(self):
		smach.State.__init__(self, outcomes=['safe','unsafe']) # Outcome

	def callback(self,data):
		global i		
		
                i=data.data
		#rospy.logerr("Success %d",i)	

	def listener(self):
		rospy.Subscriber("battery_level", Float64, self.callback) 

		

	def talker(self):
		pub = rospy.Publisher('ui_battery', Int32, queue_size=10)
		
		rate = rospy.Rate(1) # 10hz
		j=1
		while j<=2:
			hello_str = 1
			rospy.loginfo(hello_str)
			pub.publish(hello_str)			
			rate.sleep()
			j=j+1



	def execute(self, userdata):
		
		global i
		self.listener()	
		rospy.sleep(2)
		if i==100 or i!=25:

			return 'safe'
		elif i==25:			
			self.talker()			
			return 'safe'
                
