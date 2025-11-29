#ifndef IMTEXTURE_H
#define IMTEXTURE_H

#include "Log/Log.h"

namespace Editor {

	struct ImTexture
	{
		ImTexture(const char* path) { Load(path); }
		ImTexture() {}

		~ImTexture();

		void Load(const char* path);
		inline unsigned int GetID() const { return ID; }
	private:
		unsigned int ID;
		bool loaded = false;
	};

}

#endif