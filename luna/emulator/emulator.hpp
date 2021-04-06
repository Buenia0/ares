struct Emulator : velvet::Platform {
  velvet::Node::Object root;

  //emulator.cpp
  auto create(shared_pointer<velvet::Interface>, string location) -> void;
  auto unload() -> void;
  auto main() -> void;
  auto quit() -> void;
  auto power(bool on) -> void;
  auto validateConfiguration(Markup::Node, Markup::Node) -> void;

  auto connected(string location) -> velvet::Node::Port;

  //platform.cpp
  auto attach(velvet::Node::Object) -> void override;
  auto detach(velvet::Node::Object) -> void override;
  auto open(velvet::Node::Object, string name, vfs::file::mode mode, bool required) -> shared_pointer<vfs::file> override;
  auto event(velvet::Event) -> void override;
  auto log(string_view message) -> void override;
  auto video(velvet::Node::Screen, const uint32_t* data, uint pitch, uint width, uint height) -> void override;
  auto audio(velvet::Node::Stream) -> void override;
  auto input(velvet::Node::Input) -> void override;

  //video.cpp
  auto videoUpdate() -> void;
  auto videoUpdateColors() -> void;
  auto videoUpdateShader() -> void;
  auto videoToggleFullscreen() -> void;

  //audio.cpp
  auto audioUpdate() -> void;
  auto audioUpdateEffects() -> void;

  //input.cpp
  auto inputUpdate() -> void;

  //states.cpp
  auto saveState(uint slot) -> bool;
  auto loadState(uint slot) -> bool;

  //status.cpp
  auto updateMessage() -> void;
  auto showMessage(const string& message = {}) -> void;
  auto setCaption(const string& caption = {}) -> void;

  //utility.cpp
  auto captureScreenshot(const uint32_t* data, uint pitch, uint width, uint height) -> void;

  struct System {
    string name;
    string data;
    string templates;
    bool power = false;
    file_buffer log;
  } system;

  struct Events {
    bool power = false;
  } events;

  struct Requests {
    bool captureScreenshot = false;
  } requests;

  struct State {
    struct Message {
      uint64_t timestamp = 0;
      string text;
    } message;
  } state;

  vector<velvet::Node::Screen> screens;
  vector<velvet::Node::Stream> streams;
};

extern Emulator emulator;
