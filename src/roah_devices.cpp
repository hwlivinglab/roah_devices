/*
 * Copyright 2014 Instituto de Sistemas e Robotica, Instituto Superior Tecnico
 *
 * This file is part of RoAH Devices.
 *
 * RoAH Devices is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RoAH Devices is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with RoAH Devices.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string>

#include <boost/make_shared.hpp>
#include <boost/thread.hpp>
#include <boost/asio.hpp>

#include <ros/ros.h>

#include <std_msgs/Empty.h>
#include <std_srvs/Empty.h>
#include <roah_devices/DevicesState.h>
#include <roah_devices/Bool.h>
#include <roah_devices/Percentage.h>

#include "device_ids.h"
#include "devices_socket.h"
#include "devices_control.h"

#include <diagnostic_msgs/KeyValue.h>
#include <ros/ros.h>
#include <ros/console.h>
#include "std_msgs/String.h"

using namespace std;
using namespace ros;
using namespace boost::asio;
using boost::make_shared;
using boost::asio::ip::tcp;



class Bell
{
    Publisher ring_pub_;
    ServiceServer mock_srv_;
    boost::function<void () > update_;
    boost::mutex state_mutex_;
    Time state_;
    //edited by Kyna km362@hw.ac.uk
    NodeHandle nb; //initalise nodehandle for bell ring
    Publisher bell_pub = nb.advertise<diagnostic_msgs::KeyValue>("/iot_command", 1, false); //initlaise publisher
    //end of edit

    bool mock (std_srvs::Empty::Request& req, std_srvs::Empty::Response& res)
    {
      ring();
      return true;
    }

  public:
    Bell (NodeHandle& nh,
          string const& name,
          boost::function<void () > update)
      : ring_pub_ (nh.advertise<std_msgs::Empty> ("/devices/" + name, 1, false))
      , mock_srv_ (nh.advertiseService ("/devices/" + name + "/mock", &Bell::mock, this))
      , update_ (update)
      , state_ (TIME_MIN)
    {
    }

    void set_current()
    {
      // Nothing
    }

    Time get_state()
    {
      Time ret;
      {
        boost::lock_guard<boost::mutex> _ (state_mutex_);
        ret = state_;
      }
      return ret;
    }

    void ring()
    {
      {
        boost::lock_guard<boost::mutex> _ (state_mutex_);
        state_ = Time::now();
      }
      //code edit by Kyna km362@hw.ac.uk
      Rate loop_rate(10);     
      diagnostic_msgs::KeyValue msg; ///message type for /iot_command topic
      msg.key = "Hall_Intcm"; //device to change state of - intercom button
      msg.value = "ON"; //set device state to ON
      bell_pub.publish(msg); //publish message to /iot_command topic
      //ROS_ERROR_STREAM(msg); //print published message to console
      
      //gives time for code to be executed before exiting method
      ros::spinOnce();
      loop_rate.sleep();
      
      //end edit
      
      ring_pub_.publish (make_shared<std_msgs::Empty>());
      update_();
    }
};


class BoolSwitch
{
    ServiceServer srv_;
    ServiceServer on_srv_;
    ServiceServer off_srv_;
    boost::function<void () > update_;
    boost::function<void (int32_t) > setter_;
    boost::mutex state_mutex_;
    bool state_;

    bool set (roah_devices::Bool::Request& req, roah_devices::Bool::Response& res)
    {
      {
        boost::lock_guard<boost::mutex> _ (state_mutex_);
        state_ = req.data;
        setter_ (req.data ? 1 : 0);
      }
      //ROS_ERROR_STREAM("bool set"); //debug
      update_();
      return true;
    }

    bool on (std_srvs::Empty::Request& req, std_srvs::Empty::Response& res)
    {
      {
        boost::lock_guard<boost::mutex> _ (state_mutex_);
        state_ = true;
        setter_ (1);
      }

      update_(); //this method is from a separate library that we do not have access to
      return true;
    }

    bool off (std_srvs::Empty::Request& req, std_srvs::Empty::Response& res)
    {
      {
        boost::lock_guard<boost::mutex> _ (state_mutex_);
        state_ = false;
        setter_ (0);
      }

      update_();
      return true;
    }

  public:
    BoolSwitch (NodeHandle& nh,
                string const& name,
                boost::function<void () > update,
                boost::function<void (int32_t) > setter)
      : srv_ (nh.advertiseService ("/devices/" + name + "/set", &BoolSwitch::set, this))
      , on_srv_ (nh.advertiseService ("/devices/" + name + "/on", &BoolSwitch::on, this))
      , off_srv_ (nh.advertiseService ("/devices/" + name + "/off", &BoolSwitch::off, this))
      , update_ (update)
      , setter_ (setter)
      , state_ (false)
    {
    }

    void set_current()
    {
      boost::lock_guard<boost::mutex> _ (state_mutex_);
      setter_ (state_ ? 1 : 0);
    }

    bool get_state()
    {
      bool ret;
      {
        boost::lock_guard<boost::mutex> _ (state_mutex_);
        ret = state_;
      }
      return ret;
    }
};



class PercentageSwitch
{
    ServiceServer srv_;
    ServiceServer max_srv_;
    ServiceServer min_srv_;
    boost::function<void () > update_;
    boost::function<void (int32_t) > setter_;
    boost::mutex state_mutex_;
    uint8_t state_;

    bool set (roah_devices::Percentage::Request& req, roah_devices::Percentage::Response& res)
    {
      if ( (req.data < 0) || (req.data > 100)) {
        return false;
      }

      {
        boost::lock_guard<boost::mutex> _ (state_mutex_);
        state_ = req.data;
        setter_ (req.data);
      }

      update_();
      return true;
    }

    bool max (std_srvs::Empty::Request& req, std_srvs::Empty::Response& res)
    {
      {
        boost::lock_guard<boost::mutex> _ (state_mutex_);
        state_ = 100;
        setter_ (100);
      }

      update_();
      return true;
    }

    bool min (std_srvs::Empty::Request& req, std_srvs::Empty::Response& res)
    {
      {
        boost::lock_guard<boost::mutex> _ (state_mutex_);
        state_ = 0;
        setter_ (0);
      }

      update_();
      return true;
    }

  public:
    PercentageSwitch (NodeHandle& nh,
                      string const& name,
                      boost::function<void () > update,
                      boost::function<void (int32_t) > setter)
      : srv_ (nh.advertiseService ("/devices/" + name + "/set", &PercentageSwitch::set, this))
      , max_srv_ (nh.advertiseService ("/devices/" + name + "/max", &PercentageSwitch::max, this))
      , min_srv_ (nh.advertiseService ("/devices/" + name + "/min", &PercentageSwitch::min, this))
      , update_ (update)
      , setter_ (setter)
      , state_ (0)
    {
    }

    void set_current()
    {
      boost::lock_guard<boost::mutex> _ (state_mutex_);
      setter_ (state_);
    }

    uint8_t get_state()
    {
      uint8_t ret;
      {
        boost::lock_guard<boost::mutex> _ (state_mutex_);
        ret = state_;
      }
      return ret;
    }
};



class RoahDevices
{
    NodeHandle nh_;
    Publisher state_pub_;

    Bell bell_;
    BoolSwitch switch_1_;
    BoolSwitch switch_2_;
    BoolSwitch switch_3_;
    PercentageSwitch dimmer_;
    PercentageSwitch blinds_;

    io_service io_service_;
    tcp::socket socket_;
    boost::mutex write_mutex_;
    boost::thread thread_;

    uint8_t command_;
   
    // edited by Clarissa Cremona cc531@hw.ac.uk
    NodeHandle n;
    Publisher pub = n.advertise<diagnostic_msgs::KeyValue>("/iot_command", 1, false);
    // end of edited code

    void
    update()
    {
      roah_devices::DevicesState::Ptr msg = make_shared<roah_devices::DevicesState>();
      msg->bell = bell_.get_state();
      msg->switch_1 = switch_1_.get_state();
      msg->switch_2 = switch_2_.get_state();
      msg->switch_3 = switch_3_.get_state();
      msg->dimmer = dimmer_.get_state();
      msg-> blinds = blinds_.get_state();
      state_pub_.publish (msg);
    }

    void
    set_int (string const& arg0,
             int32_t arg1,
             double mul)
    {
      boost::lock_guard<boost::mutex> _ (write_mutex_);
      try {
        if (! socket_.is_open()) {
          return;
        }

        // edited by Kyna km362@hw.ac.uk and Clarissa cc531@hw.ac.uk

	// convert arg0 to int
        string switch_no = arg0.c_str(); 
        stringstream ss(switch_no);
        int x = 0;
        ss >> x;
	//ROS_ERROR_STREAM(x); //prints int that relates to case number

        Rate loop_rate(10);

	// message type for topic /iot_command
        diagnostic_msgs::KeyValue msg;
      
	// check device to manipulate
        switch(x){
          case 11: msg.key = "Ktch_light";
          break;
          case 33: msg.key = "hw_switch";
          break;
          case 40: msg.key = "Hue_iris_toggle_2";
          break;
          case 58: msg.key = "Hue_iris_dimmer_2";
          break;
          //case 77: msg.key = "name of blinds device";
          //break;
        }

	// check on/off
        if(arg1 == 1)
        {
          msg.value = "ON";
          //ROS_ERROR_STREAM("Switching on");
        }
        else if (arg1 == 0)
        {
          msg.value = "OFF";
          //ROS_ERROR_STREAM("Switching off");
        }
        else if (arg1 >= 2 && arg1 <= 10)
        {
          msg.value = "10";
          //ROS_ERROR_STREAM("Dimmer");
        }
	else if (arg1 >= 11 && arg1 <= 20)
        {
          msg.value = "20";
        }
        else if (arg1 >= 21 && arg1 <= 30)
        {
          msg.value = "30";
        }
        else if (arg1 >= 31 && arg1 <= 40)
        {
          msg.value = "40";
        }
        else if (arg1 >= 41 && arg1 <= 50)
        {
          msg.value = "50";
        }
        else if (arg1 >= 51 && arg1 <= 60)
        {
          msg.value = "60";
        }
        else if (arg1 >= 61 && arg1 <= 70)
        {
          msg.value = "70";
        }
        else if (arg1 >= 71 && arg1 <= 80)
        {
          msg.value = "80";
        }
        else if (arg1 >= 81 && arg1 <= 90)
        {
          msg.value = "90";
        }
        else if (arg1 >= 91 && arg1 <= 100)
        {
          msg.value = "100";
        }

	// publish message to topic /iot_command
        pub.publish(msg);

	// print message to console
        ROS_ERROR_STREAM(msg);

        ros::spinOnce();
        loop_rate.sleep();
	// end edit

        uint32_t arg1_val = arg1 * mul;
        ROS_ERROR_STREAM(arg1); 
        sync_write_byte (socket_, 'I');
        sync_write_string (socket_, arg0);
        sync_write_long (socket_, arg1_val);
        ROS_DEBUG_STREAM ("setInt(\"" << arg0 << "\", " << arg1_val << ")");
      }
      catch (...) {}
    }

    void
    start_read()
    {
      async_read (socket_,
                  buffer (&command_, 1),
                  boost::bind (&RoahDevices::handle_read, this,
                               boost::asio::placeholders::error));
    }

    void
    handle_read (const boost::system::error_code& error)
    {
      if (error) {
        cerr << "Some error code in handle_read" << endl << flush;
        io_service_.stop();
        return;
      }

      try {
        switch (command_) {
          case 'E': {
            string arg0 = sync_read_string (socket_);
            ROS_ERROR_STREAM ("Cannot connect to server: already a connection from: " << arg0);
            // TODO keep trying
            abort();
          }
          break;
          case '1': {
            string arg0 = sync_read_string (socket_);
            int arg1 = sync_read_long (socket_);
            int arg2 = sync_read_long (socket_);
            ROS_DEBUG_STREAM ("notifyChanges(\"" << arg0 << "\", " << arg1 << ", " << arg2 << ")");
          }
          break;
          case '2': {
            char arg0 = sync_read_byte (socket_);
            string arg1 = sync_read_string (socket_);
            string arg2 = sync_read_string (socket_);
            ROS_DEBUG_STREAM ("notifyChanges(" << (arg0 == 'N' ? "NEW" : arg0 == 'E' ? "EDIT" : arg0 == 'D' ? "DELETE" : "UNKNOWN") << ", \"" << arg1 << "\", \"" << arg2 << "\")");
            if ( (arg0 == 'E')
                 && (arg1 == BELL_ID)
                 && (arg2 == "1")) {
              bell_.ring();
            }
          }
          break;
          default:
            ROS_FATAL_STREAM ("Received unknown command value " << ( (int) command_) << " char " << ( (char) command_));
            abort();
        }
      }
      catch (...) {
        cerr << "Some error in sync reads" << endl << flush;
        io_service_.stop();
        return;
      }

      start_read();
    }

    void run_thread()
    {
      while (ok()) {
        string smartif_host;
        param::param<string> ("~smartif_host", smartif_host, "192.168.1.4");
        tcp::endpoint endpoint (ip::address::from_string (smartif_host), 6666); //why was this 6665???
        try {
          socket_.connect (endpoint);
          ROS_DEBUG_STREAM ("Connected to " << endpoint);
          start_read();
          bell_.set_current();
          switch_1_.set_current();
          switch_2_.set_current();
          switch_3_.set_current();
          dimmer_.set_current();
          blinds_.set_current();
          update();
          io_service_.run();
        }
        catch (...) {}
        socket_.close();
        io_service_.reset();
        if (ok()) {
          Duration (0.2).sleep();
        }
      }
    }

  public:
    RoahDevices()
      : nh_()
      , state_pub_ (nh_.advertise<roah_devices::DevicesState> ("/devices/state", 1, true))
      , bell_ (nh_,
               "bell",
               boost::bind (&RoahDevices::update, this))
      , switch_1_ (nh_,
                   "switch_1",
                   boost::bind (&RoahDevices::update, this),
                   boost::bind (&RoahDevices::set_int, this, SWITCH_1_ID, _1, 1))
      , switch_2_ (nh_,
                   "switch_2",
                   boost::bind (&RoahDevices::update, this),
                   boost::bind (&RoahDevices::set_int, this, SWITCH_2_ID, _1, 1))
      , switch_3_ (nh_,
                   "switch_3",
                   boost::bind (&RoahDevices::update, this),
                   boost::bind (&RoahDevices::set_int, this, SWITCH_3_ID, _1, 1))
      , dimmer_ (nh_,
                 "dimmer",
                 boost::bind (&RoahDevices::update, this),
                 boost::bind (&RoahDevices::set_int, this, DIMMER_ID, _1, 1))
      , blinds_ (nh_,
                 "blinds",
                 boost::bind (&RoahDevices::update, this),
                 boost::bind (&RoahDevices::set_int, this, BLINDS_ID, _1, 100))
      , io_service_()
      , socket_ (io_service_)
      , thread_ (&RoahDevices::run_thread, this)
    {
    }

    ~RoahDevices()
    {
      // socket_.shutdown (socket_base::shutdown_both);
      io_service_.stop();
      thread_.join();
    }
};



int main (int argc, char** argv)
{
  init (argc, argv, "roah_devices");

  RoahDevices node;

  spin();

  return 0;
}



