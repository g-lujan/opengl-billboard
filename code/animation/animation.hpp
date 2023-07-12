#include <unordered_map>
#include <string>
#include <vector>

namespace Animation {

  struct Frame {
    bool is_over() const { return time_running > duration; }
    void reset() { time_running = 0; }

    unsigned int duration = 0;
    unsigned int time_running = 0;
    unsigned int sheet_idx = 0;
  };

  struct Frame_Id {
    std::string owner = "";
    unsigned int id = 0;
  };

  class Animations {
  public:
    Animation::Animations();
    void add_frame(std::string to, Frame &frame);
    void add_frames(const std::string &to, const std::initializer_list<Frame> frames);
    Frame &get_current_frame();
    void step();
    void change_to(std::string to);

  private:
    std::unordered_map<std::string, std::vector<Animation::Frame>> animations;
    Frame_Id current_frame_id;
    unsigned int last_frame_change;
  };
}