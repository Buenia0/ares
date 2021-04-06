auto PropertiesViewer::construct() -> void {
  setCollapsible();
  setVisible(false);

  propertiesLabel.setText("Properties Viewer").setFont(Font().setBold());
  propertiesView.setEditable(false).setFont(Font().setFamily(Font::Mono));
  liveOption.setText("Live");
  refreshButton.setText("Refresh").onActivate([&] {
    refresh();
  });
}

auto PropertiesViewer::reload() -> void {
  propertiesList.reset();
  for(auto properties : velvet::Node::enumerate<velvet::Node::Properties>(emulator->root)) {
    ComboButtonItem item{&propertiesList};
    item.setAttribute<velvet::Node::Properties>("node", properties);
    item.setText(properties->name());
  }
  eventChange();
}

auto PropertiesViewer::unload() -> void {
  propertiesList.reset();
  eventChange();
}

auto PropertiesViewer::refresh() -> void {
  if(auto item = propertiesList.selected()) {
    if(auto properties = item.attribute<velvet::Node::Properties>("node")) {
      propertiesView.setText(properties->query());
    }
  } else {
    propertiesView.setText();
  }
}

auto PropertiesViewer::liveRefresh() -> void {
  if(visible() && liveOption.checked()) refresh();
}

auto PropertiesViewer::eventChange() -> void {
  refresh();
}

auto PropertiesViewer::setVisible(bool visible) -> PropertiesViewer& {
  if(visible) refresh();
  VerticalLayout::setVisible(visible);
  return *this;
}
