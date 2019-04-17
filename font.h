#ifndef FONT_H
#define FONT_H
using namespace std;


struct Character {
    GLuint      TextureID;
    Vector2     Size;
    Vector2     Bearing;
    GLuint      Advance;    //Offset to advance to next glyph
};
//Init character
    TTF_Init();
    font = TTF_OpenFont("../../Assets/consola.ttf", 24);

    SDL_Color color = { 255, 0, 0 };
    SDL_Surface *face = NULL;
    //14 is a magic number...
    for (GLubyte c = 14; c < 128; c++)
    {
        char tmpChar = /*'a' +*/ c;
        string tmp(1,tmpChar);

        face = TTF_RenderText_Blended(font, tmp.c_str(), color);

        int mode;
        if (face->format->BytesPerPixel == 3) { // RGB 24bit
            mode = GL_RGB;
        }
        else if (face->format->BytesPerPixel == 4) { // RGBA 32bit
            mode = GL_RGBA;
        }
        else {
            SDL_FreeSurface(face);
            return false;
        }

        GLuint texture = 0;

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexImage2D(GL_TEXTURE_2D, 0, mode, face->w, face->h, 0, mode, GL_UNSIGNED_BYTE, face->pixels);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int minx, maxx, miny, maxy, advance;
        if (TTF_GlyphMetrics(font, *(tmp.c_str()), &minx, &maxx, &miny, &maxy, &advance) == -1)
        {
            printf("%s\n", TTF_GetError());
        }

        Character character = {
            texture,
            Vector2(face->w, face->h),
            Vector2(minx, maxy),
            advance
        };
        Characters.insert(std::pair<GLchar, Character>(tmpChar, character));
    }

    characterShader = new ShaderProgram("../../Assets/shader/character.vert", "../../Assets/shader/character.frag");
    Matrix4x4 projection = Transform::OrthoFrustum(0.0f, static_cast<GLfloat>(creationFlags.width), 0.0f, static_cast<GLfloat>(creationFlags.height), -1000, 1000);
    characterShader->Use();
    glUniformMatrix4fv(glGetUniformLocation(characterShader->GetProgramID(), "projection"), 1, GL_FALSE, &projection[0]);

    // Configure VAO/VBO for texture quads
    glGenVertexArrays(1, &characterVAO);
    glGenBuffers(1, &characterVBO);
    glBindVertexArray(characterVAO);
    glBindBuffer(GL_ARRAY_BUFFER, characterVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return true;



#endif // FONT_H
