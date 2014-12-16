#ifndef _Geometry_Material_H
#define _Geometry_Material_H

#include <Geometry/RGBColor.h>

namespace Geometry
{
	/** \brief Materiau associé à une géométrie. */
	class Material
	{
	protected:
		RGBColor m_ambientColor ;
		RGBColor m_diffuseColor ;
		RGBColor m_specularColor ;
		float   m_specularExponent ;
		RGBColor m_emissiveColor ;

	public:
		/** \brief Contructeur de Material 
		\param ambientColor composante ambiante du matériau
		\param diffuseColor Composante diffuse du matétriau
		\param specularColor Composante spéculaire du matériau
		\param specularExponent Exposant de la composante spéculaire
		*/
		Material(RGBColor const & ambientColor, RGBColor const & diffuseColor, 
				 RGBColor specularColor, float specularExponent, RGBColor const & emissiveColor)
				 : m_ambientColor(ambientColor), m_diffuseColor(diffuseColor), m_specularColor(specularColor),
				   m_specularExponent(specularExponent), m_emissiveColor(emissiveColor) 
		{}

		/** \brief Sensibilité à la couleur ambiante */
		const RGBColor & ambientColor() const
		{ return m_ambientColor ; }

		/** \brief Sensibilité à la couleur diffuse */
		const RGBColor & diffuseColor() const
		{ return m_diffuseColor ; }

		/** \brief Sensibilité à la couleur spéculaire */
		const RGBColor & specularColor() const
		{ return m_specularColor ; }

		/** \brief Exposant associé à la spécularité du matériau */
		const float & specularExponent() const
		{ return m_specularExponent ; }

		const RGBColor & emissiveColor() const
		{ return m_emissiveColor ; }
	};
}

#endif
