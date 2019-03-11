#pragma once
#include <string>
#include <iostream>
#include "GL/glew.h"
#include "GL/freeglut.h"
#include <assert.h>

using namespace std;
namespace Core
{
	class Debug_Output
	{
	public:
		Debug_Output() {};
		~Debug_Output() {};
		static void CALLBACK my_callback(GLenum source,
			GLenum type,
			GLuint id,
			GLenum severity,
			GLsizei length,
			const GLchar *msg,
			const void *data)
		{
			//display warnings/errors however you like
			cout << "\n**********Debug Output**************" << endl;
			cout << "source: " << get_string_for_source(source).c_str() << endl;
			cout << "type: " << get_string_for_type(type).c_str() << endl;
			cout << "severity: " << get_string_for_severity(severity).c_str() << endl;
			cout << "debug call: " << msg << endl;
			cout << "\n************************" << endl;
		}

	private:
		static std::string get_string_for_type(GLenum type)
		{
			switch (type)
			{
			case GL_DEBUG_TYPE_ERROR:
				return"Error";
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
				return "Deprecated behavior";
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
				return "Undefined behavior";
			case GL_DEBUG_TYPE_PORTABILITY:
				return "Portability issue";
			case GL_DEBUG_TYPE_PERFORMANCE:
				return "Performance issue";
			case GL_DEBUG_TYPE_MARKER:
				return "Stream annotation";
			case GL_DEBUG_TYPE_OTHER_ARB:
				return "Other";
			default:
				assert(false);
				return "";
			}
		}

		static std::string get_string_for_source(GLenum source)
		{
			switch (source)
			{
			case GL_DEBUG_SOURCE_API:
				return "API";
			case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
				return "Window system";
			case GL_DEBUG_SOURCE_SHADER_COMPILER:
				return "Shader compiler";
			case GL_DEBUG_SOURCE_THIRD_PARTY:
				return "Third party";
			case GL_DEBUG_SOURCE_APPLICATION:
				return "Application";
			case GL_DEBUG_SOURCE_OTHER:
				return "Other";
			default:
				assert(false);
				return "";
			}
		}

		static std::string get_string_for_severity(GLenum severity)
		{
			switch (severity)
			{
			case GL_DEBUG_SEVERITY_HIGH:
				return "High";
			case GL_DEBUG_SEVERITY_MEDIUM:
				return "Medium";
			case GL_DEBUG_SEVERITY_LOW:
				return "Low";
			case GL_DEBUG_SEVERITY_NOTIFICATION:
				return "Notification";
			default:
				assert(false);
				return("");
			}
		}

	};
}