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

#include "r413d08_driver/srv/change_leaf_id.hpp"
#include "rclcpp/rclcpp.hpp"
#include "remote_modbus/interface.hpp"
#include "remote_switch/implementation.hpp"
#include "std_msgs/msg/int32.hpp"

namespace r413d08_driver {

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
  std::shared_ptr<remote_modbus::Interface> prov_;

  rclcpp::Service<srv::ChangeLeafId>::SharedPtr change_leaf_id_;
  void change_leaf_id_handler_(
      const std::shared_ptr<srv::ChangeLeafId::Request> request,
      std::shared_ptr<srv::ChangeLeafId::Response> response);
};

}  // namespace r413d08_driver

#endif  // OPENVMP_SWITCH_R413D08_INTERFACE_H
