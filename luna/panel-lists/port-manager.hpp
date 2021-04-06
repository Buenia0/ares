struct PortManager : PanelList {
  PortManager(View*);
  auto show() -> void override;
  auto hide() -> void override;
  auto refresh() -> void;
  auto refresh(velvet::Node::Object node) -> void;

  auto onChange() -> void;

  velvet::Node::Object root;
  ListView listView{this, Size{~0, ~0}};
};
