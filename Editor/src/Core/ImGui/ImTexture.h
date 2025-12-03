#ifndef IMTEXTURE_H
#define IMTEXTURE_H

#include "Log/Log.h"

namespace Editor {

	/* ->	ImTexture For load high quality ImGui textures	 <- */

	struct ImTexture
	{
		ImTexture(const char* path) { Load(path); }

		~ImTexture();

		unsigned int GetID();
	private:
		unsigned int ID = 0;
		bool loaded = false;
		std::string path = "";

		inline void Load(const char* path) { this->path = path; }
	};

}

#endif