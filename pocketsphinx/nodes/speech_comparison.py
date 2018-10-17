#!/usr/bin/env python
# license removed for brevity
import rospy
from std_msgs.msg import String


def callback(data):
    rospy.loginfo(rospy.get_caller_id() + "I heard %s", data.data)
    spoken_string = data.data
    comparison_string = "what is your name?"
    if (spoken_string == comparison_string):
		print "Hi I am Eva"
		talker()
    
def listener():

    # In ROS, nodes are uniquely named. If two nodes with the same
    # node are launched, the previous one is kicked off. The
    # anonymous=True flag means that rospy will choose a unique
    # name for our 'listener' node so that multiple listeners can
    # run simultaneously.
    rospy.init_node('listener', anonymous=True)

    rospy.Subscriber("/recognizer/output", String, callback)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()
    
def talker():
    speech_output_pub = rospy.Publisher('chatter', String, queue_size=10)
    rate = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
        speech_out = "publishing true %s" % rospy.get_time()
        rospy.loginfo(speech_out)
        speech_output_pub.publish(speech_out)
        rate.sleep()

if __name__ == '__main__':
    try:
		listener()
    except rospy.ROSInterruptException:
        pass
