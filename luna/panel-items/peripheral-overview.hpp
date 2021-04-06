struct PeripheralOverview : PanelItem {
  PeripheralOverview(View*);
  auto show() -> void override;
  auto hide() -> void override;
  auto refresh(velvet::Node::Peripheral peripheral) -> void;

  Label header{this, Size{~0, 0}};
  TextEdit manifest{this, Size{~0, ~0}};

  velvet::Node::Peripheral peripheral;
};
