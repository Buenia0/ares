auto ManifestViewer::construct() -> void {
  setCollapsible();
  setVisible(false);

  manifestLabel.setText("Manifest Viewer").setFont(Font().setBold());
  manifestList.onChange([&] { eventChange(); });
  manifestView.setEditable(false).setFont(Font().setFamily(Font::Mono));
}

auto ManifestViewer::reload() -> void {
  manifestList.reset();
  for(auto peripheral : velvet::Node::enumerate<velvet::Node::Peripheral>(emulator->root)) {
    if(!peripheral->manifest()) continue;  //ignore peripherals with no manifest available
    ComboButtonItem item{&manifestList};
    item.setAttribute<velvet::Node::Peripheral>("node", peripheral);
    item.setText(peripheral->name());
  }
  eventChange();
}

auto ManifestViewer::unload() -> void {
  manifestList.reset();
  eventChange();
}

auto ManifestViewer::refresh() -> void {
  if(auto item = manifestList.selected()) {
    if(auto peripheral = item.attribute<velvet::Node::Peripheral>("node")) {
      manifestView.setText(peripheral->manifest());
    }
  } else {
    manifestView.setText();
  }
}

auto ManifestViewer::eventChange() -> void {
  refresh();
}

auto ManifestViewer::setVisible(bool visible) -> ManifestViewer& {
  if(visible) refresh();
  VerticalLayout::setVisible(visible);
  return *this;
}
