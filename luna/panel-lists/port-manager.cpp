PortManager::PortManager(View* view) : PanelList(view, Size{~0, ~0}) {
  setCollapsible().setVisible(false);
  listView.onChange([&] { onChange(); });
}

auto PortManager::show() -> void {
  root = emulator.root;
  listView.selectNone().doChange();
  refresh();
  setVisible(true);
}

auto PortManager::hide() -> void {
  setVisible(false);
  root = {};
}

auto PortManager::refresh() -> void {
  //save the currently selected node to try and reselect it after rebuilding the tree
  velvet::Node::Object selected;
  if(auto item = listView.selected()) {
    selected = item.attribute<velvet::Node::Object>("node");
  }

  listView.reset();
  if(root) for(auto& node : *root) refresh(node);

  //try and restore the previously selected node
  for(auto& item : listView.items()) {
    if(item.attribute<velvet::Node::Object>("node") == selected) {
      item.setSelected().setFocused();
    }
  }
}

auto PortManager::refresh(velvet::Node::Object node) -> void {
  if(auto port = node->cast<velvet::Node::Port>()) {
    ListViewItem item{&listView};
    item.setAttribute<velvet::Node::Object>("node", port);
    item.setText(port->attribute("name") ? port->attribute("name") : port->name());
    if(auto peripheral = port->connected()) {
      ListViewItem item{&listView};
      item.setAttribute<velvet::Node::Object>("node", peripheral);
      item.setText({"   ", peripheral->attribute("name") ? peripheral->attribute("name") : peripheral->name()});
    }
  }

  for(auto& node : *node) refresh(node);
}

auto PortManager::onChange() -> void {
  if(auto node = listView.selected().attribute<velvet::Node::Object>("node")) {
    if(auto port = node->cast<velvet::Node::Port>()) {
      portConnector.refresh(port);
      return program.setPanelItem(portConnector);
    }

    if(auto setting = node->cast<velvet::Node::Setting>()) {
      settingEditor.refresh(setting);
      return program.setPanelItem(settingEditor);
    }

    if(auto inputs = node->find<velvet::Node::Input>()) {
      if(inputs.first()->parent() == node) {
        inputMapper.refresh(node);
        return program.setPanelItem(inputMapper);
      }
    }

    if(auto peripheral = node->cast<velvet::Node::Peripheral>()) {
      peripheralOverview.refresh(peripheral);
      return program.setPanelItem(peripheralOverview);
    }
  }

  program.setPanelItem(home);
}
