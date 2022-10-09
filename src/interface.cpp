/*
 * OpenVMP, 2022
 *
 * Author: Roman Kuzmenko
 * Created: 2022-09-24
 *
 * Licensed under Apache License, Version 2.0.
 */

#include "switch_r413d08/interface.hpp"

#include <locale>

#include "modbus_rtu/factory.hpp"
#include "switch_r413d08/node.hpp"

namespace switch_r413d08 {

Interface::Interface(rclcpp::Node *node) : switch_interface::Interface(node) {
  prov_ = modbus_rtu::Factory::New(node);

  node->declare_parameter("switch_r413d08_inverted", false);
  node->get_parameter("switch_r413d08_inverted", param_inverted_);

  change_leaf_id_ = node_->create_service<switch_r413d08::srv::ChangeLeafId>(
      interface_prefix_.as_string() + "/change_leaf_id",
      std::bind(&Interface::change_leaf_id_handler_, this,
                std::placeholders::_1, std::placeholders::_2));

  prov_->generate_modbus_mappings(interface_prefix_.as_string(),
                                  "config/modbus.yaml");
}

void Interface::change_leaf_id_handler_(
    const std::shared_ptr<switch_r413d08::srv::ChangeLeafId::Request> request,
    std::shared_ptr<switch_r413d08::srv::ChangeLeafId::Response> response) {
  auto req = std::make_shared<modbus::srv::HoldingRegisterWrite::Request>();
  auto resp = std::make_shared<modbus::srv::HoldingRegisterWrite::Response>();

  // req->leaf_id will be auto-filled
  req->addr = 0x00FF;
  req->value = request->new_leaf_id;

  prov_->holding_register_write(req, resp);
  response->exception_code = resp->exception_code;
}

void Interface::switch_handler_real_(
    const std::shared_ptr<switch_interface::srv::Switch::Request> request,
    std::shared_ptr<switch_interface::srv::Switch::Response> response) {
  auto req = std::make_shared<modbus::srv::HoldingRegisterWrite::Request>();
  auto resp = std::make_shared<modbus::srv::HoldingRegisterWrite::Response>();

  bool want_on = request->on;
  bool inverted = param_inverted_.as_bool();

  // req->leaf_id will be auto-filled
  req->addr = request->channel + 1;
  if (want_on ^ inverted) {
    req->value = 0x100;
  } else {
    req->value = 0x200;
  }

  prov_->holding_register_write(req, resp);
  response->exception_code = resp->exception_code;
}

}  // namespace switch_r413d08