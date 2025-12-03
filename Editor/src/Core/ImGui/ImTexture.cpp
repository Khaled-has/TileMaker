#include "ImTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glad/glad.h>

namespace Editor {

	ImTexture::~ImTexture()
	{
		if (loaded) glDeleteTextures(1, &ID);
	}

	unsigned int ImTexture::GetID()
	{
		if (!loaded)
		{
			int w, h;
			int channel;

			unsigned char* data = stbi_load((std::string(ASSETS_PATH) + path).c_str(), &w, &h, &channel, NULL);

			GLenum format = (channel == 3) ? GL_RGB : GL_RGBA;

			// Please check the Texture's path if you have any error here
			ED_ASSERT(data, "Cannot load this texture");

			glGenTextures(1, &ID);
			glBindTexture(GL_TEXTURE_2D, ID);

			glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data);

			// Filters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			ED_LOG_TRACE("Texture loaded: (> {0} <)", path);

			stbi_image_free(data);
			loaded = true;
		}

		return ID;
	}


}