#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 view;
uniform mat4 projection;
uniform vec3 board_center_worldspace;
uniform vec2 board_size;

void main()
{
    // inverse of view matrix, to bring the expected positions of the billboard
    // back to the world space
    vec3 camera_right_worldspace = vec3(view[0][0], view[1][0], view[2][0]);
    vec3 camera_up_worldspace = vec3(view[0][1], view[1][1], view[2][1]);

    // build the position in world space
    vec3 vertex_position_worldspace = board_center_worldspace
      + camera_right_worldspace * aPos.x * board_size.x
      + camera_up_worldspace * aPos.y * board_size.y;

    gl_Position = projection * view * vec4(vertex_position_worldspace, 1.0f);
    TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
}
