#include "animation.hpp"

#include <SDL.h>

namespace Animation {

    Animations::Animations() : last_frame_change{(unsigned int)SDL_GetTicks64()}{ }

    void Animations::add_frame(std::string to, Frame &frame){
        if(animations.contains(to)){
            animations.at(to).push_back(frame);  
        } else {
            animations.insert({to, {frame}});
        }
    }

    void Animations::add_frames(const std::string &to, const std::initializer_list<Frame> frames)
    {
        for (Frame frame : frames) {
            add_frame(to, frame);
        }
    }

    Frame &Animations::get_current_frame()
    {
        return animations.at(current_frame_id.owner).at(current_frame_id.id);
    }

    void Animations::step()
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

    void Animations::change_to(std::string to)
    {
        if(to == "unmapped"){
            return;
        }

        if(to != current_frame_id.owner){
            current_frame_id.id = 0;
            current_frame_id.owner = to;
        }
    }
}