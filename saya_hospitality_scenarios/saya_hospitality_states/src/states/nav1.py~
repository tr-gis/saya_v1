

import roslib
import rospy
import smach
import smach_ros
import os, sys
from std_msgs.msg import Bool
from sound_play.msg import SoundRequest

from sound_play.libsoundplay import SoundClient
import actionlib
from actionlib_msgs.msg import *
from move_base_msgs.msg import MoveBaseAction, MoveBaseGoal
from std_msgs.msg import *
from geometry_msgs.msg import *

i=0
j=0

class GoalMaker(object):
	
	def __init__(self):
		
		
		self.move_base = actionlib.SimpleActionClient("move_base", MoveBaseAction)
		
		
		
			
		rospy.logerr("Connected to move base server")
		

	def move(self,k):   # accepting k value:: has to take the subscribed value
		global j
		goal = MoveBaseGoal()
		# Use the map frame to define goal poses
		goal.target_pose.header.frame_id = 'map'

		# Set the time stamp to "now"
		goal.target_pose.header.stamp = rospy.Time.now()

		# Set the goal there
		if k==1:		
			goal.target_pose.pose.position.x=3.9891
			goal.target_pose.pose.position.y=3.6724
			goal.target_pose.pose.position.z=0
		
			goal.target_pose.pose.orientation.x=0
			goal.target_pose.pose.orientation.y=0
		        goal.target_pose.pose.orientation.z=0.6179
			goal.target_pose.pose.orientation.w=0.7861

		elif k==2:
			goal.target_pose.pose.position.x=3.9891
			goal.target_pose.pose.position.y=3.6724
			goal.target_pose.pose.position.z=0
		
			goal.target_pose.pose.orientation.x=0
			goal.target_pose.pose.orientation.y=0
			goal.target_pose.pose.orientation.z=0.6179
			goal.target_pose.pose.orientation.w=0.7861
		elif k==3:

			goal.target_pose.pose.position.x=0.9638
			goal.target_pose.pose.position.y=-0.6547
			goal.target_pose.pose.position.z=0
		
			goal.target_pose.pose.orientation.x=0
			goal.target_pose.pose.orientation.y=0
			goal.target_pose.pose.orientation.z=-0.8474
			goal.target_pose.pose.orientation.w=0.5309
		elif k==4:

			goal.target_pose.pose.position.x=3.9891
			goal.target_pose.pose.position.y=3.6724
			goal.target_pose.pose.position.z=0
		
			goal.target_pose.pose.orientation.x=0
			goal.target_pose.pose.orientation.y=0
			goal.target_pose.pose.orientation.z=0.6179
			goal.target_pose.pose.orientation.w=0.7861

		elif k==5:

			goal.target_pose.pose.position.x=3.85025906563
			goal.target_pose.pose.position.y= 2.35579514503
			goal.target_pose.pose.position.z=0
			goal.target_pose.pose.orientation.x=0
			goal.target_pose.pose.orientation.y=0
			goal.target_pose.pose.orientation.z= -0.434633170955
			goal.target_pose.pose.orientation.w= 0.90060757642
		elif k==6:

			goal.target_pose.pose.position.x=4.97587442398
			goal.target_pose.pose.position.y=3.35257005692
			goal.target_pose.pose.position.z=0
		
			goal.target_pose.pose.orientation.x=0
			goal.target_pose.pose.orientation.y=0
			goal.target_pose.pose.orientation.z=-0.375859431523
			goal.target_pose.pose.orientation.w=0.926676689971
		

				
		
		# Send the goal pose to the MoveBaseAction server
		self.move_base.send_goal(goal)

		# Allow 1 minute to get there
		finished_within_time = self.move_base.wait_for_result(rospy.Duration(240)) # 15 implies time in seconds to be waited for goal completion

		# If we don't get there in time, abort the goal
		if not finished_within_time:
			j=0				#variable for checking the goal status
			self.move_base.cancel_goal()
			rospy.logerr("Timed out achieving goal")                  #section of code to be fixed, to allow for feedback from base and removing the delay
			
		else:
			j=1
		
		
		state = self.move_base.get_state()
		if state == GoalStatus.SUCCEEDED:
			rospy.logerr("Goal succeeded")
			

	



# define state Bar
class nav(smach.State):

	
	def __init__(self, gm):
		smach.State.__init__(self,outcomes=['goal_reached','goal_not_reached'])
		
		self.mover=gm
		
		
	def callback(self,data):
		rospy.logerr("Success %d",i)  
			
                
	

	def listener(self):
		global i
		try:	
			k=rospy.wait_for_message("ui_guide", Int32, timeout=10)
			rospy.Subscriber("ui_guide", Int32, self.callback)
			#os.system("rosrun saya_hospitality_audio speech5.py") 
			#os.system("roslaunch eva_arm_controller play1.launch")
			i=k.data 
		except(rospy.ROSException), e:
			rospy.logerr("No publish")
		rospy.logerr(i)
		
		        

	def execute(self, userdata):
		global i
		global j		
		rospy.logerr("value of i=%d",i)		
		self.listener()	
		
		
		#rospy.sleep(2)  
		self.mover.move(i) 
		
                i=0	
		rospy.logerr("Second Check %d",i)	
  		#rospy.sleep(20)   #Delay put in:To be worked on
		if j==1:
			rospy.logerr("Goal_reached")	
			return 'goal_reached'
		else:	
			rospy.logerr("Goal_not_reached")			
			return 'goal_not_reached'
