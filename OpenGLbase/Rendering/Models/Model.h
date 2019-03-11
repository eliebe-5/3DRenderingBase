#pragma once
#include <vector>
#include <map>
#include "..\I_Render_Object.h"

namespace Rendering
{
	namespace Models
	{
		class Model : public I_Render_Object
		{
		public:
			Model();
			virtual ~Model();
			virtual void draw() override;
			virtual void draw(	const glm::mat4& projection_matrix,
								const glm::mat4& view_matrix) override;
			virtual void update() override;
			virtual void set_program(GLuint) override;
			virtual void destroy() override;

			virtual GLuint get_vao() const override;
			virtual const std::vector<GLuint>& get_vbos() const override;

			virtual const GLuint get_texture(std::string textureName) const override;
			virtual void set_texture(std::string textureName, GLuint texture) override;
			void use_texture(const std::string&);

			virtual void rotate(glm::vec3&) override;

		protected:
			std::string texture_in_use;
			GLuint vao;
			GLuint program;
			std::vector<GLuint> vbos;
			std::map<std::string, GLuint> textures;
		};
		
	}
}