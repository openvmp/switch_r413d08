/*
 * OpenVMP, 2022
 *
 * Author: Roman Kuzmenko
 * Created: 2022-09-24
 *
 * Licensed under Apache License, Version 2.0.
 */

#ifndef OPENVMP_SWITCH_R413D08_NODE_H
#define OPENVMP_SWITCH_R413D08_NODE_H

#include <memory>
#include <string>

#include "r413d08_driver/interface.hpp"
#include "rclcpp/rclcpp.hpp"

namespace r413d08_driver {

class Node : public rclcpp::Node {
 public:
  Node();

 private:
  std::shared_ptr<Interface> intf_;
};

}  // namespace r413d08_driver

#endif  // OPENVMP_SWITCH_R413D08_NODE_H
