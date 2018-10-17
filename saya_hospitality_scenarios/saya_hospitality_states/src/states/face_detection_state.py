####
# This file defines the states of face detection for the sayabot_hospitality robot
#
#	States:
# 		1) Face_Detection
#		2) Detected
#		3) Not_Detected
#		
##   Face_Detection State
#		Outcomes: face_detected, No_face_detected
#	This state is a simple action client state for the "face_tracking_action_server"
#	It sends the goal to the action server to find whether any face is detected or not.	
#	Based on the result from the action server the state decide the outcome.
#		if (result from action server = 1) then:
# 			it returns face_detected as an outcome.
#		else:
#			it returns No_face_detected as an outcome.
#
##   Detected State
#		Outcome: Arm Manipultaion
#	Once this state is executed it returns the outcome as Arm Manipulation
#	This state initiates the next operation after face is detected.
#
##   Not_Detected State
#		Outcome: Redoing
#	whwn this state is executed it returns the outcome as Redoing
# 	This state transfer control to Face_Detection State
####
	
import roslib
import rospy
import smach
import smach_ros
import os 
from smach_ros import SimpleActionState
import actionlib
import actionlib_msgs
from std_msgs.msg import Bool
from saya_hospitality_perception_msgs.msg import FaceTrackingAction, FaceTrackingGoal, FaceTrackingResult #Imports the Action Messages

class Face_Detection(smach.State):
	def __init__(self):
		smach.State.__init__(self, outcomes=['face_detected','No_face_detected'])
		self.detected_count = 0
		self.client = actionlib.SimpleActionClient('face_tracking_action_server',FaceTrackingAction)
		print 'waiting for server'
		self.client.wait_for_server()

	
	def execute(self,userdata):
		goal = FaceTrackingGoal(goal = 1)
		self.client.send_goal(goal)
		self.client.wait_for_result()
		check = Bool()		
		check = self.client.get_result()
		print check
		if check.result == 1:
			return 'face_detected'
		else:
			return 'No_face_detected'

class Detected(smach.State):
	def __init__(self):
		smach.State.__init__(self, outcomes=['Complete'])
		self.detected_count = 0

	def execute(self, userdata):
		rospy.sleep(1)
		return 'Complete'
				
class Not_Detected(smach.State):
	def __init__(self):
		smach.State.__init__(self, outcomes=['Redoing'])
	def execute(self, userdata):
		rospy.sleep(1)
		return 'Redoing'

