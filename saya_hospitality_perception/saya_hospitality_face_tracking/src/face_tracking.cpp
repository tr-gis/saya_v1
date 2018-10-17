#include <ros/ros.h>
#include <ros/console.h>
#include <iostream>
#include <stdio.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Bool.h>


// opencv image processing libraries
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "opencv2/objdetect/objdetect.hpp"

// to facilitate the processing of the images in ROS
#include <image_transport/image_transport.h>  // for publishing and subscribing to images in ROS
#include <cv_bridge/cv_bridge.h>              // to convert between ROS and OpenCV Image formats
#include <sensor_msgs/image_encodings.h>

static const std::string OPENCV_WINDOW = "Sayabot Face Tracking";
static const int frame_centre = 210;
int face_X_position;

static int limit = 0;
static float data = 0;
static int e = 0, e1 = 0;
static float kp = 0.00055, kd = 0.0001;
static float present_X = 0, prev_X = 0;
static int count_X = 0;

int msleep(unsigned long milisec)
{
  struct timespec req = {0};
  time_t sec = (int)(milisec / 1000);
  milisec = milisec - (sec * 1000);
  req.tv_sec = sec;
  req.tv_nsec = milisec * 1000000L;
  while (nanosleep(&req, &req) == -1)
    continue;
  return 1;
}

class FaceDetectionTracking
{
public:
  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
  image_transport::Subscriber im_sub_;
  image_transport::Publisher im_pub_;
  ros::Publisher servo_pub = nh_.advertise<std_msgs::Float64>("/pan_controller/command", 100); // Publisher for servo message
  ros::Publisher output_pub = nh_.advertise<std_msgs::Bool>("/sayabot_hospitality_perception/face_detection/output",100); //Publishes face_detection output
  cv::CascadeClassifier face_cascade_;

  cv::HOGDescriptor hog_;	

  FaceDetectionTracking() : it_(nh_)
  {
	// Path to the haarcascade_frontalface_alt.xml
    cv::String face_cascade_name =
        ("/home/asimov/robo_ws/src/saya_hospitality-ros-pkg/saya_hospitality_perception/saya_hospitality_face_tracking/include/saya_hospitality_face_tracking/haarcascade_frontalface_alt.xml");                                         

    // Load the hog descriptor
    hog_.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());

    // Load face detector HAAR cascades
    if (!face_cascade_.load(face_cascade_name))
      ROS_ERROR("--(!)Error loading face detector cascade \n");

    // Subscrive to input video feed and publish output video feed
    im_sub_ = it_.subscribe("usb_cam/image_raw", 1, &FaceDetectionTracking::imageCallback, this);
    //im_pub_ = it_.advertise("/sayabot_hospitality_face_tracker/output_video", 1);

    //cv::namedWindow(OPENCV_WINDOW);
  }

  ~FaceDetectionTracking()
  {
    cv::destroyWindow(OPENCV_WINDOW);
  }

  void imageCallback(const sensor_msgs::ImageConstPtr& msg)
  {
    cv_bridge::CvImagePtr cv_ptr;     // Make image processable in ROS


    std_msgs::Float64 servo_msg;      // Float64 message for dynamixel_servo/command topic
    
    std_msgs::Bool output_msg;

    try
    {
      cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }
    cv::Mat im_bgr = cv_ptr->image;

    std::vector<cv::Rect> detected_faces;
    cv::Mat im_gray;
    cv::cvtColor(im_bgr, im_gray, CV_BGR2GRAY); // converting RGB image to gray_scale
    cv::equalizeHist(im_gray, im_gray);

    // HAAR Face detector

    face_cascade_.detectMultiScale(im_gray, detected_faces, 1.1, 3, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));
    
    if ((detected_faces.size()) == 0)
    {
      ROS_INFO_STREAM("No person detected");
      limit++;
      output_msg.data = 0;
      output_pub.publish(output_msg);
      ROS_INFO_STREAM(limit);
      if (limit >= 2)
      {
        data = 2.5;
        ROS_INFO_STREAM("Data");
        ROS_INFO_STREAM(data);
        servo_msg.data = data;
        servo_pub.publish(servo_msg);  // Message publishes to joint_controller/command 
        limit = 0;
      }
    }

    // Draw detected detected_faces to screen as circles
    for (unsigned i = 0; i < detected_faces.size(); i++)
    {
      ROS_INFO_STREAM("height=");
      ROS_INFO_STREAM(detected_faces[i].height);

      if (detected_faces[i].height > 125 && detected_faces[i].height < 300)
      {
        limit = 0;
        ROS_INFO_STREAM("Person detected");
        output_msg.data = 1;
        output_pub.publish(output_msg);
        cv::Point center(detected_faces[i].x + detected_faces[i].width * 0.5,
                         detected_faces[i].y + detected_faces[i].height * 0.5);
                         
         //Drawing circle around faces                 
        //cv::ellipse(im_bgr, center, cv::Size(detected_faces[i].width * 0.5, detected_faces[i].height * 0.5), 0, 0, 360,
                    //cv::Scalar(255, 0, 255), 4, 8, 0);

        ROS_INFO_STREAM("X=");
        ROS_INFO_STREAM(detected_faces[i].x);

        face_X_position = detected_faces[i].x;
        ROS_INFO_STREAM(face_X_position);
        ROS_INFO_STREAM(frame_centre);

		// Logic for tracking the face 
        if (detected_faces[0].width > detected_faces[1].width)
        {
          present_X = detected_faces[0].x;
        }
        else
        {
          present_X = detected_faces[1].x;
        }
        if (prev_X <= present_X + 10 && prev_X >= present_X - 10)
        {
          count_X++;
        }
        else
        {
          count_X = 0;
        }

        e = 210 - detected_faces[i].x;
        if (e < 0)
        {
          e = -e;
        }
        /*
        ROS_INFO_STREAM("E");
        ROS_INFO_STREAM(e);
        ROS_INFO_STREAM("prev_X");
        ROS_INFO_STREAM(prev_X);
        ROS_INFO_STREAM("Present_X");
        ROS_INFO_STREAM(present_X);
        */
        
        ROS_INFO_STREAM("Count");
        ROS_INFO_STREAM(count_X);

        prev_X = present_X;

        if (count_X >= 1)
        {
          if (present_X < 200)
          {
            // data = data + kp*e + kd*(e - e1);
            data = data + kp * e;
            if (data <= 1|| data >= 4)
            {
              data = 4;
              ROS_INFO_STREAM("Data");
              ROS_INFO_STREAM(data);
              servo_msg.data = data;
              servo_pub.publish(servo_msg);
            }
            else
            {
              ROS_INFO_STREAM("Data");
              ROS_INFO_STREAM(data);
              servo_msg.data = data;
              servo_pub.publish(servo_msg);
            }
            e1 = e;
          }
          else if (present_X > 220)
          {
            // data = data - kp*e + kd*(e - e1);
            data = data - kp * e;
            if (data <= 1 || data >= 4)
            {
              data = 1;
              ROS_INFO_STREAM("Data");
              ROS_INFO_STREAM(data);
              servo_msg.data = data;
              servo_pub.publish(servo_msg);
            }
            else
            {
              servo_msg.data = data;
              ROS_INFO_STREAM("Data");
              ROS_INFO_STREAM(data);
              servo_pub.publish(servo_msg);
            }
            e1 = e;
          }
        }
      }

      else
      {
        ROS_INFO_STREAM("Person detected:OUT OF RANGE");
        limit++;
        output_msg.data = 0;
        output_pub.publish(output_msg);
        ROS_INFO_STREAM(limit);
        if (limit >= 2)
        {
          data = 2.5;
          ROS_INFO_STREAM("Data");
          ROS_INFO_STREAM(data);
          servo_msg.data = data;

          servo_pub.publish(servo_msg);
          limit = 0;
        }
        ROS_INFO_STREAM("DATA:");
        ROS_INFO_STREAM(data);
      }
    }

    //cv::imshow(OPENCV_WINDOW, im_bgr);
    cv::waitKey(3);
  }
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "hog_haar_person_detection1");
  FaceDetectionTracking object;
  ros::spin();
  return 0;
}
