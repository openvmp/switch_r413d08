/*
 * OpenVMP, 2022
 *
 * Author: Roman Kuzmenko
 * Created: 2022-09-24
 *
 * Licensed under Apache License, Version 2.0.
 */

#ifndef OPENVMP_SWITCH_R413D08_INTERFACE_H
#define OPENVMP_SWITCH_R413D08_INTERFACE_H

#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "remote_switch/implementation.hpp"
#include "ros2_modbus/interface.hpp"
#include "ros2_r413d08/srv/change_leaf_id.hpp"
#include "std_msgs/msg/int32.hpp"

namespace ros2_r413d08 {

class Interface : public remote_switch::Implementation {
 public:
  Interface(rclcpp::Node *node);
  virtual ~Interface() {}

 protected:
  rclcpp::Parameter param_inverted_;

  virtual void switch_handler_real_(
      const std::shared_ptr<remote_switch::srv::Switch::Request> request,
      std::shared_ptr<remote_switch::srv::Switch::Response> response) override;

 private:
  std::shared_ptr<ros2_modbus::Interface> prov_;

  rclcpp::Service<srv::ChangeLeafId>::SharedPtr change_leaf_id_;
  void change_leaf_id_handler_(
      const std::shared_ptr<srv::ChangeLeafId::Request> request,
      std::shared_ptr<srv::ChangeLeafId::Response> response);
};

}  // namespace ros2_r413d08

#endif  // OPENVMP_SWITCH_R413D08_INTERFACE_H
