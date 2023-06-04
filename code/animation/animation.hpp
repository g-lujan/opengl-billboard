#include <unordered_map>
#include <string>
#include <vector>

namespace Animation {

  struct Frame {
    unsigned int duration = 0;
    unsigned int time_running = 0;
    unsigned int sheet_idx = 0;

    bool is_over() const { return time_running > duration; }
    void reset() { time_running = 0; }
  };

  struct Frame_Id {
    std::string owner = "";
    unsigned int id = 0;
  };

  class Animations {
    public:
    void add_frame(std::string to, Frame &frame){
      if(animations.contains(to)){
        animations.at(to).push_back(frame);  
      } else {
        animations.insert({to, {frame}});
      }
    }

    void add_frames(const std::string &to, const std::initializer_list<Frame> frames)
    {
      for (Frame frame : frames) {
        add_frame(to, frame);
      }
    }

    Frame &get_current_frame()
    {
      return animations.at(current_frame_id.owner).at(current_frame_id.id);
    }

    void step()
    {
      std::vector<Animation::Frame> &curr_animation = animations.at(current_frame_id.owner);
      Animation::Frame &curr_frame = curr_animation.at(current_frame_id.id);
      unsigned int now = SDL_GetTicks64();

      if (curr_frame.time_running > curr_frame.duration) {
        current_frame_id.id = current_frame_id.id == curr_animation.size() - 1 ? 0 : current_frame_id.id + 1;
        curr_frame.time_running = 0;
        last_frame_change = now;
      } else {
        curr_frame.time_running += now - last_frame_change;
      }
    }

    void change_to(std::string to)
    {
      if(to != current_frame_id.owner){
        current_frame_id.id = 0;
        current_frame_id.owner = to;
      }
    }

  private:
    std::unordered_map<std::string, std::vector<Animation::Frame>> animations;
    Frame_Id current_frame_id;
    unsigned int last_frame_change = SDL_GetTicks64();
  };
}