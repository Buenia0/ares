struct NodeManager : PanelList {
  NodeManager(View*);
  auto show() -> void override;
  auto hide() -> void override;
  auto refresh() -> void;
  auto refresh(velvet::Node::Object node, uint depth) -> void;
  auto refreshSettings() -> void;
  auto name(velvet::Node::Object node, uint depth) -> string;
  auto onChange() -> void;

  velvet::Node::Object root;
  ListView listView{this, Size{~0, ~0}};
};
