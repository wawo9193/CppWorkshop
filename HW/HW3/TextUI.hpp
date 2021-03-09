#ifndef TEXTUI_HPP
#define TEXTUI_HPP

class TextUI {
public:
  TextUI();

  void UI();
  std::string Register();

private:
  std::vector<std::string> main_menu_;
};

#endif
