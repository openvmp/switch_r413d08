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

#include "modbus/interface.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include "switch_interface/interface.hpp"
#include "switch_r413d08/srv/change_leaf_id.hpp"

namespace switch_r413d08 {

class Interface : public switch_interface::Interface {
 public:
  Interface(rclcpp::Node *node);
  virtual ~Interface() {}

 protected:
  rclcpp::Parameter param_inverted_;

  virtual void switch_handler_real_(
      const std::shared_ptr<switch_interface::srv::Switch::Request> request,
      std::shared_ptr<switch_interface::srv::Switch::Response> response)
      override;

 private:
  std::shared_ptr<modbus::Interface> prov_;

  rclcpp::Service<switch_r413d08::srv::ChangeLeafId>::SharedPtr change_leaf_id_;
  void change_leaf_id_handler_(
      const std::shared_ptr<switch_r413d08::srv::ChangeLeafId::Request> request,
      std::shared_ptr<switch_r413d08::srv::ChangeLeafId::Response> response);
};

}  // namespace switch_r413d08

#endif  // OPENVMP_SWITCH_R413D08_INTERFACE_H
