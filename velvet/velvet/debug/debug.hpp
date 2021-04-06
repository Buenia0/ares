namespace velvet {

struct Debug {
  static constexpr bool enabled = true;

  auto reset() -> void;

  template<typename... P> auto unimplemented(P&&... p) -> void {
    return _unimplemented({forward<P>(p)...});
  }

private:
  auto _unimplemented(const string&) -> void;

  vector<string> _unimplementedNotices;
};

extern Debug _debug;

}

#define debug(function, ...) if constexpr(velvet::_debug.enabled) velvet::_debug.function(__VA_ARGS__)
