#pragma once

namespace Core {
	struct Context_Info
	{
		int major_version, minor_version;
		bool core;

		Context_Info()//default
		{
			major_version = 4;
			minor_version = 5;
			core = true;
		}

		Context_Info(int major_version, int minor_version, bool core)
		{
			this->major_version = major_version;
			this->minor_version = minor_version;
			this->core = core;
		}
	};
}