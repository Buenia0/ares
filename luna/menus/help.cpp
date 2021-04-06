HelpMenu::HelpMenu(MenuBar* parent) : Menu(parent) {
  setText("Help");
  about.setIcon(Icon::Prompt::Question).setText("About luna ...").onActivate([&] {
    image logo{Resource::Velvet::Logo};
    logo.shrink();
    AboutDialog()
    .setLogo(logo)
    .setDescription("luna — an advanced multi-system emulator")
    .setVersion(velvet::Version)
    .setCopyright(velvet::Copyright)
    .setLicense(velvet::License, velvet::LicenseURI)
    // .setWebsite(velvet::Website, velvet::WebsiteURI)
    .setAlignment(program, {0.5f, program.panelLayout.visible() ? 0.32f : 0.5f})
    .show();
  });
}
