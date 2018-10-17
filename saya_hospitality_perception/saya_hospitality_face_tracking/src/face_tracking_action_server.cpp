#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <saya_hospitality_perception_msgs/FaceTrackingAction.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Bool.h>

static int count_;
class FaceTrackingActionNode
{
protected:

  ros::NodeHandle nh_;
  // NodeHandle instance must be created before this line. Otherwise strange error may occur.
  actionlib::SimpleActionServer<saya_hospitality_perception_msgs::FaceTrackingAction> as_; 
  std::string action_name_;
  // create messages that are used to published feedback/result
  saya_hospitality_perception_msgs::FaceTrackingFeedback feedback_;
  saya_hospitality_perception_msgs::FaceTrackingResult result_;

  ros::Subscriber sub_;
  bool goal_;

public:

  FaceTrackingActionNode(std::string name) :
    as_(nh_, name, false),
    action_name_(name)
  {
	  
    as_.registerGoalCallback(boost::bind(&FaceTrackingActionNode::goalCB, this));
    as_.registerPreemptCallback(boost::bind(&FaceTrackingActionNode::preemptCB, this));
    
    //ROS_INFO_STREAM("as_.started");
    as_.start();
    
    ROS_INFO_STREAM("--------FaceTrackingAction_Server is started-------");
  }

  ~FaceTrackingActionNode(void)
  {
  }
  
  void goalCB()
  {
    //ROS_INFO_STREAM("Goal Started");
    // accept the new goal
    goal_ = as_.acceptNewGoal()->goal;
    ROS_INFO_STREAM(goal_);
    if(goal_)
    {
	ROS_INFO_STREAM("--------FaceTrackingAction_Server Goal Recieved-------");
    sub_ = nh_.subscribe("/sayabot_hospitality_perception/face_detection/output", 1, &FaceTrackingActionNode::analysisCB, this);
	}
  }
  
  void preemptCB()
  {
    ROS_INFO("%s: Preempted", action_name_.c_str());
    // set the action state to preempted
    as_.setPreempted();
  }

  
  
  void analysisCB(const std_msgs::Bool msg)
  {
	  if (!as_.isActive())
      return;
    
	  
	 // ROS_INFO_STREAM("AnalyaisCB is called");  
     // ROS_INFO_STREAM("MSG");
      ROS_INFO_STREAM(msg);
      if (msg.data)
      { count_ += 1;
		            ROS_INFO_STREAM(count_);

		  feedback_.feedback = true;
		  		}
		else{
			count_ -= 1;
			feedback_.feedback = false;
		}
		if(count_ >3)
		{
			result_.result= true;
			count_ = 0;
			as_.setSucceeded(result_);

	}
	if(count_ < -3){
		result_.result = false;
		count_ = 0;
		as_.setSucceeded(result_);

	}
	}


};


int main(int argc, char** argv)
{
  ros::init(argc, argv, "FaceTrackingAction_Server");

  FaceTrackingActionNode FaceTrackingAction_(ros::this_node::getName());
  ros::spin();

  return 0;
}
