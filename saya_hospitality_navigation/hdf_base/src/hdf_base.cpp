/**     Copyright (c) 2015-2016 ASIMOV Robotics. All rights reserved. ////
*
*
//------------------------------------------------------------------------------*/
#include "hdf_base/hdf_base.h"
#include "controller_manager/controller_manager.h"
#include "ros/ros.h"
#include <string>
#include <boost/asio/io_service.hpp>
#include <boost/thread.hpp>

/**
* Control loop for HDFCbot
*/
void controlLoop(const ros::TimerEvent &event, hdf_base::HdfHW &hdf,
    controller_manager::ControllerManager &cm)
{
  hdf.readFromHardware();
  cm.update(event.current_real, event.current_real - event.last_real);
  hdf.writeToHardware();
}

int main(int argc, char *argv[])
{
  ros::init(argc, argv, "hdf_base");
  ros::NodeHandle nh, private_nh("~");

  double control_frequency, diagnostic_frequency;
  private_nh.param<double>("control_frequency", control_frequency, 50.0);

  // Initialize robot hardware and link to controller manager
  hdf_base::HdfHW hdf(nh, private_nh);

  controller_manager::ControllerManager cm(&hdf, nh);

  // Setup separate queue and single-threaded spinner to process timer callbacks

  ros::CallbackQueue hdf_queue;
  ros::AsyncSpinner hdf_spinner(1, &hdf_queue);

  ros::TimerOptions control_timer(
      ros::Duration(1 / control_frequency),
      boost::bind(controlLoop, _1, boost::ref(hdf), boost::ref(cm)),
      &hdf_queue);
  ros::Timer control_loop = nh.createTimer(control_timer);
  hdf_spinner.start();

  // Process remainder of ROS callbacks separately, mainly ControlManager related
  ros::spin();

  return 0;
}
