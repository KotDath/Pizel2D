#include "DebugWindow.h"

void DebugWindow::setDebugData(const DebugData& newData) { data = newData; }

void DebugWindow::Render(std::shared_ptr<MovingImage> img,
                         std::shared_ptr<Text> text) {
  ImGui::Begin("Debug Window");  // Window title

  // Create a list of selectable items
  static int selected_item = -1;  // To keep track of the selected item
  for (int i = 0; i < data.items.size(); ++i) {
    // The second parameter is a boolean that indicates whether the item is
    // selected
    bool is_selected = (selected_item == i);
    if (ImGui::Selectable(data.items[i].c_str(), is_selected)) {
      selected_item = i;  // Update the selected item
    }
  }

  ImGui::Text("Selected Item: %d", selected_item);

  ImGui::Text("Enter some text:");  // Text field
  ImGui::InputText("Pause text", data.textBuffer, sizeof(data.textBuffer));

  if (ImGui::Button("Submit")) {  // Button
    std::cout << "Submitted text: " << data.textBuffer << std::endl;
  }

  ImGui::SliderFloat("Speed", &(data.speedValue), 0.0f,
                     100.0f);  // Slider for float value
  ImGui::SliderFloat("Size", &(data.sizeValue), 0.1f,
                     5.f);  // Slider for float value

  // Color picker
  ImGui::ColorEdit3("Color Picker", data.color);  // Color picker

  ImGui::Text("Selected Color: (%.2f, %.2f, %.2f)", data.color[0],
              data.color[1], data.color[2]);

  ImGui::End();

  img->SetSpeed(data.speedValue);
  img->SetColor(data.color[0], data.color[1], data.color[2]);
  img->LoadImage(data.items[std::max(selected_item, 0)]);
  img->SetScale(data.sizeValue);

  text->SetText(data.textBuffer);
}
