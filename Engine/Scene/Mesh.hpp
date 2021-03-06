#pragma once

#include <vector>
#include "AObject.hpp"
#include "AIntersectable.hpp"
#include "ALight.hpp"
#include "../Scene/Camera.hpp"

namespace Tricible
{
	namespace Scene
	{
		class Mesh : public AObject, public AIntersectable
		{
		public:
			std::vector<AIntersectable *> SubMeshes;
			std::string Name;
			Mesh()
			{

			}

			// Inherited via AIntersectable
			virtual bool IntersectsRay(const Point3 & origin, const Point3 & vec, IntersectionInfo * interInfo, float nearClip, float farClip) override;
			virtual void ComputeNormal(const IntersectionInfo & interInfo, Point3 & normal) override;
		};
	}
}