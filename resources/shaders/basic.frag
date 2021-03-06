#version 330

in vec2 uv;
flat in vec2 imageSize;
flat in vec4 hoverColor;
flat in vec3 atlasOffset;

layout(std140) uniform fragmentUniforms
{
    vec2 atlasSize;

    vec2 __pad;
};

uniform sampler2DArray tex;

out vec4 frag_colour;

void main()
{
    vec4 c = texture(tex, vec3((atlasOffset.xy + uv * imageSize) / atlasSize, int(atlasOffset.z)));

    if (c.w == 0. && hoverColor.a > 0.)
    {
        for (float i= -1.; i <= 1.; i++)
        {
            for (float j= -1.; j <= 1.; j++)
            {
                vec2 offset = vec2(i, j);
                vec4 n = texture(tex, vec3((atlasOffset.xy + offset + uv * imageSize) / atlasSize, int(atlasOffset.z)));
                if (n.w > 0. && (n.x > 0. || n.y > 0. || n.z > 0.))
                    c = hoverColor;
            }
        }
    }
    frag_colour = c;//vec4(c.rgb, 0.4 * c.a);
}
