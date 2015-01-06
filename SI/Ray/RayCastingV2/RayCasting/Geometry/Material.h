#ifndef _Geometry_Material_H
#define _Geometry_Material_H

#include <Geometry/RGBColor.h>

namespace Geometry
{
	/** \brief Materiau associ� � une g�om�trie. */
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
		\param ambientColor composante ambiante du mat�riau
		\param diffuseColor Composante diffuse du mat�triau
		\param specularColor Composante sp�culaire du mat�riau
		\param specularExponent Exposant de la composante sp�culaire
		*/
		Material(RGBColor const & ambientColor, RGBColor const & diffuseColor, 
				 RGBColor specularColor, float specularExponent, RGBColor const & emissiveColor)
				 : m_ambientColor(ambientColor), m_diffuseColor(diffuseColor), m_specularColor(specularColor),
				   m_specularExponent(specularExponent), m_emissiveColor(emissiveColor) 
		{}

		/** \brief Sensibilit� � la couleur ambiante */
		const RGBColor & ambientColor() const
		{ return m_ambientColor ; }

		/** \brief Sensibilit� � la couleur diffuse */
		const RGBColor & diffuseColor() const
		{ return m_diffuseColor ; }

		/** \brief Sensibilit� � la couleur sp�culaire */
		const RGBColor & specularColor() const
		{ return m_specularColor ; }

		/** \brief Exposant associ� � la sp�cularit� du mat�riau */
		const float & specularExponent() const
		{ return m_specularExponent ; }

		const RGBColor & emissiveColor() const
		{ return m_emissiveColor ; }
	};
}

#endif
